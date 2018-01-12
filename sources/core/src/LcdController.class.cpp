// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LcdController.class.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/31 15:19:48 by hestela           #+#    #+#             //
//   Updated: 2015/12/31 15:19:49 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "LcdController.class.hpp"

namespace Gbmu
{

	LcdController::LcdController ( Cpu* cpu ):
		_cpu(cpu),
		_IOREGS(_cpu->IO()->registers()),
		_cycles(0),
		_lcdDriver( new LcdDriver(cpu) )
	{ }

	LcdController::~LcdController ( void )
	{
		delete _lcdDriver;
	}

	void							LcdController::reset ( void )
	{
		_cycles = 0;
		_lcdDriver->reset();
	}

	void							LcdController::update ( uint8_t const& cycles )
	{
		_cycles += cycles;

		// Update if LCD controller on (BIT 7 LCDC)
		if (onOperation())
			updateStatus();
		else
		{
			if (_cycles >= FRAME_CYCLES)
				_cycles -= FRAME_CYCLES;
		}
	}

	// Write any value in LY will reset the register
	void							LcdController::onWriteLY ( void )
	{
		_IOREGS->LY = 0;
		LYC_LY_compare();
	}

	void							LcdController::onWriteLYC ( uint8_t const& value )
	{
		_IOREGS->LYC = value;
		LYC_LY_compare();
	}

	void							LcdController::onWriteLCDC ( uint8_t const& value )
	{
		bool		nextOnOperation = BIT_7(value);
		bool		prevOnOperation = onOperation();

		// if changes put operation OFF
		if (prevOnOperation && !nextOnOperation)
		{
			_IOREGS->LY = 0; // reset current updated line
			setMode(Mode::Mode_HBLANK); // begin Hblank mode
		}
		// if changes put operation ON
		else if (!prevOnOperation && nextOnOperation)
			LYC_LY_compare();

		_cycles = 0;
		_IOREGS->LCDC = value;
	}

	// If program write a value on stat Register
	// Keep actual mode and check changes on Interrupt mode enable
	void							LcdController::onWriteSTAT ( uint8_t const& value )
	{
		_IOREGS->STAT = (value & ~0b00000111) | (_IOREGS->STAT & 0b00000111);

		if (modeInterruptEnable(Mode::Mode_OAMRAM) && mode() == Mode::Mode_OAMRAM)
			_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::LCDC, true);

		if (modeInterruptEnable(Mode::Mode_VBLANK) && mode() == Mode::Mode_VBLANK)
			_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::LCDC, true);

		if (modeInterruptEnable(Mode::Mode_HBLANK) && mode() == Mode::Mode_HBLANK)
			_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::LCDC, true);

		LYC_LY_compare();
	}

	LcdDriver*						LcdController::lcdDriver ( void ) const	{ return (_lcdDriver); }

	/**************************************************************************/
	/**************************** PRIVATE METHODS *****************************/
	/**************************************************************************/

	// Check Lcd STAT changes due to cycles incrementation
	// the mode pattern is ( 2 - 3 - 0 - 2 - 3 - 0 .... 2 - 3 - 0 - 1)  
	void							LcdController::updateStatus ( void )
	{
		switch (mode())
		{
			case Mode::Mode_HBLANK: 
				HBlankMode();
				break;

			case Mode::Mode_VBLANK:
				VBlankMode();
				break;

			case Mode::Mode_OAMRAM:
				OAMSearchMode();
				break;

			case Mode::Mode_SCANLINE:
				TransferingMode();
				break;
		}
	}

	void							LcdController::HBlankMode ( void )
	{
		// If end of H-BLANK Period
		if (_cycles >= Cycles::Cycles_HBLANK)
		{
			_IOREGS->LY++;
			LYC_LY_compare();
			_cycles -= Cycles::Cycles_HBLANK;

			// if reach line 144 (vertical end of visible screen)
			// enter in V-BLANK mode
			if (_IOREGS->LY >= 144)
			{
				setMode(Mode::Mode_VBLANK);
				_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::V_BLANK, true);
				if (modeInterruptEnable(Mode::Mode_VBLANK))
					_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::LCDC, true);
				endOfFrame();
			}
			// Enter in Oam searching (new line procedure)
			else
			{
				setMode(Mode::Mode_OAMRAM);
				if (modeInterruptEnable(Mode::Mode_OAMRAM))
					_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::LCDC, true);
				// CGB ONLY
				_cpu->dma()->update();
			}
		}
	}

	void							LcdController::VBlankMode ( void )
	{
		// If end of V-BLANK Period for a line
		if (_cycles >= Cycles::Cycles_VBLANK)
		{
			_cycles -= Cycles::Cycles_VBLANK;

			// if reach line 153 (real end of screen)
			// Enter in Oam searching (new line procedure)
			// reset LY (begin a new screen)
			if (_IOREGS->LY >= 153)
			{
				_IOREGS->LY = 0;
				setMode(Mode::Mode_OAMRAM);
				if (modeInterruptEnable(Mode::Mode_OAMRAM))
					_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::LCDC, true);
			}
			else
				_IOREGS->LY++;
			LYC_LY_compare();
		}
	}

	void							LcdController::OAMSearchMode ( void )
	{
		// If end of OAM-RAM searching period
		// enter in Scanline mode
		if (_cycles >= Cycles::Cycles_OAMRAM)
		{
			 // getting all Sprites attributes
			_lcdDriver->oamSearching();

			_cycles -= Cycles::Cycles_OAMRAM;
			setMode(Mode::Mode_SCANLINE);
		}
	}

	void							LcdController::TransferingMode ( void )
	{
		// If end of Scanline period (transfert)
		// Enter in HBLANK period (horizontal end of visible screen)
		if (_cycles >= Cycles::Cycles_SCANLINE)
		{
			_cycles -= Cycles::Cycles_SCANLINE;
			setMode(Mode::Mode_HBLANK);
			if (modeInterruptEnable(Mode::Mode_HBLANK))
				_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::LCDC, true);

			// send a line to LCD
			_lcdDriver->transferLine();
		}
	}

	// Return BIT7 of LCDC (LcdController off/on)
	bool							LcdController::onOperation ( void ) const
	{
		return (BIT_7(_IOREGS->LCDC));
	}

	// return actual mode (BITS 01 of STAT)
	LcdController::Mode				LcdController::mode ( void ) const
	{
		return (static_cast<LcdController::Mode>(BITS_0_1(_IOREGS->STAT)));
	}

	// Set BITS 01 of stat at desired mode
	void							LcdController::setMode ( LcdController::Mode mode )
	{
		RESBIT(0, _IOREGS->STAT);
		RESBIT(1, _IOREGS->STAT);
		_IOREGS->STAT |= mode;
	}

	// Return the corresponding BIT in STAT for desired mode interruption enable
	bool							LcdController::modeInterruptEnable ( LcdController::Mode mode ) const
	{
		if (mode == Mode::Mode_HBLANK && BIT_3(_IOREGS->STAT))
			return (true);
		else if (mode == Mode::Mode_VBLANK && BIT_4(_IOREGS->STAT))
			return (true);
		else if (mode == Mode::Mode_OAMRAM && BIT_5(_IOREGS->STAT))
			return (true);
		return (false);
	}

	// compare LY to LYC
	void							LcdController::LYC_LY_compare ( void )
	{
		// IF LY = LYC, set the coincidence flag (BIT2 STAT)
		if (_IOREGS->LY == _IOREGS->LYC)
		{
			SETBIT(2, _IOREGS->STAT);
			// If interruption is enable on LY/LYC Coincidence
			// send an LCDC interrupt
			if (BIT_6(_IOREGS->STAT))
				_cpu->interruptController()->setInterrupt(InterruptController::Interrupt::LCDC, true);
		}
		// ELSE reset the coincidence flag (BIT2 STAT)
		else
			RESBIT(2, _IOREGS->STAT);
	}

	// End frame procedure
	void							LcdController::endOfFrame ( void )
	{
		_lcdDriver->flush();
		_cpu->soundController()->endFrame();
	}

	/**************************************************************************/
	/******************************* SAVE STATE *******************************/
	/**************************************************************************/

	void							LcdController::saveState ( std::fstream& file )
	{
		file.write((char*)&_cycles, sizeof(_cycles));
	}

	void							LcdController::loadState ( std::fstream& file )
	{
		file.read((char*)&_cycles, sizeof(_cycles));
	}
}
