// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SoundController.class.hpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/26 17:09:19 by hestela           #+#    #+#             //
//   Updated: 2016/01/26 17:09:26 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SOUNDCONTROLLER_CLASS_HPP
# define SOUNDCONTROLLER_CLASS_HPP

# include <fstream>

# include <GbSndEmu/Multi_Buffer.h>
# include <GbSndEmu/Gb_Apu.h>
# include <GbSndEmu/Sound_Queue.h>

# include "Cpu.class.hpp"
# include "SerialIO.class.hpp"

# define FRAME_LENGHT	10000
# define SAMPLE_SIZE	2048
# define CLOCK_RATE		4194304

namespace Gbmu
{
	
	class SoundController
	{

		private:
			Cpu*							_cpu;			// get pointer to Cpu ( parent )
			struct SerialIO::IORegisters*	_IOREGS;		// get a pointer to the IO registers 
			bool 							_enabled;
			uint32_t 						_time;
			uint32_t						_absoluteTime;
			uint32_t 						_sampleRate;
			Gb_Apu*							_apu;
			Stereo_Buffer*					_stereoBuffer;
			Sound_Queue*					_soundQueue;
			blip_sample_t*					_sampleBuffer;

		public:
			SoundController ( Cpu* cpu );
			~SoundController ( void );

			void 		reset ( void );
			void 		update ( uint8_t const& cycles );

			void		writeRegister ( uint16_t const& address, uint8_t const& value );
			uint8_t		readRegister ( uint16_t const& address );

			void		enable ( bool const& b );
			bool		isEnable ( void ) const;

			void		setClockSpeed ( size_t speed );

			void		endFrame ( void );

			void		saveState ( std::fstream& file );
			void		loadState ( std::fstream& file );

		private:
			void		init ( void );
	};

}

#else
	namespace Gbmu
	{
		class SoundController;
	}
#endif	// !SOUNDCONTROLLER_CLASS_HPP
