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
#ifndef GAMEOVERSTATE_H_
#define GAMEOVERSTATE_H_

#include "State.h"

#include "GameData.h"
#include "Sprite.h"
#include "Music.h"
#include "StateManager.h"
#include "InputManager.h"
#include "PlayerData.h"


class GameData;
class Sprite;
class Music;
class StateManager;
class InputManager;
class PlayerData;


/**
 * @brief Estado da tela de Game Over do jogo.
 *
 */
class GameOverState : public State {
public:
        /**
         * @brief Construtor.
         *
         * @param stateManager Ponteiro para uma instância da StateManager.
         */
        GameOverState(StateManager *stateManager);
        /**
         * @brief
         *
         */
        virtual ~GameOverState();

        /**
         * @brief Carrega o fundo e a música da tela de Game Over.
         *
         */
        void load();
        /**
         * @brief Descarrega os recursos.
         *
         */
        void unload();
        /**
         * @brief Ao pressionar um botão, toma providências quanto ao que ocorrer depois do Game Over,
         * de acordo com as configurações da GameData, especificadas no editor.
         *
         * @param dt
         */
        int update(int dt);
        /**
         * @brief Renderiza o fundo na tela.
         *
         * @param screen
         */
        void render(Screen *screen);


        Sprite *fundo; /**< Fundo da tela. */
        Music *musicaFundo; /**< Música de fundo da tela. */
        InputManager *inputManager; /**< Ponteiro para a InputManager */
        PlayerData *playerData; /**< Ponteiro para a PlayerData. */
        StateManager *stateManager; /**< StateManager para troca de estados. */
};

#endif /* GAMEOVERSTATE_H_ */
