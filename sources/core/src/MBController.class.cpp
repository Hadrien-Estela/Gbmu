// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MBController.class.cpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/10 13:03:09 by hestela           #+#    #+#             //
//   Updated: 2016/01/10 13:03:10 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "MBController.class.hpp"

namespace Gbmu
{
	///////////////////////// IMBC ///////////////////////////////
	IMBController*		IMBController::create ( Cartridge* cartridge )
	{
		switch (cartridge->header().cartridge_type)
		{
			case IMBController::Type::ROM_ONLY:
			case IMBController::Type::ROM_RAM:
			case IMBController::Type::ROM_RAM_BATT:
				return (new MBC0(cartridge));

			case IMBController::Type::ROM_MBC1:
			case IMBController::Type::ROM_MBC1_RAM:
			case IMBController::Type::ROM_MBC1_RAM_BATT:
				return( new MBC1(cartridge) );

			case IMBController::Type::ROM_MBC2:
			case IMBController::Type::ROM_MBC2_BATT:
				return( new MBC2(cartridge) );

			case IMBController::Type::ROM_MBC3:
			case IMBController::Type::ROM_MBC3_RAM:
			case IMBController::Type::ROM_MBC3_RAM_BATT:
			case IMBController::Type::ROM_MBC3_TIMER_BATT:
			case IMBController::Type::ROM_MBC3_TIMER_RAM_BATT:
				return( new MBC3(cartridge) );

			case IMBController::Type::ROM_MBC5:
			case IMBController::Type::ROM_MBC5_RAM:
			case IMBController::Type::ROM_MBC5_RAM_BATT:
			case IMBController::Type::ROM_MBC5_RUMBLE:
			case IMBController::Type::ROM_MBC5_RUMBLE_RAM:
			case IMBController::Type::ROM_MBC5_RUMBLE_RAM_BATT:
				return( new MBC5(cartridge) );

			default:
				throw Exception("Unimplemented MBC");
				return (NULL);
		}
	}

	void				IMBController::init ( 	struct Cartridge::Header const& header,
												uint8_t* cartData,
												struct Infos* infos )
	{
		infos->cartridge_ptr = cartData;
		infos->rom_size = IMBController::romSize(header);
		infos->mode = 0;			
		infos->bank_count = infos->rom_size / ROM_BANK_SIZE;		
		infos->bank_index = 1;		
		infos->bank_ptr = infos->cartridge_ptr + infos->bank_index * ROM_BANK_SIZE;
		infos->ram_size = IMBController::ramSize(header);		
		infos->ram_index = 0;
		infos->ram_enable = false;
		if (infos->ram_size)
		{
			infos->ram = new uint8_t[infos->ram_size];
			bzero(infos->ram, infos->ram_size);
		}
		else
			infos->ram = NULL;			
		infos->ram_ptr = infos->ram + infos->ram_index * RAM_BANK_SIZE;
	}

	size_t				IMBController::ramSize ( struct Cartridge::Header const& header )
	{
		switch (header.ram_size)
		{
			case 0x00:
				return (0x0);
			case 0x01:
				return (0x800);
			case 0x02:
				return (0x2000);
			case 0x03:
				return (0x8000);
			case 0x04:
				return (0x20000);
			default:
				return (0x0);
		}
	}

	size_t				IMBController::romSize ( struct Cartridge::Header const& header )
	{
		switch (header.rom_size)
		{
			case 0x00:
				return (0x8000);	// 2 Banks
			case 0x01:
				return (0x10000);	// 4 Banks
			case 0x02:
				return (0x20000);	// 8 Banks
			case 0x03:
				return (0x40000);	// 16 Banks
			case 0x04:
				return (0x80000);	// 32 Banks
			case 0x05:
				return (0x100000);	// 64 Banks
			case 0x06:
				return (0x200000);	// 128 Banks
			case 0x52:
				return (0x120000);	// 72 Banks
			case 0x53:
				return (0x140000);	// 80 Banks
			case 0x54:
				return (0x180000);	// 96 Banks
			default:
				return (0x8000);
		}
	}

	void				IMBController::reset ( struct IMBController::Infos* infos )
	{
		infos->mode = 0;				
		infos->bank_index = 1;		
		infos->bank_ptr = infos->cartridge_ptr + infos->bank_index * ROM_BANK_SIZE;			
		infos->ram_index = 0;
		infos->ram_enable = false;		
		infos->ram_ptr = infos->ram + infos->ram_index * RAM_BANK_SIZE;
	}

	void				IMBController::saveBatt ( std::string path, uint8_t* ram, size_t size )
	{
		std::string 	battPath;
		std::fstream	file;

		path = path.substr(0, path.find_last_of('.') + 1);
		battPath = path + std::string("save");
		file.open(battPath, std::fstream::out | std::fstream::trunc);
		file.write((char*)ram, size);
		file.close();
	}

	void				IMBController::loadBatt ( std::string path, uint8_t* ram, size_t size )
	{
		std::string 	battPath;
		std::fstream	file;
		size_t			fileSize;

		if (!size)
			return ;

		path = path.substr(0, path.find_last_of('.') + 1);
		battPath = path + std::string("save");
		file.open(battPath);
		
		file.seekg( 0, std::ios::end );
		fileSize = file.tellg();
		file.seekg( 0, std::ios::beg );

		if (file.is_open() && fileSize == size)
			file.read((char*)ram, size);
		file.close();
	}

	void				IMBController::saveMBCState ( std::fstream& file, struct IMBController::Infos* infos )
	{
		file.write((char*)&infos->mode, sizeof(infos->mode));
		file.write((char*)&infos->bank_index, sizeof(infos->bank_index));
		file.write((char*)&infos->ram_index, sizeof(infos->ram_index));
		file.write((char*)&infos->ram_enable, sizeof(infos->ram_enable));
		file.write((char*)infos->ram, infos->ram_size);
	}

	void				IMBController::loadMBCState ( std::fstream& file, struct IMBController::Infos* infos )
	{
		file.read((char*)&infos->mode, sizeof(infos->mode));
		file.read((char*)&infos->bank_index, sizeof(infos->bank_index));
		file.read((char*)&infos->ram_index, sizeof(infos->ram_index));
		file.read((char*)&infos->ram_enable, sizeof(infos->ram_enable));
		file.read((char*)infos->ram, infos->ram_size);

		infos->bank_ptr = infos->cartridge_ptr + infos->bank_index * ROM_BANK_SIZE;
		infos->ram_ptr = infos->ram + infos->ram_index * RAM_BANK_SIZE;
	}

	////////////////////////// MBC0 /////////////////////////////////

	MBC0::MBC0 ( Cartridge* cartridge ):
		_cartridge(cartridge)
	{
		IMBController::init(cartridge->header(), cartridge->data(), &_infos);
		IMBController::loadBatt(_cartridge->path(), _infos.ram, _infos.ram_size);
	}

	MBC0::~MBC0 ( void )
	{
		if (_infos.ram)
		{
			IMBController::saveBatt(_cartridge->path(), _infos.ram, _infos.ram_size);
			delete[] _infos.ram;
		}
	}

	void			MBC0::reset ( void )
	{
		IMBController::reset(&_infos);
	}

	uint8_t const&	MBC0::getByteAt ( uint16_t const& addr )
	{
		return (_infos.cartridge_ptr[addr]);
	}

	void 	 		MBC0::setByteAt ( uint16_t const& addr, uint8_t const& value )
	{
		//_infos.cartridge_ptr[addr] = value;
	}

	void			MBC0::saveState ( std::fstream& file )
	{
		IMBController::saveMBCState(file, &_infos);
	}

	void			MBC0::loadState ( std::fstream& file )
	{
		IMBController::loadMBCState(file, &_infos);
	}

	////////////////////////// MBC1 /////////////////////////////////

	MBC1::MBC1 ( Cartridge* cartridge ):
		_cartridge(cartridge)
	{
		IMBController::init(cartridge->header(), cartridge->data(), &_infos);
		// allocate minimum
		if (!_infos.ram)
		{
			if (cartridge->header().cartridge_type == ROM_MBC1_RAM
			|| cartridge->header().cartridge_type == ROM_MBC1_RAM)
			{
				_infos.ram_size = 0x8000;
				_infos.ram = new uint8_t[0x8000];
				_infos.ram_ptr = _infos.ram;
			}
		}
		IMBController::loadBatt(_cartridge->path(), _infos.ram, _infos.ram_size);
	}

	MBC1::~MBC1 ( void )
	{
		if (_infos.ram)
		{
			IMBController::saveBatt(_cartridge->path(), _infos.ram, _infos.ram_size);
			delete[] _infos.ram;
		}
	}

	void			MBC1::reset ( void )
	{
		IMBController::reset(&_infos);
	}

	uint8_t const&	MBC1::getByteAt ( uint16_t const& addr )
	{

		if (addr < ROM_BANK_OFFSET)
			return _infos.cartridge_ptr[addr];
		else if (addr < 0x8000)
			return _infos.bank_ptr[addr - ROM_BANK_OFFSET];
		else if ((addr >= RAM_BANK_OFFSET) && (addr < 0xC000) && _infos.ram_enable)
			return _infos.ram_ptr[addr - RAM_BANK_OFFSET];
		return (_infos.cartridge_ptr[0x100]); // return NOP
	}

	void 	 		MBC1::setByteAt ( uint16_t const& addr, uint8_t const& value )
	{
		// write at there address will enable or disable ram banks
		if (addr < 0x2000)
			_infos.ram_enable = ((value & 0x0F) == 0x0A);
		// write at there address will select the appropriate rom bank
		else if (addr >= 0x2000 && addr < 0x4000)
		{
			if (!value)
				_infos.bank_index = 1;
			else
				_infos.bank_index = value & 0b00011111;
			_infos.bank_ptr = _infos.cartridge_ptr + _infos.bank_index * ROM_BANK_SIZE;
		}
		// write at there address will select the appropriate ram bank
		else if (addr >= 0x4000 && addr < 0x6000)
		{
			if (_infos.mode == Mode_4_32)
			{
				_infos.ram_index = value & 0b00000011;
				_infos.ram_ptr = _infos.ram + _infos.ram_index * RAM_BANK_SIZE;
			}
			else if (_infos.mode == Mode_16_8)
			{
				_infos.bank_index = ((value & 0b00000011) << 5) | (_infos.bank_index & 0b00011111);
				_infos.bank_ptr = _infos.cartridge_ptr + _infos.bank_index * ROM_BANK_SIZE;
			}

		}
		// write at there address will select the bank mode
		else if (addr >= 0x6000 && addr < 0x8000) // select the mode
			_infos.mode = BIT_0(value);
		// write at there address write on ram bank if enabled
		else if (addr >= RAM_BANK_OFFSET && addr < 0xC000)
		{
			if (_infos.ram_enable)
	 			_infos.ram_ptr[addr - RAM_BANK_OFFSET] = value;
		}
	}

	void			MBC1::saveState ( std::fstream& file )
	{
		IMBController::saveMBCState(file, &_infos);
	}

	void			MBC1::loadState ( std::fstream& file )
	{
		IMBController::loadMBCState(file, &_infos);
	}

	////////////////////////// MBC2 /////////////////////////////////

	MBC2::MBC2 ( Cartridge* cartridge ):
		_cartridge(cartridge)
	{
		IMBController::init(cartridge->header(), cartridge->data(), &_infos);
		// allocate minimum
		if (!_infos.ram)
		{
			if (cartridge->header().cartridge_type == ROM_MBC2_BATT)
			{
				_infos.ram_size = 0x800;
				_infos.ram = new uint8_t[0x800];
				_infos.ram_ptr = _infos.ram;
			}
		}
		IMBController::loadBatt(_cartridge->path(), _infos.ram, _infos.ram_size);
	}

	MBC2::~MBC2 ( void )
	{
		if (_infos.ram)
		{
			IMBController::saveBatt(_cartridge->path(), _infos.ram, _infos.ram_size);
			delete[] _infos.ram;
		}
	}

	void			MBC2::reset ( void )
	{
		IMBController::reset(&_infos);
	}

	uint8_t const&	MBC2::getByteAt ( uint16_t const& addr )
	{

		if (addr < ROM_BANK_OFFSET)
			return _infos.cartridge_ptr[addr];
		else if (addr < 0x8000)
			return _infos.bank_ptr[addr - ROM_BANK_OFFSET];
		else if ((addr >= RAM_BANK_OFFSET) && (addr < 0xC000) && _infos.ram_enable)
			return _infos.ram_ptr[addr - RAM_BANK_OFFSET];
		return (_infos.cartridge_ptr[0x100]); // return NOP
	}

	void 	 		MBC2::setByteAt ( uint16_t const& addr, uint8_t const& value )
	{

		// write at there address will enable or disable ram banks
		if (addr < 0x2000)
		{
			if (!(addr & 0b00010000))
				_infos.ram_enable = !_infos.ram_enable;
		}
		// write at there address will select the appropriate rom bank
		else if (addr >= 0x2000 && addr < 0x4000)
		{
			if (!value)
				_infos.bank_index = 1;
			else
				_infos.bank_index = value & 0b00001111;
			_infos.bank_ptr = _infos.cartridge_ptr + _infos.bank_index * ROM_BANK_SIZE;
		}
		// write at there address write on ram bank if enabled
		else if (addr >= RAM_BANK_OFFSET && addr < 0xA200)
		{
			if (_infos.ram_enable)
	 			_infos.ram_ptr[addr - RAM_BANK_OFFSET] = value & 0x0F;
		}
	}

	void			MBC2::saveState ( std::fstream& file )
	{
		IMBController::saveMBCState(file, &_infos);
	}

	void			MBC2::loadState ( std::fstream& file )
	{
		IMBController::loadMBCState(file, &_infos);
	}

	////////////////////////// MBC3 /////////////////////////////////

	MBC3::MBC3 ( Cartridge* cartridge ):
		_cartridge(cartridge)
	{
		IMBController::init(cartridge->header(), cartridge->data(), &_infos);
		// allocate minimum
		if (!_infos.ram)
		{
			if (cartridge->header().cartridge_type == ROM_MBC3_RAM
			|| cartridge->header().cartridge_type == ROM_MBC3_RAM_BATT
			|| cartridge->header().cartridge_type == ROM_MBC3_TIMER_RAM_BATT
			|| cartridge->header().cartridge_type == ROM_MBC3_TIMER_BATT)
			{
				_infos.ram_size = 0x8000;
				_infos.ram = new uint8_t[0x8000];
				_infos.ram_ptr = _infos.ram;
			}
		}
		IMBController::loadBatt(_cartridge->path(), _infos.ram, _infos.ram_size);
	}

	MBC3::~MBC3 ( void )
	{
		if (_infos.ram)
		{
			IMBController::saveBatt(_cartridge->path(), _infos.ram, _infos.ram_size);
			delete[] _infos.ram;
		}
	}

	void			MBC3::reset ( void )
	{
		IMBController::reset(&_infos);
	}

	uint8_t const&	MBC3::getByteAt ( uint16_t const& addr )
	{

		if (addr < ROM_BANK_OFFSET)
			return _infos.cartridge_ptr[addr];
		else if (addr < 0x8000)
			return _infos.bank_ptr[addr - ROM_BANK_OFFSET];
		else if ((addr >= RAM_BANK_OFFSET) && (addr < 0xC000)
			&& _infos.ram_enable && _infos.mode == Mode_16_8)
			return _infos.ram_ptr[addr - RAM_BANK_OFFSET];
		return (_infos.cartridge_ptr[0x100]); // return NOP
	}

	void 	 		MBC3::setByteAt ( uint16_t const& addr, uint8_t const& value )
	{

		// write at there address will enable or disable ram banks
		if (addr < 0x2000)
			_infos.ram_enable = ((value & 0x0F) == 0x0A);
		// write at there address will select the appropriate rom bank
		else if (addr >= 0x2000 && addr < 0x4000)
		{
			if (!value)
				_infos.bank_index = 1;
			else
				_infos.bank_index = value & 0b01111111;
			_infos.bank_ptr = _infos.cartridge_ptr + _infos.bank_index * ROM_BANK_SIZE;
		}
		// write at there address will select the appropriate ram bank
		else if (addr >= 0x4000 && addr < 0x6000)
		{
			if (value < 4)
			{
				_infos.ram_index = value;
				_infos.ram_ptr = _infos.ram + _infos.ram_index * RAM_BANK_SIZE;
				_infos.mode = Mode_16_8;
			}
			else if ((value >= 0x08) && (value <= 0x0C))
				_infos.mode = Mode_4_32;
		}
		// Real time clock
		else if (addr >= 0x6000 && addr < 0x8000)
			;
		// write at there address write on ram bank if enabled
		else if (addr >= RAM_BANK_OFFSET && addr < 0xC000)
		{
			if (_infos.ram_enable && _infos.mode == Mode_16_8)
	 			_infos.ram_ptr[addr - RAM_BANK_OFFSET] = value;
		}

	}

	void			MBC3::saveState ( std::fstream& file )
	{
		IMBController::saveMBCState(file, &_infos);
	}

	void			MBC3::loadState ( std::fstream& file )
	{
		IMBController::loadMBCState(file, &_infos);
	}

	////////////////////////// MBC5 /////////////////////////////////

	MBC5::MBC5 ( Cartridge* cartridge ):
		_cartridge(cartridge)
	{
		IMBController::init(cartridge->header(), cartridge->data(), &_infos);
		// allocate minimum
		if (!_infos.ram)
		{
			if (cartridge->header().cartridge_type == ROM_MBC5_RAM
			|| cartridge->header().cartridge_type == ROM_MBC5_RUMBLE_RAM
			|| cartridge->header().cartridge_type == ROM_MBC5_RAM_BATT
			|| cartridge->header().cartridge_type == ROM_MBC5_RUMBLE_RAM_BATT)
			{
				_infos.ram_size = 0x20000;
				_infos.ram = new uint8_t[0x20000];
				_infos.ram_ptr = _infos.ram;
			}
		}
		IMBController::loadBatt(_cartridge->path(), _infos.ram, _infos.ram_size);
		//MBC5 allowed rom bank 0
		_infos.bank_index = 0;		
		_infos.bank_ptr = _infos.cartridge_ptr + _infos.bank_index * ROM_BANK_SIZE;
	}

	MBC5::~MBC5 ( void )
	{
		if (_infos.ram)
		{
			IMBController::saveBatt(_cartridge->path(), _infos.ram, _infos.ram_size);
			delete[] _infos.ram;
		}
	}

	void			MBC5::reset ( void )
	{
		IMBController::reset(&_infos);
		_infos.bank_index = 0;		
		_infos.bank_ptr = _infos.cartridge_ptr + _infos.bank_index * ROM_BANK_SIZE;
	}

	uint8_t const&	MBC5::getByteAt ( uint16_t const& addr )
	{

		if (addr < ROM_BANK_OFFSET)
			return _infos.cartridge_ptr[addr];
		else if (addr < 0x8000)
			return _infos.bank_ptr[addr - ROM_BANK_OFFSET];
		else if ((addr >= RAM_BANK_OFFSET) && (addr < 0xC000) && _infos.ram_enable)
			return _infos.ram_ptr[addr - RAM_BANK_OFFSET];
		return (_infos.cartridge_ptr[0x100]); // return NOP
	}

	void 	 		MBC5::setByteAt ( uint16_t const& addr, uint8_t const& value )
	{

		// write at there address will enable or disable ram banks
		if (addr < 0x2000)
			_infos.ram_enable = ((value & 0x0F) == 0x0A);
		// write at there address will select the appropriate rom bank
		else if (addr >= 0x2000 && addr < 0x3000)
		{
			_infos.bank_index = (_infos.bank_index & 0b100000000) | value;
			_infos.bank_ptr = _infos.cartridge_ptr + _infos.bank_index * ROM_BANK_SIZE;
		}
		else if (addr >= 0x3000 && addr < 0x4000)
		{
			_infos.bank_index = ((value & 0b00000001) << 8) | (_infos.bank_index & 0b11111111);
			_infos.bank_ptr = _infos.cartridge_ptr + _infos.bank_index * ROM_BANK_SIZE;
		}
		// write at there address will select the appropriate ram bank
		else if (addr >= 0x4000 && addr < 0x6000)
		{
			_infos.ram_index = value & 0b00001111;
			_infos.ram_ptr = _infos.ram + _infos.ram_index * RAM_BANK_SIZE;
		}
		// write at there address write on ram bank if enabled
		else if (addr >= RAM_BANK_OFFSET && addr < 0xC000)
		{
			if (_infos.ram_enable)
	 			_infos.ram_ptr[addr - RAM_BANK_OFFSET] = value;
		}
	}

	void			MBC5::saveState ( std::fstream& file )
	{
		IMBController::saveMBCState(file, &_infos);
	}

	void			MBC5::loadState ( std::fstream& file )
	{
		IMBController::loadMBCState(file, &_infos);
	}

}