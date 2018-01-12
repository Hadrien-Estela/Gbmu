// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Application.class.cpp                              :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 11:38:23 by hestela           #+#    #+#             //
//   Updated: 2016/01/23 11:38:35 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Application.class.hpp"

Application::Application ( int &ac, char** av):
    QApplication(ac, av),
    _mainWindow( new MainWindow() )
{
    _mainWindow->show();
    if (ac > 1 && av[1])
        _mainWindow->openROM(std::string(av[1]));
}

Application::~Application ( void )
{
    delete _mainWindow;
}


bool        Application::event ( QEvent* event )
{
    if (event->type() == QEvent::FileOpen )
    {
        QFileOpenEvent* fileOpenEvent = static_cast<QFileOpenEvent *>(event);

        if(fileOpenEvent)
            _mainWindow->openROM(fileOpenEvent->file().toUtf8().constData());
        return (true);
    }
    return QApplication::event(event);
}
