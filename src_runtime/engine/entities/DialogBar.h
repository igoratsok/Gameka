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
#ifndef DIALOGBAR_H_
#define DIALOGBAR_H_

#include "Screen.h"
#include "Sprite.h"
#include "GameData.h"

class Screen;
class Sprite;
class GameData;

/**
 * @brief Barra de diálogos.
 *
 */
class DialogBar {
public:
        /**
         * @brief Posição da barra.
         *
         * @param posicao Posição:  \n
                            - 0: embaixo;
                            - 1: em cima.
         */
        DialogBar(int posicao);

        /**
         * @brief
         *
         */
        virtual ~DialogBar();

        Sprite *dialogBarSprite; /**< Sprite da barra */

        Vector2 pos; /**< Posição real. */

        int barWidth; /**< Largura da barra. */

        static const int POS_DOWN = 0; /**<  */
        static const int POS_UP = 1; /**<  */

        /**
         * @brief Renderiza a barra.
         *
         * @param screen
         */
        void render(Screen *screen);
};

#endif /* DIALOGBAR_H_ */
