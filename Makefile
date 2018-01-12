#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hestela <hestela@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/02 12:44:29 by hestela           #+#    #+#              #
#    Updated: 2016/01/06 16:07:18 by hestela          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

#******************************************************************************#
#*								PROJECT COMPILING 			    			  *#
#******************************************************************************#

.SILENT:

all: _apu _core _gui _deploy
	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m Gbmu.app\n"
	printf "\e[32m----------------------------------\e[36m\n"

_apu:
	make -C sources/GbSndEmu

_core:
	make -C sources/core

_gui:
	if ! type qmake > /dev/null; \
	then \
	    error YOU MUST INSTALL Qt 5.5; \
	fi;
	if [ ! -f ./sources/gui/Makefile ] ; \
	then \
	    cd sources/gui; qmake ; \
	fi;
	make -C sources/gui
	ln -sF sources/gui/build .
	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m Qt Gui\n"
	printf "\e[32m----------------------------------\e[36m\n"

_deploy:
	if [ ! -d ./build/Gbmu.app/Contents/Plugins ] ; \
	then \
	    macdeployqt ./build/Gbmu.app; \
	fi;
	

#******************************************************************************#
#*								GENERALS RULES				    			  *#
#******************************************************************************#

clean:
	make -C sources/GbSndEmu clean;
	make -C sources/core clean;
	if [ -f ./sources/gui/Makefile ] ; \
	then \
	    make -C sources/gui clean ; \
	fi;

fclean: clean
	make -C sources/GbSndEmu fclean;
	make -C sources/core fclean
	if [ -f ./sources/gui/Makefile ] ; \
	then \
	    make -C sources/gui distclean ; \
	fi;
	rm -rf ./build

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

upgrade: fclean mrtemp
	git add --all
	@read -p "commit message: " msg;\
	git commit -m "$$msg";
	git push

update: fclean mrtemp
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
