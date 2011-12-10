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

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "Vector2.h"
#include "ScrollManager.h"

class Vector2;
class ScrollManager;


/**
 * @brief Classe representando a tela do jogo, na qual
 * todos os objetos serão desenhados.
 * Encapsula a SDL_Surface em seu formato de tela,
 * obtida via SDL_SetVideoMode().
 *
 */
class Screen {
public:
        /**
         * @brief Largura e altura da tela.
         *
         * @param width
         * @param height
         */
        Screen(int width, int height);
        /**
         * @brief
         *
         */
        virtual ~Screen();

        /**
         * @brief Obtém a Surface da tela.
         *
         */
        SDL_Surface* getTopScreen();
        /**
         * @brief Apaga a tela.
         *
         */
        void fillScreen();
        /**
         * @brief Troca o buffer da tela. Deve ser chamado após
         * todas as operações de renderização sobre a tela.
         *
         */
        void flipScreen();
        /**
         * @brief Atualiza o top screen (por enquanto não faz nada).
         *
         */
        void updateTopScreen();
        /**
         * @brief Desenha a top screen.
         *
         */
        void blitTopScreen();

        /**
         * @brief Determina zoom na tela.
         *
         * @param zoom
         */
        void setZoom(float zoom);


        int width, height; /**< TODO */

private:
        /**
         * @brief Cria retângulo de rotação da tela.
         *
         */
        void createRectRot();

        SDL_Surface *topScreen, *screen, *topScreenRot; /**<  */
        Vector2 *screenPos; /**<  */
        SDL_Rect rect, rectRot; /**<  */
        float zoom; /**< Zoom da tela. */
        ScrollManager *scrollManager; /**<  */
};

#endif /* SCREEN_H_ */
