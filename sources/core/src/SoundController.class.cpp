// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SoundController.class.cpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/26 17:09:36 by hestela           #+#    #+#             //
//   Updated: 2016/01/26 17:10:14 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "SoundController.class.hpp"

namespace Gbmu
{

	SoundController::SoundController ( Cpu* cpu ):
		_cpu(cpu),
		_IOREGS(cpu->IO()->registers()),
		_enabled(true),
		_time(0),
		_absoluteTime(0),
		_sampleRate(44100),
		_apu(NULL),
		_stereoBuffer(NULL),
		_soundQueue(NULL),
		_sampleBuffer(NULL)
	{
		init();
	}

	SoundController::~SoundController ( void )
	{
		if (_apu)
			delete _apu;
		if (_stereoBuffer)
			delete _stereoBuffer;
		if (_soundQueue)
			delete _soundQueue;
		if (_sampleBuffer)
			delete[] _sampleBuffer;

		SDL_Quit();
	}

	void			SoundController::reset ( void )
	{
		Gb_Apu::mode_t			mode;
		uint16_t				reg = 0xFF10;

		if (_cpu->cartridge() && _cpu->cartridge()->colorGB())
			mode = Gb_Apu::mode_cgb;
		else
			mode = Gb_Apu::mode_dmg;

		while ( reg <= 0xFF3F)
		{
			_apu->write_register(0, reg, _cpu->memory()->data()[reg]);
			reg++;
		}

		_apu->reset(mode);
		_stereoBuffer->clear();
		_time = 0;
		_absoluteTime = 0;

		_soundQueue->stop();
		_soundQueue->start(_sampleRate, 2);
	}

	void			SoundController::update ( uint8_t const& cycles )
	{
		_time += cycles;
		_absoluteTime += cycles;

		if (_time >= FRAME_LENGHT)
		{
			endFrame();
			_time -= FRAME_LENGHT;
			_absoluteTime = 0;
		}
	}

	void			SoundController::writeRegister ( uint16_t const& address, uint8_t const& value )
	{
		_apu->write_register(_time, address, value);
	}

	uint8_t			SoundController::readRegister ( uint16_t const& address )
	{
		return _apu->read_register(_time, address);
	}

	void			SoundController::enable ( bool const& b )
	{
		_enabled = b;
	}

	bool			SoundController::isEnable ( void ) const
	{
		return (_enabled);
	}

	void			SoundController::setClockSpeed ( size_t speed )
	{
		_stereoBuffer->clock_rate(CLOCK_RATE * speed);
	}

	/**************************************************************************/
	/**************************** PRIVATE METHODS *****************************/
	/**************************************************************************/

	void			SoundController::init ( void )
	{
		if (SDL_Init(SDL_INIT_AUDIO) < 0)
			;

		_sampleBuffer = new blip_sample_t[SAMPLE_SIZE];
		_apu = new Gb_Apu();
		_stereoBuffer = new Stereo_Buffer();
		_soundQueue = new Sound_Queue();

		_stereoBuffer->clock_rate(CLOCK_RATE);
		_stereoBuffer->set_sample_rate(_sampleRate);

		_apu->treble_eq(-15.0);
		_stereoBuffer->bass_freq(100);

		_apu->set_output(_stereoBuffer->center(), _stereoBuffer->left(), _stereoBuffer->right());

		_soundQueue->start(_sampleRate, 2);
	}

	void			SoundController::endFrame ( void )
	{
		_apu->end_frame(_absoluteTime);
		_stereoBuffer->end_frame(_absoluteTime);

		if (_stereoBuffer->samples_avail() >= SAMPLE_SIZE)
		{
			long count = _stereoBuffer->read_samples(_sampleBuffer, SAMPLE_SIZE);
			if (_enabled)
				_soundQueue->write(_sampleBuffer, (int)count);
		}
	}

	/**************************************************************************/
	/******************************* SAVE STATE *******************************/
	/**************************************************************************/

	void			SoundController::saveState ( std::fstream& file )
	{
		struct gb_apu_state_t 		state;

		_apu->save_state(&state);

		file.write((char*)&_time, sizeof(_time));
		file.write((char*)&_absoluteTime, sizeof(_absoluteTime));
		file.write((char*)&state, sizeof(state));
	}

	void			SoundController::loadState ( std::fstream& file )
	{
		struct gb_apu_state_t 		state;

		file.read((char*)&_time, sizeof(_time));
		file.read((char*)&_absoluteTime, sizeof(_absoluteTime));
		file.read((char*)&state, sizeof(state));

		_apu->load_state(state);
	}

}
