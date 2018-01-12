// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LinkController.class.hpp                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/16 09:49:20 by hestela           #+#    #+#             //
//   Updated: 2016/01/16 09:49:20 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LINKCONTROLLER_CLASS_HPP
# define LINKCONTROLLER_CLASS_HPP

# include <iostream>
# include <fstream>

# include "Cpu.class.hpp"
# include "SerialIO.class.hpp"
# include "Defines.hpp"

/*

	Transfer is initiated by setting the Transfer Start Flag.
	This bit may be read and is automatically set to 0 at the end of Transfer.
	Transmitting and receiving serial data is done simultaneously.
	The received data is automatically stored in SB.

************************* USED REGISTERS ************************

	-- SB Register (Serial transfer data) [0xFF01]
		8 Bits of data to be read/written

	-- SC Register (SIO control) [0xFF02]
		BIT 7: Transfer Start Flag
				0: Non transfer
				1: Start transfer

		BIT 0: Shift Clock
				0: External Clock (500KHz Max.)
				1: Internal Clock (8192Hz)

*/

namespace Gbmu
{

	class LinkController
	{

		private:
			Cpu*							_cpu;		// get a pointer to the Cpu ( the parent )
			struct SerialIO::IORegisters*	_IOREGS;	// get a pointer to the IO registers
			size_t							_cycles;	// cycle counter for Serail transfert
			int8_t							_serialBit; // current transfered bit

		public:
			LinkController( Cpu* cpu );
			virtual ~LinkController( void );
			
			void			reset ( void );
			void			update ( uint8_t const& cycles );

			void			saveState ( std::fstream& file );
			void			loadState ( std::fstream& file );
	};

}

#else
	namespace Gbmu
	{
		class LinkController;
	}
#endif // !LINKCONTROLLER_CLASS_HPP
