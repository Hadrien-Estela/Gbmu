// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Cartridge.class.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/18 17:59:04 by hestela           #+#    #+#             //
//   Updated: 2015/12/18 17:59:26 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Cartridge.class.hpp"
#include "MBController.class.hpp"

namespace Gbmu
{

	Cartridge::Cartridge ( Cpu* cpu, std::string const& path, Gb::Model const& model ):
		_cpu(cpu),
		_path(path),
		_model(model),
		_data(NULL),
		_mbc(NULL)
	{
		load();
	}

	Cartridge::~Cartridge ( void )
	{
		if (_data)
			delete[] _data;
		if (_mbc)
			delete _mbc;
	}

	void							Cartridge::reset ( void )
	{
		_mbc->reset();
	}

	void							Cartridge::setModel ( Gb::Model const& model )
	{
		_model = model;
	}

	std::string						Cartridge::title ( void ) const
	{
		char 		title[0x10];

		std::memcpy(title, _header.title, 0x10);
		title[0x0F] = '\0';
		return (std::string(title));
	}

	bool							Cartridge::colorGB ( void ) const
	{
		// return the forced GB Model
		if (_model == Gb::Model::DMG)
			return (false);
		else if (_model == Gb::Model::CGB)
			return (true);

		// else if model is auto: check the CGB flag in header
		if (_header.CGB_flag == 0x80 || _header.CGB_flag == 0xC0)
			return (true);
		return (false);
	}

	bool							Cartridge::colorCart ( void ) const
	{
		// if Model is forced to color and the GB is booting return always true
		if (_model == Gb::Model::CGB && _cpu->onBoot())
			return (true);
		// else check the CGB flag in header		
		if (_header.CGB_flag == 0x80 || _header.CGB_flag == 0xC0)
			return (true);
		return (false);
	}

	uint8_t	const&					Cartridge::getByteAt ( uint16_t const& addr )
	{
		return (_mbc->getByteAt(addr));
	}

	void							Cartridge::setByteAt ( uint16_t const& addr, uint8_t const& value )
	{
		_mbc->setByteAt(addr, value);
	}

	struct Cartridge::Header const&	Cartridge::header ( void ) const	{ return (_header); }
	uint8_t*						Cartridge::data ( void ) const 		{ return (_data); }
	std::string const&				Cartridge::path ( void ) const		{ return (_path); }

	/**************************************************************************/
	/**************************** PRIVATE METHODS *****************************/
	/**************************************************************************/

	void							Cartridge::load ( void )
	{
		std::fstream	file;
		size_t			size;

		// open the file
		file.open(_path, std::fstream::in);
		if (!file.is_open())
			throw Exception("Unable to load ROM: Can't find file: " + _path);
		
		// check the size of ROM
		file.seekg( 0, std::ios::end );
		size = file.tellg();
		file.seekg( 0, std::ios::beg );
		if (size < 0x7FFF)
			throw Exception("Unable to load ROM: File to short to be a GB rom");

		// get cartridge data
		_data = new uint8_t[size];
		file.read((char*)_data, size);
		file.close();
		std::memcpy(&_header, _data + 0x100, sizeof(struct Cartridge::Header));

		// header checksum verify
		size_t		idx = 0x134;
		uint8_t 	x = 0;

		while (idx < 0x14D)
		{
			x = x - _data[idx] - 1;
			idx++;
		}
		if (x != _header.header_checksum)
			throw Exception("Unable to load ROM: Header checksum incorrect");

		// create the MemoryBankController
		_mbc = IMBController::create(this);
	}

	/**************************************************************************/
	/******************************* SAVE STATE *******************************/
	/**************************************************************************/

	void							Cartridge::saveState ( std::fstream& file )
	{
		_mbc->saveState(file);
	}

	void							Cartridge::loadState ( std::fstream& file )
	{
		_mbc->loadState(file);
	}

}