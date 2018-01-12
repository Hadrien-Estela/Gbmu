// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Gb.class.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/20 14:39:53 by hestela           #+#    #+#             //
//   Updated: 2015/12/20 14:40:39 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Gb.class.hpp"
#include "Cpu.class.hpp"
#include "Debugger.class.hpp"

namespace Gbmu
{

	Gb::Gb( void ):
		_model(Gb::Model::Auto),
		_cpu(new Cpu),
		_debugger(new Debugger(_cpu)),
		_thread(NULL),
		_play(false),
		_speed(1)
	{ }

	Gb::~Gb( void )
	{
		pause();
		delete _cpu;
		delete _debugger;
	}

	void			Gb::load ( std::string const& cartridgePath )
	{
		pause();
		_cpu->loadCartridge(cartridgePath, _model);
	}

	bool			Gb::saveState ( std::string const& path )
	{
		std::fstream		file;

		file.open(path, std::fstream::out | std::fstream::trunc);
		if (!file.is_open())
			return (false);

		// write TITLE
		file.write((char*)_cpu->cartridge()->header().title, 0x10);
		// write state
		_cpu->saveState(file);

		file.close();
		return (true);
	}

	bool			Gb::loadState ( std::string const& path )
	{
		std::fstream		file;
		char				buf[0x10];

		file.open(path, std::fstream::in);
		if (!file.is_open())
			return (false);

		// check Title
		file.read(buf, 0x10);
		if (memcmp(buf, _cpu->cartridge()->header().title, 0x10))
		{
			file.close();
			return (false);
		}
		// load state
		_cpu->loadState(file);

		file.close();
		return (true);
	}


	void			Gb::play ( void )
	{
		if (_thread == NULL)
		{
			_thread = new std::thread(&Gb::run, this);
			_play = true;
		}
	}

	void			Gb::pause ( void )
	{
		if (_thread != NULL)
		{
			_play = false;
			_thread->join();
			delete _thread;
			_thread = NULL;
		}
	}

	void			Gb::reset ( void )
	{
		bool		playing = _play;

		pause();
		_cpu->reset();
		if (_cpu->cartridge())
			_cpu->cartridge()->setModel(_model);
		if (playing)
			play();
	}

	void			Gb::setSpeed ( size_t const& speed)
	{
		bool		playing = _play;

		pause();
		_speed = speed;
		_cpu->soundController()->setClockSpeed(speed);
		if (playing)
			play();
	}

	void			Gb::mute ( bool const& b )
	{
		_cpu->soundController()->enable(!b);
	}

	void			Gb::setScreen ( IScreen* screen )
	{
		_cpu->lcdController()->lcdDriver()->setScreen(screen);
	}

	void			Gb::setModel ( Gb::Model const& model)
	{
		_model = model;
	}

	bool			Gb::isLoaded ( void ) const 	{ return (_cpu->cartridge() ? true : false ); }
	bool			Gb::isRunning ( void ) const	{ return (_play); }
	size_t			Gb::speed ( void ) const		{ return (_speed); }
	std::string		Gb::gameTitle ( void ) const 	{ return (_cpu->cartridge()->title()); }
	Gb::Model		Gb::model ( void ) const		{ return (_model); }

	IDebugger*		Gb::debugger ( void ) const		{ return (_debugger); }
	IKeyPad*		Gb::keyPad ( void ) const		{ return (_cpu->keyPad()); }


	/**************************************************************************/
	/**************************** PRIVATE METHODS *****************************/
	/**************************************************************************/
	
	void			Gb::run ( void )
	{
		clock_t		begin;
		clock_t		end;
		double		frameTime;
		double 		elapsed;

		frameTime = 1000.0 / (60.0 * (double)_speed);
		while (1)
		{
			begin = clock();
			_cpu->executeFrame();
			end = clock();

			if (_play == false)
				break;

			elapsed = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000;
			if (frameTime > elapsed)
				usleep( (frameTime - elapsed) * 1000 );
		}
	}
}
