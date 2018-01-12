// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Screen.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 10:05:36 by hestela           #+#    #+#             //
//   Updated: 2016/01/23 10:05:52 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SCREEN_H
# define SCREEN_H

# include <iostream>

# include <QImage>
# include <QGraphicsView>
# include <QPixmap>
# include <QGraphicsPixmapItem>
# include <QTimer>

# include <Gbmu/Gbmu.hpp>

# include "Scene.class.hpp"

class Screen: public QGraphicsView, public Gbmu::IScreen
{
	Q_OBJECT

	private:
		QImage				_background;
		QImage*				_buffer1;
		QImage*				_buffer2;
		Scene*				_scene;
		bool				_bufIdx;
		bool				_romEnable;
		QTimer*				_fpsTimer;

	public:
		explicit Screen ( QWidget *parent = 0 );
		~Screen ( void );

		// Reimplemented functions
		void	drawPix ( size_t x, size_t y, int32_t rgb );
		void	update ( void );
		void	clear ( int32_t fillColor );

		void	resizeScene ( void );
		void	updateScene ( void );
		void	setRomEnable ( bool b );

		Scene*  scene ( void ) const;

	public slots:
		void	endFrame ( void );
};

#endif // SCREEN_H
