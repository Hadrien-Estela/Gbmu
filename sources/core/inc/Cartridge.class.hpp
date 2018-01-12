// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Cartridge.class.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/18 17:57:44 by hestela           #+#    #+#             //
//   Updated: 2015/12/18 17:58:38 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CARTRIDGE_CLASS_HPP
# define CARTRIDGE_CLASS_HPP

# include <iostream>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <cstring>
# include <fstream>

# include "Exception.class.hpp"
# include "Gb.class.hpp"
# include "Cpu.class.hpp"

/*

********************** CATRIDGE MEMORY MAP ****************************

									max 7FFFFF
										  ^
	Extended rom/ram banks ( depend type )|
	--------------------------- 0x8000 ---+
	16kB switchable ROM bank		      |
	--------------------------- 0x4000    |--- 32KB Cartridge ROM
	16kB ROM bank #0 				      |
	--------------------------- 0x0000 ---+

	Cartridges have differents formats but the first 32KB have the same map.
	
	ROM Bank0 from 0x0000 to 0x4000 is the main program of the game.
	
	Switchable ROM Bank is for the datas (tile sets, sprites, etc).
	if cartridge exceed 0x8000 address, this part is used for access
	to the extended banks (0x8000 to 7FFFFFF max ) via the Memory Bank Controller.

*/

namespace Gbmu
{

	class IMBController;
	
	class Cartridge
	{
		public:
		// Header Area (0x100 <-> 0x14F)
			struct Header
			{
				uint8_t		entry_point[0x04]; 		// usually NOP - JUMP NZ 16bits immediate value 	| 0x0100 - 0x0103
				uint8_t		nintendo_logo[0x30];	// nintendo scrolling logo 							| 0x0104 - 0x0133
				char		title[0x0F];			// Upercase game title 								| 0x0134 - 0x0142
				uint8_t		CGB_flag;				// $80 = CGB-DMG | $C0 CGB | $00 or $other = DMG 	| 0x0143
				uint16_t	new_license_code;		//													| 0x0144
				uint8_t		SGB_flag;				// $00 = false | $03 = true 						| 0x0146
				uint8_t		cartridge_type;			// enum MBC Type 									| 0x0147
				uint8_t		rom_size;				//													| 0x0148
				uint8_t		ram_size;				//													| 0x0149
				uint8_t		destination_code;		// $00 - Japan | $01 - Non-Japan					| 0x014A
				uint8_t		old_license_code;		//													| 0x014B
				uint8_t		rom_version;			// usually $00										| 0x014C
				uint8_t		header_checksum;		// higtest bit first ( x << 8 | x : 8 )				| 0x014D
				uint16_t	global_checksum;		// 													| 0x014E - 0x014F
			};

		private:
			Cpu*						_cpu;		// get pointer to CPU ( parent )
			std::string					_path;		// ROM file path
			Gb::Model					_model;		// GB forced model
			uint8_t*					_data;		// pointer on cartridge data
			struct Header				_header;	// cartridge header
			IMBController*				_mbc;		// MBC ( Controller for extended data of cartridge )


		public:
			Cartridge ( Cpu* cpu, std::string const& path, Gb::Model const& model );
			virtual ~Cartridge ( void );

			void							reset ( void );

			void							setModel ( Gb::Model const& model );

			std::string						title ( void ) const;
			bool							colorGB ( void ) const;
			bool							colorCart ( void ) const;

			uint8_t	const&					getByteAt ( uint16_t const& addr );
			void							setByteAt ( uint16_t const& addr, uint8_t const& value );

			struct Cartridge::Header const&	header ( void ) const;
			uint8_t*						data ( void ) const;
			std::string const&				path ( void ) const;

			void							saveState ( std::fstream& file );
			void							loadState ( std::fstream& file );

		private:
			void							load( void );
	};

}

#else
	namespace Gbmu
	{
		class Cartridge;
	}
#endif // !CARTRIDGE_CLASS_HPP
