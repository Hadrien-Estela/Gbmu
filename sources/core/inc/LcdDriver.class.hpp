// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LcdDriver.class.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/07 17:49:02 by hestela           #+#    #+#             //
//   Updated: 2016/01/07 17:49:02 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LCDDRIVER_CLASS_HPP
# define LCDDRIVER_CLASS_HPP

# include <iostream>
# include <vector>

# include "IScreen.class.hpp"
# include "LcdController.class.hpp"
# include "Memory.class.hpp"
# include "SerialIO.class.hpp"
# include "Defines.hpp"

/*

************************* USED REGISTERS ************************

	-- LCDC Register (LCDControl) [0xFF40]
		BIT 6: Window Tile Map Display Select		 0x9800 - 0x9BFF | 0x9C00 - 0x9FFF
		BIT 5: Window Display							   off		 |	   	on
		BIT 4: BG & WindowTile Data Select			 0x8800 - 0x97FF | 0x8000 - 0x8FFF
		BIT 3: BG Tile Map Display Select 			 0x9800 - 0x9BFF | 0x9C00 - 0x9FFF
		BIT 2: OBJ (Sprite) size 						  8 * 8		 |	  8 * 16
		BIT 1: OBJ (Sprite) Display 					   off		 |		on
		BIT 0: BG & Window Display 						   off		 |		on

	-- SCY Register (Scroll Y) [0xFF42]
		8 Bit value $00-$FF to scroll BG Y screen position.

	-- SCX Register (Scroll X) [0xFF43]
		8 Bit value $00-$FF to scroll BG X screen position.

	-- BGP Register (BG & WindowPalette Data) [0xFF47]
		This selects the shade of grays to use for the background (BG) & window pixels.
		Since each pixel uses 2 bits, the corresponding shade wi ll be selected from here.
		BITS 7-6: Data for Dot Data 11 (Normally darkest color)
		BITS 5-4: Data for Dot Data 10
		BITS 3-2: Data for Dot Data 01
		BITS 1-0: Data for Dot Data 00 (Normally lightest color)

	-- OBP0 Regsiter (Sprite Palette 0 Data) [0xFF48]
	-- OBP1 Regsiter (Sprite Palette 1 Data) [0xFF49]
		This selects the colors for sprite palette 0 & 1. It works exactly as BGP
		except each each value of 0 is transparent.

	-- WY Register (Window Y position) [0xFF4A]
	-- WX Register (Window X position) [0xFF4B]
		Window displayed coorinate.
		WX is offset from absolute screen coordinates by 7


*********************** SCREEN SPECIFICATIONS *********************
	
	*** Scrolling Area ***
	The Main buffer of the gameboy is a 256x256 frame
	but only 160x144 can be visible (gameBoy Screen) 

		0 											   256
	  0 +-----------------------------------------------+
		|												|
		|												|
		|					Buffer						|
		|				   (On VRAM)					|
		|												|
		|					   SCX						|
		|					SCY	+-----------------------+
		|						|						|
		|						|	  visible Area		|
		|						|		 160x144   		|
		|	   current line LY->|.......................|
		|						|						|
		|						|						|
	256	+-----------------------+-----------------------+

	*** Window ***
	Visible area can have a window
	if enable, only the part contained in window can be drawed
	window is used only for tiles !!!
	
	 	0 									   160
	  0 +---------------------------------------+
	  	|		  Visible Area					|
		|										|
		|	   WX-7								|
		|	 WY +---------------------------------------+
		|		|								|		|
		|		|								|		|
		|		|								|		|
		|		|			  Window			|		|
		|		|			(if enable)			|		|
		|		|								|		|
		|		|								|		|
	144	+---------------------------------------+		|
				|										|
				|										|
				+---------------------------------------+

****************** OBJ MEMORY ATTRIBUTES (Sprites) ***************

	Sprite definitions are strored in the OAM
	each sprite specification take 4 bytes

	+---+---+---+---+---+---+---+---+
	|	|	|	|	|	|	|	|	|	YPosition
	+---+---+---+---+---+---+---+---+
	+---+---+---+---+---+---+---+---+
	|	|	|	|	|	|	|	|	|	XPosition
	+---+---+---+---+---+---+---+---+
	+---+---+---+---+---+---+---+---+
	|	|	|	|	|	|	|	|	|	offset addr
	+---+---+---+---+---+---+---+---+
	+---+---+---+---+---+---+---+---+
	| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0	|	Attribtes
	+---+---+---+---+---+---+---+---+

	BITS 0-2: Color palette index (CGB only)
	BIT    3: character bank (CGB only)
	BIT    4: DMG Palette (DMG only)
			(! in CGB compatibility mode, select the OBJ color palette 0 or 1 )
	BIT    5: X Flip
	BIT    6: Y Flip
	BIT    7: BG priority for colors index 1-2-3

****************** TILE ATTRIBUTES (CGB ONLY) *******************

	For each tile data CHR code in Vram bank 0 (Bg data select Part)
	exist Attributes at the same adress in Bank 1.

				  BANK 0
	+---+---+---+---+---+---+---+---+
	|	|	|	|	|	|	|	|	|	CHR Code
	+---+---+---+---+---+---+---+---+

				  BANK 1
	+---+---+---+---+---+---+---+---+
	| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0	|	Attribtes
	+---+---+---+---+---+---+---+---+

	BITS 0-2: Color palette index
	BIT    3: character bank
	BIT    5: X Flip
	BIT    6: Y Flip
	BIT    7: BG priority from OBJ
	
***************** TILES AND SPRITES SPECIFICATIONS **************

	each line of sprite or tile is defined by 2 byte representing 8 pixels
	so a 8x8 tile take 16 bytes
	each pixel have a 2Bits color index ( 1 bit on Byte1 & 1bit on Byte2 )
	give us 4 index possible

	Tiles are always placed at 8 multiple on the main screen buffer ( 256*256 )
	Sprite are placed wherever on the visible area via position attribute.

	 	  TILES 			  SPRITE
		always 8x8 			8x8 | 8x16

		0 		8 			8
	  0 +-------+		 16 +-------+
		|		| 			| 		|
		|		|			|		|
		|		|			|		|
	  8 +-------+ 			+-------+ 8
							|		|
							|		|
							|		|
							+-------+ 0
									0
*/

# define GB_SCREEN_W 	160
# define GB_SCREEN_H 	144
# define VRAM_OFFSET	0x8000
# define OAM_OFFSET 	0xFE00
# define SPRITE_W		8
# define SPRITE_H		16
# define TILE_SIZE		8
# define TILE_BYTES		16
# define LINE_BYTES		32


namespace Gbmu
{
	
	class LcdDriver
	{
		private:
			enum DMGColor // enum for normal hardware colors
			{
				Black 		= 0x000000,
				DarkGray 	= 0x777777,
				LightGray	= 0xCCCCCC,
				White		= 0xFFFFFF
			};

			struct DMGPalette
			{
				int32_t		bgp[4];		// tiles palette
				int32_t		obp0[4];	// sprite palette 0
				int32_t		obp1[4];	// sprite palette 1
			};

			struct CGBPalette
			{
				int32_t		bcp[8][4];	// BG - 8 palettes - 4 color
				int32_t 	ocp[8][4];	// OBJ - 8 palettes - 4 color
			};

			struct BackgroundAttrib
			{
				uint8_t 		y;				// position in Main screen buffer ( 256 * 256 )
				uint8_t 		x;				// position in Main screen buffer ( 256 * 256 )
				uint16_t 		tilesCodes;		// tiles specs
				uint16_t		tilesDatas;		// tile Set Addr
				bool			signedIndex;	// signed index of tile ?
				int32_t			tilesSetCol;	// current tile column to draw in tileset
				int32_t			tilesSetRow;	// current tile row to draw in tileset
			};

			struct Tile
			{
				uint16_t 		addr;		// Tile Addr
				uint8_t 		data1;		// line Byte 1
				uint8_t 		data2;		// line Byte 2
				uint8_t			attributes;	// (CGB only)
				bool			xFlip;		// if sprite is horizontally flipped ( CGB ONLY )
				bool			yFlip;		// if sprite is vertically flipped ( CGB ONLY )
				bool			priority;	// if All OBJ ares above BG ( CGB ONLY )
				int32_t*		palette;	// palette to use
			};

			struct SpriteAttrib
			{
				uint8_t		positionY;		// y position where draw sprite
				uint8_t		positionX;		// x position where draw sprite
				uint8_t		index;			// index of sprite in VRAM ( VRAM + (index * 16) = SpriteAddr )
				uint8_t		attributes;		// Attributes for sprite ( palette , xFlip, yFlip)	
			};

			struct Sprite
			{
				uint16_t	addr;			// addr of sprite in the VRAM
				int32_t		y;				// x position off sprite on screen
				int32_t		x;				// y position off sprite on screen
				bool		visible; 		// if sprite is visible
				size_t		height;			// height of sprite ( 8 or 16) defined bit Bit 2 LCDC
				bool		xFlip;			// if sprite is horizontally flipped
				bool		yFlip;			// if sprite is vertically flipped
				bool		bgPriority;		// priority background
				int32_t*	palette;		// palette to use for render

			};

		private:
			Cpu*							_cpu;						// get pointer to cpu ( the master parent )
			struct SerialIO::IORegisters*	_IOREGS; 					// Pointer to IO registers
			Memory*							_memory; 					// pointer to GbMemory
			IScreen*						_screen; 					// Pointer to GUI screen
			struct DMGPalette				_DMGpalettes;				// palettes used for DMG (BGP, OBP0, OBP1)
			struct CGBPalette				_CGBpalettes;				// colors palettes for BG & OBJ
			std::vector<struct Sprite>		_sprites;					// sprites from OAM register
			uint8_t							_BgIndexBuffer[160][144]; 	// Background index buffer for BG priority test


		public:
			LcdDriver ( Cpu* cpu );
			virtual ~LcdDriver ( void );

			void				reset ( void );
			void				setScreen ( IScreen* screen );

			void				oamSearching ( void );
			void				transferLine ( void );

			void				clear ( void );
			void 				flush ( void );

		private:
			void				updateDMGPalettes ( void );
			void				updateCGBPalettes ( void );

			void				drawBackground ( void );
			void 				getBackgroundAttributes( struct BackgroundAttrib* attributes );

			void				drawWindow ( void );
			void 				getWindowAttributes( struct BackgroundAttrib* attributes );

			void				getTileInfos ( struct BackgroundAttrib const& attributes, struct Tile* tile );
			void				getTileAttributes ( struct BackgroundAttrib const& attributes, struct Tile* tile );

			void				drawSprites ( void );
			bool				spriteNeedDrawOnThisScanline ( struct Sprite const& sprite );
			void				drawSpriteLine ( struct Sprite const& sprite );

			int32_t				getDMGNormalColorValue ( uint8_t const& idx );
			uint8_t				getPixelColorIndex ( int const& pixIdx, uint8_t const& data1, uint8_t const& data2);
	};

}

#else
	namespace Gbmu
	{	
		class LcdDriver;
	}
#endif // !LCDDRIVER_CLASS_HPP
