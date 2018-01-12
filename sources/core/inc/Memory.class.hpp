// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Memory.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/05 16:46:16 by hestela           #+#    #+#             //
//   Updated: 2016/01/05 16:47:57 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MEMORY_CLASS_HPP
# define MEMORY_CLASS_HPP

# include <iostream>
# include <fstream>

# include "Cpu.class.hpp"
# include "Defines.hpp"

/*

**************************** GB MEMORY MAP ******************************

	Interrupt Enable Register			  |--- interrupt flags register
	--------------------------- 0xFFFF ---+
	Stack RAM 							  |--- 127B stack ram
	--------------------------- 0xFF80 ---+
	CGB I/O ports 						  |--- extended IO ( for CGB only )
	--------------------------- 0xFF4C ---+
	DMG I/O ports 						  |--- serial IO for DMG
	--------------------------- 0xFF00 ---+
	Empty but unusable for I/O 			  |--- prohibed area
	--------------------------- 0xFEA0 ---+
	Sprite Attrib Memory (OAM) 			  |--- OAM ram 40 x 4Bytes ( store 40 strite attributes )
	--------------------------- 0xFE00 ---+
	Echo of 8kB Internal RAM 			  |--- prohibed area 
	--------------------------- 0xE000 ---+
	8kB Internal RAM					  |--- 8KB Work RAM ( extended 32KB for CGB )
	--------------------------- 0xC000 ---+
	8kB switchable RAM bank 			  |--- switchable cartridge extended RAM Banks
	--------------------------- 0xA000 ---+
	8kB Video RAM						  |--- 8KB Display RAM ( extended to 16KB for CGB )
	--------------------------- 0x8000 ---+---------------------------------------------+
	16kB switchable ROM bank		   	  |--- Switchable cartridge extended ROM Banks	|
	--------------------------- 0x4000 ---+												|--- 32KB Cartridge ROM
	16kB ROM bank #0 				   	  |--- Main program								|
	--------------------------- 0x0000 ---+---------------------------------------------+

********************* BANK CONTROL REGISTERS ( CGB ONLY ) ****************

	-- VBK Register (VRAM bank control register) [0xFF4F]
		BIT 0: 		0 specify Bank 0
					1 specify Bank 1

		0x8000 	+-----------+-----------+
				| 	BANK 0	|	BANK 1	|
		0xA000	+-----------+-----------+


	-- SVBK Register (RAM bank control register) [0xFF70]
		BITS 0-2: 	0 and 1 specify Bank 1 ( bank 0 always enable )
					2-7 specify bank 2 to 7

		0xC000 	+-----------+
				| 	BANK 0	| 							Fixed
		0xD000	+-----------+-----------+-----------+
				|	BANK 1 	|	.....	| 	BANK 7	|	Switchable
		0xE000	+-----------+-----------+-----------+

************************* PALETTE RAM ( CGB ONLY ) **********************

	The CGB have a Ram for color palette.
	8 palettes each are provided for BG and OBJ.
	Each palette consists of 4 colors represented with 2 Bytes
	with 5 bits of data for each color of RGB

	So: 1 palette consist of 8Bytes ( 4colors )
		8 palettes: 64Bytes
		palette ram = 64Bytes * 2

					HSB									LSB
	+---+---+---+---+---+---+---+---+	+---+---+---+---+---+---+---+---+
	| /	| B | B | B | B | B | G | G |	| G | G | G | R | R | R | R | R |
	+---+---+---+---+---+---+---+---+	+---+---+---+---+---+---+---+---+

************* COLOR PALETTE CONTROL REGISTERS ( CGB ONLY ) ***************

	CGB have registers to perform write on palettes

	-- BCPS Register (BG color palette specs register) [0xFF68]
	-- OCPS Register (OBJ color palette specs register) [0xFF6A]
		The write-specification and write-data registers
		BIT    0: 	0 - Specify LSB
					1 - Specify HSB
		BITS 1-2: 	Specify the palette data n°
		BITS 3-5: 	Specify the palette n°
		BIT    7: 	0 - Values of bits 0-5 fixed
					1 - With each write, specify the next palette

	-- BCPD Register (BG Palette write data) [0xFF69]
	-- OCPD Register (BG Palette write data) [0xFF6B]
		the value to write in color palette

*/

# define GB_MEM_SIZE 	0x10000
# define VRAM_SIZE		0x4000
# define WRAM_SIZE		0x8000

# define OCP_SIZE		0x40
# define BCP_SIZE		0x40

# define VRAM_BANK_SIZE	0x2000
# define WRAM_BANK_SIZE	0x1000

namespace Gbmu
{

	class Memory
	{
		private:
			Cpu*			_cpu; 			// get pointer to the Cpu ( the parent )
			uint8_t*		_data; 			// allocated DMG memory map
			uint8_t*		_vram;			// allocated VRAM (max 16KB for CGB)
			uint8_t*		_vramBankPtr;	// pointer to switch banks
			uint8_t*		_ram;			// allocated RAM (max 32KB for CGB)
			uint8_t*		_ramBankPtr;	// pointer to switch banks
			uint8_t*		_bcp;			// allocated palettes RAM for BG
			uint8_t*		_ocp;			// allocated palettes RAM for OBJ

		public:
			Memory( Cpu* cpu );
			virtual ~Memory( void );

			void			reset ( void );

			uint8_t			getByteAt ( uint16_t const& addr );
			uint16_t		getWordAt ( uint16_t const& addr );

			void			setByteAt ( uint16_t const& addr, uint8_t const& value );
			void			setWordAt ( uint16_t const& addr, uint16_t const& value );

			void			onWriteVBK ( uint8_t const& value );
			void			onWriteSVBK ( uint8_t const& value );
			void			onWriteBCPS ( uint8_t const& value );
			void			onWriteBCPD ( uint8_t const& value );
			void			onWriteOCPS ( uint8_t const& value );
			void			onWriteOCPD ( uint8_t const& value );

			uint8_t*		data ( void ) const;
			uint8_t*		vram ( void ) const;
			uint8_t*		vramBankPtr ( void ) const;
			uint8_t*		ram ( void ) const;
			uint8_t*		ramBankPtr ( void ) const;
			uint8_t*		bcp ( void ) const;
			uint8_t*		ocp ( void ) const;

			void			saveState ( std::fstream& file );
			void			loadState ( std::fstream& file );

	};

}

#else
	class Memory;
#endif // !MEMORY_CLASS_HPP
