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
#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include <stdlib.h>

#include "../../engine/entities/State.h"

#include "GameData.h"
#include "Sprite.h"
#include "DialogBar.h"
#include "ChoiceText.h"
#include "Music.h"
#include "ModalManager.h"
#include "StateManager.h"


class GameData;
class Sprite;
class DialogBar;
class ChoiceText;
class Music;
class ModalStack;
class StateManager;

/**
 * @brief Estado de título do jogo.
 *
 */
class TitleState : public State {
public:
        /**
         * @brief Construtor.
         *
         * @param stateManager Instância da StateManager.
         */
        TitleState(StateManager *stateManager);
        /**
         * @brief
         *
         */
        virtual ~TitleState();

        /**
         * @brief Carrega todos os recursos da tela de título, o que inclui o fundo,
         * a ModalStack com um ChoiceText e a música.
         *
         */
        void load();
        /**
         * @brief Descarrega os recursos da tela de título.
         *
         */
        void unload();
        /**
         * @brief Verifica a opção escolhida do menu, e toma providências de acordo.
         *
         * @param dt
         */
        int update(int dt);
        /**
         * @brief Renderiza tudo da tela de título na tela.
         *
         * @param screen
         */
        void render(Screen *screen);

        Sprite *fundo; /**< Fundo da tela. */
        DialogBar *dialogBar; /**< Barra de diálogos da tela. */
        ModalStack *modalManager; /**< ModalStack da tela. */
        StateManager *stateManager; /**< StateManager para troca de estados. */
        Music *musicaFundo; /**< Música de fundo da tela. */
};

#endif /* TITLESTATE_H_ */
