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

#ifndef SCREENEFFECTS_H_
#define SCREENEFFECTS_H_

#include "Sprite.h"
#include "Screen.h"

class Sprite;
class Screen;


/**
 * @brief  * Classe para efeitos de tela.
 * Possui os seguintes efeitos:
 *  - piscar tela
 *
 */
class ScreenEffects {
public:
        /**
         * @brief Construtor.
         *
         */
        ScreenEffects();
        /**
         * @brief
         *
         */
        virtual ~ScreenEffects();
        /**
         * @brief Atualiza os temporizadores.
         *
         * @param dt
         */
        void update(int dt);
        /**
         * @brief Renderiza o efeito na tela.
         *
         * @param screen
         */
        void render(Screen *screen);

        /**
         * @brief Pisca a tela.
         *
         * @param r Intensidade da cor vermelha (0, 255)
         * @param g Intensidade da cor verde (0, 255)
         * @param b Intensidade da cor azul (0, 255)
         */
        void piscaTela(int r, int g, int b);
        /**
         * @brief Fade in na tela.
         *
         * @param r Intensidade da cor vermelha (0, 255)
         * @param g Intensidade da cor verde (0, 255)
         * @param b Intensidade da cor azul (0, 255)
         */
        void fadeIn(int r, int g, int b);

        /**
         * @brief Se terminou de piscar a tela.
         *
         */
        bool terminouPiscaTela();
        /**
         * @brief Se o fade in terminou.
         *
         */
        bool terminouFadeIn();

        int timerPisca; /**< Temporizador da piscada. */
        int timerFadeIn; /**< Temporizador do fade in */
        int corPiscaR, corPiscaG, corPiscaB; /**<  */
        int corFadeInR, corFadeInG, corFadeInB; /**<  */
};

#endif /* SCREENEFFECTS_H_ */
