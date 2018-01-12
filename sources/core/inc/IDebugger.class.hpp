// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IDebugger.class.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/10 09:09:11 by hestela           #+#    #+#             //
//   Updated: 2016/01/10 09:09:12 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IDEBUGGER_CLASS_HPP
# define IDEBUGGER_CLASS_HPP

# include <map>
# include <vector>
# include <string>

namespace Gbmu
{
	
	class IDebugger
	{
		public:
			virtual ~IDebugger( void ) {}

			virtual void								reset ( void ) = 0;

			virtual void								executeStep ( void ) = 0;
			virtual void								executeFrame ( void ) = 0;
			virtual void								executeSecond ( void ) = 0;

			virtual std::vector<std::string>			disassembly ( void ) const = 0;
			virtual std::vector<std::string>			memory ( uint16_t addr) const = 0;
			virtual std::map<uint16_t, bool> const&		breakpoints ( void ) const = 0;
			virtual bool								setBreakpoint ( uint16_t const& addr ) = 0;
			virtual void								delBreakpoint ( uint16_t const& addr ) = 0;
			virtual void								setEnableBreakpoint ( uint16_t const& addr, bool const& b ) = 0;

			virtual std::string							getAF ( void ) const = 0;
			virtual std::string							getBC ( void ) const = 0;
			virtual std::string							getDE ( void ) const = 0;
			virtual std::string							getHL ( void ) const = 0;
			virtual std::string							getSP ( void ) const = 0;
			virtual std::string							getPC ( void ) const = 0;
			virtual std::string							getLCDC ( void ) const = 0;
			virtual std::string							getSTAT ( void ) const = 0;
			virtual std::string							getSCY ( void ) const = 0;
			virtual std::string							getSCX ( void ) const = 0;
			virtual std::string							getLY ( void ) const = 0;
			virtual std::string							getLYC ( void ) const = 0;
			virtual std::string							getDMA ( void ) const = 0;
			virtual std::string							getBGP ( void ) const = 0;
			virtual std::string							getOBP0 ( void ) const = 0;
			virtual std::string							getOBP1 ( void ) const = 0;
			virtual std::string							getWY ( void ) const = 0;
			virtual std::string							getWX ( void ) const = 0;
			virtual std::string							getBGPI ( void ) const = 0;
			virtual std::string							getBGPD ( void ) const = 0;
			virtual std::string							getOBPI ( void ) const = 0;
			virtual std::string							getOBPD ( void ) const = 0;
			virtual std::string							getP1 ( void ) const = 0;
			virtual std::string							getSB ( void ) const = 0;
			virtual std::string							getSC ( void ) const = 0;
			virtual std::string							getDIV ( void ) const = 0;
			virtual std::string							getTIMA ( void ) const = 0;
			virtual std::string							getTMA ( void ) const = 0;
			virtual std::string							getTAC ( void ) const = 0;
			virtual std::string							getKEY1 ( void ) const = 0;
			virtual std::string							getVBK ( void ) const = 0;
			virtual std::string							getHDMA1 ( void ) const = 0;
			virtual std::string							getHDMA2 ( void ) const = 0;
			virtual std::string							getHDMA3 ( void ) const = 0;
			virtual std::string							getHDMA4 ( void ) const = 0;
			virtual std::string							getHDMA5 ( void ) const = 0;
			virtual std::string							getSVBK ( void ) const = 0;
			virtual std::string							getIF ( void ) const = 0;
			virtual std::string							getIE ( void ) const = 0;
	};
	
}

#else
	namespace Gbmu
	{
		class IDebugger;
	}
#endif // !IDEBUGGER_CLASS_HPP
