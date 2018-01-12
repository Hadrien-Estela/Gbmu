// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Registers.class.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/20 11:23:30 by hestela           #+#    #+#             //
//   Updated: 2015/11/20 11:34:47 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef REGISTERS_CLASS_HPP
# define REGISTERS_CLASS_HPP

# include <iostream>
# include <fstream>

# include "Defines.hpp"

/*

8 8-Bit Registers: A B C D E F H L
2 16-Bit Registers: SP (stack pointer) & PC (program counter)
Can pairing 8-Bit registers to 16-Bit: AF BC DE HL

	+-------+-------+
	| HIGHT |  LOW  |
	+-------+-------+
	|   A   |   F   |
	|   B   |   C   |
	|   D   |   E   |
	|   H   |   L   |
	+-------+-------+
	|       SP      |
	|       PC      |
	+---------------+

 8-Bit register F is the flag register

	+---+---+---+---+---+---+---+---+
	| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
	+---+---+---+---+---+---+---+---+
	| Z | N | H | C | 0 | 0 | 0 | 0 |
	+---+---+---+---+---+---+---+---+
	/!\ low nibble of F register isn't writable /!\

Zero Flag (Z):
	This bit is set when the result of a math operation
	is zero or two values match when using the CP
	instruction

Subtract Flag (N):
	This bit is set if a subtraction was performed in the
	last math instruction.

Half Carry Flag (H):
	This bit is set if a carry occurred from the lower
	nibble in the last math operation.

Carry Flag (C):
	This bit is set if a carry occurred from the last
	math operation or if register A is the smaller value
	when executing the CP instruction

*/

namespace Gbmu
{

	class Registers
	{

		public:
			enum class Byte
			{
				A,
				B,
				C,
				D,
				E,
				H,
				L
			};

			enum class Word
			{
				AF,
				BC,
				DE,
				HL,
				SP,
				PC
			};

			enum class Flag
			{
				Z,
				N,
				H,
				C
			};

		private:
			enum
			{
				Low,
				Hight
			};

			union Register
			{
				uint8_t		byte[2];
				uint16_t	word;
			};

			Registers::Register		_af;
			Registers::Register		_bc;
			Registers::Register		_de;
			Registers::Register		_hl;
			Registers::Register		_sp;
			Registers::Register		_pc;

		public:
			Registers ( void );
			virtual ~Registers ( void );

			void					reset ( void );

			void					setRegister ( Registers::Byte r, uint8_t const& n );
			void					setRegister ( Registers::Word r, uint16_t  const& nn );
			void					setFlag ( Registers::Flag f, bool const& b );

			uint8_t const&			getRegister ( Registers::Byte r ) const;
			uint16_t const&			getRegister ( Registers::Word r ) const;
			bool					getFlag ( Registers::Flag f ) const;

			void					incPC ( uint8_t const& x );
			void					incSP ( uint8_t const& x );
			void					decSP ( uint8_t const& x );

			void					setA ( uint8_t const& n );
			void					setF ( uint8_t const& n );
			void					setB ( uint8_t const& n );
			void					setC ( uint8_t const& n );
			void					setD ( uint8_t const& n );
			void					setE ( uint8_t const& n );
			void					setH ( uint8_t const& n );
			void					setL ( uint8_t const& n );
			void					setAF ( uint16_t const& nn );
			void					setBC ( uint16_t const& nn );
			void					setDE ( uint16_t const& nn );
			void					setHL ( uint16_t const& nn );
			void					setSP ( uint16_t const& nn );
			void					setPC ( uint16_t const& nn );
			void					setFZ ( bool const& b );
			void					setFN ( bool const& b );
			void					setFH ( bool const& b );
			void					setFC ( bool const& b );

			uint8_t	const &			getA ( void ) const;
			uint8_t	const &	 		getF ( void ) const;
			uint8_t	const &	 		getB ( void ) const;
			uint8_t	const &	 		getC ( void ) const;
			uint8_t	const &	 		getD ( void ) const;
			uint8_t	const &	 		getE ( void ) const;
			uint8_t	const &	 		getH ( void ) const;
			uint8_t	const &	 		getL ( void ) const;
			uint16_t const &		getAF ( void ) const;
			uint16_t const &		getBC ( void ) const;
			uint16_t const &		getDE ( void ) const;
			uint16_t const &		getHL ( void ) const;
			uint16_t const &		getSP ( void ) const;
			uint16_t const &		getPC ( void ) const;
			bool		 			getFZ ( void ) const;
			bool		 			getFN ( void ) const;
			bool		 			getFH ( void ) const;
			bool		 			getFC ( void ) const;
			
			void					saveState ( std::fstream& file );
			void					loadState ( std::fstream& file );
	};

}

#else
	namespace Gbmu
	{
		class Registers;
	}
#endif // !REGISTERS_CLASS_HPP
