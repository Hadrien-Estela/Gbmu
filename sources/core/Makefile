#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hestela <hestela@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/20 11:08:57 by hestela           #+#    #+#              #
#    Updated: 2016/01/26 15:00:02 by hestela          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

#******************************************************************************#
#*								PROJECT SOURCES 			    			  *#
#******************************************************************************#

NAME		= Gbmu.framework
LIB 		= Gbmu

SOURCES		= src/Gb.class.cpp \
			src/Bios.class.cpp \
			src/Memory.class.cpp \
			src/Cpu.class.cpp \
			src/Registers.class.cpp \
			src/Instructions.class.cpp \
			src/Cartridge.class.cpp \
			src/MBController.class.cpp \
			src/KeyPad.class.cpp \
			src/InterruptController.class.cpp \
			src/LcdController.class.cpp \
			src/LcdDriver.class.cpp \
			src/TimerController.class.cpp \
			src/LinkController.class.cpp \
			src/Dma.class.cpp \
			src/SerialIO.class.cpp \
			src/Exception.class.cpp \
			src/Debugger.class.cpp \
			src/SoundController.class.cpp

HEADERS		= -I inc/ \
			-F ../GbSndEmu/frameworks \
			-F ../GbSndEmu/build

LIBRARIES	=

FRAMEWORKS	= -F ../GbSndEmu/frameworks -framework SDL2 \
			-F ../GbSndEmu/build -framework GbSndEmu

RESSOURCES	=

#******************************************************************************#
#*								GENERALS DEFINES 			    			  *#
#******************************************************************************#

CC		= g++ -std=c++11
CCLIB	= g++ -std=c++11 -dynamiclib
CCFLAGS	= -Wextra -Wall -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-private-field 
OBJECTS	= $(subst src,obj,$(subst .cpp,.o,$(SOURCES)))

#******************************************************************************#
#*								PROJECT COMPILING 			    			  *#
#******************************************************************************#

.SILENT:

all: directories build/$(NAME)

build/$(NAME): $(LIB)
	rm -rf ./build/$(NAME)
	mkdir -p ./build/$(NAME)/Versions/A
	cd ./build/$(NAME)/Versions; ln -sf A Current
	mv $(LIB) ./build/$(NAME)/Versions/Current
	cp -r common ./build/$(NAME)/Versions/Current/Headers
	cp -r inc ./build/$(NAME)/Versions/Current/Headers/includes
	cd ./build/$(NAME)/; ln -sf Versions/Current/Headers Headers
	cd ./build/$(NAME)/; ln -sf Versions/Current/$(LIB) $(LIB)
	mkdir -p ./build/$(NAME)/Versions/Current/Frameworks
	cp -r ../GbSndEmu/frameworks/SDL2.framework ./build/$(NAME)/Versions/Current/Frameworks
	cp -r ../GbSndEmu/build/GbSndEmu.framework ./build/$(NAME)/Versions/Current/Frameworks
	install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 @loader_path/Frameworks/SDL2.framework/Versions/Current/SDL2 ./build/$(NAME)/Versions/Current/Gbmu
	install_name_tool -change GbSndEmu @loader_path/Frameworks/GbSndEmu.framework/Versions/Current/GbSndEmu ./build/$(NAME)/Versions/Current/Gbmu

	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m $(NAME)\n"
	printf "\e[32m----------------------------------\e[36m\n"

$(LIB): $(OBJECTS)
	$(CCLIB) $(CCFLAGS) $(OBJECTS) $(LIBRARIES) $(FRAMEWORKS) -o $(LIB)

obj/%.o: src/%.cpp
	$(CC) $(CCFLAGS) $(HEADERS) -c $^ -o $@
	printf "\e[32m[✔]\e[36m $^ \n"

directories:
	mkdir -p obj build

#******************************************************************************#
#*								GENERALS RULES				    			  *#
#******************************************************************************#

clean:
	rm -rf obj

fclean: clean
	rm -rf build

re: fclean all
