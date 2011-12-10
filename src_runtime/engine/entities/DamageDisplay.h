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

#ifndef DAMAGEDISPLAY_H_
#define DAMAGEDISPLAY_H_

#include <string>
#include <sstream>

#include "Screen.h"
#include "Text.h"

class Screen;
class Text;

/**
 * @brief Display de dano que sai de um objeto quando ele leva dano.
 * Também pode mostrar mensagens de LEVEL UP.
 *
 */
class DamageDisplay {
public:
        /**
         * @brief Construtor.
         *
         * @param damage Quantidade de dano.
         * @param position Posição.
         * @param type Tipo: \n
                    - 0: dano;
                    - 1: level up;
         */
        DamageDisplay(int damage, Vector2 position, int type);
        /**
         * @brief
         *
         */
        virtual ~DamageDisplay();

        /**
         * @brief Sobe o dano e aplica o timer.
         *
         * @param dt
         */
        int update(int dt);
        /**
         * @brief Renderiza.
         *
         * @param screen
         */
        void render(Screen *screen);

        int tempo; /**< Timer. */

        Text *damageText; /**< Texto do dano. */

        static const int TYPE_DAMAGE = 0; /**<  */
        static const int TYPE_LEVELUP = 1; /**<  */
};

#endif /* DAMAGEDISPLAY_H_ */
