// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Registers.class.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/20 18:18:27 by hestela           #+#    #+#             //
//   Updated: 2015/11/20 18:18:53 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Registers.class.hpp"

namespace Gbmu
{

	Registers::Registers ( void )
	{ }

	Registers::~Registers ( void ) {}

	void				Registers::reset ( void )
	{
		_af.word = 0x11B0;
		_bc.word = 0x0013;
		_de.word = 0x00D8;
		_hl.word = 0x014D;
		_sp.word = 0xFFFE;
		_pc.word = 0x0000;
	}

	void				Registers::setRegister ( Registers::Byte r, uint8_t const& n ) 
	{
		switch (r)
		{
			case Registers::Byte::A:
				setA(n);
				break;
			case Registers::Byte::B:
				setB(n);
				break;
			case Registers::Byte::C:
				setC(n);
				break;
			case Registers::Byte::D:
				setD(n);
				break;
			case Registers::Byte::E:
				setE(n);
				break;
			case Registers::Byte::H:
				setH(n);
				break;
			case Registers::Byte::L:
				setL(n);
				break;
		}
	}

	void				Registers::setRegister ( Registers::Word r, uint16_t const& nn )
	{
		switch (r)
		{
			case Registers::Word::AF:
				setAF(nn);
				break;
			case Registers::Word::BC:
				setBC(nn);
				break;
			case Registers::Word::DE:
				setDE(nn);
				break;
			case Registers::Word::HL:
				setHL(nn);
				break;
			case Registers::Word::PC:
				setPC(nn);
				break;
			case Registers::Word::SP:
				setSP(nn);
				break;
		}
	}

	void				Registers::setFlag ( Registers::Flag f, bool const& b )
	{
		switch (f)
		{
			case Registers::Flag::Z:
				setFZ(b);
				break;
			case Registers::Flag::N:
				setFN(b);
				break;
			case Registers::Flag::H:
				setFH(b);
				break;
			case Registers::Flag::C:
				setFC(b);
				break;
		}
	}

	uint8_t const&		Registers::getRegister ( Registers::Byte r ) const
	{
		switch (r)
		{
			case Registers::Byte::A:
				return (getA());
				break;
			case Registers::Byte::B:
				return (getB());
				break;
			case Registers::Byte::C:
				return (getC());
				break;
			case Registers::Byte::D:
				return (getD());
				break;
			case Registers::Byte::E:
				return (getE());
				break;
			case Registers::Byte::H:
				return (getH());
				break;
			case Registers::Byte::L:
				return (getL());
				break;
		}
	}

	uint16_t const&		Registers::getRegister ( Registers::Word r ) const
	{
		switch (r)
		{
			case Registers::Word::AF:
				return (getAF());
				break;
			case Registers::Word::BC:
				return (getBC());
				break;
			case Registers::Word::DE:
				return (getDE());
				break;
			case Registers::Word::HL:
				return (getHL());
				break;
			case Registers::Word::PC:
				return (getPC());
				break;
			case Registers::Word::SP:
				return (getSP());
				break;
		}
	}

	bool				Registers::getFlag ( Registers::Flag f ) const
	{
		switch (f)
		{
			case Registers::Flag::Z:
				return (getFZ());
				break;
			case Registers::Flag::N:
				return (getFN());
				break;
			case Registers::Flag::H:
				return (getFH());
				break;
			case Registers::Flag::C:
				return (getFC());
				break;
		}
		return (false);
	}

	void				Registers::incPC ( uint8_t const& x ) { _pc.word += x; }
	void				Registers::incSP ( uint8_t const& x ) { _sp.word += x; }
	void				Registers::decSP ( uint8_t const& x ) { _sp.word -= x; }

	void				Registers::setA ( uint8_t const& n ) { _af.byte[Hight] = n; }
	void				Registers::setF ( uint8_t const& n ) { _af.byte[Low] = n & 0xF0; }
	void				Registers::setB ( uint8_t const& n ) { _bc.byte[Hight] = n; }
	void				Registers::setC ( uint8_t const& n ) { _bc.byte[Low] = n; }
	void				Registers::setD ( uint8_t const& n ) { _de.byte[Hight] = n; }
	void				Registers::setE ( uint8_t const& n ) { _de.byte[Low] = n; }
	void				Registers::setH ( uint8_t const& n ) { _hl.byte[Hight] = n; }
	void				Registers::setL ( uint8_t const& n ) { _hl.byte[Low] = n; }

	void				Registers::setAF ( uint16_t const& nn ) { _af.word = nn & 0xFFF0; }
	void				Registers::setBC ( uint16_t const& nn ) { _bc.word = nn; }
	void				Registers::setDE ( uint16_t const& nn ) { _de.word = nn; }
	void				Registers::setHL ( uint16_t const& nn ) { _hl.word = nn; }
	void				Registers::setSP ( uint16_t const& nn ) { _sp.word = nn; }
	void				Registers::setPC ( uint16_t const& nn ) { _pc.word = nn; }

	void					Registers::setFZ ( bool const& b )
	{
		if (b)
			SETBIT(7, _af.byte[Low]);
		else
			RESBIT(7, _af.byte[Low]);
	};

	void					Registers::setFN ( bool const& b )
	{
		if (b)
			SETBIT(6, _af.byte[Low]);
		else
			RESBIT(6, _af.byte[Low]);
	};

	void					Registers::setFH ( bool const& b )
	{
		if (b)
			SETBIT(5, _af.byte[Low]);
		else
			RESBIT(5, _af.byte[Low]);
	};

	void					Registers::setFC ( bool const& b )
	{
		if (b)
			SETBIT(4, _af.byte[Low]);
		else
			RESBIT(4, _af.byte[Low]);
	};


	uint8_t const&			Registers::getA ( void ) const { return (_af.byte[Hight]); }
	uint8_t const&			Registers::getF ( void ) const { return (_af.byte[Low]); }
	uint8_t const&			Registers::getB ( void ) const { return (_bc.byte[Hight]); }
	uint8_t const&			Registers::getC ( void ) const { return (_bc.byte[Low]); }
	uint8_t const&			Registers::getD ( void ) const { return (_de.byte[Hight]); }
	uint8_t const&			Registers::getE ( void ) const { return (_de.byte[Low]); }
	uint8_t const&			Registers::getH ( void ) const { return (_hl.byte[Hight]); }
	uint8_t const&			Registers::getL ( void ) const { return (_hl.byte[Low]); }

	uint16_t const&			Registers::getAF ( void ) const { return (_af.word); }
	uint16_t const&			Registers::getBC ( void ) const { return (_bc.word); }
	uint16_t const&			Registers::getDE ( void ) const { return (_de.word); }
	uint16_t const&			Registers::getHL ( void ) const { return (_hl.word); }
	uint16_t const&			Registers::getSP ( void ) const { return (_sp.word); }
	uint16_t const&			Registers::getPC ( void ) const { return (_pc.word); }

	bool					Registers::getFZ ( void ) const { return ( BIT_7(getF()) ); }
	bool					Registers::getFN ( void ) const { return ( BIT_6(getF()) ); }
	bool					Registers::getFH ( void ) const { return ( BIT_5(getF()) ); }
	bool					Registers::getFC ( void ) const { return ( BIT_4(getF()) ); }

	/**************************************************************************/
	/******************************* SAVE STATE *******************************/
	/**************************************************************************/

	void					Registers::saveState ( std::fstream& file )
	{
		file.write((char*)&_af.word, sizeof(_af.word));
		file.write((char*)&_bc.word, sizeof(_bc.word));
		file.write((char*)&_de.word, sizeof(_de.word));
		file.write((char*)&_hl.word, sizeof(_hl.word));
		file.write((char*)&_sp.word, sizeof(_sp.word));
		file.write((char*)&_pc.word, sizeof(_pc.word));
	}

	void					Registers::loadState ( std::fstream& file )
	{
		file.read((char*)&_af.word, sizeof(_af.word));
		file.read((char*)&_bc.word, sizeof(_bc.word));
		file.read((char*)&_de.word, sizeof(_de.word));
		file.read((char*)&_hl.word, sizeof(_hl.word));
		file.read((char*)&_sp.word, sizeof(_sp.word));
		file.read((char*)&_pc.word, sizeof(_pc.word));
	}

}

