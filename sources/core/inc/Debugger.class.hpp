// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Debugger.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/16 10:06:14 by hestela           #+#    #+#             //
//   Updated: 2016/01/16 10:06:17 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef DEBUGGER_CLASS_HPP
# define DEBUGGER_CLASS_HPP

# include <iostream>
# include <sstream>
# include <iomanip>

# include "IDebugger.class.hpp"
# include "Cpu.class.hpp"

namespace Gbmu
{
		
	class Debugger: public IDebugger
	{

		private:
			Cpu*								_cpu; 			// Get pointer to the Cpu
			std::map<uint16_t, bool> 			_breakpoints;	// Breakpoints Table

		public:
			Debugger( Cpu* Cpu );
			virtual ~Debugger( void );

			void								reset ( void );

			void								executeStep ( void );
			void								executeFrame ( void );
			void								executeSecond ( void );

			std::vector<std::string>			disassembly ( void ) const;
			std::vector<std::string>			memory ( uint16_t addr) const;
			std::map<uint16_t, bool> const&		breakpoints ( void ) const;
			bool								setBreakpoint ( uint16_t const& addr );
			void								delBreakpoint ( uint16_t const& addr );
			void								setEnableBreakpoint ( uint16_t const& addr, bool const& b );

			std::string							getAF ( void ) const;
			std::string							getBC ( void ) const;
			std::string							getDE ( void ) const;
			std::string							getHL ( void ) const;
			std::string							getSP ( void ) const;
			std::string							getPC ( void ) const;
			std::string							getLCDC ( void ) const;
			std::string							getSTAT ( void ) const;
			std::string							getSCY ( void ) const;
			std::string							getSCX ( void ) const;
			std::string							getLY ( void ) const;
			std::string							getLYC ( void ) const;
			std::string							getDMA ( void ) const;
			std::string							getBGP ( void ) const;
			std::string							getOBP0 ( void ) const;
			std::string							getOBP1 ( void ) const;
			std::string							getWY ( void ) const;
			std::string							getWX ( void ) const;
			std::string							getBGPI ( void ) const;
			std::string							getBGPD ( void ) const;
			std::string							getOBPI ( void ) const;
			std::string							getOBPD ( void ) const;
			std::string							getP1 ( void ) const;
			std::string							getSB ( void ) const;
			std::string							getSC ( void ) const;
			std::string							getDIV ( void ) const;
			std::string							getTIMA ( void ) const;
			std::string							getTMA ( void ) const;
			std::string							getTAC ( void ) const;
			std::string							getKEY1 ( void ) const;
			std::string							getVBK ( void ) const;
			std::string							getHDMA1 ( void ) const;
			std::string							getHDMA2 ( void ) const;
			std::string							getHDMA3 ( void ) const;
			std::string							getHDMA4 ( void ) const;
			std::string							getHDMA5 ( void ) const;
			std::string							getSVBK ( void ) const;
			std::string							getIF ( void ) const;
			std::string							getIE ( void ) const;

		private:
			std::string							toHex ( int value, size_t len, char fill ) const;
			std::string							getInstructionDisassembly ( uint16_t addr ) const;
	};

}

#else
	namespace Gbmu
	{
		class Debugger;
	}
#endif // !DEBUGGER_CLASS_HPP
