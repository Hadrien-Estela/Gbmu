// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Cpu.class.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/20 14:31:28 by hestela           #+#    #+#             //
//   Updated: 2015/12/20 14:31:28 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CPU_CLASS_HPP
# define CPU_CLASS_HPP

# include <iostream>
# include <fstream>

# include "Exception.class.hpp"
# include "Bios.class.hpp"
# include "Registers.class.hpp"
# include "Instructions.class.hpp"
# include "Memory.class.hpp"
# include "Cartridge.class.hpp"
# include "Dma.class.hpp"
# include "SerialIO.class.hpp"
# include "InterruptController.class.hpp"
# include "LcdController.class.hpp"
# include "TimerController.class.hpp"
# include "LinkController.class.hpp"
# include "KeyPad.class.hpp"
# include "SoundController.class.hpp"

/*

************************* USED REGISTERS ************************

	-- KEY1 Register (Double speed switching) [0xFF4D] ( CGB ONLY )
		this register enable the double speed switching on CGB

		BIT 0: enable Switching
		BIT 7: Speed Flag ( 0:Normal | 1:Double )

*/

namespace Gbmu
{

	class Cpu
	{
		private:
			Bios*					_bios;				// Boot program class
			Registers*				_registers;			// Cpu registers
			Instructions*			_instructions;		// Cpu instructions set
			Memory*					_memory;			// GB General Memory
			Cartridge*				_cartridge;			// Cartridge
			SerialIO*				_IO;				// SerialIO from GB General Memory
			Dma*					_dma;				// Direct memory access
			InterruptController*	_interruptCtl;		// Interruption controller
			LcdController*			_lcdCtl;			// LCD Controller
			TimerController*		_timerCtl;			// Timer Controller
			LinkController*			_linkCtl;			// VBA Link Transfert Controller
			SoundController*		_soundCtl;			// Sound Controller
			KeyPad*					_keyPad;			// GB KeyPad
			bool					_BOOT;				// Booting Flag
			bool					_HALT;				// Halting Flag
			bool					_doubleSpeed;		// DoubleSpeed Flag (CGB ONLY)

		public:
			Cpu ( void );
			virtual ~Cpu ( void );

			void					reset ( void );
			void					loadCartridge ( std::string const& cartridgePath, Gb::Model const& model );
			
			void					executeFrame ( void );
			size_t					execute ( void );

			void					onWriteKey1 ( uint8_t const& value );
			void					switchSpeed ( void );

			void					setHALT ( bool const& b );
			void					stopBOOT ( void );

			bool const&				onHalt ( void ) const;
			bool const&				onBoot ( void ) const;

			Bios*					bios ( void ) const;
			Registers*				registers ( void ) const;
			Instructions*			instructions ( void ) const;
			Memory*					memory ( void ) const;
			Cartridge*				cartridge ( void ) const;
			Dma*					dma ( void ) const;
			SerialIO*				IO ( void ) const;
			InterruptController*	interruptController ( void ) const;
			LcdController*			lcdController ( void ) const;
			TimerController*		timerController ( void ) const;
			LinkController*			linkController ( void ) const;
			SoundController*		soundController ( void ) const;
			KeyPad*					keyPad ( void ) const;

			void					saveState ( std::fstream& file );
			void					loadState ( std::fstream& file );
	};

}

#else
	namespace Gbmu
	{
		class Cpu;
	}
#endif // !CPU_CLASS_HPP
