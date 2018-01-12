// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Debugger.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 10:06:14 by hestela           #+#    #+#             //
//   Updated: 2016/01/23 10:06:28 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Debugger.class.hpp"

Debugger::Debugger ( Gbmu::IDebugger *gbDebugger, QWidget *parent ):
	QMainWindow(parent),
	_ui(new Ui::Debugger),
	_gbDebugger(gbDebugger),
	_exitShortcut(new QShortcut(QKeySequence("Escape"), this)),
	_addrMemory(0x0000)
{
	_ui->setupUi(this);

	// table manipulations
	_ui->memoryTable->horizontalHeader()->resizeSection(0,48);
	_ui->registersTable->verticalHeader()->resizeSection(5, 19);
	_ui->disassemblerTable->horizontalHeader()->resizeSection(0, 20);
	_ui->disassemblerTable->horizontalHeader()->resizeSection(1, 102);

	//Set Tables
	setRegisters();
	setVideoRegisters();
	setOtherRegisters();
	setDisassembleTable();
	setMemoryTable();
	setBreakPointList();

	//Line edit
	_ui->memoryEdit->setText(QString("0000"));

	//Connects
	QObject::connect(_exitShortcut, SIGNAL(activated()), this, SLOT(close()));
	QObject::connect(_ui->resetButton, SIGNAL(pressed()), this, SLOT(resetButtonSlot()));
	QObject::connect(_ui->stepButton, SIGNAL(pressed()), this, SLOT(stepButtonSlot()));
	QObject::connect(_ui->frameButton, SIGNAL(pressed()), this, SLOT(frameButtonSlot()));
	QObject::connect(_ui->memoryEdit, SIGNAL(returnPressed()), this, SLOT(memorySlot()));
	QObject::connect(_ui->breakpointButton, SIGNAL(clicked(bool)), this, SLOT(breakpointSlot(bool)));
	QObject::connect(_ui->delBrkpButton, SIGNAL(pressed()), this, SLOT(breakpointDelSlot()));
	QObject::connect(_ui->addBrkpButton, SIGNAL(pressed()), this, SLOT(breakpointAddSlot()));
	QObject::connect(_ui->brkpEdit , SIGNAL(returnPressed()), this, SLOT(breakpointAddSlot()));
	QObject::connect(_ui->secondButton, SIGNAL(pressed()), this, SLOT(secondButtonSlot()));
	QObject::connect(_ui->brkpList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(brkpItemSlot(QListWidgetItem*)));
	QObject::connect(_ui->disassemblerTable, SIGNAL(cellClicked(int,int)), this, SLOT(disassemblyCellPressSlot(int,int)));
}

Debugger::~Debugger()
{
	delete _exitShortcut;
	delete _ui;
}

//SLOTS


// set or enable/disable breakpoint if cell col 0 id pressed n disassembly table
void				Debugger::disassemblyCellPressSlot ( int row, int col )
{
	std::string					valueStr;
	uint16_t					addr;
	std::stringstream			ss;
	std::map<uint16_t, bool>	brkpList = _gbDebugger->breakpoints();
	QListWidgetItem*			item;
	QList<QListWidgetItem*>		items;

	valueStr = _ui->disassemblerTable->item(row, 1)->text().toUtf8().constData();
	ss << std::hex << valueStr;
	ss >> addr;
	if (col == 0)
	{
		if (brkpList.find(addr) == brkpList.end())
		{
			_gbDebugger->setBreakpoint(addr);
			item = new QListWidgetItem(QString::fromStdString(ss.str()));
			item->setCheckState(Qt::CheckState::Checked);
			_ui->brkpList->addItem(item);
		}
		else
		{
			items = _ui->brkpList->findItems(_ui->disassemblerTable->item(row, 1)->text(), Qt::MatchExactly);
			item = *items.begin();
			if (brkpList[addr] == true)
			{
				_gbDebugger->setEnableBreakpoint(addr, false);
				item->setCheckState(Qt::CheckState::Unchecked);
			}
			else
			{
				_gbDebugger->setEnableBreakpoint(addr, true);
				item->setCheckState(Qt::CheckState::Checked);
			}
		}
		setDisassembleTable();
	}
}

// if breakpoint is checked/unchecked in brkpList
void		   Debugger::brkpItemSlot ( QListWidgetItem* item )
{
	std::string		 	valueStr = item->text().toUtf8().constData();
	uint16_t			addr;
	std::stringstream   ss;

	ss << std::hex << valueStr;
	ss >> addr;
	if (item->checkState() == Qt::CheckState::Checked)
		_gbDebugger->setEnableBreakpoint(addr, true);
	else
		_gbDebugger->setEnableBreakpoint(addr, false);
	setDisassembleTable();
}

// run to breakpoint is pressed
void		   Debugger::secondButtonSlot ( void )
{
	_gbDebugger->executeSecond();
	setRegisters();
	setVideoRegisters();
	setOtherRegisters();
	setDisassembleTable();
	setMemoryTable();
}

// Breakpoint button is pressed
void		   Debugger::breakpointSlot( bool checked )
{
	if ( checked )
	{
		this->setMaximumWidth(830);
		this->setMinimumWidth(830);
		this->resize(830, 425);
	}
	else
	{
		this->setMaximumWidth(740);
		this->setMinimumWidth(740);
		this->resize(740, 425);
	}
}

// Add breakpoint is pressed
void			Debugger::breakpointAddSlot ( void )
{
	std::string				valueStr = _ui->brkpEdit->text().toUtf8().constData();
	std::regex				reg("[0-9A-Fa-f]{4}");
	std::stringstream		ss;
	uint16_t				addr;
	QListWidgetItem*		item;

	if (regex_match(valueStr, reg))
	{
		ss << std::hex << valueStr;
		ss >> addr;

		if (_gbDebugger->setBreakpoint(addr) == true)
		{
			ss.str("");
			ss.clear();
			ss << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << addr;
			item = new QListWidgetItem(QString::fromStdString(ss.str()));
			item->setCheckState(Qt::CheckState::Checked);
			_ui->brkpList->addItem(item);
			setDisassembleTable();
		}
		_ui->brkpEdit->setText("");
	}
}

// del breakpoint is pressed
void			Debugger::breakpointDelSlot ( void )
{
	QList<QListWidgetItem *>			toDelList = _ui->brkpList->selectedItems();
	QList<QListWidgetItem *>::iterator	it = toDelList.begin();

	while (it != toDelList.end())
	{
		QListWidgetItem*	selectedItem = *it;
		std::string			valueStr;
		uint16_t			addr;
		std::stringstream	ss;

		valueStr = selectedItem->text().toUtf8().constData();
		ss << std::hex << valueStr;
		ss >> addr;
		_gbDebugger->delBreakpoint(addr);
		_ui->brkpList->removeItemWidget(selectedItem);
		delete selectedItem;
		it++;
	}
	setDisassembleTable();
}

// reset button is pressed
void			Debugger::resetButtonSlot ( void )
{
	_gbDebugger->reset();
	setRegisters();
	setVideoRegisters();
	setOtherRegisters();
	setDisassembleTable();
	setMemoryTable();
}

// step button is pressed
void			Debugger::stepButtonSlot ( void )
{
	_gbDebugger->executeStep();
	setRegisters();
	setVideoRegisters();
	setOtherRegisters();
	setDisassembleTable();
	setMemoryTable();
}

// frame button is pressed
void			Debugger::frameButtonSlot ( void )
{
	_gbDebugger->executeFrame();
	setRegisters();
	setVideoRegisters();
	setOtherRegisters();
	setDisassembleTable();
	setMemoryTable();
}

// Memory adress fiel has changed
void			Debugger::memorySlot ( void )
{
	std::string				value = _ui->memoryEdit->text().toUtf8().constData();
	std::regex				reg("[0-9A-Fa-f]{4}");
	std::stringstream		ss;

	if (regex_match(value, reg)) // check value is valid
	{
		ss << std::hex << value;
		ss >> _addrMemory;
		_addrMemory = _addrMemory - (_addrMemory % 16);
		// check max offset
		if (_addrMemory > 0xFF70)
			_addrMemory = 0xFF70;
		// refill table
		setMemoryTable();
	}

	// update field
	ss.str("");
	ss.clear();
	ss << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << _addrMemory;
	_ui->memoryEdit->setText(QString::fromStdString(ss.str()));
}

//SET REGISTERS TABLES

void			Debugger::setRegisters ( void )
{
	QVector<QString>	registersTxt;
	int					row = 0;
	QString				text;
	QTableWidgetItem*	item;

	registersTxt.push_back(QString::fromStdString(_gbDebugger->getPC()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getAF()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getBC()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getDE()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getHL()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getSP()));

	while (row < 6)
	{
		item = new QTableWidgetItem(registersTxt[row]);
		if (_ui->registersTable->item(row, 0) && registersTxt[row] != _ui->registersTable->item(row, 0)->text())
			item->setTextColor(Qt::blue);
		else
			item->setTextColor(Qt::black);
		_ui->registersTable->setItem(row, 0, item);
		row++;
	}
}

void			Debugger::setVideoRegisters ( void )
{
	QVector<QString>	registersTxt;
	int					row = 0;
	QString				text;
	QTableWidgetItem*	item;

	registersTxt.push_back(QString::fromStdString(_gbDebugger->getLCDC()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getSTAT()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getSCY()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getSCX()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getLY()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getLYC()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getDMA()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getBGP()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getOBP0()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getOBP1()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getWY()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getWX()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getBGPI()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getBGPD()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getOBPI()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getOBPD()));

	while (row < 16)
	{
		item = new QTableWidgetItem(registersTxt[row]);
		if (_ui->videoRegistersTable->item(row, 1) && registersTxt[row] != _ui->videoRegistersTable->item(row, 1)->text())
		{
			item->setTextColor(Qt::blue);
			_ui->videoRegistersTable->item(row, 0)->setTextColor(Qt::blue);
		}
		else
		{
			_ui->videoRegistersTable->item(row, 0)->setTextColor(Qt::black);
			item->setTextColor(Qt::black);
		}
		_ui->videoRegistersTable->setItem(row, 1, item);
		row++;
	}
}

void			Debugger::setOtherRegisters ( void )
{
	QVector<QString>	registersTxt;
	int					row = 0;
	QString				text;
	QTableWidgetItem*	item;

	registersTxt.push_back(QString::fromStdString(_gbDebugger->getP1()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getSB()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getSC()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getDIV()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getTIMA()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getTMA()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getTAC()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getKEY1()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getVBK()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getHDMA1()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getHDMA2()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getHDMA3()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getHDMA4()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getHDMA5()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getSVBK()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getIF()));
	registersTxt.push_back(QString::fromStdString(_gbDebugger->getIE()));

	while (row < 17)
	{
		item = new QTableWidgetItem(registersTxt[row]);
		if (_ui->otherRegistersTable->item(row, 1) && registersTxt[row] != _ui->otherRegistersTable->item(row, 1)->text())
		{
			item->setTextColor(Qt::blue);
			_ui->otherRegistersTable->item(row, 0)->setTextColor(Qt::blue);
		}
		else
		{
			_ui->otherRegistersTable->item(row, 0)->setTextColor(Qt::black);
			item->setTextColor(Qt::black);
		}
		_ui->otherRegistersTable->setItem(row, 1, item);
		row++;
	}
}

void			Debugger::setDisassembleTable ( void )
{
	// each lines must be splitted on character ':' to get separate fields (addr : instruction : data)
	std::vector<std::string>		instructions = _gbDebugger->disassembly();
	int								row = 0;

	while (row < 6)
	{
		std::stringstream			line(instructions[row]);
		std::stringstream			ss;
		uint16_t					addr;
		std::string					segment;
		std::map<uint16_t, bool>	brkpList = _gbDebugger->breakpoints();
		int							col = 1;

		while(std::getline(line, segment, ':'))
		{
			if (col == 1) // check adress corresponding to a breakpoint
			{
				ss.str("");
				ss.clear();
				ss << std::hex << segment;
				ss >> addr;
				_ui->disassemblerTable->setItem(row, 0, new QTableWidgetItem);
				if (brkpList.find(addr) != brkpList.end())
				{
					if (brkpList[addr] == true)
						_ui->disassemblerTable->item(row, 0)->setBackground(Qt::red);
					else
						_ui->disassemblerTable->item(row, 0)->setBackground(Qt::darkGray);
				}
				else
					_ui->disassemblerTable->item(row, 0)->setBackground(Qt::white);
			}
			_ui->disassemblerTable->setItem(row, col, new QTableWidgetItem(QString::fromStdString(segment)));
			col++;
		}
		row++;
	}
}


void			Debugger::setMemoryTable ( void )
{
	std::vector<std::string>	lines = _gbDebugger->memory(_addrMemory);
	int							row = 0;

	while (row < 9)
	{
		std::stringstream	line(lines[row]);
		int					col = 0;
		std::string			segment;

		while(std::getline(line, segment, '/'))
		{
			_ui->memoryTable->setItem(row, col, new QTableWidgetItem(QString::fromStdString(segment)));
			col++;
		}
		row++;
	}
}

 void		Debugger::setBreakPointList ( void )
{
	std::map<uint16_t, bool>			list = _gbDebugger->breakpoints();
	std::map<uint16_t, bool>::iterator	it = list.begin();
	std::stringstream					ss;
	QListWidgetItem*					item;
	uint16_t							key;

	while (it != list.end())
	{
		key = it->first;

		ss.str("");
		ss.clear();
		ss << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << key;
		item = new QListWidgetItem(QString::fromStdString(ss.str()));
		if (list[key] == true)
			item->setCheckState(Qt::CheckState::Checked);
		else
			item->setCheckState(Qt::CheckState::Unchecked);
		_ui->brkpList->addItem(item);
		it++;
	}
}
