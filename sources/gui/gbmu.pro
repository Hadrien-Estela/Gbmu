#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Gbmu.pro                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hestela <hestela@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/02 12:44:29 by hestela           #+#    #+#              #
#    Updated: 2016/01/06 16:07:18 by hestela          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

QT				 	+=	core \
						gui \
						widgets

CONFIG				+=	c++11 \
						release

DESTDIR				=	build
TARGET				=	Gbmu
TEMPLATE			=	app
ICON				=	resources/Gbmu.icns
QMAKE_INFO_PLIST	=	info.plist

LIBS				+=	-F../core/build -framework Gbmu
QMAKE_CXXFLAGS		+=	-F../core/build  

GBMU.path			=	Contents/Frameworks
GBMU.files			=	../core/build/Gbmu.framework
QMAKE_BUNDLE_DATA	+=	GBMU

SOURCES				+=	src/main.cpp \
						src/Application.class.cpp \
						src/MainWindow.class.cpp \
						src/Debugger.class.cpp \
						src/Screen.class.cpp \
						src/Scene.class.cpp

INCPATH				+=	inc \

HEADERS				+=	inc/Application.class.hpp \
						inc/MainWindow.class.hpp \
						inc/Debugger.class.hpp \
						inc/Screen.class.hpp \
						inc/Scene.class.hpp

FORMS				+=	forms/MainWindow.ui \
						forms/Debugger.ui

RESOURCES			+=	resources/resources.qrc

OBJECTS_DIR			=	obj
MOC_DIR				=	moc
UI_DIR				=	ui
RCC_DIR				=	rcc

QMAKE_CLEAN			=	OBJECTS_DIR \
						MOC_DIR \
						UI_DIR \
						RCC_DIR

QMAKE_DISTCLEAN		=	-r obj \
						-r ui \
						-r moc \
						-r rcc \
						-r build

QMAKE_POST_LINK		+= 	install_name_tool -change Gbmu @executable_path/../Frameworks/Gbmu.framework/Versions/Current/Gbmu ./build/gbmu.app/Contents/MacOS/Gbmu;
