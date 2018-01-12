// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Instructions.class.cpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/22 16:00:31 by hestela           #+#    #+#             //
//   Updated: 2015/11/22 16:00:31 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Instructions.class.hpp"

namespace Gbmu
{

	Instructions::Instructions ( Cpu* cpu ):
		_cpu(cpu)
	{ }

	Instructions::~Instructions ( void )
	{ }

	uint8_t				Instructions::doInstruction ( uint8_t const& opcode )
	{
		switch (opcode)
		{
			case 0x00: return NOP(_cpu->registers());
			case 0x01: return LD_N_NN(_cpu->registers(), Registers::Word::BC, _cpu->memory());
			case 0x02: return LD_R1_R2(_cpu->registers(), Registers::Word::BC, Registers::Byte::A, _cpu->memory());
			case 0x03: return INC_NN(_cpu->registers(), Registers::Word::BC);
			case 0x04: return INC_N(_cpu->registers(), Registers::Byte::B);
			case 0x05: return DEC_N(_cpu->registers(), Registers::Byte::B);
			case 0x06: return LD_NN_N(_cpu->registers(), Registers::Byte::B, _cpu->memory());
			case 0x07: return RLCA(_cpu->registers());
			case 0x08: return LD_NN_SP(_cpu->registers(), _cpu->memory());
			case 0x09: return ADD_HL_N(_cpu->registers(), Registers::Word::BC);
			case 0x0A: return LD_R1_R2(_cpu->registers(), Registers::Byte::A, Registers::Word::BC, _cpu->memory());
			case 0x0B: return DEC_NN(_cpu->registers(), Registers::Word::BC);
			case 0x0C: return INC_N(_cpu->registers(), Registers::Byte::C);
			case 0x0D: return DEC_N(_cpu->registers(), Registers::Byte::C);
			case 0x0E: return LD_NN_N(_cpu->registers(), Registers::Byte::C, _cpu->memory());
			case 0x0F: return RRCA(_cpu->registers());
			
			case 0x10: return STOP(_cpu->registers());
			case 0x11: return LD_N_NN(_cpu->registers(), Registers::Word::DE, _cpu->memory());
			case 0x12: return LD_R1_R2(_cpu->registers(), Registers::Word::DE, Registers::Byte::A, _cpu->memory());
			case 0x13: return INC_NN(_cpu->registers(), Registers::Word::DE);
			case 0x14: return INC_N(_cpu->registers(), Registers::Byte::D);
			case 0x15: return DEC_N(_cpu->registers(), Registers::Byte::D);
			case 0x16: return LD_NN_N(_cpu->registers(), Registers::Byte::D, _cpu->memory());
			case 0x17: return RLA(_cpu->registers());
			case 0x18: return JR(_cpu->registers(), _cpu->memory());
			case 0x19: return ADD_HL_N(_cpu->registers(), Registers::Word::DE);
			case 0x1A: return LD_R1_R2(_cpu->registers(), Registers::Byte::A, Registers::Word::DE, _cpu->memory());
			case 0x1B: return DEC_NN(_cpu->registers(), Registers::Word::DE);
			case 0x1C: return INC_N(_cpu->registers(), Registers::Byte::E);
			case 0x1D: return DEC_N(_cpu->registers(), Registers::Byte::E);
			case 0x1E: return LD_NN_N(_cpu->registers(), Registers::Byte::E, _cpu->memory());
			case 0x1F: return RRA(_cpu->registers());

			case 0x20: return JR_NZ(_cpu->registers(), _cpu->memory());
			case 0x21: return LD_N_NN(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x22: return LDI_HL_A(_cpu->registers(), _cpu->memory());
			case 0x23: return INC_NN(_cpu->registers(), Registers::Word::HL);
			case 0x24: return INC_N(_cpu->registers(), Registers::Byte::H);
			case 0x25: return DEC_N(_cpu->registers(), Registers::Byte::H);
			case 0x26: return LD_NN_N(_cpu->registers(), Registers::Byte::H, _cpu->memory());
			case 0x27: return DAA(_cpu->registers());
			case 0x28: return JR_Z(_cpu->registers(), _cpu->memory());
			case 0x29: return ADD_HL_N(_cpu->registers(), Registers::Word::HL);
			case 0x2A: return LDI_A_HL(_cpu->registers(), _cpu->memory());
			case 0x2B: return DEC_NN(_cpu->registers(), Registers::Word::HL);
			case 0x2C: return INC_N(_cpu->registers(), Registers::Byte::L);
			case 0x2D: return DEC_N(_cpu->registers(), Registers::Byte::L);
			case 0x2E: return LD_NN_N(_cpu->registers(), Registers::Byte::L, _cpu->memory());
			case 0x2F: return CPL(_cpu->registers());

			case 0x30: return JR_NC(_cpu->registers(), _cpu->memory());
			case 0x31: return LD_N_NN(_cpu->registers(), Registers::Word::SP, _cpu->memory());
			case 0x32: return LDD_HL_A(_cpu->registers(), _cpu->memory());
			case 0x33: return INC_NN(_cpu->registers(), Registers::Word::SP);
			case 0x34: return INC_N(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x35: return DEC_N(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x36: return LD_R1_R2(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x37: return SCF(_cpu->registers());
			case 0x38: return JR_C(_cpu->registers(), _cpu->memory());
			case 0x39: return ADD_HL_N(_cpu->registers(), Registers::Word::SP);
			case 0x3A: return LDD_A_HL(_cpu->registers(), _cpu->memory());
			case 0x3B: return DEC_NN(_cpu->registers(), Registers::Word::SP);
			case 0x3C: return INC_N(_cpu->registers(), Registers::Byte::A);
			case 0x3D: return DEC_N(_cpu->registers(), Registers::Byte::A);
			case 0x3E: return LD_NN_N(_cpu->registers(), Registers::Byte::A, _cpu->memory());
			case 0x3F: return CCF(_cpu->registers());

			case 0x40: return LD_R1_R2(_cpu->registers(), Registers::Byte::B, Registers::Byte::B);
			case 0x41: return LD_R1_R2(_cpu->registers(), Registers::Byte::B, Registers::Byte::C);
			case 0x42: return LD_R1_R2(_cpu->registers(), Registers::Byte::B, Registers::Byte::D);
			case 0x43: return LD_R1_R2(_cpu->registers(), Registers::Byte::B, Registers::Byte::E);
			case 0x44: return LD_R1_R2(_cpu->registers(), Registers::Byte::B, Registers::Byte::H);
			case 0x45: return LD_R1_R2(_cpu->registers(), Registers::Byte::B, Registers::Byte::L);
			case 0x46: return LD_R1_R2(_cpu->registers(), Registers::Byte::B, Registers::Word::HL, _cpu->memory());
			case 0x47: return LD_R1_R2(_cpu->registers(), Registers::Byte::B, Registers::Byte::A);
			case 0x48: return LD_R1_R2(_cpu->registers(), Registers::Byte::C, Registers::Byte::B);
			case 0x49: return LD_R1_R2(_cpu->registers(), Registers::Byte::C, Registers::Byte::C);
			case 0x4A: return LD_R1_R2(_cpu->registers(), Registers::Byte::C, Registers::Byte::D);
			case 0x4B: return LD_R1_R2(_cpu->registers(), Registers::Byte::C, Registers::Byte::E);
			case 0x4C: return LD_R1_R2(_cpu->registers(), Registers::Byte::C, Registers::Byte::H);
			case 0x4D: return LD_R1_R2(_cpu->registers(), Registers::Byte::C, Registers::Byte::L);
			case 0x4E: return LD_R1_R2(_cpu->registers(), Registers::Byte::C, Registers::Word::HL, _cpu->memory());
			case 0x4F: return LD_R1_R2(_cpu->registers(), Registers::Byte::C, Registers::Byte::A);

			case 0x50: return LD_R1_R2(_cpu->registers(), Registers::Byte::D, Registers::Byte::B);
			case 0x51: return LD_R1_R2(_cpu->registers(), Registers::Byte::D, Registers::Byte::C);
			case 0x52: return LD_R1_R2(_cpu->registers(), Registers::Byte::D, Registers::Byte::D);
			case 0x53: return LD_R1_R2(_cpu->registers(), Registers::Byte::D, Registers::Byte::E);
			case 0x54: return LD_R1_R2(_cpu->registers(), Registers::Byte::D, Registers::Byte::H);
			case 0x55: return LD_R1_R2(_cpu->registers(), Registers::Byte::D, Registers::Byte::L);
			case 0x56: return LD_R1_R2(_cpu->registers(), Registers::Byte::D, Registers::Word::HL, _cpu->memory());
			case 0x57: return LD_R1_R2(_cpu->registers(), Registers::Byte::D, Registers::Byte::A);
			case 0x58: return LD_R1_R2(_cpu->registers(), Registers::Byte::E, Registers::Byte::B);
			case 0x59: return LD_R1_R2(_cpu->registers(), Registers::Byte::E, Registers::Byte::C);
			case 0x5A: return LD_R1_R2(_cpu->registers(), Registers::Byte::E, Registers::Byte::D);
			case 0x5B: return LD_R1_R2(_cpu->registers(), Registers::Byte::E, Registers::Byte::E);
			case 0x5C: return LD_R1_R2(_cpu->registers(), Registers::Byte::E, Registers::Byte::H);
			case 0x5D: return LD_R1_R2(_cpu->registers(), Registers::Byte::E, Registers::Byte::L);
			case 0x5E: return LD_R1_R2(_cpu->registers(), Registers::Byte::E, Registers::Word::HL, _cpu->memory());
			case 0x5F: return LD_R1_R2(_cpu->registers(), Registers::Byte::E, Registers::Byte::A);

			case 0x60: return LD_R1_R2(_cpu->registers(), Registers::Byte::H, Registers::Byte::B);
			case 0x61: return LD_R1_R2(_cpu->registers(), Registers::Byte::H, Registers::Byte::C);
			case 0x62: return LD_R1_R2(_cpu->registers(), Registers::Byte::H, Registers::Byte::D);
			case 0x63: return LD_R1_R2(_cpu->registers(), Registers::Byte::H, Registers::Byte::E);
			case 0x64: return LD_R1_R2(_cpu->registers(), Registers::Byte::H, Registers::Byte::H);
			case 0x65: return LD_R1_R2(_cpu->registers(), Registers::Byte::H, Registers::Byte::L);
			case 0x66: return LD_R1_R2(_cpu->registers(), Registers::Byte::H, Registers::Word::HL, _cpu->memory());
			case 0x67: return LD_R1_R2(_cpu->registers(), Registers::Byte::H, Registers::Byte::A);
			case 0x68: return LD_R1_R2(_cpu->registers(), Registers::Byte::L, Registers::Byte::B);
			case 0x69: return LD_R1_R2(_cpu->registers(), Registers::Byte::L, Registers::Byte::C);
			case 0x6A: return LD_R1_R2(_cpu->registers(), Registers::Byte::L, Registers::Byte::D);
			case 0x6B: return LD_R1_R2(_cpu->registers(), Registers::Byte::L, Registers::Byte::E);
			case 0x6C: return LD_R1_R2(_cpu->registers(), Registers::Byte::L, Registers::Byte::H);
			case 0x6D: return LD_R1_R2(_cpu->registers(), Registers::Byte::L, Registers::Byte::L);
			case 0x6E: return LD_R1_R2(_cpu->registers(), Registers::Byte::L, Registers::Word::HL, _cpu->memory());
			case 0x6F: return LD_R1_R2(_cpu->registers(), Registers::Byte::L, Registers::Byte::A);

			case 0x70: return LD_R1_R2(_cpu->registers(), Registers::Word::HL, Registers::Byte::B, _cpu->memory());
			case 0x71: return LD_R1_R2(_cpu->registers(), Registers::Word::HL, Registers::Byte::C, _cpu->memory());
			case 0x72: return LD_R1_R2(_cpu->registers(), Registers::Word::HL, Registers::Byte::D, _cpu->memory());
			case 0x73: return LD_R1_R2(_cpu->registers(), Registers::Word::HL, Registers::Byte::E, _cpu->memory());
			case 0x74: return LD_R1_R2(_cpu->registers(), Registers::Word::HL, Registers::Byte::H, _cpu->memory());
			case 0x75: return LD_R1_R2(_cpu->registers(), Registers::Word::HL, Registers::Byte::L, _cpu->memory());
			case 0x77: return LD_R1_R2(_cpu->registers(), Registers::Word::HL, Registers::Byte::A, _cpu->memory());
			case 0x76: return HALT(_cpu->registers());
			case 0x78: return LD_R1_R2(_cpu->registers(), Registers::Byte::A, Registers::Byte::B);
			case 0x79: return LD_R1_R2(_cpu->registers(), Registers::Byte::A, Registers::Byte::C);
			case 0x7A: return LD_R1_R2(_cpu->registers(), Registers::Byte::A, Registers::Byte::D);
			case 0x7B: return LD_R1_R2(_cpu->registers(), Registers::Byte::A, Registers::Byte::E);
			case 0x7C: return LD_R1_R2(_cpu->registers(), Registers::Byte::A, Registers::Byte::H);
			case 0x7D: return LD_R1_R2(_cpu->registers(), Registers::Byte::A, Registers::Byte::L);
			case 0x7E: return LD_R1_R2(_cpu->registers(), Registers::Byte::A, Registers::Word::HL, _cpu->memory());
			case 0x7F: return LD_R1_R2(_cpu->registers(), Registers::Byte::A, Registers::Byte::A);

			case 0x80: return ADD(_cpu->registers(), Registers::Byte::B);
			case 0x81: return ADD(_cpu->registers(), Registers::Byte::C);
			case 0x82: return ADD(_cpu->registers(), Registers::Byte::D);
			case 0x83: return ADD(_cpu->registers(), Registers::Byte::E);
			case 0x84: return ADD(_cpu->registers(), Registers::Byte::H);
			case 0x85: return ADD(_cpu->registers(), Registers::Byte::L);
			case 0x86: return ADD(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x87: return ADD(_cpu->registers(), Registers::Byte::A);
			case 0x88: return ADC(_cpu->registers(), Registers::Byte::B);
			case 0x89: return ADC(_cpu->registers(), Registers::Byte::C);
			case 0x8A: return ADC(_cpu->registers(), Registers::Byte::D);
			case 0x8B: return ADC(_cpu->registers(), Registers::Byte::E);
			case 0x8C: return ADC(_cpu->registers(), Registers::Byte::H);
			case 0x8D: return ADC(_cpu->registers(), Registers::Byte::L);
			case 0x8E: return ADC(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x8F: return ADC(_cpu->registers(), Registers::Byte::A);

			case 0x90: return SUB(_cpu->registers(), Registers::Byte::B);
			case 0x91: return SUB(_cpu->registers(), Registers::Byte::C);
			case 0x92: return SUB(_cpu->registers(), Registers::Byte::D);
			case 0x93: return SUB(_cpu->registers(), Registers::Byte::E);
			case 0x94: return SUB(_cpu->registers(), Registers::Byte::H);
			case 0x95: return SUB(_cpu->registers(), Registers::Byte::L);
			case 0x96: return SUB(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x97: return SUB(_cpu->registers(), Registers::Byte::A);
			case 0x98: return SBC(_cpu->registers(), Registers::Byte::B);
			case 0x99: return SBC(_cpu->registers(), Registers::Byte::C);
			case 0x9A: return SBC(_cpu->registers(), Registers::Byte::D);
			case 0x9B: return SBC(_cpu->registers(), Registers::Byte::E);
			case 0x9C: return SBC(_cpu->registers(), Registers::Byte::H);
			case 0x9D: return SBC(_cpu->registers(), Registers::Byte::L);
			case 0x9E: return SBC(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x9F: return SBC(_cpu->registers(), Registers::Byte::A);

			case 0xA0: return AND(_cpu->registers(), Registers::Byte::B);
			case 0xA1: return AND(_cpu->registers(), Registers::Byte::C);
			case 0xA2: return AND(_cpu->registers(), Registers::Byte::D);
			case 0xA3: return AND(_cpu->registers(), Registers::Byte::E);
			case 0xA4: return AND(_cpu->registers(), Registers::Byte::H);
			case 0xA5: return AND(_cpu->registers(), Registers::Byte::L);
			case 0xA6: return AND(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0xA7: return AND(_cpu->registers(), Registers::Byte::A);
			case 0xA8: return XOR(_cpu->registers(), Registers::Byte::B);
			case 0xA9: return XOR(_cpu->registers(), Registers::Byte::C);
			case 0xAA: return XOR(_cpu->registers(), Registers::Byte::D);
			case 0xAB: return XOR(_cpu->registers(), Registers::Byte::E);
			case 0xAC: return XOR(_cpu->registers(), Registers::Byte::H);
			case 0xAD: return XOR(_cpu->registers(), Registers::Byte::L);
			case 0xAE: return XOR(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0xAF: return XOR(_cpu->registers(), Registers::Byte::A);

			case 0xB0: return OR(_cpu->registers(), Registers::Byte::B);
			case 0xB1: return OR(_cpu->registers(), Registers::Byte::C);
			case 0xB2: return OR(_cpu->registers(), Registers::Byte::D);
			case 0xB3: return OR(_cpu->registers(), Registers::Byte::E);
			case 0xB4: return OR(_cpu->registers(), Registers::Byte::H);
			case 0xB5: return OR(_cpu->registers(), Registers::Byte::L);
			case 0xB6: return OR(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0xB7: return OR(_cpu->registers(), Registers::Byte::A);
			case 0xB8: return CP(_cpu->registers(), Registers::Byte::B);
			case 0xB9: return CP(_cpu->registers(), Registers::Byte::C);
			case 0xBA: return CP(_cpu->registers(), Registers::Byte::D);
			case 0xBB: return CP(_cpu->registers(), Registers::Byte::E);
			case 0xBC: return CP(_cpu->registers(), Registers::Byte::H);
			case 0xBD: return CP(_cpu->registers(), Registers::Byte::L);
			case 0xBE: return CP(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0xBF: return CP(_cpu->registers(), Registers::Byte::A);

			case 0xC0: return RET_NZ(_cpu->registers(), _cpu->memory());
			case 0xC1: return POP(_cpu->registers(), Registers::Word::BC, _cpu->memory());
			case 0xC2: return JP_NZ(_cpu->registers(), _cpu->memory());
			case 0xC3: return JP(_cpu->registers(), _cpu->memory());
			case 0xC4: return CALL_NZ(_cpu->registers(), _cpu->memory());
			case 0xC5: return PUSH(_cpu->registers(), Registers::Word::BC, _cpu->memory());
			case 0xC6: return ADD(_cpu->registers(), _cpu->memory());
			case 0xC7: return RST(_cpu->registers(), _cpu->memory(), 0x0000);
			case 0xC8: return RET_Z(_cpu->registers(), _cpu->memory());
			case 0xC9: return RET(_cpu->registers(), _cpu->memory());
			case 0xCA: return JP_Z(_cpu->registers(), _cpu->memory());
			case 0xCB: return doCBInstruction();
			case 0xCC: return CALL_Z(_cpu->registers(), _cpu->memory());
			case 0xCD: return CALL(_cpu->registers(), _cpu->memory());
			case 0xCE: return ADC(_cpu->registers(), _cpu->memory());
			case 0xCF: return RST(_cpu->registers(), _cpu->memory(), 0x0008);

			case 0xD0: return RET_NC(_cpu->registers(), _cpu->memory());
			case 0xD1: return POP(_cpu->registers(), Registers::Word::DE, _cpu->memory());
			case 0xD2: return JP_NC(_cpu->registers(), _cpu->memory());
			case 0xD3: throw Exception("Instruction not exist: 0xD3"); break;
			case 0xD4: return CALL_NC(_cpu->registers(), _cpu->memory());
			case 0xD5: return PUSH(_cpu->registers(), Registers::Word::DE, _cpu->memory());
			case 0xD6: return SUB(_cpu->registers(), _cpu->memory());
			case 0xD7: return RST(_cpu->registers(), _cpu->memory(), 0x0010);
			case 0xD8: return RET_C(_cpu->registers(), _cpu->memory());
			case 0xD9: return RETI(_cpu->registers(), _cpu->memory());
			case 0xDA: return JP_C(_cpu->registers(), _cpu->memory());
			case 0xDB: throw Exception("Instruction not exist: 0xDB"); break;
			case 0xDC: return CALL_C(_cpu->registers(), _cpu->memory());
			case 0xDD: throw Exception("Instruction not exist: 0xDD"); break;
			case 0xDE: return SBC(_cpu->registers(), _cpu->memory());
			case 0xDF: return RST(_cpu->registers(), _cpu->memory(), 0x0018);

			case 0xE0: return LDH_N_A(_cpu->registers(), _cpu->memory());
			case 0xE1: return POP(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0xE2: return LD_C_A(_cpu->registers(), _cpu->memory());
			case 0xE3: throw Exception("Instruction not exist: 0xE3"); break;
			case 0xE4: throw Exception("Instruction not exist: 0xE4"); break;
			case 0xE5: return PUSH(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0xE6: return AND(_cpu->registers(), _cpu->memory());
			case 0xE7: return RST(_cpu->registers(), _cpu->memory(), 0x0020);
			case 0xE8: return ADD_SP_N(_cpu->registers(), _cpu->memory());
			case 0xE9: return JP_HL(_cpu->registers(), _cpu->memory());
			case 0xEA: return LD_N_A(_cpu->registers(), _cpu->memory());
			case 0xEB: throw Exception("Instruction not exist: 0xEB"); break;
			case 0xEC: throw Exception("Instruction not exist: 0xEC"); break;
			case 0xED: throw Exception("Instruction not exist: 0xED"); break;
			case 0xEE: return XOR(_cpu->registers(), _cpu->memory());
			case 0xEF: return RST(_cpu->registers(), _cpu->memory(), 0x0028);

			case 0xF0: return LDH_A_N(_cpu->registers(), _cpu->memory());
			case 0xF1: return POP(_cpu->registers(), Registers::Word::AF, _cpu->memory());
			case 0xF2: return LD_A_C(_cpu->registers(), _cpu->memory());
			case 0xF3: return DI(_cpu->registers());
			case 0xF4: throw Exception("Instruction not exist: 0xF4"); break;
			case 0xF5: return PUSH(_cpu->registers(), Registers::Word::AF, _cpu->memory());
			case 0xF6: return OR(_cpu->registers(), _cpu->memory());
			case 0xF7: return RST(_cpu->registers(), _cpu->memory(), 0x0030);
			case 0xF8: return LDHL_SP_N(_cpu->registers(), _cpu->memory());
			case 0xF9: return LD_SP_HL(_cpu->registers());
			case 0xFA: return LD_A_N(_cpu->registers(), _cpu->memory());
			case 0xFB: return EI(_cpu->registers());
			case 0xFC: throw Exception("Instruction not exist: 0xFC"); break;
			case 0xFD: throw Exception("Instruction not exist: 0xFD"); break;
			case 0xFE: return CP(_cpu->registers(), _cpu->memory());
			case 0xFF: return RST(_cpu->registers(), _cpu->memory(), 0x0038);

			default:
				throw Exception("Unimplemented instruction!");
				return (0);
			break; 
		}
	}

	void				Instructions::PUSH_PC ( void )
	{
		uint16_t		pc = _cpu->registers()->getPC();
		uint16_t		store_addr = _cpu->registers()->getSP() - 2;

		_cpu->registers()->decSP(2);
		_cpu->memory()->setWordAt(store_addr, pc);
	}

	/**************************************************************************/
	/**************************** PRIVATE METHODS *****************************/
	/**************************************************************************/

	uint8_t				Instructions::doCBInstruction ( void )
	{
		uint8_t			opcode = _cpu->memory()->getByteAt(_cpu->registers()->getPC() + 1);

		switch (opcode)
		{
			case 0x00: return RLC(_cpu->registers(), Registers::Byte::B);
			case 0x01: return RLC(_cpu->registers(), Registers::Byte::C);
			case 0x02: return RLC(_cpu->registers(), Registers::Byte::D);
			case 0x03: return RLC(_cpu->registers(), Registers::Byte::E);
			case 0x04: return RLC(_cpu->registers(), Registers::Byte::H);
			case 0x05: return RLC(_cpu->registers(), Registers::Byte::L);
			case 0x06: return RLC(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x07: return RLC(_cpu->registers(), Registers::Byte::A);
			case 0x08: return RRC(_cpu->registers(), Registers::Byte::B);
			case 0x09: return RRC(_cpu->registers(), Registers::Byte::C);
			case 0x0A: return RRC(_cpu->registers(), Registers::Byte::D);
			case 0x0B: return RRC(_cpu->registers(), Registers::Byte::E);
			case 0x0C: return RRC(_cpu->registers(), Registers::Byte::H);
			case 0x0D: return RRC(_cpu->registers(), Registers::Byte::L);
			case 0x0E: return RRC(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x0F: return RRC(_cpu->registers(), Registers::Byte::A);

			case 0x10: return RL(_cpu->registers(), Registers::Byte::B);
			case 0x11: return RL(_cpu->registers(), Registers::Byte::C);
			case 0x12: return RL(_cpu->registers(), Registers::Byte::D);
			case 0x13: return RL(_cpu->registers(), Registers::Byte::E);
			case 0x14: return RL(_cpu->registers(), Registers::Byte::H);
			case 0x15: return RL(_cpu->registers(), Registers::Byte::L);
			case 0x16: return RL(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x17: return RL(_cpu->registers(), Registers::Byte::A);
			case 0x18: return RR(_cpu->registers(), Registers::Byte::B);
			case 0x19: return RR(_cpu->registers(), Registers::Byte::C);
			case 0x1A: return RR(_cpu->registers(), Registers::Byte::D);
			case 0x1B: return RR(_cpu->registers(), Registers::Byte::E);
			case 0x1C: return RR(_cpu->registers(), Registers::Byte::H);
			case 0x1D: return RR(_cpu->registers(), Registers::Byte::L);
			case 0x1E: return RR(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x1F: return RR(_cpu->registers(), Registers::Byte::A);

			case 0x20: return SLA(_cpu->registers(), Registers::Byte::B);
			case 0x21: return SLA(_cpu->registers(), Registers::Byte::C);
			case 0x22: return SLA(_cpu->registers(), Registers::Byte::D);
			case 0x23: return SLA(_cpu->registers(), Registers::Byte::E);
			case 0x24: return SLA(_cpu->registers(), Registers::Byte::H);
			case 0x25: return SLA(_cpu->registers(), Registers::Byte::L);
			case 0x26: return SLA(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x27: return SLA(_cpu->registers(), Registers::Byte::A);
			case 0x28: return SRA(_cpu->registers(), Registers::Byte::B);
			case 0x29: return SRA(_cpu->registers(), Registers::Byte::C);
			case 0x2A: return SRA(_cpu->registers(), Registers::Byte::D);
			case 0x2B: return SRA(_cpu->registers(), Registers::Byte::E);
			case 0x2C: return SRA(_cpu->registers(), Registers::Byte::H);
			case 0x2D: return SRA(_cpu->registers(), Registers::Byte::L);
			case 0x2E: return SRA(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x2F: return SRA(_cpu->registers(), Registers::Byte::A);

			case 0x30: return SWAP(_cpu->registers(), Registers::Byte::B);
			case 0x31: return SWAP(_cpu->registers(), Registers::Byte::C);
			case 0x32: return SWAP(_cpu->registers(), Registers::Byte::D);
			case 0x33: return SWAP(_cpu->registers(), Registers::Byte::E);
			case 0x34: return SWAP(_cpu->registers(), Registers::Byte::H);
			case 0x35: return SWAP(_cpu->registers(), Registers::Byte::L);
			case 0x36: return SWAP(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x37: return SWAP(_cpu->registers(), Registers::Byte::A);
			case 0x38: return SRL(_cpu->registers(), Registers::Byte::B);
			case 0x39: return SRL(_cpu->registers(), Registers::Byte::C);
			case 0x3A: return SRL(_cpu->registers(), Registers::Byte::D);
			case 0x3B: return SRL(_cpu->registers(), Registers::Byte::E);
			case 0x3C: return SRL(_cpu->registers(), Registers::Byte::H);
			case 0x3D: return SRL(_cpu->registers(), Registers::Byte::L);
			case 0x3E: return SRL(_cpu->registers(), Registers::Word::HL, _cpu->memory());
			case 0x3F: return SRL(_cpu->registers(), Registers::Byte::A);
			
			case 0x40: return BIT(_cpu->registers(), 0, Registers::Byte::B);
			case 0x41: return BIT(_cpu->registers(), 0, Registers::Byte::C);
			case 0x42: return BIT(_cpu->registers(), 0, Registers::Byte::D);
			case 0x43: return BIT(_cpu->registers(), 0, Registers::Byte::E);
			case 0x44: return BIT(_cpu->registers(), 0, Registers::Byte::H);
			case 0x45: return BIT(_cpu->registers(), 0, Registers::Byte::L);
			case 0x46: return BIT(_cpu->registers(), 0, Registers::Word::HL, _cpu->memory());
			case 0x47: return BIT(_cpu->registers(), 0, Registers::Byte::A);
			case 0x48: return BIT(_cpu->registers(), 1, Registers::Byte::B);
			case 0x49: return BIT(_cpu->registers(), 1, Registers::Byte::C);
			case 0x4A: return BIT(_cpu->registers(), 1, Registers::Byte::D);
			case 0x4B: return BIT(_cpu->registers(), 1, Registers::Byte::E);
			case 0x4C: return BIT(_cpu->registers(), 1, Registers::Byte::H);
			case 0x4D: return BIT(_cpu->registers(), 1, Registers::Byte::L);
			case 0x4E: return BIT(_cpu->registers(), 1, Registers::Word::HL, _cpu->memory());
			case 0x4F: return BIT(_cpu->registers(), 1, Registers::Byte::A);

			case 0x50: return BIT(_cpu->registers(), 2, Registers::Byte::B);
			case 0x51: return BIT(_cpu->registers(), 2, Registers::Byte::C);
			case 0x52: return BIT(_cpu->registers(), 2, Registers::Byte::D);
			case 0x53: return BIT(_cpu->registers(), 2, Registers::Byte::E);
			case 0x54: return BIT(_cpu->registers(), 2, Registers::Byte::H);
			case 0x55: return BIT(_cpu->registers(), 2, Registers::Byte::L);
			case 0x56: return BIT(_cpu->registers(), 2, Registers::Word::HL, _cpu->memory());
			case 0x57: return BIT(_cpu->registers(), 2, Registers::Byte::A);
			case 0x58: return BIT(_cpu->registers(), 3, Registers::Byte::B);
			case 0x59: return BIT(_cpu->registers(), 3, Registers::Byte::C);
			case 0x5A: return BIT(_cpu->registers(), 3, Registers::Byte::D);
			case 0x5B: return BIT(_cpu->registers(), 3, Registers::Byte::E);
			case 0x5C: return BIT(_cpu->registers(), 3, Registers::Byte::H);
			case 0x5D: return BIT(_cpu->registers(), 3, Registers::Byte::L);
			case 0x5E: return BIT(_cpu->registers(), 3, Registers::Word::HL, _cpu->memory());
			case 0x5F: return BIT(_cpu->registers(), 3, Registers::Byte::A);

			case 0x60: return BIT(_cpu->registers(), 4, Registers::Byte::B);
			case 0x61: return BIT(_cpu->registers(), 4, Registers::Byte::C);
			case 0x62: return BIT(_cpu->registers(), 4, Registers::Byte::D);
			case 0x63: return BIT(_cpu->registers(), 4, Registers::Byte::E);
			case 0x64: return BIT(_cpu->registers(), 4, Registers::Byte::H);
			case 0x65: return BIT(_cpu->registers(), 4, Registers::Byte::L);
			case 0x66: return BIT(_cpu->registers(), 4, Registers::Word::HL, _cpu->memory());
			case 0x67: return BIT(_cpu->registers(), 4, Registers::Byte::A);
			case 0x68: return BIT(_cpu->registers(), 5, Registers::Byte::B);
			case 0x69: return BIT(_cpu->registers(), 5, Registers::Byte::C);
			case 0x6A: return BIT(_cpu->registers(), 5, Registers::Byte::D);
			case 0x6B: return BIT(_cpu->registers(), 5, Registers::Byte::E);
			case 0x6C: return BIT(_cpu->registers(), 5, Registers::Byte::H);
			case 0x6D: return BIT(_cpu->registers(), 5, Registers::Byte::L);
			case 0x6E: return BIT(_cpu->registers(), 5, Registers::Word::HL, _cpu->memory());
			case 0x6F: return BIT(_cpu->registers(), 5, Registers::Byte::A);

			case 0x70: return BIT(_cpu->registers(), 6, Registers::Byte::B);
			case 0x71: return BIT(_cpu->registers(), 6, Registers::Byte::C);
			case 0x72: return BIT(_cpu->registers(), 6, Registers::Byte::D);
			case 0x73: return BIT(_cpu->registers(), 6, Registers::Byte::E);
			case 0x74: return BIT(_cpu->registers(), 6, Registers::Byte::H);
			case 0x75: return BIT(_cpu->registers(), 6, Registers::Byte::L);
			case 0x76: return BIT(_cpu->registers(), 6, Registers::Word::HL, _cpu->memory());
			case 0x77: return BIT(_cpu->registers(), 6, Registers::Byte::A);
			case 0x78: return BIT(_cpu->registers(), 7, Registers::Byte::B);
			case 0x79: return BIT(_cpu->registers(), 7, Registers::Byte::C);
			case 0x7A: return BIT(_cpu->registers(), 7, Registers::Byte::D);
			case 0x7B: return BIT(_cpu->registers(), 7, Registers::Byte::E);
			case 0x7C: return BIT(_cpu->registers(), 7, Registers::Byte::H);
			case 0x7D: return BIT(_cpu->registers(), 7, Registers::Byte::L);
			case 0x7E: return BIT(_cpu->registers(), 7, Registers::Word::HL, _cpu->memory());
			case 0x7F: return BIT(_cpu->registers(), 7, Registers::Byte::A);

			case 0x80: return RES(_cpu->registers(), 0, Registers::Byte::B);
			case 0x81: return RES(_cpu->registers(), 0, Registers::Byte::C);
			case 0x82: return RES(_cpu->registers(), 0, Registers::Byte::D);
			case 0x83: return RES(_cpu->registers(), 0, Registers::Byte::E);
			case 0x84: return RES(_cpu->registers(), 0, Registers::Byte::H);
			case 0x85: return RES(_cpu->registers(), 0, Registers::Byte::L);
			case 0x86: return RES(_cpu->registers(), 0, Registers::Word::HL, _cpu->memory());
			case 0x87: return RES(_cpu->registers(), 0, Registers::Byte::A);
			case 0x88: return RES(_cpu->registers(), 1, Registers::Byte::B);
			case 0x89: return RES(_cpu->registers(), 1, Registers::Byte::C);
			case 0x8A: return RES(_cpu->registers(), 1, Registers::Byte::D);
			case 0x8B: return RES(_cpu->registers(), 1, Registers::Byte::E);
			case 0x8C: return RES(_cpu->registers(), 1, Registers::Byte::H);
			case 0x8D: return RES(_cpu->registers(), 1, Registers::Byte::L);
			case 0x8E: return RES(_cpu->registers(), 1, Registers::Word::HL, _cpu->memory());
			case 0x8F: return RES(_cpu->registers(), 1, Registers::Byte::A);

			case 0x90: return RES(_cpu->registers(), 2, Registers::Byte::B);
			case 0x91: return RES(_cpu->registers(), 2, Registers::Byte::C);
			case 0x92: return RES(_cpu->registers(), 2, Registers::Byte::D);
			case 0x93: return RES(_cpu->registers(), 2, Registers::Byte::E);
			case 0x94: return RES(_cpu->registers(), 2, Registers::Byte::H);
			case 0x95: return RES(_cpu->registers(), 2, Registers::Byte::L);
			case 0x96: return RES(_cpu->registers(), 2, Registers::Word::HL, _cpu->memory());
			case 0x97: return RES(_cpu->registers(), 2, Registers::Byte::A);
			case 0x98: return RES(_cpu->registers(), 3, Registers::Byte::B);
			case 0x99: return RES(_cpu->registers(), 3, Registers::Byte::C);
			case 0x9A: return RES(_cpu->registers(), 3, Registers::Byte::D);
			case 0x9B: return RES(_cpu->registers(), 3, Registers::Byte::E);
			case 0x9C: return RES(_cpu->registers(), 3, Registers::Byte::H);
			case 0x9D: return RES(_cpu->registers(), 3, Registers::Byte::L);
			case 0x9E: return RES(_cpu->registers(), 3, Registers::Word::HL, _cpu->memory());
			case 0x9F: return RES(_cpu->registers(), 3, Registers::Byte::A);

			case 0xA0: return RES(_cpu->registers(), 4, Registers::Byte::B);
			case 0xA1: return RES(_cpu->registers(), 4, Registers::Byte::C);
			case 0xA2: return RES(_cpu->registers(), 4, Registers::Byte::D);
			case 0xA3: return RES(_cpu->registers(), 4, Registers::Byte::E);
			case 0xA4: return RES(_cpu->registers(), 4, Registers::Byte::H);
			case 0xA5: return RES(_cpu->registers(), 4, Registers::Byte::L);
			case 0xA6: return RES(_cpu->registers(), 4, Registers::Word::HL, _cpu->memory());
			case 0xA7: return RES(_cpu->registers(), 4, Registers::Byte::A);
			case 0xA8: return RES(_cpu->registers(), 5, Registers::Byte::B);
			case 0xA9: return RES(_cpu->registers(), 5, Registers::Byte::C);
			case 0xAA: return RES(_cpu->registers(), 5, Registers::Byte::D);
			case 0xAB: return RES(_cpu->registers(), 5, Registers::Byte::E);
			case 0xAC: return RES(_cpu->registers(), 5, Registers::Byte::H);
			case 0xAD: return RES(_cpu->registers(), 5, Registers::Byte::L);
			case 0xAE: return RES(_cpu->registers(), 5, Registers::Word::HL, _cpu->memory());
			case 0xAF: return RES(_cpu->registers(), 5, Registers::Byte::A);

			case 0xB0: return RES(_cpu->registers(), 6, Registers::Byte::B);
			case 0xB1: return RES(_cpu->registers(), 6, Registers::Byte::C);
			case 0xB2: return RES(_cpu->registers(), 6, Registers::Byte::D);
			case 0xB3: return RES(_cpu->registers(), 6, Registers::Byte::E);
			case 0xB4: return RES(_cpu->registers(), 6, Registers::Byte::H);
			case 0xB5: return RES(_cpu->registers(), 6, Registers::Byte::L);
			case 0xB6: return RES(_cpu->registers(), 6, Registers::Word::HL, _cpu->memory());
			case 0xB7: return RES(_cpu->registers(), 6, Registers::Byte::A);
			case 0xB8: return RES(_cpu->registers(), 7, Registers::Byte::B);
			case 0xB9: return RES(_cpu->registers(), 7, Registers::Byte::C);
			case 0xBA: return RES(_cpu->registers(), 7, Registers::Byte::D);
			case 0xBB: return RES(_cpu->registers(), 7, Registers::Byte::E);
			case 0xBC: return RES(_cpu->registers(), 7, Registers::Byte::H);
			case 0xBD: return RES(_cpu->registers(), 7, Registers::Byte::L);
			case 0xBE: return RES(_cpu->registers(), 7, Registers::Word::HL, _cpu->memory());
			case 0xBF: return RES(_cpu->registers(), 7, Registers::Byte::A);

			case 0xC0: return SET(_cpu->registers(), 0, Registers::Byte::B);
			case 0xC1: return SET(_cpu->registers(), 0, Registers::Byte::C);
			case 0xC2: return SET(_cpu->registers(), 0, Registers::Byte::D);
			case 0xC3: return SET(_cpu->registers(), 0, Registers::Byte::E);
			case 0xC4: return SET(_cpu->registers(), 0, Registers::Byte::H);
			case 0xC5: return SET(_cpu->registers(), 0, Registers::Byte::L);
			case 0xC6: return SET(_cpu->registers(), 0, Registers::Word::HL, _cpu->memory());
			case 0xC7: return SET(_cpu->registers(), 0, Registers::Byte::A);
			case 0xC8: return SET(_cpu->registers(), 1, Registers::Byte::B);
			case 0xC9: return SET(_cpu->registers(), 1, Registers::Byte::C);
			case 0xCA: return SET(_cpu->registers(), 1, Registers::Byte::D);
			case 0xCB: return SET(_cpu->registers(), 1, Registers::Byte::E);
			case 0xCC: return SET(_cpu->registers(), 1, Registers::Byte::H);
			case 0xCD: return SET(_cpu->registers(), 1, Registers::Byte::L);
			case 0xCE: return SET(_cpu->registers(), 1, Registers::Word::HL, _cpu->memory());
			case 0xCF: return SET(_cpu->registers(), 1, Registers::Byte::A);

			case 0xD0: return SET(_cpu->registers(), 2, Registers::Byte::B);
			case 0xD1: return SET(_cpu->registers(), 2, Registers::Byte::C);
			case 0xD2: return SET(_cpu->registers(), 2, Registers::Byte::D);
			case 0xD3: return SET(_cpu->registers(), 2, Registers::Byte::E);
			case 0xD4: return SET(_cpu->registers(), 2, Registers::Byte::H);
			case 0xD5: return SET(_cpu->registers(), 2, Registers::Byte::L);
			case 0xD6: return SET(_cpu->registers(), 2, Registers::Word::HL, _cpu->memory());
			case 0xD7: return SET(_cpu->registers(), 2, Registers::Byte::A);
			case 0xD8: return SET(_cpu->registers(), 3, Registers::Byte::B);
			case 0xD9: return SET(_cpu->registers(), 3, Registers::Byte::C);
			case 0xDA: return SET(_cpu->registers(), 3, Registers::Byte::D);
			case 0xDB: return SET(_cpu->registers(), 3, Registers::Byte::E);
			case 0xDC: return SET(_cpu->registers(), 3, Registers::Byte::H);
			case 0xDD: return SET(_cpu->registers(), 3, Registers::Byte::L);
			case 0xDE: return SET(_cpu->registers(), 3, Registers::Word::HL, _cpu->memory());
			case 0xDF: return SET(_cpu->registers(), 3, Registers::Byte::A);

			case 0xE0: return SET(_cpu->registers(), 4, Registers::Byte::B);
			case 0xE1: return SET(_cpu->registers(), 4, Registers::Byte::C);
			case 0xE2: return SET(_cpu->registers(), 4, Registers::Byte::D);
			case 0xE3: return SET(_cpu->registers(), 4, Registers::Byte::E);
			case 0xE4: return SET(_cpu->registers(), 4, Registers::Byte::H);
			case 0xE5: return SET(_cpu->registers(), 4, Registers::Byte::L);
			case 0xE6: return SET(_cpu->registers(), 4, Registers::Word::HL, _cpu->memory());
			case 0xE7: return SET(_cpu->registers(), 4, Registers::Byte::A);
			case 0xE8: return SET(_cpu->registers(), 5, Registers::Byte::B);
			case 0xE9: return SET(_cpu->registers(), 5, Registers::Byte::C);
			case 0xEA: return SET(_cpu->registers(), 5, Registers::Byte::D);
			case 0xEB: return SET(_cpu->registers(), 5, Registers::Byte::E);
			case 0xEC: return SET(_cpu->registers(), 5, Registers::Byte::H);
			case 0xED: return SET(_cpu->registers(), 5, Registers::Byte::L);
			case 0xEE: return SET(_cpu->registers(), 5, Registers::Word::HL, _cpu->memory());
			case 0xEF: return SET(_cpu->registers(), 5, Registers::Byte::A);

			case 0xF0: return SET(_cpu->registers(), 6, Registers::Byte::B);
			case 0xF1: return SET(_cpu->registers(), 6, Registers::Byte::C);
			case 0xF2: return SET(_cpu->registers(), 6, Registers::Byte::D);
			case 0xF3: return SET(_cpu->registers(), 6, Registers::Byte::E);
			case 0xF4: return SET(_cpu->registers(), 6, Registers::Byte::H);
			case 0xF5: return SET(_cpu->registers(), 6, Registers::Byte::L);
			case 0xF6: return SET(_cpu->registers(), 6, Registers::Word::HL, _cpu->memory());
			case 0xF7: return SET(_cpu->registers(), 6, Registers::Byte::A);
			case 0xF8: return SET(_cpu->registers(), 7, Registers::Byte::B);
			case 0xF9: return SET(_cpu->registers(), 7, Registers::Byte::C);
			case 0xFA: return SET(_cpu->registers(), 7, Registers::Byte::D);
			case 0xFB: return SET(_cpu->registers(), 7, Registers::Byte::E);
			case 0xFC: return SET(_cpu->registers(), 7, Registers::Byte::H);
			case 0xFD: return SET(_cpu->registers(), 7, Registers::Byte::L);
			case 0xFE: return SET(_cpu->registers(), 7, Registers::Word::HL, _cpu->memory());
			case 0xFF: return SET(_cpu->registers(), 7, Registers::Byte::A);

			default:
				throw Exception("Unimplemented CB instruction!");
				return (0);
			break; 
		}
	}

	/*********************************************************************
	**************************** 8Bits LOAD ******************************
	*********************************************************************/

	// Load 8bits immediate value into Byte register
	uint8_t				Instructions::LD_NN_N ( Registers* regs, Registers::Byte const& r, Memory* mem)
	{
		uint16_t		imdt_value_addr = regs->getPC() + 1;
		uint8_t			imdt_value = mem->getByteAt(imdt_value_addr);

		regs->setRegister(r, imdt_value);
		regs->incPC(2);
		return (8);
	}

	// Load register R2 into register R1
	uint8_t				Instructions::LD_R1_R2 ( Registers* regs, Registers::Byte const& r1, Registers::Byte const& r2 )
	{
		uint8_t			value = regs->getRegister(r2);

		regs->setRegister(r1, value);
		regs->incPC(1);
		return (4);
	}

	uint8_t				Instructions::LD_R1_R2 ( Registers* regs, Registers::Byte const& r1, Registers::Word const& r2, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r2);
		uint8_t			value = mem->getByteAt(value_addr);

		regs->setRegister(r1, value);
		regs->incPC(1);
		return (8);
	}

	uint8_t				Instructions::LD_R1_R2 ( Registers* regs, Registers::Word const& r1, Registers::Byte const& r2, Memory* mem )
	{
		uint16_t		store_addr = regs->getRegister(r1);
		uint8_t			value = regs->getRegister(r2);

		mem->setByteAt(store_addr, value);
		regs->incPC(1);
		return (8);
	}

	uint8_t 			Instructions::LD_R1_R2 ( Registers* regs, Registers::Word const& r1, Memory* mem )
	{
		uint16_t		imdt_value_addr = regs->getPC() + 1;
		uint16_t		store_addr = regs->getRegister(r1);
		uint8_t			imdt_value = mem->getByteAt(imdt_value_addr);

		mem->setByteAt(store_addr, imdt_value);
		regs->incPC(2);
		return (12);
	}

	// load value at 16bits immediate address into A
	uint8_t 			Instructions::LD_A_N ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_value_addr = regs->getPC() + 1;
		uint16_t		value_addr = mem->getWordAt(imdt_value_addr);
		uint8_t			value = mem->getByteAt(value_addr);

		regs->setA(value);
		regs->incPC(3);
		return (16);
	}

	// load value of register A at 16bits immediate address
	uint8_t 			Instructions::LD_N_A ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_value_addr = regs->getPC() + 1;
		uint16_t		store_addr = mem->getWordAt(imdt_value_addr);
		uint8_t			value = regs->getA();

		mem->setByteAt(store_addr, value);
		regs->incPC(3);
		return (16);
	}

	// load value at address 0xFF00 + register C into register A.
	uint8_t				Instructions::LD_A_C ( Registers* regs, Memory* mem )
	{
		uint16_t		value_addr = 0xFF00 + regs->getC();
		uint8_t			value = mem->getByteAt(value_addr);

		regs->setA(value);
		regs->incPC(1);
		return (8);
	}

	// load value of register A at address 0xFF00 + register C.
	uint8_t				Instructions::LD_C_A ( Registers* regs, Memory* mem )
	{
		uint16_t		store_addr = 0xFF00 + regs->getC();
		uint8_t			value = regs->getA();

		mem->setByteAt(store_addr, value);
		regs->incPC(1);
		return (8);
	}

	// load value at address contain in register HL into register A and decrement HL.
	uint8_t				Instructions::LDD_A_HL ( Registers* regs, Memory* mem )
	{
		uint16_t		value_addr = regs->getHL();
		uint8_t			value = mem->getByteAt(value_addr);

		regs->setA(value);
		regs->setHL(value_addr - 1);
		regs->incPC(1);
		return (8);
	}

	// load value of register A at address contain in register HL and decrement HL.
	uint8_t				Instructions::LDD_HL_A ( Registers* regs, Memory* mem )
	{
		uint16_t		store_addr = regs->getHL();
		uint8_t			value = regs->getA();

		mem->setByteAt(store_addr, value);
		regs->setHL(store_addr - 1);
		regs->incPC(1);
		return (8);
	}

	// load value at address contain in register HL into register A and increment HL.
	uint8_t				Instructions::LDI_A_HL ( Registers* regs, Memory* mem )
	{
		uint16_t		value_addr = regs->getHL();
		uint8_t			value = mem->getByteAt(value_addr);

		regs->setA(value);
		regs->setHL(value_addr + 1);
		regs->incPC(1);
		return (8);
	}

	// load value of register A at address contain in register HL and increment HL.
	uint8_t				Instructions::LDI_HL_A ( Registers* regs, Memory* mem )
	{
		uint16_t		store_addr = regs->getHL();
		uint8_t			value = regs->getA();

		mem->setByteAt(store_addr, value);
		regs->setHL(store_addr + 1);
		regs->incPC(1);
		return (8);
	}

	// load value of register A at address 0xFF00 + 8bits immediate value.
	uint8_t				Instructions::LDH_N_A ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_value_addr = regs->getPC() + 1;
		uint8_t			imdt_value = mem->getByteAt(imdt_value_addr);
		uint16_t		store_addr = 0xFF00 + imdt_value;
		uint8_t			value = regs->getA();

		mem->setByteAt(store_addr, value);
		regs->incPC(2);
		return (12);
	}

	// load value at address 0xFF00 + 8bits immediate value into register A
	uint8_t				Instructions::LDH_A_N ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_value_addr = regs->getPC() + 1;
		uint8_t			imdt_value = mem->getByteAt(imdt_value_addr);
		uint16_t		value_addr = 0xFF00 + imdt_value;
		uint8_t			value = mem->getByteAt(value_addr);

		regs->setA(value);
		regs->incPC(2);
		return (12);
	}

	/*********************************************************************
	**************************** 16Bits LOAD *****************************
	*********************************************************************/

	// load 16bits immediate value into Word register
	uint8_t				Instructions::LD_N_NN ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		imdt_value_addr = regs->getPC() + 1;
		uint16_t		imdt_value = mem->getWordAt(imdt_value_addr);

		regs->setRegister(r, imdt_value);
		regs->incPC(3);
		return (12);
	}

	// load value of register HL into register SP
	uint8_t				Instructions::LD_SP_HL ( Registers* regs )
	{
		uint16_t		value = regs->getHL();

		regs->setSP(value);
		regs->incPC(1);
		return (8);
	}

	// load value of register SP + 8bits signed immediate value into register HL
	// Z - reset
	// N - reset
	// H - Set or reset according to operation.
	// C - Set or reset according to operation.
	uint8_t				Instructions::LDHL_SP_N ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_value_addr = regs->getPC() + 1;
		int8_t			imdt_value = mem->getByteAt(imdt_value_addr);
		uint16_t		value = regs->getSP() + imdt_value;

		regs->setHL(value);

		regs->setFlag(Registers::Flag::Z, false);
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, ( (regs->getSP() & 0x0F) + (imdt_value & 0x0F) > 0x0F ) );
		regs->setFlag(Registers::Flag::C, ( (regs->getSP() & 0xFF) + (imdt_value & 0xFF) > 0xFF ) );
		
		regs->incPC(2);
		return (12);
	}

	// load value of register SP at 16bits immediate address
	uint8_t				Instructions::LD_NN_SP ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_value_addr = regs->getPC() + 1;
		uint16_t		store_addr = mem->getWordAt(imdt_value_addr);
		uint16_t 		value = regs->getSP();

		mem->setWordAt(store_addr, value);
		regs->incPC(3);
		return (20);
	}

	// push 16bits value of Word register on the stack and decremment SP twice.
	uint8_t				Instructions::PUSH ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value = regs->getRegister(r);
		uint16_t		store_addr = regs->getSP() - 2;

		mem->setWordAt(store_addr, value);
		regs->decSP(2);
		regs->incPC(1);
		return (16);
	}

	// pop 16bits from the stack and store in Word register. increment SP twice
	uint8_t				Instructions::POP ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getSP();
		uint16_t 		value = mem->getWordAt(value_addr);

		regs->setRegister(r, value);
		regs->incSP(2);
		regs->incPC(1);
		return (12);
	}

	/*********************************************************************
	***************************** 8Bits ALU ******************************
	*********************************************************************/

	// Addition register A AND N then store result in register A
	// Z - set if result equal Zero
	// N - reset
	// H - Set if carry from bit 3.
	// C - Set if carry from bit 7.
	uint8_t				Instructions::ADD (Registers* regs, Registers::Byte const& r )
	{
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = regs->getRegister(r);
		uint16_t		result = lhs + rhs;
		uint8_t			value = (result & 0xFF);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) + (rhs & 0x0F) > 0x0F) );
		regs->setFlag(Registers::Flag::C, (result > 0xFF) );
		
		regs->incPC(1);
		return (4);
	}
	
	uint8_t				Instructions::ADD (Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		rhs_addr = regs->getRegister(r);
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(rhs_addr);
		uint16_t		result = lhs + rhs;
		uint8_t			value = (result & 0xFF);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) + (rhs & 0x0F) > 0x0F) );
		regs->setFlag(Registers::Flag::C, (result > 0xFF) );
		
		regs->incPC(1);

		return (8);
	}

	uint8_t				Instructions::ADD (Registers* regs, Memory* mem )
	{
		uint16_t		imdt_addr = regs->getPC() + 1;
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(imdt_addr);
		uint16_t		result = lhs + rhs;
		uint8_t			value = (result & 0xFF);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) + (rhs & 0x0F) > 0x0F) );
		regs->setFlag(Registers::Flag::C, (result > 0xFF) );
		
		regs->incPC(2);

		return (8);
	}

	// Addition register A AND N + Carry flag then store result in register A
	// Z - set if result equal Zero
	// N - reset
	// H - Set if carry from bit 3.
	// C - Set if carry from bit 7.
	uint8_t				Instructions::ADC (Registers* regs, Registers::Byte const& r )
	{
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = regs->getRegister(r);
		uint8_t			carry = regs->getFC();
		uint16_t		result = lhs + rhs + carry;
		uint8_t			value = (result & 0xFF);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) + (rhs & 0x0F) + carry > 0x0F) );
		regs->setFlag(Registers::Flag::C, (result > 0xFF) );
		
		regs->incPC(1);
		return (4);
	}

	uint8_t				Instructions::ADC (Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		rhs_addr = regs->getRegister(r);
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(rhs_addr);
		uint8_t			carry = regs->getFC();
		uint16_t		result = lhs + rhs + carry;
		uint8_t			value = (result & 0xFF);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) + (rhs & 0x0F) + carry > 0x0F) );
		regs->setFlag(Registers::Flag::C, (result > 0xFF) );
		
		regs->incPC(1);

		return (8);
	}

	uint8_t				Instructions::ADC (Registers* regs, Memory* mem )
	{
		uint16_t		imdt_addr = regs->getPC() + 1;
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(imdt_addr);
		uint8_t			carry = regs->getFC();
		uint16_t		result = lhs + rhs + carry;
		uint8_t			value = (result & 0xFF);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) + (rhs & 0x0F) + carry > 0x0F) );
		regs->setFlag(Registers::Flag::C, (result > 0xFF) );
		
		regs->incPC(2);

		return (8);
	}

	// Substract N From register A then store result in register A
	// Z - set if result equal Zero
	// N - reset
	// H - Set if no borrow from bit 4.
	// C - Set if no borrow.
	uint8_t				Instructions::SUB ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = regs->getRegister(r);
		uint8_t			value = lhs - rhs;

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, true);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) < (rhs & 0x0F)) );
		regs->setFlag(Registers::Flag::C, (lhs < rhs) );

		regs->incPC(1);
		return (4);
	}

	uint8_t				Instructions::SUB ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		rhs_addr = regs->getRegister(r);
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(rhs_addr);
		uint8_t			value = lhs - rhs;

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, true);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) < (rhs & 0x0F)) );
		regs->setFlag(Registers::Flag::C, (lhs < rhs) );

		regs->incPC(1);
		return (8);
	}

	uint8_t				Instructions::SUB ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_addr = regs->getPC() + 1;
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(imdt_addr);
		uint8_t			value = lhs - rhs;

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, true);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) < (rhs & 0x0F)) );
		regs->setFlag(Registers::Flag::C, (lhs < rhs) );

		regs->incPC(2);
		return (8);
	}

	// Substract N + Carry flag From register A then store result in register A
	// Z - set if result equal Zero
	// N - reset
	// H - Set if no borrow from bit 4.
	// C - Set if no borrow.
	uint8_t				Instructions::SBC ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			carry = regs->getFC();
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = regs->getRegister(r);
		int16_t			sum = rhs + carry;
		uint8_t			value = lhs - sum;

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, true);
		if ((lhs & 0x0F) < (rhs & 0x0F))
        	regs->setFH(true);
    	else if ((lhs & 0x0F) < (sum & 0x0F))
        	regs->setFH(true);
    	else if (((lhs & 0x0F) == (rhs & 0x0F)) && ((rhs & 0x0F) == 0x0F) && carry)
        	regs->setFH(true);
    	else
        	regs->setFH(false);
		regs->setFlag(Registers::Flag::C, (lhs < sum) );

		regs->incPC(1);
		return (4);
	}

	uint8_t				Instructions::SBC ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint8_t			carry = regs->getFC();
		uint16_t		rhs_addr = regs->getRegister(r);
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(rhs_addr);
		int16_t			sum = rhs + carry;
		uint8_t			value = lhs - sum;

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, true);
		if ((lhs & 0x0F) < (rhs & 0x0F))
        	regs->setFH(true);
    	else if ((lhs & 0x0F) < (sum & 0x0F))
        	regs->setFH(true);
    	else if (((lhs & 0x0F) == (rhs & 0x0F)) && ((rhs & 0x0F) == 0x0F) && carry)
        	regs->setFH(true);
    	else
        	regs->setFH(false);
		regs->setFlag(Registers::Flag::C, (lhs < sum) );

		regs->incPC(1);
		return (8);
	}

	uint8_t				Instructions::SBC ( Registers* regs, Memory* mem )
	{
		uint8_t			carry = regs->getFC();
		uint16_t		imdt_addr = regs->getPC() + 1;
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(imdt_addr);
		int16_t			sum = rhs + carry;
		uint8_t			value = lhs - sum;

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, true);
		if ((lhs & 0x0F) < (rhs & 0x0F))
        	regs->setFH(true);
    	else if ((lhs & 0x0F) < (sum & 0x0F))
        	regs->setFH(true);
    	else if (((lhs & 0x0F) == (rhs & 0x0F)) && ((rhs & 0x0F) == 0x0F) && carry)
        	regs->setFH(true);
    	else
        	regs->setFH(false);
		regs->setFlag(Registers::Flag::C, (lhs < sum) );
		regs->incPC(2);
		return (8);
	}

	// Logical AND N with register A then store result in register A
	// Z - set if result is Zero
	// N - reset
	// H - set
	// C - reset
	uint8_t				Instructions::AND ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = regs->getRegister(r);
		uint8_t			value = (lhs & rhs);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, true);
		regs->setFlag(Registers::Flag::C, false);

		regs->incPC(1);
		return (4);
	}

	uint8_t				Instructions::AND ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		rhs_addr = regs->getRegister(r);
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(rhs_addr);
		uint8_t			value = (lhs & rhs);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, true);
		regs->setFlag(Registers::Flag::C, false);

		regs->incPC(1);
		return (8);
	}

	uint8_t				Instructions::AND ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_addr = regs->getPC() + 1;
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(imdt_addr);
		uint8_t			value = (lhs & rhs);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, true);
		regs->setFlag(Registers::Flag::C, false);

		regs->incPC(2);
		return (8);
	}

	// Logical OR N with register A then store in register A
	// Z - set if result is Zero
	// N - reset
	// H - reset
	// C - reset
	uint8_t				Instructions::OR ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = regs->getRegister(r);
		uint8_t			value = (lhs | rhs);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, false);

		regs->incPC(1);
		return (4);
	}

	uint8_t				Instructions::OR ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		rhs_addr = regs->getRegister(r);
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(rhs_addr);
		uint8_t			value = (lhs | rhs);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, false);

		regs->incPC(1);
		return (8);
	}

	uint8_t				Instructions::OR ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_addr = regs->getPC() + 1;
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(imdt_addr);
		uint8_t			value = (lhs | rhs);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, false);

		regs->incPC(2);
		return (8);
	}

	// Logical exclusive OR N with Register A then store in A
	// Z - set if result is Zero
	// N - reset
	// H - reset
	// C - reset
	uint8_t				Instructions::XOR ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = regs->getRegister(r);
		uint8_t			value = (lhs ^ rhs);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, false);

		regs->incPC(1);
		return (4);
	}

	uint8_t				Instructions::XOR ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		rhs_addr = regs->getRegister(r);
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(rhs_addr);
		uint8_t			value = (lhs ^ rhs);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, false);

		regs->incPC(1);
		return (8);
	}

	uint8_t				Instructions::XOR ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_addr = regs->getPC() + 1;
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(imdt_addr);
		uint8_t			value = (lhs ^ rhs);

		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, false);

		regs->incPC(2);
		return (8);
	}

	// Compare A with N ( A - N )
	// Z - Set if result is zero. (Set if A = n.)
	// N - Set.
	// H - Set if no borrow from bit 4.
	// C - Set for no borrow. (Set if A < n.)
	uint8_t				Instructions::CP ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = regs->getRegister(r);
		uint8_t			value = lhs - rhs;

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, true);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) < (rhs & 0x0F)) );
		regs->setFlag(Registers::Flag::C, (lhs < rhs) );

		regs->incPC(1);
		return (4);
	}

	uint8_t				Instructions::CP ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		rhs_addr = regs->getRegister(r);
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(rhs_addr);
		uint8_t			value = lhs - rhs;

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, true);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) < (rhs & 0x0F)) );
		regs->setFlag(Registers::Flag::C, (lhs < rhs) );

		regs->incPC(1);
		return (8);
	}

	uint8_t				Instructions::CP ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_addr = regs->getPC() + 1;
		uint8_t			lhs = regs->getA();
		uint8_t			rhs = mem->getByteAt(imdt_addr);
		uint8_t			value = lhs - rhs;

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, true);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) < (rhs & 0x0F)) );
		regs->setFlag(Registers::Flag::C, (lhs < rhs) );

		regs->incPC(2);
		return (8);
	}

	// Increment N
	// Z - Set if result is zero.
	// N - Reset.
	// H - Set if carry from bit 3.
	// C - Not affected.
	uint8_t				Instructions::INC_N ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r) + 1;

		regs->setRegister(r, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, ((value & 0x0F) ? false : true) );

		regs->incPC(1);
		return (4);
	}

	uint8_t				Instructions::INC_N ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr) + 1;

		mem->setByteAt(value_addr, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, ((value & 0x0F) ? false : true) );

		regs->incPC(1);
		return (12);
	}

	// Decrement N
	// Z - if result is zero
	// N - set
	// H - set if no borrow from bit 4.
	// C - Not affected.
	uint8_t				Instructions::DEC_N ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r) - 1;

		regs->setRegister(r, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, true);
		regs->setFlag(Registers::Flag::H, ((value & 0x0F) == 0x0F) );

		regs->incPC(1);
		return (4);
	}

	uint8_t				Instructions::DEC_N ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr) - 1;

		mem->setByteAt(value_addr, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, true);
		regs->setFlag(Registers::Flag::H, ((value & 0x0F) == 0x0F) );

		regs->incPC(1);
		return (12);
	}

	// Decimal Adjust register A
	// Z - Set if register A is zero.
	// N - Not affected.
	// H - Reset.
	// C - Set according to operation.
	uint8_t				Instructions::DAA ( Registers* regs )
	{
		int16_t 	value = regs->getA();
    
	    if (regs->getFlag(Registers::Flag::N) == false)
	    {
	        if (regs->getFlag(Registers::Flag::H) == true
	        	|| (value & 0xF) > 0x09)
	            value += 0x06;
	        
	        if (regs->getFlag(Registers::Flag::C) == true
	        	|| value > 0x9F)
	            value += 0x60;
	    }
	    else
	    {
	        if (regs->getFlag(Registers::Flag::H) == true)
	            value = (value - 6) & 0xFF;
	        
	        if (regs->getFlag(Registers::Flag::C) == true)
	            value -= 0x60;
	    }
	    regs->setA((value & 0xFF));

	    regs->setFlag(Registers::Flag::Z, ((value & 0xFF) == 0) );
	    regs->setFlag(Registers::Flag::H, false);
	    if ((value & 0x100) == 0x100)
	    	regs->setFlag(Registers::Flag::C, true );

		regs->incPC(1);
		return (4);
	}

	// Compliment register A
	// Z- Not affected.
	// N- Set.
	// H- Set.
	// C- Not affected.
	uint8_t				Instructions::CPL ( Registers* regs )
	{
		uint8_t			value = regs->getA();

		value = ~value;
		regs->setA(value);

		regs->setFlag(Registers::Flag::N, true);
	    regs->setFlag(Registers::Flag::H, true);

		regs->incPC(1);
		return (4);
	}

	// Compliment Carry Flag
	// Z - Not affected.
	// N - Reset.
	// H - Reset.
	// C - Complemented.
	uint8_t				Instructions::CCF ( Registers* regs )
	{
		regs->setFlag(Registers::Flag::N, false);
	    regs->setFlag(Registers::Flag::H, false);

	    if (regs->getFlag(Registers::Flag::C) == true)
	    	regs->setFlag(Registers::Flag::C, false);
	    else
	    	regs->setFlag(Registers::Flag::C, true);

		regs->incPC(1);
		return (4);
	}

	// Set Carry flag
	// Z - Not affected.
	// N - Reset.
	// H - Reset.
	// C - Set.
	uint8_t				Instructions::SCF ( Registers* regs )
	{
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, true);

		regs->incPC(1);
		return (4);
	}

	/*********************************************************************
	**************************** 16Bits ALU ******************************
	*********************************************************************/

	// Addition HL AND N then store in register HL
	// Z - Not affected.
	// N - Reset.
	// H - Set if carry from bit 11.
	// C - Set if carry from bit 15.
	uint8_t				Instructions::ADD_HL_N ( Registers* regs, Registers::Word const& r )
	{
		uint16_t		lhs = regs->getHL();
		uint16_t		rhs = regs->getRegister(r);
		uint32_t		result = lhs + rhs;
		uint16_t		value = (result & 0xFFFF);

		regs->setHL(value);

		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0FFF) + (rhs & 0x0FFF) > 0x0FFF) );
		regs->setFlag(Registers::Flag::C, (result > 0xFFFF) );

		regs->incPC(1);
		return (8);
	}

	// Addition 8bits signed immediate value with register SP then store in register SP
	// Z - Reset.
	// N - Reset.
	// H - Set or reset according to operation.
	// C - Set or reset according to operation.
	uint8_t				Instructions::ADD_SP_N ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_addr = regs->getPC() + 1;
		uint16_t		lhs = regs->getSP();
		int8_t			rhs = mem->getByteAt(imdt_addr);
		uint16_t		value = lhs + rhs;

		regs->setSP(value);

		regs->setFlag(Registers::Flag::Z, false);
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, ((lhs & 0x0F) + (rhs & 0x0F) > 0x0F) );
		regs->setFlag(Registers::Flag::C, ((lhs & 0xFF) + (rhs & 0xFF) > 0xFF) );

		regs->incPC(2);
		return (16);
	}

	// increment NN 
	uint8_t				Instructions::INC_NN ( Registers* regs, Registers::Word const& r )
	{
		uint16_t		value = regs->getRegister(r) + 1;

		regs->setRegister(r, value);
		regs->incPC(1);
		return (8);
	}

	// decrement NN
	uint8_t				Instructions::DEC_NN ( Registers* regs, Registers::Word const& r )
	{
		uint16_t		value = regs->getRegister(r) - 1;

		regs->setRegister(r, value);
		regs->incPC(1);
		return (8);
	}

	/*********************************************************************
	************************** MISC / CONTROL ****************************
	*********************************************************************/
	// No Operation
	uint8_t 				Instructions::NOP ( Registers* regs )
	{
		regs->incPC(1);
		return (4);
	}

	// Power Down _cpu until interupt occurs
	uint8_t				Instructions::HALT ( Registers* regs )
	{
		_cpu->setHALT(true);
		regs->incPC(1);
		return (4);
	}

	// Hatl _cpu & LCD until button pressed
	uint8_t				Instructions::STOP ( Registers* regs )
	{
		// Game boy color reclaim the speed switching via STOP is switching is enable ( IOREG KEY1 )
		if (_cpu->cartridge()->colorGB() && _cpu->cartridge()->colorCart())
			_cpu->switchSpeed(); 
		regs->incPC(2);
		return (4);
	}

	// Disable Interrupts
	uint8_t				Instructions::DI ( Registers* regs )
	{
		_cpu->interruptController()->setIME(false);
		regs->incPC(1);
		return (4);
	}

	// Enable Interrupts
	uint8_t				Instructions::EI ( Registers* regs )
	{
		_cpu->interruptController()->setIME(true);
		regs->incPC(1);
		return (4);
	}

	// Jump at 16bits immediate address
	uint8_t				Instructions::JP ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_addr = regs->getPC() + 1;
		uint16_t		imdt_value = mem->getWordAt(imdt_addr);

		regs->setPC(imdt_value);
		return (16);
	}

	// JP if Flag Z is Set
	uint8_t				Instructions::JP_Z ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::Z) == true)
			return (JP(regs, mem));
		regs->incPC(3);
		return (12);
	}

	// JP if Flag Z is Reset
	uint8_t				Instructions::JP_NZ ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::Z) == false)
			return (JP(regs, mem));
		regs->incPC(3);
		return (12);
	}

	// JP if Flag C is Set
	uint8_t				Instructions::JP_C ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::C) == true)
			return (JP(regs, mem));
		regs->incPC(3);
		return (12);
	}

	// JP if Flag C is Reset
	uint8_t				Instructions::JP_NC ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::C) == false)
			return (JP(regs, mem));
		regs->incPC(3);
		return (12);
	}

	// Jump at address contain in HL
	uint8_t				Instructions::JP_HL ( Registers* regs, Memory* mem )
	{
		uint16_t		value = regs->getHL();

		regs->setPC(value);
		return (4);
	}

	// Add 8bits signed immediate value to current adress and Jump to it
	uint8_t				Instructions::JR ( Registers* regs, Memory* mem )
	{
		uint16_t		imdt_addr = regs->getPC() + 1;
		int8_t			imdt_value = mem->getByteAt(imdt_addr);
		uint16_t		value = regs->getPC() + 2 + imdt_value;

		regs->setPC(value);
		return (12);
	}

	// JR if Flag Z is Set
	uint8_t				Instructions::JR_Z ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::Z) == true)
			return (JR(regs, mem));
		regs->incPC(2);
		return (8);
	}

	// JR if Flag Z is Reset
	uint8_t				Instructions::JR_NZ ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::Z) == false)
			return (JR(regs, mem));
		regs->incPC(2);
		return (8);
	}

	// JR if Flag C is Set
	uint8_t				Instructions::JR_C ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::C) == true)
			return (JR(regs, mem));
		regs->incPC(2);
		return (8);
	}

	// JR if Flag C is Reset
	uint8_t				Instructions::JR_NC ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::C) == false)
			return (JR(regs, mem));
		regs->incPC(2);
		return (8);
	}

	// push address of next instruction onto the stack and jump at 16bits immediate address
	uint8_t				Instructions::CALL ( Registers* regs, Memory* mem )
	{
		uint16_t		nextop_addr = regs->getPC() + 3;
		uint16_t		imdt_addr = regs->getPC() + 1;
		uint16_t		imdt_value = mem->getWordAt(imdt_addr);

		regs->decSP(2);
		mem->setWordAt(regs->getSP(), nextop_addr);
		regs->setPC(imdt_value);
		return (24);
	}

	// Call if Z flag is Set
	uint8_t				Instructions::CALL_Z ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::Z) == true)
			return(CALL(regs, mem));
		regs->incPC(3);
		return (12);
	}

	// Call if Z flag is Reset
	uint8_t				Instructions::CALL_NZ ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::Z) == false)
			return(CALL(regs, mem));
		regs->incPC(3);
		return (12);
	}

	// Call if C flag is Set
	uint8_t				Instructions::CALL_C ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::C) == true)
			return(CALL(regs, mem));
		regs->incPC(3);
		return (12);
	}

	// Call if C flag is Reset
	uint8_t				Instructions::CALL_NC ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::C) == false)
			return(CALL(regs, mem));
		regs->incPC(3);
		return (12);
	}

	// Push current adress onto the stack and jump at new address
	uint8_t				Instructions::RST ( Registers* regs, Memory* mem, uint16_t const& addr )
	{
		uint16_t		current_addr = regs->getPC() + 1;

		regs->decSP(2);
		mem->setWordAt(regs->getSP(), current_addr);
		regs->setPC(addr);
		return (16);
	}

	// Pop two byte from stack and jump to that address
	uint8_t				Instructions::RET ( Registers* regs, Memory* mem )
	{
		uint16_t		addr = mem->getWordAt(regs->getSP());

		regs->incSP(2);
		regs->setPC(addr);
		return (16);
	}

	// Ret if flag Z is Set
	uint8_t				Instructions::RET_Z ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::Z) == true)
			return (RET(regs, mem) + 4);
		regs->incPC(1);
		return (8);
	}

	// Ret if flag Z is Reset
	uint8_t				Instructions::RET_NZ ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::Z) == false)
			return (RET(regs, mem) + 4);
		regs->incPC(1);
		return (8);
	}

	// Ret if flag C is Set
	uint8_t				Instructions::RET_C ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::C) == true)
			return (RET(regs, mem) + 4);
		regs->incPC(1);
		return (8);
	}

	// Ret if flag C is Reset
	uint8_t				Instructions::RET_NC ( Registers* regs, Memory* mem )
	{
		if (regs->getFlag(Registers::Flag::C) == false)
			return (RET(regs, mem) + 4);
		regs->incPC(1);
		return (8);
	}

	// Pop two byte from stack and jump to that address then enable interupts
	uint8_t				Instructions::RETI ( Registers* regs, Memory* mem )
	{
		uint16_t		addr = mem->getWordAt(regs->getSP());

		_cpu->interruptController()->setIME(true);
		regs->incSP(2);
		regs->setPC(addr);
		return (16);
	}

	/*********************************************************************
	*************************** Bit OPERATION ****************************
	*********************************************************************/

	// Rotate register A left. Old bit 7 to Carry flag.
	// Z - reset
	// N - reset
	// H - reset
	// C - Contains old bit 7 data.
	uint8_t				Instructions::RLCA ( Registers* regs )
	{
		uint8_t			value = regs->getA();
		bool			bit7 = BIT_7(value);

		value = (value << 1) | bit7;
		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, false);
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit7);

		regs->incPC(1);
		return (4);
	}

	// Rotate register A left through Carry flag.
	// Z - reset
	// N - reset
	// H - reset
	// C - Contains old bit 7 data.
	uint8_t				Instructions::RLA ( Registers* regs )
	{
		uint8_t			value = regs->getA();
		bool			bit7 = BIT_7(value);

		value = (value << 1) | regs->getFC();
		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, false);
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit7);

		regs->incPC(1);
		return (4);
	}

	// Rotate register A right. Old bit 0 to Carry flag.
	// Z - reset
	// N - reset
	// H - reset
	// C - Contains old bit 0 data.
	uint8_t				Instructions::RRCA ( Registers* regs )
	{
		uint8_t			value = regs->getA();
		bool			bit0 = BIT_0(value);

		value = (bit0 << 7) | (value >> 1);
		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, false);
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit0);

		regs->incPC(1);
		return (4);
	}

	// Rotate register A right through Carry flag.
	// Z - reset
	// N - reset
	// H - reset
	// C - Contains old bit 0 data.
	uint8_t				Instructions::RRA ( Registers* regs )
	{
		uint8_t			value = regs->getA();
		bool			bit0 = BIT_0(value);

		value = (regs->getFC() << 7) | (value >> 1);
		regs->setA(value);

		regs->setFlag(Registers::Flag::Z, false);
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit0);

		regs->incPC(1);
		return (4);
	}

	/*********************************************************************
	************************* CB Bit OPERATION ***************************
	*********************************************************************/

	// Swap low nibble and hight nibble of register
	// Z - Set if result is zero.
	// N - Reset.
	// H - Reset.
	// C - Reset.
	uint8_t				Instructions::SWAP ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r);

		value = (BITS_0_3(value) << 4) | BITS_4_7(value);
		regs->setRegister(r, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, false);

		regs->incPC(2);
		return (8);
	}

	uint8_t				Instructions::SWAP ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr);

		value = (BITS_0_3(value) << 4) | BITS_4_7(value);
		mem->setByteAt(value_addr, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, false);

		regs->incPC(2);
		return (16);
	}

	// Rotate Byte register r left. Old bit 7 to Carry flag.
	// Z - set if result is zero
	// N - reset
	// H - reset
	// C - Contains old bit 7 data.
	uint8_t				Instructions::RLC ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r);
		bool			bit7 = BIT_7(value);

		value = (value << 1) | bit7;
		regs->setRegister(r, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit7);

		regs->incPC(2);
		return (8);
	}

	uint8_t				Instructions::RLC ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr);
		bool			bit7 = BIT_7(value);

		value = (value << 1) | bit7;
		mem->setByteAt(value_addr, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit7);

		regs->incPC(2);
		return (16);
	}

	// Rotate Byte left through Carry flag.
	// Z - set if result is zero
	// N - reset
	// H - reset
	// C - Contains old bit 7 data.
	uint8_t				Instructions::RL ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r);
		bool			bit7 = BIT_7(value);

		value = (value << 1) | regs->getFC();
		regs->setRegister(r, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit7);

		regs->incPC(2);
		return (8);
	}

	uint8_t				Instructions::RL ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr);
		bool			bit7 = BIT_7(value);

		value = (value << 1) | regs->getFC();
		mem->setByteAt(value_addr, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit7);

		regs->incPC(2);
		return (16);
	}

	// Rotate Byte right. Old bit 0 to Carry flag.
	// Z - set if result is zero
	// N - reset
	// H - reset
	// C - Contains old bit 0 data.
	uint8_t				Instructions::RRC ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r);
		bool			bit0 = BIT_0(value);

		value = (bit0 << 7) | (value >> 1);
		regs->setRegister(r, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit0);

		regs->incPC(2);
		return (8);
	}

	uint8_t				Instructions::RRC ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr);
		bool			bit0 = BIT_0(value);

		value = (bit0 << 7) | (value >> 1);
		mem->setByteAt(value_addr, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit0);

		regs->incPC(2);
		return (16);
	}

	// Rotate Byte right through Carry flag.
	// Z - set if result is zero
	// N - reset
	// H - reset
	// C - Contains old bit 0 data.
	uint8_t				Instructions::RR ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r);
		bool			bit0 = BIT_0(value);

		value = (regs->getFC() << 7) | (value >> 1);
		regs->setRegister(r, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit0);

		regs->incPC(2);
		return (8);
	}

	uint8_t				Instructions::RR ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr);
		bool			bit0 = BIT_0(value);

		value = (regs->getFC() << 7) | (value >> 1);
		mem->setByteAt(value_addr, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit0);

		regs->incPC(2);
		return (16);
	}

	// Shift Byte register r left. Old bit 7 to Carry flag. Lowest bit set to 0
	// Z - set if result is zero
	// N - reset
	// H - reset
	// C - Contains old bit 7 data.
	uint8_t				Instructions::SLA ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r);
		bool			bit7 = BIT_7(value);

		value = value << 1;
		regs->setRegister(r, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit7);

		regs->incPC(2);
		return (8);
	}

	uint8_t				Instructions::SLA ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr);
		bool			bit7 = BIT_7(value);

		value = value << 1;
		mem->setByteAt(value_addr, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit7);

		regs->incPC(2);
		return (16);
	}

	// Rotate Byte right. Old bit 0 to Carry flag. Hightest bit doesn't change
	// Z - set if result is zero
	// N - reset
	// H - reset
	// C - Contains old bit 0 data.
	uint8_t				Instructions::SRA ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r);
		bool			bit0 = BIT_0(value);
		bool			bit7 = BIT_7(value);

		value = (bit7 << 7) | (value >> 1);
		regs->setRegister(r, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit0);

		regs->incPC(2);
		return (8);
	}

	uint8_t				Instructions::SRA ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr);
		bool			bit0 = BIT_0(value);
		bool			bit7 = BIT_7(value);

		value = (bit7 << 7) | (value >> 1);
		mem->setByteAt(value_addr, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit0);

		regs->incPC(2);
		return (16);
	}

	// Rotate Byte right. Old bit 0 to Carry flag. Hightest bit set to 0
	// Z - set if result is zero
	// N - reset
	// H - reset
	// C - Contains old bit 0 data.
	uint8_t				Instructions::SRL ( Registers* regs, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r);
		bool			bit0 = BIT_0(value);

		value = value >> 1;
		regs->setRegister(r, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit0);

		regs->incPC(2);
		return (8);
	}

	uint8_t				Instructions::SRL ( Registers* regs, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr);
		bool			bit0 = BIT_0(value);

		value = value >> 1;
		mem->setByteAt(value_addr, value);

		regs->setFlag(Registers::Flag::Z, (value == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, false);
		regs->setFlag(Registers::Flag::C, bit0);

		regs->incPC(2);
		return (16);
	}

	// Test Bit b of Byte.
	// Z - Set if bit b is 0.
	// N - Reset.
	// H - Set.
	uint8_t				Instructions::BIT ( Registers* regs, uint8_t const& b, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r);
		bool			bit = BIT_N(b, value);

		regs->setFlag(Registers::Flag::Z, (bit == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, true);

		regs->incPC(2);
		return (8);
	}

	uint8_t				Instructions::BIT ( Registers* regs, uint8_t const& b, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr);
		bool			bit = BIT_N(b, value);

		regs->setFlag(Registers::Flag::Z, (bit == 0) );
		regs->setFlag(Registers::Flag::N, false);
		regs->setFlag(Registers::Flag::H, true);

		regs->incPC(2);
		return (12);
	}

	// Reset Bit b of Byte.
	uint8_t				Instructions::RES ( Registers* regs, uint8_t const& b, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r);

		RESBIT(b, value);
		regs->setRegister(r, value);
		
		regs->incPC(2);
		return (8);
	}

	uint8_t				Instructions::RES ( Registers* regs, uint8_t const& b, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr);
		
		RESBIT(b, value);
		mem->setByteAt(value_addr, value);
		
		regs->incPC(2);
		return (16);
	}

	// Set Bit b of Byte.
	uint8_t				Instructions::SET ( Registers* regs, uint8_t const& b, Registers::Byte const& r )
	{
		uint8_t			value = regs->getRegister(r);

		SETBIT(b, value);
		regs->setRegister(r, value);
		
		regs->incPC(2);
		return (8);
	}

	uint8_t				Instructions::SET ( Registers* regs, uint8_t const& b, Registers::Word const& r, Memory* mem )
	{
		uint16_t		value_addr = regs->getRegister(r);
		uint8_t			value = mem->getByteAt(value_addr);
		
		SETBIT(b, value);
		mem->setByteAt(value_addr, value);
		
		regs->incPC(2);
		return (16);
	}
}
