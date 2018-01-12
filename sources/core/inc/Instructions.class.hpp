// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Instructions.class.hpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/21 22:35:26 by hestela           #+#    #+#             //
//   Updated: 2015/11/21 22:36:47 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef INSTRUCTIONS_CLASS_HPP
# define INSTRUCTIONS_CLASS_HPP

# include <iostream>

# include "Cpu.class.hpp"
# include "Registers.class.hpp"
# include "Memory.class.hpp"
# include "Defines.hpp"

/*
	Instructions returns the number of cycles
*/

namespace Gbmu
{

	class Instructions
	{

		private:
			Cpu*				_cpu;	// get a pointer to the Cpu ( the parent )

		public:
			Instructions ( Cpu* cpu );
			virtual ~Instructions ( void );

			uint8_t				doInstruction ( uint8_t const& opcode );
			void				PUSH_PC ( void );

		private:
			uint8_t				doCBInstruction ( void );

			// 8Bits LOAD
			uint8_t				LD_NN_N ( Registers* regs, Registers::Byte const& r, Memory* mem );
			uint8_t				LD_R1_R2 ( Registers* regs, Registers::Byte const& r1, Registers::Byte const& r2 );
			uint8_t				LD_R1_R2 ( Registers* regs, Registers::Byte const& r1, Registers::Word const& r2, Memory* mem );
			uint8_t				LD_R1_R2 ( Registers* regs, Registers::Word const& r1, Registers::Byte const& r2, Memory* mem );
			uint8_t 			LD_R1_R2 ( Registers* regs, Registers::Word const& r1, Memory* mem );
			uint8_t 			LD_A_N ( Registers* regs, Memory* mem );
			uint8_t 			LD_N_A ( Registers* regs, Memory* mem );
			uint8_t				LD_A_C ( Registers* regs, Memory* mem );
			uint8_t				LD_C_A ( Registers* regs, Memory* mem );
			uint8_t				LDD_A_HL ( Registers* regs, Memory* mem );
			uint8_t				LDD_HL_A ( Registers* regs, Memory* mem );
			uint8_t				LDI_A_HL ( Registers* regs, Memory* mem );
			uint8_t				LDI_HL_A ( Registers* regs, Memory* mem );
			uint8_t				LDH_N_A ( Registers* regs, Memory* mem );
			uint8_t				LDH_A_N ( Registers* regs, Memory* mem );
	
			// 16Bits LOAD
			uint8_t				LD_N_NN ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				LD_SP_HL ( Registers* regs );
			uint8_t				LDHL_SP_N ( Registers* regs, Memory* mem );
			uint8_t				LD_NN_SP ( Registers* regs, Memory* mem );
			uint8_t				PUSH ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				POP ( Registers* regs, Registers::Word const& r, Memory* mem );
	
			// 8Bits ALU
			uint8_t				ADD ( Registers* regs, Registers::Byte const& r );
			uint8_t				ADD ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				ADD ( Registers* regs, Memory* mem );
			uint8_t				ADC ( Registers* regs, Registers::Byte const& r );
			uint8_t				ADC ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				ADC ( Registers* regs, Memory* mem );
			uint8_t				SUB ( Registers* regs, Registers::Byte const& r );
			uint8_t				SUB ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				SUB ( Registers* regs, Memory* mem );
			uint8_t				SBC ( Registers* regs, Registers::Byte const& r );
			uint8_t				SBC ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				SBC ( Registers* regs, Memory* mem );
			uint8_t				AND ( Registers* regs, Registers::Byte const& r );
			uint8_t				AND ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				AND ( Registers* regs, Memory* mem );
			uint8_t				OR ( Registers* regs, Registers::Byte const& r );
			uint8_t				OR ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				OR ( Registers* regs, Memory* mem );
			uint8_t				XOR ( Registers* regs, Registers::Byte const& r );
			uint8_t				XOR ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				XOR ( Registers* regs, Memory* mem );
			uint8_t				CP ( Registers* regs, Registers::Byte const& r );
			uint8_t				CP ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				CP ( Registers* regs, Memory* mem );
			uint8_t				INC_N ( Registers* regs, Registers::Byte const& r );
			uint8_t				INC_N ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				DEC_N ( Registers* regs, Registers::Byte const& r );
			uint8_t				DEC_N ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				DAA ( Registers* regs );
			uint8_t				CPL ( Registers* regs );
			uint8_t				CCF ( Registers* regs );
			uint8_t				SCF ( Registers* regs );

			// 16Bits ALU
			uint8_t				ADD_HL_N ( Registers* regs, Registers::Word const& r );
			uint8_t				ADD_SP_N ( Registers* regs, Memory* mem );
			uint8_t				INC_NN ( Registers* regs, Registers::Word const& r );
			uint8_t				DEC_NN ( Registers* regs, Registers::Word const& r );

			// Misc / Control
			uint8_t				NOP ( Registers* regs );
			uint8_t				HALT ( Registers* regs );
			uint8_t				STOP ( Registers* regs );
			uint8_t				DI ( Registers* regs );
			uint8_t				EI ( Registers* regs );
			uint8_t				JP ( Registers* regs, Memory* mem );
			uint8_t				JP_Z ( Registers* regs, Memory* mem );
			uint8_t				JP_NZ ( Registers* regs, Memory* mem );
			uint8_t				JP_C ( Registers* regs, Memory* mem );
			uint8_t				JP_NC ( Registers* regs, Memory* mem );
			uint8_t				JP_HL ( Registers* regs, Memory* mem );
			uint8_t				JR ( Registers* regs, Memory* mem );
			uint8_t				JR_Z ( Registers* regs, Memory* mem );
			uint8_t				JR_NZ ( Registers* regs, Memory* mem );
			uint8_t				JR_C ( Registers* regs, Memory* mem );
			uint8_t				JR_NC ( Registers* regs, Memory* mem );
			uint8_t				CALL ( Registers* regs, Memory* mem );
			uint8_t				CALL_Z ( Registers* regs, Memory* mem );
			uint8_t				CALL_NZ ( Registers* regs, Memory* mem );
			uint8_t				CALL_C ( Registers* regs, Memory* mem );
			uint8_t				CALL_NC ( Registers* regs, Memory* mem );
			uint8_t				RST ( Registers* regs, Memory* mem, uint16_t const& addr );
			uint8_t				RET ( Registers* regs, Memory* mem );
			uint8_t				RET_Z ( Registers* regs, Memory* mem );
			uint8_t				RET_NZ ( Registers* regs, Memory* mem );
			uint8_t				RET_C ( Registers* regs, Memory* mem );
			uint8_t				RET_NC ( Registers* regs, Memory* mem );
			uint8_t				RETI ( Registers* regs, Memory* mem );

			// Bit operation
			uint8_t				RLCA ( Registers* regs );
			uint8_t				RLA ( Registers* regs );
			uint8_t				RRCA ( Registers* regs );
			uint8_t				RRA ( Registers* regs );

			// CB bit operations
			uint8_t				SWAP ( Registers* regs, Registers::Byte const& r );
			uint8_t				SWAP ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				RLC ( Registers* regs, Registers::Byte const& r );
			uint8_t				RLC ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				RL ( Registers* regs, Registers::Byte const& r );
			uint8_t				RL ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				RRC ( Registers* regs, Registers::Byte const& r );
			uint8_t				RRC ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				RR ( Registers* regs, Registers::Byte const& r );
			uint8_t				RR ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				SLA ( Registers* regs, Registers::Byte const& r );
			uint8_t				SLA ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				SRA ( Registers* regs, Registers::Byte const& r );
			uint8_t				SRA ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				SRL ( Registers* regs, Registers::Byte const& r );
			uint8_t				SRL ( Registers* regs, Registers::Word const& r, Memory* mem );
			uint8_t				BIT ( Registers* regs, uint8_t const& b, Registers::Byte const& r );
			uint8_t				BIT ( Registers* regs, uint8_t const& b, Registers::Word const& r, Memory* mem );
			uint8_t				RES ( Registers* regs, uint8_t const& b, Registers::Byte const& r );
			uint8_t				RES ( Registers* regs, uint8_t const& b, Registers::Word const& r, Memory* mem );
			uint8_t				SET ( Registers* regs, uint8_t const& b, Registers::Byte const& r );
			uint8_t				SET ( Registers* regs, uint8_t const& b, Registers::Word const& r, Memory* mem );
	};

}

#else
	namespace Gbmu
	{
		class Instructions;
	}
#endif // !INSTRUCTIONS_CLASS_HPP
