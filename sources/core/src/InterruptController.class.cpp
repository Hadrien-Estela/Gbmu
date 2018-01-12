// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   InterruptController.class.cpp                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/31 12:05:31 by hestela           #+#    #+#             //
//   Updated: 2015/12/31 12:05:32 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "InterruptController.class.hpp"

namespace Gbmu
{

	InterruptController::InterruptController ( Cpu* cpu ):
		_cpu(cpu),
		_IME(false),
		_IOREGS(_cpu->IO()->registers())
	{ }

	InterruptController::~InterruptController ( void )
	{ }

	void				InterruptController::reset ( void )
	{
		_IME = false;
	}

	bool				InterruptController::update ( void )
	{
		if (!interruptOccured()) 			// if we have interrupts pending, treat them.
			return (0);

		_IME = false; 						// IME is disable when an interrupt is occured
		_cpu->instructions()->PUSH_PC();	// Program counter is push on the stack

		// Check interrupt by priority
		// then jump at the corresponding address
		// and reset the corresponding BIT in register IF
		if (interrupt(Interrupt::V_BLANK))
		{
			_cpu->registers()->setPC(0x0040);
			setInterrupt(Interrupt::V_BLANK, false);
			return (true);
		}
		else if (interrupt(Interrupt::LCDC))
		{
			_cpu->registers()->setPC(0x0048);
			setInterrupt(Interrupt::LCDC, false);
			return (true);
		}
		else if (interrupt(Interrupt::TIMER_OVERFLOW))
		{
			_cpu->registers()->setPC(0x0050);
			setInterrupt(Interrupt::TIMER_OVERFLOW, false);
			return (true);
		}
		else if(interrupt(Interrupt::SERIAL_TRANSFER_COMPLETE))
		{
			_cpu->registers()->setPC(0x0058);
			setInterrupt(Interrupt::SERIAL_TRANSFER_COMPLETE, false);
			return (true);
		}
		else if (interrupt(Interrupt::TRANSITION_KEYPAD_MATRIX))
		{
			_cpu->registers()->setPC(0x0060);
			setInterrupt(Interrupt::TRANSITION_KEYPAD_MATRIX, false);
			return (true);
		}
		return (false);
	}

	void				InterruptController::setIME ( bool const& b )
	{
		_IME = b;
	}

	// Set the corresponding bit of an interrupt in IF
	void				InterruptController::setInterrupt ( InterruptController::Interrupt interrupt, bool const& b )
	{
		if (b)
			SETBIT(interrupt, _IOREGS->IF);
		else
			RESBIT(interrupt, _IOREGS->IF);
	}

	void				InterruptController::onWriteIF ( uint8_t const& value )
	{
		_IOREGS->IF = 0b11100000 | (value & 0b00011111);
	}

	void				InterruptController::onWriteIE ( uint8_t const& value )
	{
		_IOREGS->IE = value & 0b00011111;
	}

	/**************************************************************************/
	/**************************** PRIVATE METHODS *****************************/
	/**************************************************************************/

	bool const&			InterruptController::IME ( void ) const { return (_IME); }

	bool				InterruptController::interrupt ( InterruptController::Interrupt interrupt ) const
	{
		return (BIT_N(interrupt, _IOREGS->IF)); // return the correponding BIT of IF register
	}

	bool				InterruptController::interruptOccured ( void ) const
	{
		// if we have at least one coresonding BIT in register IE & IF
		if (_IOREGS->IE & _IOREGS->IF)
		{
			_cpu->setHALT(false); // if interrupt corresponding, reset halt
			if (!_IME)
				return (false);
			return (true);
		}

		return (false);
	}

	/**************************************************************************/
	/******************************* SAVE STATE *******************************/
	/**************************************************************************/

	void				InterruptController::saveState ( std::fstream& file )
	{
		file.write((char*)&_IME, sizeof(_IME));
	}

	void				InterruptController::loadState ( std::fstream& file )
	{
		file.read((char*)&_IME, sizeof(_IME));
	}


}
