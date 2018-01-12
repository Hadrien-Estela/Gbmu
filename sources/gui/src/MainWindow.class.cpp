// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MainWindow.class.cpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 10:06:37 by hestela           #+#    #+#             //
//   Updated: 2016/01/23 10:06:42 by hestela          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "MainWindow.class.hpp"

MainWindow::MainWindow ( QWidget *parent ):
	QMainWindow(parent),
	_ui(new Ui::MainWindow),
	_debuggerWindow(NULL),
	_screen(new Screen(this)),
	_gameBoy(new Gbmu::Gb())
{
	// Ui
	_ui->setupUi(this);
	setWindowTitle("Gbmu");
    _ui->actionPlay->setVisible(true);
    _ui->actionPause->setVisible(false);

	// disable action without rom
	enableActions(false);

	//Connects
	QObject::connect(_ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadSlot()));
	QObject::connect(_ui->actionDebug, SIGNAL(triggered()), this, SLOT(debugSlot()));
	QObject::connect(_ui->actionPlay, SIGNAL(triggered()), this, SLOT(playSlot()));
	QObject::connect(_ui->actionStop, SIGNAL(triggered()), this, SLOT(stopSlot()));
	QObject::connect(_ui->actionPause, SIGNAL(triggered()), this, SLOT(pauseSlot()));
	QObject::connect(_ui->actionReset, SIGNAL(triggered()), this, SLOT(resetSlot()));
	QObject::connect(_ui->menuSpeed, SIGNAL(triggered(QAction*)), this, SLOT(changeSpeedSlot(QAction*)));
	QObject::connect(_ui->menuModel, SIGNAL(triggered(QAction*)), this, SLOT(changeModelSlot(QAction*)));
	QObject::connect(_screen->scene(), SIGNAL(onDropFile(std::string)), this, SLOT(dropSlot(std::string)));
    QObject::connect(_ui->actionMute, SIGNAL(triggered()), this, SLOT(muteSlot()));
    QObject::connect(_ui->actionSave_state, SIGNAL(triggered()), SLOT(saveStateSlot()));
    QObject::connect(_ui->actionLoad_state, SIGNAL(triggered()), SLOT(loadStateSlot()));

	// Screen
	this->setCentralWidget(_screen);
	_gameBoy->setScreen(_screen);
	_screen->show();
}

MainWindow::~MainWindow()
{
	delete _ui;
	if (_debuggerWindow)
		delete _debuggerWindow;
	delete _gameBoy;
	delete _screen;
}

/* //////////////// PRIVATE SLOTS /////////////////// */

void MainWindow::saveStateSlot ( void )
{
    bool        running = _gameBoy->isRunning();

    // put on pause
    pauseSlot();

    // launch dialog
    QString file = QFileDialog::getSaveFileName(this, "Save State", QString(), "state Files (*.state)");
    std::string path = file.toUtf8().constData();

    if (file != NULL)
    {
        if(!_gameBoy->saveState(path))
            QMessageBox::critical(this, "State ERROR", "Can't create state file !");
    }
    if (running)
        playSlot();
}

void MainWindow::loadStateSlot ( void )
{
    bool        running = _gameBoy->isRunning();

    // put on pause
    pauseSlot();

    // launch dialog
    QString file = QFileDialog::getOpenFileName(this, "Save State", QString(), "state Files (*.state)");
    std::string path = file.toUtf8().constData();

    if (file != NULL)
    {
        if (!_gameBoy->loadState(path))
            QMessageBox::critical(this, "State ERROR", "Can't load state file !");
    }
    if (running)
        playSlot();
}

void MainWindow::muteSlot ( void )
{
    if (_ui->actionMute->isChecked())
        _gameBoy->mute(true);
    else
        _gameBoy->mute(false);
}

void MainWindow::changeModelSlot ( QAction* action )
{
	if (action == _ui->actionModelAuto)
	{
		_ui->actionModelAuto->setChecked(true);
		_ui->actionModelDMG->setChecked(false);
		_ui->actionModelCGB->setChecked(false);
		_gameBoy->setModel(Gbmu::Gb::Model::Auto);
	}

	else if (action == _ui->actionModelDMG)
	{
		_ui->actionModelAuto->setChecked(false);
		_ui->actionModelDMG->setChecked(true);
		_ui->actionModelCGB->setChecked(false);
		_gameBoy->setModel(Gbmu::Gb::Model::DMG);
	}

   else if (action == _ui->actionModelCGB)
	{
		_ui->actionModelAuto->setChecked(false);
		_ui->actionModelDMG->setChecked(false);
		_ui->actionModelCGB->setChecked(true);
		_gameBoy->setModel(Gbmu::Gb::Model::CGB);
	}
}

void MainWindow::changeSpeedSlot ( QAction* action )
{
	_ui->actionSpeed_x1->setChecked(false);
	_ui->actionSpeed_x2->setChecked(false);
	_ui->actionSpeed_x4->setChecked(false);

	if (action == _ui->actionSpeed_x1)
	{
		_ui->actionSpeed_x1->setChecked(true);
		_gameBoy->setSpeed(1);
	}
	else if (action == _ui->actionSpeed_x2)
	{
		_ui->actionSpeed_x2->setChecked(true);
		_gameBoy->setSpeed(2);
	}
	else if (action == _ui->actionSpeed_x4)
	{
		_ui->actionSpeed_x4->setChecked(true);
		_gameBoy->setSpeed(4);
	}
}

void MainWindow::debugSlot ( void )
{
	// put on pause
	pauseSlot();
	// launch debugger
	if (_debuggerWindow)
		delete _debuggerWindow;
	_debuggerWindow = new Debugger(_gameBoy->debugger());
	_debuggerWindow->show();
}

void MainWindow::dropSlot ( std::string path )
{
	openROM(path);
}

void MainWindow::loadSlot ( void )
{
    bool        running = _gameBoy->isRunning();

	// put on pause
	if (_gameBoy->isLoaded())
		pauseSlot();

	// launch dialog
	QString file = QFileDialog::getOpenFileName(this, "Load ROM", QString(), "ROM Files (*.gb *.gbc)");
	std::string path = file.toUtf8().constData();

	if (file != NULL)
		openROM(path);
	else if (_gameBoy->isLoaded() != true)
		enableActions(false);
    else if (running)
		playSlot();
}

void MainWindow::playSlot ( void )
{
    _ui->actionPlay->setVisible(false);
    _ui->actionPause->setVisible(true);
    _ui->actionPlay->setEnabled(false);
    _ui->actionPause->setEnabled(true);
	_ui->actionStop->setEnabled(true);
	_gameBoy->play();
}

void MainWindow::pauseSlot ( void )
{
    _ui->actionPlay->setVisible(true);
    _ui->actionPause->setVisible(false);
    _ui->actionPlay->setEnabled(true);
    _ui->actionPause->setEnabled(false);
	_ui->actionStop->setEnabled(true);
	_gameBoy->pause();
}

void MainWindow::stopSlot ( void )
{
    _ui->actionPlay->setVisible(true);
    _ui->actionPause->setVisible(false);
    _ui->actionPlay->setEnabled(true);
    _ui->actionPause->setEnabled(false);
	_ui->actionStop->setEnabled(false);
	_gameBoy->pause();
	_gameBoy->reset();
}

void MainWindow::resetSlot ( void )
{
	_gameBoy->reset();
}

/*//////////////////// PROTECTED /////////////////////*/

void MainWindow::resizeEvent ( QResizeEvent* event )
{
	event = NULL;
	_screen->resizeScene();
}

bool MainWindow::event( QEvent *event )
{
	if (event->type() == QEvent::KeyPress
		|| event->type() == QEvent::ShortcutOverride
		|| event->type() == QEvent::KeyRelease)
	{
		QKeyEvent* keyEvent = (QKeyEvent*)event;

		if (!_gameBoy->isLoaded() || keyEvent->isAutoRepeat())
			return (QWidget::event(event));

		/////////////// KEY PRESSED
		if (event->type() == QEvent::KeyPress || event->type() == QEvent::ShortcutOverride)
		{
			switch (keyEvent->key())
			{
				case Qt::Key_Left:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Left, true);
					break;
				case Qt::Key_Right:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Right, true);
					break;
				case Qt:: Key_Up:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Up, true);
					break;
				case Qt::Key_Down:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Down, true);
					break;
				case Qt::Key_V:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::B, true);
					break;
				case Qt::Key_C:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::A, true);
					break;
				case Qt::Key_Return:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Start, true);
					break;
				case Qt::Key_Tab:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Select, true);
					break;
				default:
					break;
			}
		}
		/////////////// KEY RELEASED
		if (event->type() == QEvent::KeyRelease)
		{
			switch (keyEvent->key())
			{
				case Qt::Key_Left:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Left, false);
					break;
				case Qt::Key_Right:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Right, false);
					break;
				case Qt:: Key_Up:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Up, false);
					break;
				case Qt::Key_Down:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Down, false);
					break;
				case Qt::Key_V:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::B, false);
					break;
				case Qt::Key_C:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::A, false);
					break;
				case Qt::Key_Return:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Start, false);
					break;
				case Qt::Key_Tab:
					_gameBoy->keyPad()->setKey(Gbmu::IKeyPad::Select, false);
					break;
				default:
					break;
			}
		}
		_gameBoy->keyPad()->updateKeys();
	} // end if key event

	return (QWidget::event(event));
}

/* //////////////////// PRIVATE ////////////////// */

void MainWindow::enableActions ( bool b )
{
	_ui->menuControls->setEnabled(b);
	_ui->menuTools->setEnabled(b);
	_ui->actionPlay->setEnabled(b);
	_ui->actionPause->setEnabled(b);
	_ui->actionStop->setEnabled(b);
	_ui->actionDebug->setEnabled(b);
	_ui->actionReset->setEnabled(b);
    _ui->actionSave_state->setEnabled(b);
    _ui->actionLoad_state->setEnabled(b);
}

void MainWindow::openROM ( std::string path )
{
	// stop current rom
	stopSlot();
	// call Gb Load Rom
	_gameBoy->load(path);

	// If Succeed
	if (_gameBoy->isLoaded())
	{
		// Set Window Title
		setWindowTitle(QString::fromStdString(_gameBoy->gameTitle()));
		_screen->setRomEnable(true);
		// update Screen
		_screen->updateScene();
		// disable Shortcut
		enableActions(true);
		// play
		playSlot();
	}
	// If failed
	else
	{
		// Set Window Title
		setWindowTitle("Gbmu");
		_screen->setRomEnable(false);
		// update Screen
		_screen->updateScene();
		// disable Shortcuts
		enableActions(false);
		// AlertBox
		QMessageBox::critical(this, "ROM ERROR", "Can't load ROM file !");
	}
}
