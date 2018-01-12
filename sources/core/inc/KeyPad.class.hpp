// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   KeyPad.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/06 14:29:02 by hestela           #+#    #+#             //
//   Updated: 2016/01/06 14:29:03 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef KEYPAD_CLASS_HPP
# define KEYPAD_CLASS_HPP

# include <iostream>

# include "IKeyPad.class.hpp"
# include "Cpu.class.hpp"

/*
	-- P1 Register (Register for reading joy pad info) [0xFF00]
	Bit 5: P15 out port
	Bit 4: P14 out port
	Bit 3: P13 in port
	Bit 2: P12 in port
	Bit 1: P11 in port
	Bit 0: P10 in port
 	
		   P14		   P15
			|			|
	P10 ----o-RIGHT-----o-A
			|			|
	P11	----o-LEFT------o-B
			|			|
	P12	----o-UP--------o-SELECT
			|			|
	P13	----o-DOWN------o-START
			|			|
			v 			v 	// if button is pressed, power out here

*/

namespace Gbmu
{

	class KeyPad: public IKeyPad
	{
		private:
			Cpu*							_cpu; 		// get a pointer to Cpu ( the parent )
			struct SerialIO::IORegisters*	_IOREGS; 	// get a pointer to the IO registers
			bool							_states[8];	// states of buttons ( off / on )

		public:
			KeyPad( Cpu* cpu );
			virtual ~KeyPad( void );
			
			void			reset ( void );

			void			setKey ( Gbmu::IKeyPad::Key key, bool b );
			void			updateKeys ( void );

			void			onWriteP1 ( uint8_t value );

		private:
			uint8_t			updateInput ( uint8_t value );

	};

}

#else
	namespace Gbmu
	{
		class KeyPad;
	}
#endif // !KEYPAD_CLASS_HPP
