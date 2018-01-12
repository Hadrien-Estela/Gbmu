// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Dma.class.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/24 09:47:34 by hestela           #+#    #+#             //
//   Updated: 2016/01/24 09:47:34 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef DMA_CLASS_HPP
# define DMA_CLASS_HPP

# include <iostream>
# include <fstream>

# include "Cpu.class.hpp"
# include "Memory.class.hpp"
# include "SerialIO.class.hpp"
# include "Defines.hpp"

/*

	DMA perform direct memory transfert

************************* USED REGISTERS ************************
	
	-- DMA Register (DMA Transfer and Start Address) [0xFF46]
		The DMA Transfer (40*28 bit) from internal ROM or RAM ( $0000- $F19F)
		to the OAM ( address $FE00- $FE9F)

	****** CGB ONLY ******

	-- HDMA1 Register [0xFF51]
		hight nibble of source HDMA transfer address

	-- HDMA2 Register [0xFF52]
		low nibble of source HDMA transfer address

	-- HDMA3 Register [0xFF53]
		hight nibble of destination HDMA transfer address

	-- HDMA4 Register [0xFF54]
		low nibble of destination HDMA transfer address

	-- HDMA5 Register [0xFF55]
		Hdma Transfer controller

		BIT 0-6 :	number of line to transfer ( n + 1 )
					transfering 16 bytes * (n + 1)
		BIT 7:		General purpose DMA enabling

*/

namespace Gbmu
{

	class Dma
	{

		private:
			Cpu*							_cpu;			// get pointer to Cpu ( parent )
			Memory*							_memory;		// get a pointer to memory
			struct SerialIO::IORegisters*	_IOREGS;		// get a pointer to the IO registers
			bool							_HDMA;			// HDMA enable Flag (CGB ONLY)
			uint16_t						_sourceAddr;	// source address (CGB ONLY)
			uint16_t						_destAddr;		// destination address (CGB ONLY)
			int32_t							_nBytes;		// number of byte to transfer (CGB ONLY)

		public:
			Dma ( Cpu* cpu );
			virtual ~Dma ( void );

			void			reset ( void );
			void			update ( void );

			void			onWriteDMA ( uint8_t const& value );
			void			onWriteHDMA1 ( uint8_t const& value );
			void			onWriteHDMA2 ( uint8_t const& value );
			void			onWriteHDMA3 ( uint8_t const& value );
			void			onWriteHDMA4 ( uint8_t const& value );
			void			onWriteHDMA5 ( uint8_t const& value );
		
			void			saveState ( std::fstream& file );
			void			loadState ( std::fstream& file );
		
		private:
			void			DMA_Transfert ( uint8_t const& value );
			void			GDMA_Transfert ( uint8_t const& value );
			void			HDMA_Transfert ( void );
	};

}

#else
	namespace Gbmu
	{
		class Dma;
	}
#endif // !DMA_CLASS_HPP
