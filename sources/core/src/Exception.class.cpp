// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Exception.class.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/19 20:54:50 by hestela           #+#    #+#             //
//   Updated: 2015/12/19 20:54:50 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Exception.class.hpp"

namespace Gbmu
{

	Exception::Exception( void ):
		_message("default error")
	{ }

	Exception::Exception( std::string const error_msg):
		_message(error_msg)
	{ }

	Exception::Exception( Exception const& rhs )
	{
		*this = rhs;
	}

	const char* 		Exception::what() const throw ()
	{
		return (_message.c_str());
	}

	std::string const&	Exception::message() const
	{
		return (_message);
	}

	Exception::~Exception( void ) throw () {}

	Exception&		Exception::operator=( Exception const& rhs )
	{
		_message = rhs.message();
		return (*this);
	}

}