// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Debugger.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 10:03:57 by hestela           #+#    #+#             //
//   Updated: 2016/01/23 10:04:27 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef DEBUGGER_HPP
# define DEBUGGER_HPP

# include <iostream>
# include <iomanip>
# include <sstream>
# include <regex>

# include <QMainWindow>
# include <QShortcut>
# include <QVector>

# include <Gbmu/Gbmu.hpp>

# include "ui_Debugger.h"

namespace Ui {
class Debugger;
}

class Debugger: public QMainWindow
{
	Q_OBJECT

	private:
		Ui::Debugger*		_ui;
		Gbmu::IDebugger*	_gbDebugger;
		QShortcut*			_exitShortcut;
		uint16_t			_addrMemory;

	public:
		explicit Debugger ( Gbmu::IDebugger* gbDebugger, QWidget* parent = 0 );
		~Debugger();

	private:
		void			setRegisters ( void );
		void			setVideoRegisters ( void );
		void			setOtherRegisters ( void );
		void			setDisassembleTable ( void );
		void			setMemoryTable ( void );
		void			setBreakPointList ( void );

	private slots:
		void			resetButtonSlot ( void );
		void			stepButtonSlot ( void );
		void			frameButtonSlot ( void );
		void			secondButtonSlot ( void );
		void			memorySlot ( void );
		void			breakpointSlot( bool checked );
		void			breakpointAddSlot ( void );
		void			breakpointDelSlot ( void );
		void			brkpItemSlot ( QListWidgetItem* item );
		void			disassemblyCellPressSlot ( int row, int col );
};

#endif // DEBUGGER_HPP
