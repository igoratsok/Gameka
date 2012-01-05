/***********************************************

Gameka: A game development tool for non-programmers
Copyright (C) 2011 Igor Augusto de Faria Costa

This software is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This software is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

************************************************/



#include <QtGui/QApplication>
#include <QLocale>
#include <QTranslator>
#include <QIcon>
#include <exception>

#include <stdlib.h>


#include <SDL/SDL_mixer.h>

#include "gamedata.h"
#include "maincontroller.h"
#include "builder.h"
#include "messageboxes.h"

class GameData;
class MessageBoxes;

#undef main

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    QTranslator translator;
    if(!translator.load("gameka_tr_en")) {
        std::cout << "Fail!!" << std::endl;
        system("pwd");
    }
    a.installTranslator(&translator);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 640);

    /* inicializando uma instância do GameData */
    GameData *gameData;
    gameData = GameData::getInstance();
    gameData->argv0 = QString(argv[0]);


    /* construindo o sistema */
    Builder *builder;
    MainController *mainController;

    builder = new Builder();
    mainController = builder->build();

    /* inicializa o mainController */
    mainController->init();



    return a.exec();


}
