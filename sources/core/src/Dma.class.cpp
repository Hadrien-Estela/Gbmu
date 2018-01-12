// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Dma.class.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/24 09:47:43 by hestela           #+#    #+#             //
//   Updated: 2016/01/24 09:47:43 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Dma.class.hpp"

namespace Gbmu
{

	Dma::Dma( Cpu* cpu ):
		_cpu(cpu),
		_memory(cpu->memory()),
		_IOREGS(_cpu->IO()->registers()),
		_HDMA(false),
		_sourceAddr(0x0000),
		_destAddr(0x0000),
		_nBytes(0)
	{ }

	Dma::~Dma( void )
	{ }

	void			Dma::reset ( void )
	{
		_HDMA = false;
		_sourceAddr = 0x0000;
		_destAddr = 0x0000;
		_nBytes = 0;
	}

	void			Dma::update ( void )
	{
		if (_HDMA && !_cpu->onHalt())
			HDMA_Transfert();
	}

	void			Dma::onWriteDMA ( uint8_t const& value )
	{
		_IOREGS->DMA = value;
		DMA_Transfert(value);
	}

	void			Dma::onWriteHDMA1 ( uint8_t const& value )
	{
		_IOREGS->HDMA1 = value;
		_sourceAddr = (_IOREGS->HDMA1 << 8) | (_sourceAddr & 0xF0);
		
	}

	void			Dma::onWriteHDMA2 ( uint8_t const& value )
	{
		_IOREGS->HDMA2 = value & 0xF0;
		_sourceAddr = (_sourceAddr & 0xFF00) | _IOREGS->HDMA2;
	}

	void			Dma::onWriteHDMA3 ( uint8_t const& value )
	{
		_IOREGS->HDMA3 = (value & 0x1F);
		_destAddr = (_IOREGS->HDMA3 << 8) | (_destAddr & 0xF0);
	}

	void			Dma::onWriteHDMA4 ( uint8_t const& value )
	{
		_IOREGS->HDMA4 = value & 0xF0;
		_destAddr = (_destAddr & 0x1F00) | _IOREGS->HDMA4;
	}

	void			Dma::onWriteHDMA5 ( uint8_t const& value )
	{
		_nBytes = ((value & 0x7F) + 1) * 16;
		if (_HDMA)
		{
			if (BIT_7(value))
				_IOREGS->HDMA5 = value & 0x7F;
			else
			{
				_IOREGS->HDMA5 = 0xFF;
				_HDMA = false;
			}
		}
		else
		{
			if (BIT_7(value))
			{
				_HDMA = true;
				_IOREGS->HDMA5 = value & 0x7F;
				// if (m_pVideo->GetCurrentStatusMode() == 0)
				// {
				//     m_pProcessor->AddCycles(PerformHDMA());
				// }
			}
			else
				GDMA_Transfert(value);
		}
	}

	/**************************************************************************/
	/**************************** PRIVATE METHODS *****************************/
	/**************************************************************************/

	// The DMA Transfer 40 Objects (Sprites) Attributes from internal ROM or RAM
	// to the Object Attribute Memory (OAM) at addresses $FE00 - $FE9F
	void			Dma::DMA_Transfert ( uint8_t const& value )
	{
		uint16_t	sourceAddr = value << 8; 	// value is the hight nibble of adrress to start transfer from ROM
		uint16_t 	destAddr = 0xFE00;			// Begin address of the OAM

		while (destAddr < 0xFEA0)
		{
			_memory->setByteAt(destAddr, _memory->getByteAt(sourceAddr));
			destAddr++;
			sourceAddr++;
		}
	}

	// Transfering N bytes specify in HDMA5 register
	void			Dma::GDMA_Transfert ( uint8_t const& value )
	{
		uint16_t			count = 0;

		// transfering
		while (count < _nBytes)
		{
			_memory->vramBankPtr()[_destAddr + count] = _memory->getByteAt(_sourceAddr + count);
			count++;
		}

		// increments address
		_sourceAddr += _nBytes;
		_destAddr += _nBytes;

		// update registers
		_IOREGS->HDMA1 = _sourceAddr >> 8;
		_IOREGS->HDMA2 = _sourceAddr & 0x00FF;
		_IOREGS->HDMA3 = _destAddr >> 8;
		_IOREGS->HDMA4 = _destAddr & 0x00FF;
		_IOREGS->HDMA5 = 0xFF;
	}

	// HBlanking DMA transfering only 16 bytes in HBLANK Period
	void			Dma::HDMA_Transfert ( void )
	{
		uint8_t				count = 0;

		// transfering
		while (count < 0x10)
		{
			_memory->vramBankPtr()[_destAddr + count] = _memory->getByteAt(_sourceAddr + count);
			count++;
		}

		// increments address
		_destAddr += 0x10;
		_sourceAddr += 0x10;

		// update registers
		_IOREGS->HDMA1 = _sourceAddr >> 8;
		_IOREGS->HDMA2 = _sourceAddr & 0x00FF;
		_IOREGS->HDMA3 = _destAddr >> 8;
		_IOREGS->HDMA4 = _destAddr & 0x00FF;

		// update line transfer count
		_IOREGS->HDMA5--;
		if (_IOREGS->HDMA5 == 0xFF)
			_HDMA = false;
	}

	/**************************************************************************/
	/******************************* SAVE STATE *******************************/
	/**************************************************************************/

	void			Dma::saveState ( std::fstream& file )
	{
		file.write((char*)&_HDMA, sizeof(_HDMA));
		file.write((char*)&_sourceAddr, sizeof(_sourceAddr));
		file.write((char*)&_destAddr, sizeof(_destAddr));
		file.write((char*)&_nBytes, sizeof(_nBytes));
	}

	void			Dma::loadState ( std::fstream& file )
	{
		file.read((char*)&_HDMA, sizeof(_HDMA));
		file.read((char*)&_sourceAddr, sizeof(_sourceAddr));
		file.read((char*)&_destAddr, sizeof(_destAddr));
		file.read((char*)&_nBytes, sizeof(_nBytes));
	}
}