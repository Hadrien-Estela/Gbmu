// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   KeyPad.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/06 14:29:11 by hestela           #+#    #+#             //
//   Updated: 2016/01/06 14:29:11 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "KeyPad.class.hpp"

namespace Gbmu
{

	KeyPad::KeyPad( Cpu* cpu ):
		_cpu(cpu),
		_IOREGS(NULL)
	{ }

	KeyPad::~KeyPad( void )
	{ }

	void			KeyPad::reset ( void )
	{
		bzero(_states, sizeof(_states));
		_IOREGS = _cpu->IO()->registers();
	}

	void			KeyPad::setKey ( Gbmu::IKeyPad::Key key, bool b )
	{
		_states[key] = b;
	}

	void			KeyPad::updateKeys ( void )
	{
		uint8_t			newP1 = updateInput(_IOREGS->P1);

		// check value changed and button pressed
		if (newP1 != _IOREGS->P1 && (newP1 & 0b00001111) != 0b00001111)
			_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::TRANSITION_KEYPAD_MATRIX, true);
		_IOREGS->P1 = newP1;
	}

	void			KeyPad::onWriteP1 ( uint8_t value )
	{
		value = (value & 0b11110000) | (_IOREGS->P1 & 0b00001111);
		// Update buttons in P1
		value = updateInput(value);
		// if value has changed and buttons ares sets throw an interrupt
		if (value != _IOREGS->P1 && (value & 0b00001111) != 0b00001111)
			_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::TRANSITION_KEYPAD_MATRIX, true);
		_IOREGS->P1 = value;
	}

	/**************************************************************************/
	/**************************** PRIVATE METHODS *****************************/
	/**************************************************************************/

	uint8_t			KeyPad::updateInput ( uint8_t value )
	{
		// keep P14 & P15
		value = value & 0b11110000;

		// if P15 is active (0 value at bit 5)
		if (!BIT_5(value))
		{
			// set all buttons (0 mean enable)
			value |= (!_states[Start] << 3) | (!_states[Select] << 2) | (!_states[B] << 1) | !_states[A];
			return (value);
		}

		// if P14 is active (0 value at bit 4)
		if (!BIT_4(value))
		{
			// set all buttons (0 mean enable)
			value |= (!_states[Down] << 3) | (!_states[Up] << 2) | (!_states[Left] << 1) | !_states[Right];
			return (value);
		}

		// else fill all Bits
		return (0b11111111);
	}

}