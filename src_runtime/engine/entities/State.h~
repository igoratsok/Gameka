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

#ifndef STATE_H_
#define STATE_H_

#include <SDL/SDL.h>

#include "GameData.h"
#include "Screen.h"



class Screen;
class GameData;

/**
 * @brief Classe abstrata State, representando um estado do jogo.
 * É uma superclasse, não deve ser instanciada.
 * Devem haver classes filhas para implementar os
 * métodos da State.
 *
 */
class State {
public:

        /**
         * @brief Fornecimento de um ponteiro da GameData.
         *
         * @param
         */
        void setGameData(GameData*);

        /**
         * @brief Carrega os recursos do estado.
         *
         */
        virtual void load() = 0;
        /**
         * @brief Descarrega os recursos do estado.
         *
         */
        virtual void unload() = 0;
        /**
         * @brief Método de atualização.
         *
         * @param dt
         */
        virtual int update(int dt) = 0;
        /**
         * @brief Método de renderização.
         *
         * @param screen
         */
        virtual void render(Screen *screen) = 0;


        GameData *gameData; /**<  */

};

#endif /* STATE_H_ */
