// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Memory.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/05 16:48:06 by hestela           #+#    #+#             //
//   Updated: 2016/01/05 16:48:22 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Memory.class.hpp"

namespace Gbmu
{

	Memory::Memory( Cpu* cpu ):
		_cpu(cpu),
		_data( new uint8_t[GB_MEM_SIZE] ),
		_vram( new uint8_t[VRAM_SIZE] ),
		_ram( new uint8_t[WRAM_SIZE] ),
		_bcp( new uint8_t[BCP_SIZE] ),
		_ocp( new uint8_t[OCP_SIZE] )
	{ }

	Memory::~Memory( void )
	{
		delete[] _data;
		delete[] _vram;
		delete[] _ram;
		delete[] _bcp;
		delete[] _ocp;
	}

	void			Memory::reset ( void )
	{
		bzero(_data, GB_MEM_SIZE);
		bzero(_vram, VRAM_SIZE);
		bzero(_ram, WRAM_SIZE);
		bzero(_bcp, BCP_SIZE);
		bzero(_ocp, OCP_SIZE);

		_vramBankPtr = _vram;
		_ramBankPtr = _ram + WRAM_BANK_SIZE;
	}

	uint8_t			Memory::getByteAt ( uint16_t const& addr )
	{
		// if on boot routine DMG
		if (_cpu->onBoot() && addr < 0x100 )
			return (_cpu->bios()->getByteAt(addr));
		// if on boot routine CGB
		else if (_cpu->onBoot() && addr >= 0x0200 && addr < 0x0900)
			return (_cpu->bios()->getByteAt(addr - 0x100));

		// if read catridge ROM or switchable Banks
		else if (addr < 0x8000 || (addr >= 0xA000 && addr < 0xC000))
			return (_cpu->cartridge()->getByteAt(addr));

		// if read on VRAM
		else if (addr >= 0x8000 && addr < 0xA000)
		{
			// if CGB read on appropriate switchable VRAM Bank
			if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
				return (_vramBankPtr[addr - 0x8000]);
			// if DMG simply read on VRAM
			else
				return (_vram[addr - 0x8000]);
		}

		// if read on RAM
		else if (addr >= 0xC000 && addr < 0xE000)
		{
			// if CGB read on appropriate switchable RAM Bank
			if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			{
				// if Bank 0
				if (addr < 0xD000)
					return (_ram[addr - 0xC000]);
				// if bank 1 - 7
				else
					return (_ramBankPtr[addr - 0xD000]);
			}
			// if DMG simply read on RAM
			else
				return (_ram[addr - 0xC000]);
		}

		// read audio register
		else if (addr >= 0xFF10 && addr <= 0xFF3F)
			return (_cpu->IO()->onReadSoundRegister(addr));

		// else read GB memory
		return (_data[addr]);
	}

	uint16_t		Memory::getWordAt ( uint16_t const& addr )
	{
		return (getByteAt(addr + 1) << 8 | getByteAt(addr));
	}

	void			Memory::setByteAt ( uint16_t const& addr, uint8_t const& value )
	{
		// if write switchable cartridge Banks
		if (addr < 0x8000 || (addr >= 0xA000 && addr < 0xC000))
			_cpu->cartridge()->setByteAt(addr, value);

		// if write on VRAM
		else if (addr >= 0x8000 && addr < 0xA000)
		{
			// if CGB write on appropriate switchable VRAM Bank
			if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
				_vramBankPtr[addr - 0x8000] = value;
			// if DMG simply write on VRAM
			else
				_vram[addr - 0x8000] = value;
		}

		// if write on RAM
		else if (addr >= 0xC000 && addr < 0xE000)
		{
			// if CGB write on appropriate switchable RAM Bank
			if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			{
				// if Bank 0
				if (addr < 0xD000)
					_ram[addr - 0xC000] = value;
				// if bank 1 - 7
				else
					_ramBankPtr[addr - 0xD000] = value;
			}
			// if DMG simply write on RAM
			else
				_ram[addr - 0xC000] = value;
		}

		// if write on serial IO
		else if (addr == 0xFF00)
			_cpu->IO()->onWriteP1(value);
		else if (addr == 0xFF04)
			_cpu->IO()->onWriteDIV();
		else if (addr == 0xFF06)
			_cpu->IO()->onWriteTAC(value);
		else if (addr == 0xFF0F)
			_cpu->IO()->onWriteIF(value);
		else if (addr >= 0xFF10 && addr <= 0xFF3F)
			_cpu->IO()->onWriteSoundRegister(addr, value);
		else if (addr == 0xFF40)
			_cpu->IO()->onWriteLCDC(value);
		else if (addr == 0xFF41)
			_cpu->IO()->onWriteSTAT(value);
		else if (addr == 0xFF44)
			_cpu->IO()->onWriteLY();
		else if (addr == 0xFF45)
			_cpu->IO()->onWriteLYC(value);
		else if (addr == 0xFF46)
			_cpu->IO()->onWriteDMA(value);
		else if (addr == 0xFF4F)
			_cpu->IO()->onWriteVBK(value);
		else if (addr == 0xFF50)
			_cpu->IO()->onWriteBOOTSTP();
		else if (addr == 0xFF51)
			_cpu->IO()->onWriteHDMA1(value);
		else if (addr == 0xFF52)
			_cpu->IO()->onWriteHDMA2(value);
		else if (addr == 0xFF53)
			_cpu->IO()->onWriteHDMA3(value);
		else if (addr == 0xFF54)
			_cpu->IO()->onWriteHDMA4(value);
		else if (addr == 0xFF55)
			_cpu->IO()->onWriteHDMA5(value);
		else if (addr == 0xFF68)
			_cpu->IO()->onWriteBCPS(value);
		else if (addr == 0xFF69)
			_cpu->IO()->onWriteBCPD(value);
		else if (addr == 0xFF6A)
			_cpu->IO()->onWriteOCPS(value);
		else if (addr == 0xFF6B)
			_cpu->IO()->onWriteOCPD(value);
		else if (addr == 0xFF70)
			_cpu->IO()->onWriteSVBK(value);
		else if (addr == 0xFFFF)
			_cpu->IO()->onWriteIE(value);

		// else write on GB memory
		else
			_data[addr] = value;
	}

	void			Memory::setWordAt ( uint16_t const& addr, uint16_t const& value )
	{
		uint8_t 	lsb = (value >> 8);
		uint8_t 	hsb = value;

		setByteAt(addr, hsb);
		setByteAt(addr + 1, lsb);
	}

	void			Memory::onWriteVBK ( uint8_t const& value )
	{
		_vramBankPtr = _vram + (VRAM_BANK_SIZE * BIT_0(value));
		_cpu->IO()->registers()->VBK = BIT_0(value);
	}

	void			Memory::onWriteSVBK ( uint8_t const& value )
	{
		uint8_t		bankIdx = BITS_0_2(value);

		if (!bankIdx)
			bankIdx = 1;
		_ramBankPtr = _ram + (WRAM_BANK_SIZE * bankIdx);
		_cpu->IO()->registers()->SVBK = bankIdx;
	}

	void			Memory::onWriteBCPS ( uint8_t const& value )
	{
		_cpu->IO()->registers()->BCPS = value & 0b10111111;
	}

	void			Memory::onWriteBCPD ( uint8_t const& value )
	{
		uint8_t		paletteByteIdx = _cpu->IO()->registers()->BCPS & 0b00111111;

		_bcp[paletteByteIdx] = value;
		// if Bit 7 enable increment the palette idx
		if (BIT_7(_cpu->IO()->registers()->BCPS))
			_cpu->IO()->registers()->BCPS = 0x80 | ((paletteByteIdx + 1) & 0b00111111);
	}

	void			Memory::onWriteOCPS ( uint8_t const& value )
	{
		_cpu->IO()->registers()->OCPS = value & 0b10111111;
	}

	void			Memory::onWriteOCPD ( uint8_t const& value )
	{
		uint8_t		paletteByteIdx = _cpu->IO()->registers()->OCPS & 0b00111111;

		_ocp[paletteByteIdx] = value;
		// if Bit 7 enable increment the palette idx
		if (BIT_7(_cpu->IO()->registers()->OCPS))
			_cpu->IO()->registers()->OCPS = 0x80 | ((paletteByteIdx + 1) & 0b00111111);
	}

	uint8_t*		Memory::data ( void ) const 		{ return (_data); }
	uint8_t*		Memory::vram ( void ) const			{ return (_vram); }
	uint8_t*		Memory::vramBankPtr ( void ) const	{ return (_vramBankPtr); }
	uint8_t*		Memory::ram ( void ) const			{ return (_ram); }
	uint8_t*		Memory::ramBankPtr ( void ) const	{ return (_ramBankPtr); }
	uint8_t*		Memory::bcp ( void ) const			{ return (_bcp); }
	uint8_t*		Memory::ocp ( void ) const			{ return (_ocp); }

	/**************************************************************************/
	/******************************* SAVE STATE *******************************/
	/**************************************************************************/


	void			Memory::saveState ( std::fstream& file )
	{
		// write memory
		file.write((char*)_data, GB_MEM_SIZE);
		// write VRAM
		file.write((char*)_vram, VRAM_SIZE);
		// write RAM
		file.write((char*)_ram, WRAM_SIZE);
		// write Palettes
		file.write((char*)_bcp, BCP_SIZE);
		file.write((char*)_ocp, OCP_SIZE);
	}

	void			Memory::loadState ( std::fstream& file )
	{
		// write memory
		file.read((char*)_data, GB_MEM_SIZE);
		// write VRAM
		file.read((char*)_vram, VRAM_SIZE);
		// write RAM
		file.read((char*)_ram, WRAM_SIZE);
		// write Palettes
		file.read((char*)_bcp, BCP_SIZE);
		file.read((char*)_ocp, OCP_SIZE);

		// reset Banks
		_vramBankPtr = _vram + (VRAM_BANK_SIZE * BIT_0(_cpu->IO()->registers()->VBK));
		_ramBankPtr = _ram + (WRAM_BANK_SIZE * BITS_0_2(_cpu->IO()->registers()->SVBK));
	}

}