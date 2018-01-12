// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   InterruptController.class.hpp                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/31 12:05:15 by hestela           #+#    #+#             //
//   Updated: 2015/12/31 12:05:20 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef INTERRUPTCONTROLLER_CLASS_HPP
# define INTERRUPTCONTROLLER_CLASS_HPP

# include <iostream>
# include <fstream>

# include "Cpu.class.hpp"
# include "SerialIO.class.hpp"
# include "Defines.hpp"

/*

************************* INTERRUPT PROCEDURE *********************************

	1. When an interrupt is generated, the IF flag will be set.
	2. If the IME flag is set &the corresponding IE flag is set, the following
	   steps are performed.
	3. Reset the IME flag and prevent all interrupts.
	4. The PC(programcounter) is pushed onto the stack.
	5. Jump to the starting address of the interrupt.
	6. Resetting of the IF register, which was the cause of the interrupt

	The interrupt procedure Take 20 Cycles for DI (4) and PUSH (16) (Jump is not the
	JP nn instruction but a simple register set)

***************************** USED REGISTERS **********************************

	-- IF Register (Interruption Flag) [0xFF0F]						|	jump addr
		BIT 4: Transition from High to Low of Pin number P10- P13	|	0x0060
		BIT 3: Serial I/O transfer complete 						|	0x0058
		BIT 2: Timer Overflow 										|	0x0050
		BIT 1: LCDC(see STAT) 										|	0x0048
		BIT 0: V-Blank 												|	0x0040
		***** Priority order from lowest signifiant BIT *****

	-- IE Register (Interruption Enable) [0xFFFF]
		Same as the IF register.
		value 0 = disable | value 1 = enable

*/

namespace Gbmu
{
	
	class InterruptController
	{

		public:
			enum Interrupt 	// Index of BIT in register IF & IE
			{
				V_BLANK,
				LCDC,
				TIMER_OVERFLOW,
				SERIAL_TRANSFER_COMPLETE,
				TRANSITION_KEYPAD_MATRIX
			};

		private:
			Cpu*							_cpu;		// get a pointer to the Cpu ( the parent )
			bool							_IME;		// interrupt master enable Flag
			struct SerialIO::IORegisters*	_IOREGS;	// get a pointer to the IO registers


		public:
			InterruptController ( Cpu* cpu );
			virtual ~InterruptController ( void );

			void			reset ( void );
			bool			update ( void );

			void			setIME ( bool const& b );
			void			setInterrupt ( InterruptController::Interrupt interrupt, bool const& b );

			void			onWriteIF ( uint8_t const& value );
			void			onWriteIE ( uint8_t const& value );

			void			saveState ( std::fstream& file );
			void			loadState ( std::fstream& file );

		private:
			bool const&		IME ( void ) const;
			bool			interrupt ( InterruptController::Interrupt interrupt ) const;
			bool			interruptOccured ( void ) const;
	};

}

#else
	namespace Gbmu
	{
		class InterruptController;
	}
#endif // !INTERRUPTCONTROLLER_CLASS_HPP
