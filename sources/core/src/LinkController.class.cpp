// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LinkController.class.cpp                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/16 09:49:33 by hestela           #+#    #+#             //
//   Updated: 2016/01/16 09:49:33 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "LinkController.class.hpp"

namespace Gbmu
{

	LinkController::LinkController ( Cpu* cpu ):
		_cpu(cpu),
		_IOREGS(_cpu->IO()->registers()),
		_cycles(0)
	{ }

	LinkController::~LinkController ( void )
	{ }

	void		LinkController::reset ( void )
	{
		_cycles = 0;
		_serialBit = -1;
	}

	void		LinkController::update ( uint8_t const& cycles )
	{
		if (BIT_7(_IOREGS->SC) && BIT_0(_IOREGS->SC))
		{
	        _cycles += cycles;
	        
			if (_serialBit < 0)
			{
				_serialBit = 0;
				_cycles = 0;
				return ;
			}
			if (_cycles >= 0x200)
			{
				if (_serialBit > 7)
				{
					_IOREGS->SC &= 0b01111111;
					_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::SERIAL_TRANSFER_COMPLETE, true);
					_serialBit = -1;
					return ;
				}
				
				_IOREGS->SB = _IOREGS->SB << 1;
				_IOREGS->SB |= 0x01;
				
				_cycles -= 0x200;
				_serialBit++;
			}
		}
	}

	/**************************************************************************/
	/******************************* SAVE STATE *******************************/
	/**************************************************************************/

	void		LinkController::saveState ( std::fstream& file )
	{
		file.write((char*)&_cycles, sizeof(_cycles));
		file.write((char*)&_serialBit, sizeof(_serialBit));
	}

	void		LinkController::loadState ( std::fstream& file )
	{
		file.read((char*)&_cycles, sizeof(_cycles));
		file.read((char*)&_serialBit, sizeof(_serialBit));
	}

}


