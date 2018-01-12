// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bios.class.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/18 15:32:53 by hestela           #+#    #+#             //
//   Updated: 2016/01/18 15:32:54 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bios.class.hpp"

namespace Gbmu
{

	Bios::Bios ( Cpu* cpu ):
		_cpu(cpu)
	{ }

	Bios::~Bios ( void )
	{ }

	uint8_t const&		Bios::getByteAt ( uint16_t const& addr )
	{
		if (_cpu->cartridge()->colorGB())
			return (_cgbBios[addr]);
		return (_dmgBios[addr]);
	}

}
