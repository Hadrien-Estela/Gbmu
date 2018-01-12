// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TimerController.class.cpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/01 14:07:24 by hestela           #+#    #+#             //
//   Updated: 2016/01/01 14:07:25 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "TimerController.class.hpp"

namespace Gbmu
{

	TimerController::TimerController( Cpu* cpu ):
		_cpu(cpu),
		_IOREGS(_cpu->IO()->registers()),
		_cyclesTIMA(0),
		_cyclesDIV(0)
	{ }

	TimerController::~TimerController( void )
	{ }

	void					TimerController::reset ( void )
	{
		_cyclesTIMA = 0;
		_cyclesDIV = 0;
	}

	void					TimerController::update ( uint8_t const& cycles )
	{
		if (timerStarted())
		{
			_cyclesTIMA += cycles;
			while (_cyclesTIMA >= InputClock())
			{
				if (_IOREGS->TIMA == 0xFF)
				{
					_IOREGS->TIMA = _IOREGS->TMA;
					_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::TIMER_OVERFLOW, true);
				}
				else
					_IOREGS->TIMA++;
				
				_cyclesTIMA -= InputClock();
			}
		}

		_cyclesDIV += cycles;
		while (_cyclesDIV >= 0xFF)
		{
			_IOREGS->DIV++;
			_cyclesDIV -= 0x100;
		}
	}

	void						TimerController::onWriteDIV ( void )
	{
		_IOREGS->DIV = 0;
	}

	void						TimerController::onWriteTAC ( uint8_t const& value )
	{
		uint8_t 	newClockTiming = BITS_0_1(value);
		uint8_t 	oldClockTiming = BITS_0_1(_IOREGS->TAC);
		bool		timerDisable = !BIT_2(value);

		// if input clock changed or timer is disable
		if (newClockTiming != oldClockTiming || timerDisable)
		{
			_cyclesTIMA = 0;
			_IOREGS->TIMA = _IOREGS->TMA;
		}
		_IOREGS->TAC = value;
	}

	/**************************************************************************/
	/**************************** PRIVATE METHODS *****************************/
	/**************************************************************************/

	bool					TimerController::timerStarted ( void ) const
	{
		return (BIT_2(_IOREGS->TAC));
	}

	size_t					TimerController::InputClock ( void ) const
	{
		uint8_t				clock = BITS_0_1(_IOREGS->TAC);

		switch (clock)
		{
			case 0b00:
				return (InputClock::Clock_00);
				break;
			case 0b01:
				return (InputClock::Clock_01);
				break;
			case 0b10:
				return (InputClock::Clock_10);
				break;
			case 0b11:
				return (InputClock::Clock_11);
				break;
		}
		return (0);
	}

	/**************************************************************************/
	/******************************* SAVE STATE *******************************/
	/**************************************************************************/

	void					TimerController::saveState ( std::fstream& file )
	{
		file.write((char*)&_cyclesTIMA, sizeof(_cyclesTIMA));
		file.write((char*)&_cyclesDIV, sizeof(_cyclesDIV));
	}

	void					TimerController::loadState ( std::fstream& file )
	{
		file.read((char*)&_cyclesTIMA, sizeof(_cyclesTIMA));
		file.read((char*)&_cyclesDIV, sizeof(_cyclesDIV));
	}

}