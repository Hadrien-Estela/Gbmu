// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IScreen.class.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/07 15:07:17 by hestela           #+#    #+#             //
//   Updated: 2016/01/08 08:57:55 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ISCREEN_CLASS_HPP
# define ISCREEN_CLASS_HPP

namespace Gbmu
{
	
	class IScreen
	{
		public:
			virtual ~IScreen( void ) {}
			
			// draw a pixel in buffer
			virtual void	drawPix ( size_t x, size_t y, int32_t rgb ) = 0;
			// flush buffer on screen
			virtual void	update ( void ) = 0;
			// clear screen with black color
			virtual void	clear ( int32_t fillColor ) = 0;
	};
	
}

#else
	namespace
	{
		class IScreen;
	}
#endif // !ISCREEN_CLASS_HPP
