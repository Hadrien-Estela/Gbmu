// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Application.class.hpp                              :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 11:38:01 by hestela           #+#    #+#             //
//   Updated: 2016/01/23 11:38:06 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef APPLICATION_H
#define APPLICATION_H

# include <QApplication>
# include "MainWindow.class.hpp"

class Application: public QApplication
{
    Q_OBJECT

    private:
        MainWindow*         _mainWindow;

    public:
        explicit Application (int &ac, char** av );
        ~Application ( void );

    protected:
        bool            event ( QEvent* event );

};

#endif // APPLICATION_H
