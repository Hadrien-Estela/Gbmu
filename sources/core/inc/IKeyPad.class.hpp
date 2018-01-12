// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IKeyPad.class.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/10 09:08:50 by hestela           #+#    #+#             //
//   Updated: 2016/01/10 09:08:51 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IKEYPAD_CLASS_HPP
# define IKEYPAD_CLASS_HPP

namespace Gbmu
{
	
	class IKeyPad
	{
		public:
			enum Key
			{
				Up,
				Down,
				Left,
				Right,
				A,
				B,
				Select,
				Start
			};

			virtual ~IKeyPad ( void ) {}
			
			// set A Game boy button
			virtual void	setKey ( Gbmu::IKeyPad::Key key, bool b ) = 0;
			
			// Call after you have set/reset all buttons
			virtual void	updateKeys ( void ) = 0;
	};
	
}

#else
	namespace Gbmu
	{
		class IKeyPad;
	}
#endif // !IKEYPAD_CLASS_HPP
