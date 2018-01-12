// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MainWindow.class.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 10:04:37 by hestela           #+#    #+#             //
//   Updated: 2016/01/23 10:04:50 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAINWINDOW_HPP
# define MAINWINDOW_HPP

# include <iostream>

# include <QMainWindow>
# include <QFileDialog>
# include <QShortcut>
# include <QMessageBox>
# include <QWidget>
# include <QGraphicsPixmapItem>
# include <QToolButton>
# include <QKeyEvent>

# include <Gbmu/Gbmu.hpp>

# include "Debugger.class.hpp"
# include "Screen.class.hpp"

# include "ui_MainWindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow
{
	Q_OBJECT

	private:
		Ui::MainWindow*		_ui;
		Debugger*			_debuggerWindow;
		Screen*				_screen;
		Gbmu::Gb*			_gameBoy;

	public:
		explicit MainWindow ( QWidget *parent = 0 );
		~MainWindow();

        void				enableActions ( bool b );
        void				openROM ( std::string path );

    protected:
        void				resizeEvent( QResizeEvent* event );
        bool				event ( QEvent *event );

	public slots:
		void				debugSlot ( void );
		void				dropSlot ( std::string path );
		void				loadSlot ( void );
		void				playSlot ( void );
		void				pauseSlot ( void );
		void				stopSlot ( void );
		void				resetSlot ( void );
        void                muteSlot ( void );
		void				changeSpeedSlot ( QAction* action );
		void				changeModelSlot ( QAction* action );
        void                saveStateSlot ( void );
        void                loadStateSlot ( void );

};

#endif // MAINWINDOW_H
