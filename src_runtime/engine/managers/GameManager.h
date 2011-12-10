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
#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_framerate.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>
#include <string>

#include "StateManager.h"
#include "TimerManager.h"
#include "GameData.h"
#include "Screen.h"


class StateManager;
class TimerManager;
class GameData;
class Screen;

using namespace std;

/**
 * @brief Gerenciador do jogo. É aqui que a biblioteca é inicializada,
 * os parâmetros iniciais são determinados e o game loop é rodado.
 *
 */
class GameManager {
public:
        /**
         * @brief Construtor. Recebe uma instância da GameData para
         * poder realizar todas as configurações iniciais do jogo.
         *
         * @param gameData
         */
        GameManager(GameData *gameData);
        /**
         * @brief
         *
         */
        virtual ~GameManager();

        /**
         * @brief
         *
         */
        void run();
private:
        Screen *screen; /**< A tela do jogo. */
        Uint32 timer; /**< O tempo desde a inicialização do jogo. */
        int dt; /**< O tempo do quadro. */
        GameData *gameData; /**< Dados do jogo. */
        StateManager *stateManager; /**< Gerenciador de estados. */
        TimerManager *timerManager; /**< Gerenciador de tempo. */

        FPSmanager *fpsManager; /**< Gerenciador de taxa de quadros por seguindo. */

        int timemean; /**< Média dos tempos (para testes). */
};

#endif /* GAMEMANAGER_H_ */
