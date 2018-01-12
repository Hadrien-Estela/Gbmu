// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Cpu.class.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/20 14:31:37 by hestela           #+#    #+#             //
//   Updated: 2015/12/20 14:31:38 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Cpu.class.hpp"

namespace Gbmu
{

	Cpu::Cpu ( void ):
		_bios ( new Bios(this) ),
		_registers( new Registers ),
		_instructions( new Instructions(this) ),
		_memory( new Memory(this) ),
		_cartridge(NULL),
		_IO( new SerialIO(this) ),
		_dma ( new Dma(this) ),
		_interruptCtl( new InterruptController(this) ),
		_lcdCtl( new LcdController(this) ),
		_timerCtl( new TimerController(this) ),
		_linkCtl( new LinkController(this) ),
		_soundCtl( new SoundController(this) ),
		_keyPad( new KeyPad(this) ),
		_BOOT(true),
		_HALT(false),
		_doubleSpeed(false)
	{ }

	Cpu::~Cpu ( void )
	{
		delete _bios;
		delete _registers;
		delete _instructions;
		delete _memory;
		if (_cartridge)
			delete _cartridge;
		delete _dma;
		delete _IO;
		delete _interruptCtl;
		delete _lcdCtl;
		delete _timerCtl;
		delete _linkCtl;
		delete _soundCtl;
		delete _keyPad;
	}

	void				Cpu::reset ( void )
	{
		_registers->reset();
		_memory->reset();
		if (_cartridge)
		{
			_cartridge->reset();
			if (_cartridge->colorGB())
				_registers->setA(0x11);
			else
				_registers->setA(0x01);
		}
		_IO->reset();
		_dma->reset();
		_interruptCtl->reset();
		_lcdCtl->reset();
		_timerCtl->reset();
		_linkCtl->reset();
		_soundCtl->reset();
		_keyPad->reset();
		_BOOT = true;
		_HALT = false;
		_doubleSpeed = false;
	}

	void				Cpu::loadCartridge ( std::string const& cartridgePath, Gb::Model const& model )
	{
		if (_cartridge)
		{
			delete _cartridge;
			_cartridge = NULL;
		}
		try
		{
			_cartridge = new Cartridge(this, cartridgePath, model);
		}
		catch (Exception const& e)
		{
			std::cout << e.what() << std::endl;
			delete _cartridge;
			_cartridge = NULL;
		}
		reset();
	}

	void				Cpu::executeFrame ( void )
	{
		size_t			cycles = 0;

		while (cycles < FRAME_CYCLES)
			cycles += execute();
	}

	size_t				Cpu::execute ( void )
	{
		size_t		cycles = 0;
		uint8_t		opcode = _memory->getByteAt(_registers->getPC());		

		if (!_HALT)
		{
			try
			{
				cycles = _instructions->doInstruction(opcode);
			}
			catch (Exception const& e)
			{
				std::cout << e.what() << std::endl;
				reset();
			}
		}
		else
			cycles = 4;

		// if an interrupt occured cycles take 20 cause the interrupt procedure ( DI + PUSH )
		if (_interruptCtl->update())
			cycles += 20;

		// case CPU operate in Double Speed (CGB  ONLY)
		if (_doubleSpeed)
			cycles /= 2;

		_lcdCtl->update(cycles);
		_timerCtl->update(cycles);
		_linkCtl->update(cycles);
		_soundCtl->update(cycles);
		
		return (cycles);
	}

	void					Cpu::onWriteKey1 ( uint8_t const& value )
	{
		// Keep the speed flag, only change the enabe flag
		_IO->registers()->KEY1 = (_IO->registers()->KEY1 & 0b10000000) | (value & 0b00000001);
	}

	void					Cpu::switchSpeed ( void )
	{
		if (BIT_0(_IO->registers()->KEY1))
		{
			if (BIT_7(_IO->registers()->KEY1))
			{
				_IO->registers()->KEY1 = 0x00;
				_doubleSpeed = false;
			}
			else
			{
				_IO->registers()->KEY1 = 0x80;
				_doubleSpeed = true;
			}
		}
	}

	void					Cpu::setHALT ( bool const& b ) 			{ _HALT = b; }
	void					Cpu::stopBOOT ( void )					{ _BOOT = false; }

	bool const&				Cpu::onHalt ( void ) const				{ return (_HALT); }
	bool const&				Cpu::onBoot ( void ) const				{ return (_BOOT); }

	Bios*					Cpu::bios ( void ) const				{ return (_bios); }
	Registers*				Cpu::registers ( void ) const			{ return (_registers); }
	Instructions*			Cpu::instructions ( void ) const		{ return (_instructions); }
	Memory*					Cpu::memory ( void ) const				{ return (_memory); }
	Cartridge*				Cpu::cartridge ( void ) const			{ return (_cartridge); }
	Dma*					Cpu::dma ( void ) const					{ return (_dma); }
	SerialIO*				Cpu::IO ( void ) const					{ return (_IO); }
	InterruptController*	Cpu::interruptController ( void ) const	{ return (_interruptCtl); }
	LcdController*			Cpu::lcdController ( void ) const		{ return (_lcdCtl); }
	TimerController*		Cpu::timerController ( void ) const		{ return (_timerCtl); }
	LinkController*			Cpu::linkController ( void ) const		{ return (_linkCtl); }
	SoundController*		Cpu::soundController ( void ) const		{ return (_soundCtl); }
	KeyPad*					Cpu::keyPad ( void ) const				{ return (_keyPad); }

	/**************************************************************************/
	/******************************* SAVE STATE *******************************/
	/**************************************************************************/

	void					Cpu::saveState ( std::fstream& file )
	{
		// save vars
		file.write((char*)&_BOOT, sizeof(_BOOT));
		file.write((char*)&_HALT, sizeof(_HALT));
		file.write((char*)&_doubleSpeed, sizeof(_doubleSpeed));
		// save registers
		_registers->saveState(file);
		// save memory
		_memory->saveState(file);
		// save cartridge
		_cartridge->saveState(file);
		// save DMA
		_dma->saveState(file);
		// save InterruptCtl
		_interruptCtl->saveState(file);
		// save LCD ctl
		_lcdCtl->saveState(file);
		// save Timer Ctl
		_timerCtl->saveState(file);
		// save Link Ctl
		_linkCtl->saveState(file);
		// save sound Ctl
		_soundCtl->saveState(file);

	}

	void					Cpu::loadState ( std::fstream& file )
	{
		file.read((char*)&_BOOT, sizeof(_BOOT));
		file.read((char*)&_HALT, sizeof(_HALT));
		file.read((char*)&_doubleSpeed, sizeof(_doubleSpeed));
		// load registers
		_registers->loadState(file);
		// load memory
		_memory->loadState(file);
		// load cartridge
		_cartridge->loadState(file);
		// load DMA
		_dma->loadState(file);
		// load InterruptCtl
		_interruptCtl->loadState(file);
		// load LCD ctl
		_lcdCtl->loadState(file);
		// load Timer Ctl
		_timerCtl->loadState(file);
		// load Link Ctl
		_linkCtl->loadState(file);
		// load sound Ctl
		_soundCtl->loadState(file);
	}
}
