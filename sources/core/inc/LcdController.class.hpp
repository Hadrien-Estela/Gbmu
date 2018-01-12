// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LcdController.class.hpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/31 15:19:40 by hestela           #+#    #+#             //
//   Updated: 2015/12/31 15:19:40 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LCDCONTROLLER_CLASS_HPP
# define LCDCONTROLLER_CLASS_HPP

# include <iostream>

# include "Cpu.class.hpp"
# include "SerialIO.class.hpp"
# include "LcdDriver.class.hpp"
# include "Defines.hpp"

/*

************************* USED REGISTERS ************************

															0		 |		1		
	-- LCDC Register (LCDControl) [0xFF40]
		Bit 7: LCDControl Operation					  no operation 	 |	 operation

	-- STAT Register (LCDC Status) [0xFF41]
		Bit 6: LYC = LY Coincidence interrupt			 disable	 |     enable
		Bit 5: Mode 10 interrupt						 disable	 |     enable
		Bit 4: Mode 01 interrupt						 disable	 |     enable
		Bit 3: Mode 00 interrupt						 disable	 |     enable
		Bit 2: Coincidence Flag ( LY = LYC ) 			   false	 | 	    true
		Bit 1-0: Mode Flag (see enum Mode)

	-- LY Register (LCDC Y-Coordinate) [0xFF44]
		indicates the vertical line to which the present data is transferred to the LCD Driver
		The values between 144 and 153 indicate the V-Blank period.
		Writing any value will reset the counter.

	-- LYC Register (LY Conmpare) [0xFF45]
		The LYC compares itself with the LY.
		If the values are the same it causes the STAT to set the coincident flag.

*********************** FRAME PROCEDURE **************************

			<------------- 172 cycles ---------><- 204 ->
			0								   160
		  0 +-----------------------------------+-------+	^
			|									|		|	|
			|									|		|	|
			|									|	H	|	|
			|									|	B	|	|
			|				VISIBLE				|	L	|	7
			|				SCREEN				|	A	|	0
	current	|									|	N	|	2 cycles
	 line ->|...................................|	K	|	2
	 (LY)	|									|		|	4
			|									|		|	|
		144	+-----------------------------------+-------+	|
			|				   VBLANK					|	|
			|				  							|	|
		153	+-------------------------------------------+	v
			<-------------- 456 cylces ----------------->

*/

namespace Gbmu
{

	class LcdController
	{

		public:
			enum Mode // enum for Mode Flag (BITS 01 in Register STAT)
			{
				Mode_HBLANK   = 0b00,
				Mode_VBLANK   = 0b01,
				Mode_OAMRAM   = 0b10,
				Mode_SCANLINE = 0b11
			};

			enum Cycles // enum for machine cycles by modes
			{
				Cycles_HBLANK   = 204,
				Cycles_VBLANK   = 456,
				Cycles_OAMRAM   = 80,
				Cycles_SCANLINE = 172
			};

		private:
			Cpu*							_cpu; 		// get a pointer to the Cpu ( the parent )
			struct SerialIO::IORegisters*	_IOREGS;	// get a pointer to the IO registers 
			size_t							_cycles;	// cycle counter for LCD Controller
			LcdDriver*						_lcdDriver;	// LcdDriver (transferring data to lcd)

		public:
			LcdController ( Cpu* cpu );
			virtual ~LcdController ( void );

			void							reset ( void );
			void							update ( uint8_t const& cycles );

			void							onWriteLY ( void );
			void							onWriteLYC ( uint8_t const& value );
			void							onWriteLCDC ( uint8_t const& value );
			void							onWriteSTAT ( uint8_t const& value );

			void							saveState ( std::fstream& file );
			void							loadState ( std::fstream& file );

			LcdDriver*						lcdDriver ( void ) const;

		private:
			void							updateStatus ( void );
			void							HBlankMode ( void );
			void							VBlankMode ( void );
			void							OAMSearchMode ( void );
			void							TransferingMode ( void );

			bool							onOperation ( void ) const;
			LcdController::Mode				mode ( void ) const;
			void							setMode ( LcdController::Mode mode );
			bool							modeInterruptEnable ( LcdController::Mode mode ) const;
			void							LYC_LY_compare ( void );
			void							endOfFrame ( void );
	};

}

#else
	namespace Gbmu
	{
		class LcdController;
	}
#endif // !LCDCONTROLLER_CLASS_HPP
