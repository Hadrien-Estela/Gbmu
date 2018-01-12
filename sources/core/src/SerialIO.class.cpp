// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SerialIO.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/21 11:21:14 by hestela           #+#    #+#             //
//   Updated: 2015/12/21 11:21:14 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "SerialIO.class.hpp"
# include "Cpu.class.hpp"

namespace Gbmu
{

	SerialIO::SerialIO( Cpu* cpu ):
		_cpu(cpu),
		_registers((struct IORegisters*)&_cpu->memory()->data()[0xFF00])
	{ }

	SerialIO::~SerialIO( void )
	{ }

	void							SerialIO::reset ( void )
	{			
		size_t	count = 0;

		if (_cpu->cartridge() && _cpu->cartridge()->colorGB())
		{
			while (count < 0x100)
			{
				_cpu->memory()->data()[0xFF00 + count] = _initialValuesCGB[count];
				count++;
			}
		}
		else
		{
			while (count < 0x100)
			{
				_cpu->memory()->data()[0xFF00 + count] = _initialValuesDMG[count];
				count++;
			}
		}
	}

	struct SerialIO::IORegisters*	SerialIO::registers ( void ) const
	{
		return (_registers);
	}

	void							SerialIO::onWriteLY ( void )
	{
		_cpu->lcdController()->onWriteLY();
	}

	void							SerialIO::onWriteLYC ( uint8_t const& value )
	{
		_cpu->lcdController()->onWriteLYC(value);
	}

	void							SerialIO::onWriteLCDC ( uint8_t const& value )
	{
		_cpu->lcdController()->onWriteLCDC(value);
	}

	void							SerialIO::onWriteDIV ( void )
	{
		_cpu->timerController()->onWriteDIV();
	}

	void							SerialIO::onWriteSTAT ( uint8_t const& value )
	{
		_cpu->lcdController()->onWriteSTAT(value);
	}

	void							SerialIO::onWriteIF ( uint8_t const& value )
	{
		_cpu->interruptController()->onWriteIF(value);
	}

	void							SerialIO::onWriteIE ( uint8_t const& value )
	{
		_cpu->interruptController()->onWriteIE(value);
	}

	void							SerialIO::onWriteP1 ( uint8_t const& value )
	{
		_cpu->keyPad()->onWriteP1(value);
	}

	void							SerialIO::onWriteTAC ( uint8_t const& value )
	{
		_cpu->timerController()->onWriteTAC(value);
	}

	void							SerialIO::onWriteDMA ( uint8_t const& value )
	{
		_cpu->dma()->onWriteDMA(value);
	}

	void							SerialIO::onWriteBOOTSTP ( void )
	{
		if (_cpu->onBoot())
			_cpu->stopBOOT();
	}

	void							SerialIO::onWriteVBK ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->memory()->onWriteVBK(value);
	}

	void							SerialIO::onWriteSVBK ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->memory()->onWriteSVBK(value);
	}

	void							SerialIO::onWriteBCPS ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->memory()->onWriteBCPS(value);
	}

	void							SerialIO::onWriteBCPD ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->memory()->onWriteBCPD(value);
	}

	void							SerialIO::onWriteOCPS ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->memory()->onWriteOCPS(value);
	}

	void							SerialIO::onWriteOCPD ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->memory()->onWriteOCPD(value);
	}

	void							SerialIO::onWriteHDMA1 ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->dma()->onWriteHDMA1(value);
	}

	void							SerialIO::onWriteHDMA2 ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->dma()->onWriteHDMA2(value);
	}

	void							SerialIO::onWriteHDMA3 ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->dma()->onWriteHDMA3(value);
	}

	void							SerialIO::onWriteHDMA4 ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->dma()->onWriteHDMA4(value);
	}

	void							SerialIO::onWriteHDMA5 ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->dma()->onWriteHDMA5(value);
	}

	void							SerialIO::onWriteKey1 ( uint8_t const& value )
	{
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->onWriteKey1(value);
	}

	void							SerialIO::onWriteSoundRegister ( uint16_t addr, uint8_t value )
	{
		_cpu->soundController()->writeRegister(addr, value);
	}

	uint8_t							SerialIO::onReadSoundRegister ( uint16_t addr )
	{
		return (_cpu->soundController()->readRegister(addr));
	}

}
