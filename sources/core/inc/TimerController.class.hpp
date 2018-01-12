// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TimerController.class.hpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/01 14:06:59 by hestela           #+#    #+#             //
//   Updated: 2016/01/01 14:06:59 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TIMERCONTROLLER_CLASS_HPP
# define TIMERCONTROLLER_CLASS_HPP

# include <iostream>
# include <fstream>

# include "Cpu.class.hpp"
# include "SerialIO.class.hpp"
# include "Defines.hpp"

/*

************************* USED REGISTERS ************************

	-- DIV Register (Divider Register) [0xFF04]
		This register is incremented 16384 (~16779 on SGB) times a second.
		Writing any value sets it to $00.

	-- TIMA Register (Timer counter) [0xFF05]
		This timer is incremented by a clock frequency specified by the TAC register ($FF07).
		The timer generates an interrupt when it overflows.

	-- TMA Register (Timer Modulo) [0xFF06]
		When the TIMA overflows, this data will be loaded.

	-- TAC Register (Timer Control) [0xFF07]
		BIT    2: Timer Stop. ( 0 = Stop | 1 = start )
		BITS 0-1: Input Clock Select
					00: 4. 096 KHz
					01: 262. 144 Khz
					10: 65. 536 KHz
					11: 16. 384 KHz

*/

namespace Gbmu
{

	class TimerController
	{

		private:
			enum InputClock // values of Bits 01 of TAC register in cycles
			{
				Clock_00 = 1024,
				Clock_01 = 16,
				Clock_10 = 64,
				Clock_11 = 256
			};

		private:
			Cpu*							_cpu;			// get a pointer to the Cpu ( the parent )
			struct SerialIO::IORegisters*	_IOREGS;		// get a pointer to the IO registers
			size_t							_cyclesTIMA;	// Cycle counter for TIMA
			size_t							_cyclesDIV;		// Cycle counter for DIV

		public:
			TimerController( Cpu* cpu );
			virtual ~TimerController( void );
			
			void							reset ( void );
			void							update ( uint8_t const& cycles );

			void							onWriteDIV ( void );
			void							onWriteTAC ( uint8_t const& value );

			void							saveState ( std::fstream& file );
			void							loadState ( std::fstream& file );

		private:
			bool							timerStarted ( void ) const;
			size_t							InputClock ( void ) const;
	};

}

#else
	namespace Gbmu
	{
		class TimerController;
	}
#endif // !TIMERCONTROLLER_CLASS_HPP
