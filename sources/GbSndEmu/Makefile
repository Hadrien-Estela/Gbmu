#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hestela <hestela@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 14:09:29 by hestela           #+#    #+#              #
#    Updated: 2016/01/12 14:27:32 by hestela          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

#******************************************************************************#
#*								PROJECT SOURCES 			    			  *#
#******************************************************************************#

NAME		= GbSndEmu.framework
LIB 		= GbSndEmu

SOURCES		= src/Blip_Buffer.cpp \
			src/Effects_Buffer.cpp \
			src/Gb_Apu_State.cpp \
			src/Gb_Apu.cpp \
			src/Gb_Oscs.cpp \
			src/Multi_Buffer.cpp \
			src/Sound_Queue.cpp

HEADERS		= -I inc \
				-F frameworks

LIBRARIES	=

FRAMEWORKS	= -F frameworks -framework SDL2

RESSOURCES	=

#******************************************************************************#
#*								GENERALS DEFINES 			    			  *#
#******************************************************************************#

CC		= g++ -std=c++11
CCLIB	= g++ -std=c++11 -dynamiclib
CCFLAGS	= -Wextra -Wall -Werror
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
	cp -r inc ./build/$(NAME)/Versions/Current/Headers/
	cd ./build/$(NAME)/; ln -sf Versions/Current/Headers Headers
	cd ./build/$(NAME)/; ln -sf Versions/Current/$(LIB) $(LIB)

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

mrproper: fclean

re: fclean all

mrtemp:
	find . -name "#*#" -print -delete
	find . -name "*~" -print -delete
	find . -name ".DS_*" -print -delete

#******************************************************************************#
#*									GIT RULES				    			  *#
#******************************************************************************#

init: mrtemp
	git add --all
	git commit -m "init repository"
	git push origin master

upgrade: mrproper mrtemp
	git add --all
	@read -p "commit message: " msg;\
	git commit -m "$$msg";
	git push

update: mrproper mrtemp
	git pull
	git submodule sync --recursive
	git submodule update --init --recursive
	git submodule update --remote --rebase --recursive

addsubmodule:
	@read -p "Enter repository URL: " url;\
	read -p "Enter submodule PATH: " path;\
	git submodule add $$url $$path;\
	git submodule init $$path

delsubmodule:
	@read -p "Enter submodule PATH: " path;\
	git submodule deinit -f $$path;\
	git rm -f $$path
