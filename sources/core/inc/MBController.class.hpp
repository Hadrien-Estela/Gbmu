// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MBController.class.hpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/10 12:53:10 by hestela           #+#    #+#             //
//   Updated: 2016/01/10 12:53:46 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MBCONTROLLER_CLASS_HPP
# define MBCONTROLLER_CLASS_HPP

# include <fstream>

# include "Exception.class.hpp"
# include "Cartridge.class.hpp"
# include "Defines.hpp"

/*

	+---------------+\	|	..................	|
	|	RAM BANK x	| \	+-----------------------+
	+---------------+  \| 	  Internal RAM		|	 
	|	RAM BANK 2	|	+-----------------------+	   
	+---------------+	|  Switchable RAM BANK  |  /+---------------+	  
	|	RAM BANK 1	|	+-----------------------+ /	|	ROM BANK x	|
	+---------------+  /|		  VRAM			|/	+---------------+
	|	RAM BANK 0	| /	+-----------------------+	|	R0M BANK 3	|
	+---------------+/	|  Switchable ROM BANK 	|	+---------------+
						+-----------------------+	|	R0M BANK 2	|
						|	Main ROM BANK 0		|\	+---------------+
						+-----------------------+ \	|	R0M BANK 1	|
												   \+---------------+
*/

# define ROM_BANK_SIZE 		0x4000
# define RAM_BANK_SIZE 		0x2000
# define ROM_BANK_OFFSET	0x4000
# define RAM_BANK_OFFSET	0xA000

namespace Gbmu
{

	class IMBController
	{
		public:
			// Cartridge Type
			enum Type
			{
				ROM_ONLY = 0x00,
				ROM_MBC1,
				ROM_MBC1_RAM,
				ROM_MBC1_RAM_BATT,
				ROM_MBC2 = 0x05,
				ROM_MBC2_BATT,
				ROM_RAM,
				ROM_RAM_BATT,
				ROM_MMM01 = 0x0B,
				ROM_MMM01_RAM,
				ROM_MMM01_RAM_BATT,
				ROM_MBC3_TIMER_BATT = 0x0F,
				ROM_MBC3_TIMER_RAM_BATT,
				ROM_MBC3,
				ROM_MBC3_RAM,
				ROM_MBC3_RAM_BATT,
				ROM_MBC4 = 0x15,
				ROM_MBC4_RAM,
				ROM_MBC4_RAM_BATT,
				ROM_MBC5 = 0x19,
				ROM_MBC5_RAM,
				ROM_MBC5_RAM_BATT,
				ROM_MBC5_RUMBLE,
				ROM_MBC5_RUMBLE_RAM,
				ROM_MBC5_RUMBLE_RAM_BATT,
				POCKET_CAMERA = 0xFC,
				BANDAI_TAMA5,
				HUDSON_HUC3,
				HUDSON_HUC1
			};

			// Memory Bank mode
			enum Mode 
			{
				Mode_16_8, // 16 / 8
				Mode_4_32  // 4 / 32
			};

			struct Infos
			{
				uint8_t*				cartridge_ptr;	// pointer to first cartridge address
				size_t					rom_size;		// size of ROM
				uint8_t					mode;			// mode of MBC
				uint16_t				bank_count;		// number of banks
				uint16_t 				bank_index;		// current bank index
				uint8_t*				bank_ptr;		// pointer on current Bank
				size_t					ram_size;		// size of ram
				uint8_t 				ram_index; 		// current ram bank index
				bool					ram_enable;		// ram bank (off/on)
				uint8_t*				ram;			// allocated Ram
				uint8_t*				ram_ptr;		// pointer on current ram bank
			};

		public:
			virtual ~IMBController ( void ) {}
			
			static IMBController*		create ( Cartridge* cartridge );
			static size_t				ramSize ( struct Cartridge::Header const& header );
			static size_t				romSize ( struct Cartridge::Header const& header );
			static void					init ( 	struct Cartridge::Header const& header,
												uint8_t* cartData,
												struct IMBController::Infos* infos );
			static void					reset ( struct IMBController::Infos* infos );
			static void					saveBatt ( std::string path, uint8_t* ram, size_t size );
			static void					loadBatt ( std::string path, uint8_t* ram, size_t size );
			static void					saveMBCState ( std::fstream& file, struct IMBController::Infos* infos );
			static void					loadMBCState ( std::fstream& file, struct IMBController::Infos* infos );

			virtual void				reset ( void ) = 0;
			virtual uint8_t	const&		getByteAt ( uint16_t const& addr ) = 0;
			virtual void				setByteAt ( uint16_t const& addr, uint8_t const& value ) = 0;
			virtual void				saveState ( std::fstream& file ) = 0;
			virtual void				loadState ( std::fstream& file ) = 0;
	};

	class MBC0: public IMBController
	{
		private:
			Cartridge*							_cartridge;
			struct IMBController::Infos 		_infos;

		public:
			MBC0 ( Cartridge* cartridge);
			virtual ~MBC0 ( void );

			void						reset ( void );
			uint8_t	const&				getByteAt ( uint16_t const& addr );
			void						setByteAt ( uint16_t const& addr, uint8_t const& value );
			void						saveState ( std::fstream& file );
			void						loadState ( std::fstream& file );
	};

	class MBC1: public IMBController
	{
		private:
			Cartridge*							_cartridge;
			struct IMBController::Infos 		_infos;

		public:
			MBC1 ( Cartridge* cartridge );
			virtual ~MBC1 ( void );

			void						reset ( void );
			uint8_t	const&				getByteAt ( uint16_t const& addr );
			void						setByteAt ( uint16_t const& addr, uint8_t const& value );
			void						saveState ( std::fstream& file );
			void						loadState ( std::fstream& file );
	};

	class MBC2: public IMBController
	{
		private:
			Cartridge*							_cartridge;
			struct IMBController::Infos 		_infos;

		public:
			MBC2 ( Cartridge* cartridge );
			virtual ~MBC2 ( void );

			void						reset ( void );
			uint8_t	const&				getByteAt ( uint16_t const& addr );
			void						setByteAt ( uint16_t const& addr, uint8_t const& value );
			void						saveState ( std::fstream& file );
			void						loadState ( std::fstream& file );
	};

	class MBC3: public IMBController
	{
		private:
			Cartridge*							_cartridge;
			struct IMBController::Infos 		_infos;

		public:
			MBC3 ( Cartridge* cartridge );
			virtual ~MBC3 ( void );

			void						reset ( void );
			uint8_t	const&				getByteAt ( uint16_t const& addr );
			void						setByteAt ( uint16_t const& addr, uint8_t const& value );
			void						saveState ( std::fstream& file );
			void						loadState ( std::fstream& file );
	};

	class MBC5: public IMBController
	{
		private:
			Cartridge*							_cartridge;
			struct IMBController::Infos 		_infos;

		public:
			MBC5 ( Cartridge* cartridge );
			virtual ~MBC5 ( void );

			void						reset ( void );
			uint8_t	const&				getByteAt ( uint16_t const& addr );
			void						setByteAt ( uint16_t const& addr, uint8_t const& value );
			void						saveState ( std::fstream& file );
			void						loadState ( std::fstream& file );
	};
	
}

#else
	namespace Gbmu
	{
		class IMBController;
		class MBC0;
		class MBC1;
		class MBC2;
		class MBC3;
		class MBC5;
	}
#endif // !MBCONTROLLER_CLASS_HPP
