// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Gb.class.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/20 14:39:19 by hestela           #+#    #+#             //
//   Updated: 2015/12/20 14:39:19 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GB_CLASS_HPP
# define GB_CLASS_HPP

# include <thread>
# include <unistd.h>
# include <ctime>
# include <fstream>

# include "IScreen.class.hpp"
# include "IKeyPad.class.hpp"
# include "IDebugger.class.hpp"

# define FRAME_PERSEC 60

namespace Gbmu
{

	class Cpu;
	class Debugger;

	class Gb
	{
		public:
			enum Model
			{
				Auto,
				DMG,
				CGB
			};

		private:
			Gb::Model 		_model;			// Gb model
			Cpu*			_cpu;			// the gameboy CPU
			Debugger*		_debugger;		// the gameboy debugger
			std::thread*	_thread;		// running thread
			bool			_play;			// playing flag
			size_t			_speed;			// running speed

		public:
			Gb( void );
			virtual ~Gb( void );

			// Load a cartridge
			void			load ( std::string const& cartridgePath );
			bool			saveState ( std::string const& path );
			bool			loadState ( std::string const& path );
			
			// set your gui screen to gameBoy screen
			void			setScreen ( IScreen* screen );

			// the the GameBoy model to use
			void			setModel ( Gb::Model const& model);

			// Controls
			void			play ( void );
			void			pause ( void );
			void			reset ( void );
			void			setSpeed ( size_t const& speed); // x1 , x2, ........
			void			mute ( bool const& b );

			// Infos
			bool			isLoaded ( void ) const;
			bool			isRunning ( void ) const;
			size_t			speed ( void ) const;
			Gb::Model		model ( void ) const;
			std::string		gameTitle ( void ) const;

			// components
			IDebugger*		debugger ( void ) const;
			IKeyPad*		keyPad ( void ) const;

		private:
			void			run ( void );		
	};

}

#else
	namespace Gbmu
	{
		class Gb;
	}
#endif // !GB_CLASS_HPP
