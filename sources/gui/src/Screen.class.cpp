// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Screen.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 10:06:56 by hestela           #+#    #+#             //
//   Updated: 2016/01/23 10:07:02 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Screen.class.hpp"

Screen::Screen ( QWidget *parent ):
	QGraphicsView(parent),
	_background(":logo.jpg"),
	_buffer1( new QImage(160, 144, QImage::Format_RGB32) ),
	_buffer2( new QImage(160, 144, QImage::Format_RGB32) ),
	_scene( new Scene(this) ),
	_bufIdx(0),
	_romEnable(false),
	_fpsTimer( new QTimer(this) )
{
	//init scene
	setScene(_scene);
	_scene->setBackgroundBrush(QBrush(0xFFDCDCDC, Qt::SolidPattern));
	_buffer1->fill(Qt::black);
	_buffer2->fill(Qt::black);

	// timer to force 60fps
	QObject::connect(_fpsTimer, SIGNAL(timeout()), this, SLOT(endFrame()));
	_fpsTimer->start(1000 / 60);
}


Screen::~Screen ( void )
{
	delete _buffer1;
	delete _buffer2;
	delete _scene;
}

void	Screen::drawPix ( size_t x, size_t y, int32_t rgb )
{
	if (_bufIdx == 0)
		_buffer1->setPixel(QPoint(x, y), rgb);
	else
		_buffer2->setPixel(QPoint(x, y), rgb);

}

void	Screen::update ( void )
{
	_bufIdx = !_bufIdx; // invert buffers
}

void	Screen::clear ( int32_t fillColor )
{
	if (_bufIdx == 0)
		_buffer1->fill(fillColor);
	else
		_buffer2->fill(fillColor);
}

void	Screen::resizeScene ( void )
{
	_scene->setSceneRect(this->rect());
}

void	Screen::updateScene( void )
{
	QPixmap				 pixs;
	QGraphicsPixmapItem	 *item;

	_scene->clear();

	if (!_romEnable)
	{
		pixs = QPixmap::fromImage(_background);
		pixs = pixs.scaled(QSize(this->width(), this->height()), Qt::KeepAspectRatio);
		item = _scene->addPixmap(pixs);
	}
	else
	{
		if (_bufIdx == 1)
			pixs = QPixmap::fromImage(*_buffer1);
		else
			pixs = QPixmap::fromImage(*_buffer2);

		// scale from view
		pixs = pixs.scaled(QSize(this->width(), this->height()), Qt::KeepAspectRatio);
		item = _scene->addPixmap(pixs);
	}
	
	// center pixmap
	int x = (this->rect().width() - pixs.rect().width()) / 2;
	int y = (this->rect().height() - pixs.rect().height()) / 2;
	item->setPos(x, y);
}

void   Screen::setRomEnable ( bool b )
{
	_romEnable = b;
}

Scene*  Screen::scene ( void ) const	{ return (_scene); };

void	Screen::endFrame( void )
{
	updateScene();
}
