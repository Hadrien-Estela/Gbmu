// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Exception.class.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/19 20:54:38 by hestela           #+#    #+#             //
//   Updated: 2015/12/19 20:54:39 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EXCEPTION_CLASS_HPP
# define EXCEPTION_CLASS_HPP

#include <iostream>

namespace Gbmu
{

	class Exception: public std::exception
	{

		public:
			Exception( void );
			Exception( std::string const error_msg );
			Exception( Exception const& rhs );
			virtual ~Exception( void ) throw ();

			virtual const char* what() const throw ();

			std::string const&	message() const;

			Exception&			operator=( Exception const& rhs );

		private:
			std::string 	_message;
	};

}

#else
	namespace Gbmu
	{
		class Exception;
	}
#endif // !EXCEPTION_CLASS_HPP
