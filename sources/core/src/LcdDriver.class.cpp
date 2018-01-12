// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LcdDriver.class.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/07 17:49:09 by hestela           #+#    #+#             //
//   Updated: 2016/01/07 17:49:10 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "LcdDriver.class.hpp"

namespace Gbmu
{

	LcdDriver::LcdDriver ( Cpu* cpu ):
		_cpu(cpu),
		_IOREGS(cpu->IO()->registers()),
		_memory(cpu->memory()),
		_screen(NULL)
	{ }

	LcdDriver::~LcdDriver( void )
	{ }

	void				LcdDriver::reset ( void )
	{
		_sprites.clear();
		bzero(_BgIndexBuffer, sizeof(_BgIndexBuffer));
		clear();
		flush();
	}

	void				LcdDriver::setScreen( IScreen* screen ) { _screen = screen; }

	// get all sprites from OAM
	void				LcdDriver::oamSearching ( void )
	{
		size_t						spriteIdx = 0;
		struct SpriteAttrib*		attrib;
		struct Sprite				sprite;

		// if OBJ disable, don't need to search OBJ attributes
		if (BIT_1(_IOREGS->LCDC) == 0)
			return ;

		// clear sprite list
		_sprites.clear();
		// getting all sprites
		while (spriteIdx < 40)
		{
			attrib = (struct SpriteAttrib*)&_memory->data()[OAM_OFFSET + spriteIdx * 4];

			// check sprite is visible on screen
			if (attrib->positionY == 0 || attrib->positionY >= GB_SCREEN_H + SPRITE_H
				|| attrib->positionX == 0 || attrib->positionX >= GB_SCREEN_W + SPRITE_W)
				sprite.visible = false;
			else
				sprite.visible = true;

			// getting all attributes
			sprite.y = attrib->positionY - SPRITE_H;
			sprite.x = attrib->positionX - SPRITE_W;
			sprite.height = (BIT_2(_IOREGS->LCDC) ? 16 : 8);
			sprite.addr = attrib->index * TILE_BYTES; // addr in VRAM
			sprite.xFlip = BIT_5(attrib->attributes);
			sprite.yFlip = BIT_6(attrib->attributes);
			sprite.bgPriority = BIT_7(attrib->attributes);
			if (_cpu->cartridge()->colorGB())
			{
				if (_cpu->cartridge()->colorCart())
				{
					// BIT 3 attrib Specify the VRAM BANK to use
					if (BIT_3(attrib->attributes))
						sprite.addr += VRAM_BANK_SIZE;
					// BIT 0_2 specify the color palette to use
					sprite.palette = _CGBpalettes.ocp[BITS_0_2(attrib->attributes)];
				}
				else
					sprite.palette = (BIT_4(attrib->attributes) ? _CGBpalettes.ocp[1] : _CGBpalettes.ocp[0]);
			}
			else
				sprite.palette = (BIT_4(attrib->attributes) ? _DMGpalettes.obp1 : _DMGpalettes.obp0);

			// push on list
			_sprites.push_back(sprite);

			spriteIdx++;
		}
	}

	// Draw a LCD line
	void				LcdDriver::transferLine ( void )
	{
		if (_screen == NULL)
			return ;

		// if LCD Active
		if (!BIT_7(_IOREGS->LCDC))
			return ;

		// update palettes
		if (_cpu->cartridge()->colorGB())
			updateCGBPalettes();
		else
			updateDMGPalettes();

		// if BG enable
		if (BIT_0(_IOREGS->LCDC))
			drawBackground();
		// if Win enable
		if (BIT_5(_IOREGS->LCDC))
			drawWindow();
		// if OBJ enable
		if (BIT_1(_IOREGS->LCDC))
		 	drawSprites();
	}

	void				LcdDriver::clear ( void )
	{
		if (_screen)
		{
			// fill black if CGB
			if (_cpu->cartridge()
				&& _cpu->cartridge()->colorGB()
				&& _cpu->cartridge()->colorCart())
				_screen->clear(0x000000);
			// fill white on DMG
			else
				_screen->clear(0xFFFFFF);
		}
	}

	void 				LcdDriver::flush ( void )
	{
		if (_screen)
		 	_screen->update();
	}

	/**************************************************************************/
	/**************************** PRIVATE METHODS *****************************/
	/**************************************************************************/
	
	void				LcdDriver::drawBackground ( void )
	{
		struct BackgroundAttrib 	attributes;
		struct Tile 				tile;
		uint8_t						drawX = 0;
		uint8_t						colorIndex;
		uint8_t						pixelIndex;
		int 						previousCol = -1;

		// getting all BG attributes
		getBackgroundAttributes(&attributes);

		// for each pixel of the current line
		while (drawX < GB_SCREEN_W)
		{
			// curent col in tileset
			attributes.tilesSetCol = attributes.x / TILE_SIZE;

			// get All infos needes to draw tile
			if (attributes.tilesSetCol != previousCol)
				getTileInfos(attributes, &tile);

			// get pixel index in tile line
			pixelIndex = attributes.x % TILE_SIZE;
			if (tile.xFlip)
				pixelIndex = 7 - pixelIndex;

			// get the color palette index
			colorIndex = getPixelColorIndex(pixelIndex, tile.data1, tile.data2);

			// store index in buffer
			if (tile.priority)
				_BgIndexBuffer[drawX][_IOREGS->LY] = 4; // put an invalid index to check when sprite draw
			else
				_BgIndexBuffer[drawX][_IOREGS->LY] = colorIndex;

			// draw tile pixel
			_screen->drawPix(drawX, _IOREGS->LY, tile.palette[colorIndex]);

			attributes.x++;
			drawX++;
		}
	}

	void 				LcdDriver::getBackgroundAttributes( struct BackgroundAttrib* attributes )
	{
		attributes->tilesDatas = (BIT_4(_IOREGS->LCDC) ? 0x8000 : 0x8800) - VRAM_OFFSET; // get addr in VRAM
		attributes->signedIndex = (BIT_4(_IOREGS->LCDC) ? false : true);
		attributes->x = _IOREGS->SCX;
		attributes->y = _IOREGS->SCY + _IOREGS->LY;
		attributes->tilesCodes = (BIT_3(_IOREGS->LCDC) ? 0x9C00 : 0x9800) - VRAM_OFFSET; // get addr in VRAM
		attributes->tilesSetRow = (attributes->y / TILE_SIZE) * LINE_BYTES;
	}

	void				LcdDriver::drawWindow ( void )
	{
		struct BackgroundAttrib 	attributes;
		struct Tile 				tile;
		uint8_t						drawX;
		uint8_t						colorIndex;
		uint8_t						pixelIndex;
		int 						previousCol = -1;

		// if is visible on this scanline
		if (_IOREGS->LY < _IOREGS->WY || _IOREGS->WX - 7 > GB_SCREEN_W)
			return ;

		// getting all Window attributes
		getWindowAttributes(&attributes);

		drawX = attributes.x;
		attributes.x -= _IOREGS->WX - 7;
		// for each pixel of the current line
		while (drawX < GB_SCREEN_W)
		{
			// curent col in tileset
			attributes.tilesSetCol = attributes.x / TILE_SIZE;

			// get All infos needes to draw tile
			if (attributes.tilesSetCol != previousCol)
				getTileInfos(attributes, &tile);

			// get pixel index in tile line
			pixelIndex = attributes.x % TILE_SIZE;
			if (tile.xFlip)
				pixelIndex = 7 - pixelIndex;

			// get the color palette index
			colorIndex = getPixelColorIndex(pixelIndex, tile.data1, tile.data2);

			// store index in buffer
			if (tile.priority)
				_BgIndexBuffer[drawX][_IOREGS->LY] = 4; // put an invalid index to check when sprite draw
			else
				_BgIndexBuffer[drawX][_IOREGS->LY] = colorIndex;

			// draw tile pixel
			_screen->drawPix(drawX, _IOREGS->LY, tile.palette[colorIndex]);

			attributes.x++;
			drawX++;
		}
	}

	void 				LcdDriver::getWindowAttributes( struct BackgroundAttrib* attributes )
	{
		attributes->tilesDatas = (BIT_4(_IOREGS->LCDC) ? 0x8000 : 0x8800) - VRAM_OFFSET; // Addrees in VRAM
		attributes->signedIndex = (BIT_4(_IOREGS->LCDC) ? false : true);
		attributes->x = (_IOREGS->WX - 7 < 0 ? 0 : _IOREGS->WX - 7);
		attributes->y = _IOREGS->LY - _IOREGS->WY;
		attributes->tilesCodes = (BIT_6(_IOREGS->LCDC) ? 0x9C00 : 0x9800) - VRAM_OFFSET; // Addrees in VRAM
		attributes->tilesSetRow = (attributes->y / TILE_SIZE) * LINE_BYTES;
	}

	void				LcdDriver::getTileInfos ( struct BackgroundAttrib const& attributes, struct Tile* tile )
	{
		int 			tileIndex;
		int				tileLine;

		// get tile address in VRAM
		if(!attributes.signedIndex)
		{
			tileIndex = (uint8_t)_memory->vram()[attributes.tilesCodes + attributes.tilesSetRow + attributes.tilesSetCol];
			tile->addr = attributes.tilesDatas + (tileIndex * TILE_BYTES) ;
		}
		else
		{
			tileIndex = (int8_t)_memory->vram()[attributes.tilesCodes + attributes.tilesSetRow + attributes.tilesSetCol];
			tile->addr = attributes.tilesDatas + ((tileIndex + 128) * TILE_BYTES) ;
		}

		// get Tile Attributes for CGB
			getTileAttributes(attributes, tile);

		// get Tile line Data
		tileLine = (attributes.y % TILE_SIZE) * 2;
		if (tile->yFlip)
			tileLine = (7 - (attributes.y % TILE_SIZE)) * 2;
		tile->data1 = _memory->vram()[tile->addr + tileLine] ;
		tile->data2 = _memory->vram()[tile->addr + tileLine + 1];

	}

	void				LcdDriver::getTileAttributes ( struct BackgroundAttrib const& attributes, struct Tile* tile )
	{
		if (_cpu->cartridge()->colorGB())
		{
			if (_cpu->cartridge()->colorCart())
			{
				tile->attributes = _memory->vram()[attributes.tilesCodes + attributes.tilesSetRow + attributes.tilesSetCol + VRAM_BANK_SIZE];
				tile->palette = _CGBpalettes.bcp[BITS_0_2(tile->attributes)];
				if (BIT_3(tile->attributes))
					tile->addr += VRAM_BANK_SIZE;
				tile->xFlip = BIT_5(tile->attributes);
				tile->yFlip = BIT_6(tile->attributes);
				tile->priority = BIT_7(tile->attributes);
			}
			else
				tile->palette = _CGBpalettes.bcp[0];
		}
		else
		{
			tile->palette = _DMGpalettes.bgp;
			tile->xFlip = false;
			tile->yFlip = false;
			tile->priority = false;
		}
	}

	void				LcdDriver::drawSprites ( void )
	{
		int 			spriteIdx = 39;

		// priority from the first in list
		while (spriteIdx >= 0)
		{
			// Sprite visible on this line
			if (spriteNeedDrawOnThisScanline(_sprites[spriteIdx]))
				drawSpriteLine(_sprites[spriteIdx]);
			spriteIdx--;
		}
	}

	inline bool			LcdDriver::spriteNeedDrawOnThisScanline( struct Sprite const& sprite)
	{
		if (sprite.visible && _IOREGS->LY >= sprite.y && _IOREGS->LY < sprite.y + sprite.height)
			return (true);
		return (false);
	}

	void				LcdDriver::drawSpriteLine ( struct Sprite const& sprite )
	{
		int 			spriteLine = _IOREGS->LY - sprite.y;
		int 			x;
		uint8_t 		data1;
		uint8_t			data2;
		int 			pixelIdx;
		int 			colorIndex;

		// check line is valid && on OBJ
		if (spriteLine < 0 || spriteLine >= (int)sprite.height)
			return ;

		// Active vertical Symetry
		spriteLine = (sprite.yFlip ? sprite.height - 1 - spriteLine : spriteLine);

		// get sprite line datas ( 8 pixels == 2Bytes )
		data1 = _memory->vram()[sprite.addr + spriteLine * 2];
		data2 = _memory->vram()[sprite.addr + spriteLine * 2 + 1];
		x = 7;
		while (x >= 0)
		{
			// Active horizontal symetry
			pixelIdx = (sprite.xFlip ? 7 - x : x);

			// getting color index
			colorIndex = getPixelColorIndex(pixelIdx, data1, data2);

			// if OBJ pixel is visible
			if (sprite.x + x >= 0 && sprite.x + x < GB_SCREEN_W)
			{
				// case BG special CGB Priority
				if (_BgIndexBuffer[sprite.x + x][_IOREGS->LY] == 4)
					; // nothing to draw

				// case BG priority (draw sprite only on BG color index 00)
				else if (sprite.bgPriority && _BgIndexBuffer[sprite.x + x][_IOREGS->LY] == 0 && colorIndex != 0)
					_screen->drawPix(sprite.x + x, _IOREGS->LY, sprite.palette[colorIndex]);

				// normal case for OBJ (OBJ color index 00 is transparent)
				else if (colorIndex != 0 && !sprite.bgPriority)
					_screen->drawPix(sprite.x + x, _IOREGS->LY, sprite.palette[colorIndex]);
			}
			x--;
		}
	}

	// Update palettes (BGP OBP0 OBP1) for DMG (CBG use others)
	void				LcdDriver::updateDMGPalettes ( void )
	{
		// BGP
		_DMGpalettes.bgp[0] = getDMGNormalColorValue(BITS_0_1(_IOREGS->BGP));
		_DMGpalettes.bgp[1] = getDMGNormalColorValue(BITS_2_3(_IOREGS->BGP));
		_DMGpalettes.bgp[2] = getDMGNormalColorValue(BITS_4_5(_IOREGS->BGP));
		_DMGpalettes.bgp[3] = getDMGNormalColorValue(BITS_6_7(_IOREGS->BGP));
		// OBP0
		_DMGpalettes.obp0[0] = getDMGNormalColorValue(BITS_0_1(_IOREGS->OBP0));
		_DMGpalettes.obp0[1] = getDMGNormalColorValue(BITS_2_3(_IOREGS->OBP0));
		_DMGpalettes.obp0[2] = getDMGNormalColorValue(BITS_4_5(_IOREGS->OBP0));
		_DMGpalettes.obp0[3] = getDMGNormalColorValue(BITS_6_7(_IOREGS->OBP0));
		// OBP1
		_DMGpalettes.obp1[0] = getDMGNormalColorValue(BITS_0_1(_IOREGS->OBP1));
		_DMGpalettes.obp1[1] = getDMGNormalColorValue(BITS_2_3(_IOREGS->OBP1));
		_DMGpalettes.obp1[2] = getDMGNormalColorValue(BITS_4_5(_IOREGS->OBP1));
		_DMGpalettes.obp1[3] = getDMGNormalColorValue(BITS_6_7(_IOREGS->OBP1));
	}

	// Standard colors for values 0 - 3
	int32_t				LcdDriver::getDMGNormalColorValue ( uint8_t const& idx )
	{
		switch (idx)
		{
			case 0b00: return (DMGColor::White);
			case 0b01: return (DMGColor::LightGray);
			case 0b10: return (DMGColor::DarkGray);
			case 0b11: return (DMGColor::Black);
		}
		return (0);
	}

	// Update colors palettes
	void				LcdDriver::updateCGBPalettes ( void )
	{
		uint16_t*		bcp = (uint16_t*)_memory->bcp();
		uint16_t*		ocp = (uint16_t*)_memory->ocp();

		uint8_t			paletteIdx;
		uint8_t			colorIdx;
		uint16_t		color;
		uint8_t			r;
		uint8_t			g;
		uint8_t			b;
		int32_t			rgb;

		// update BG Palettes
		paletteIdx = 0;
		while (paletteIdx < 8)
		{
			colorIdx = 0;
			while (colorIdx < 4)
			{
				color = bcp[(paletteIdx * 4) + colorIdx];
				r = BITS_0_4(color) << 3;
				g = BITS_5_9(color) << 3;
				b = BITS_10_14(color) << 3;
				rgb = b | (g << 8) | (r << 16);
				_CGBpalettes.bcp[paletteIdx][colorIdx] = rgb;
				colorIdx++;
			}
			paletteIdx++;
		}

		// update OBJ Palettes
		paletteIdx = 0;
		while (paletteIdx < 8)
		{
			colorIdx = 0;
			while (colorIdx < 4)
			{
				color = ocp[(paletteIdx * 4) + colorIdx];
				r = BITS_0_4(color) << 3;
				g = BITS_5_9(color) << 3;
				b = BITS_10_14(color) << 3;
				rgb = b | (g << 8) | (r << 16);
				_CGBpalettes.ocp[paletteIdx][colorIdx] = rgb;
				colorIdx++;
			}
			paletteIdx++;
		}
	}

	// return the color index in palette for a pixel
	// each pixel is define by two corresponding bits in data1 & data2
	inline uint8_t		LcdDriver::getPixelColorIndex ( int const& pixIdx, uint8_t const& data1, uint8_t const& data2)
	{
		return (BIT_N((7 - pixIdx), data2) << 1 | BIT_N((7 - pixIdx), data1));
	}
}