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
#ifndef STATEMANAGER_H_
#define STATEMANAGER_H_

#include <SDL/SDL.h>
#include <stdlib.h>

#include "GameData.h"
#include "Screen.h"
#include "State.h"
#include "SplashState.h"
#include "TitleState.h"
#include "GameOverState.h"
#include "MapState.h"
#include "ScrollManager.h"
#include "ScreenEffects.h"
#include "InputManager.h"

class GameData;
class Screen;
class State;
class SplashState;
class TitleState;
class GameOverState;
class MapState;
class ScrollManager;
class ScreenEffects;
class InputManager;


/**
 * @brief  Gerenciador de estados do jogo. Permite
 * realizar a troca de estados no jogo.
 *
 */
class StateManager {
public:
        /**
         * @brief Construtor recebe GameData.
         *
         * @param gameData
         */
        StateManager(GameData *gameData);
        /**
         * @brief
         *
         */
        virtual ~StateManager();


        State *currentState; /**< Estado atual. */
        State *nextState; /**< Próximo estado (usado apra fazer transição de estados). */

        /**
         * @brief Passa o estado para o estado inicial.
         *
         */
        void setSplashState();
        /**
         * @brief Reinicia o jogo, voltando para o estado inicial.
         *
         */
        void resetGame();
        /**
         * @brief Passa o estado para um estado de mapa.
         *
         * @param idLevel Número do mapa.
         */
        void setMapState(int idLevel);
        /**
         * @brief Retorna para o último mapa antes de entrar em um Game Over.
         *
         */
        void returnLastMap();

        /**
         * @brief Passa o estado para o estado de Game Over.
         *
         * @param currentMapId
         */
        void setGameOverState(int currentMapId);

        /**
         * @brief Atualiza o estado atual.
         *
         * @param dt
         * @param screen Instância da tela para cuidar do fade-in e fade-out
         * entre os estados.
         */
        void updateState(int dt, Screen *screen);
        /**
         * @brief Renderiza o estado atual.
         *
         * @param screen
         */
        void renderState(Screen *screen);



        GameData *gameData; /**< Instância da GameData. */
        static StateManager *singleton; /**< Instância singleton. */
        ScreenEffects *screenEffects; /**< Efeitos de tela. */

        InputManager *inputManager; /**< InputManager. */

        int etapaTransicao; /**< Em qual etapa de transição fade-in fade-out está: \n
                                        - 0: Etapa rodando estado;
                                        - 1: Etapa apagando (fade-int);
                                        - 2: Etapa mostrando (fade-out). */

        int mapGameOverBackId; /**< Mapa a se voltar depois do Game Over. */

        static const int ETAPA_RODANDO_ESTADO = 0; /**< */
        static const int ETAPA_APAGANDO_ESTADO = 1; /**<  */
        static const int ETAPA_MOSTRANDO_ESTADO = 2; /**<  */

};

#endif

