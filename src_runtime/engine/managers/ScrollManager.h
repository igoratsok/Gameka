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
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "Vector2.h"
#include "GameData.h"
#include "Tilemap.h"

class Vector2;
class GameData;
class Tilemap;

#ifndef SCROLLMANAGER_H_
#define SCROLLMANAGER_H_

/**
 * @brief ScrollManager, responsável por realizar o "scrolling" do mapa,
 * ou seja, movimentação da câmera.
 * Para que ele exista, é necessário determinar uma posição
 * que será o centro da câmera, ou seja, para onde ela irá apontar.
 *
 */
class ScrollManager {
public:
        /**
         * @brief
         *
         */
        ScrollManager();
        /**
         * @brief
         *
         */
        virtual ~ScrollManager();
        /**
         * @brief Obtém instância singleton.
         *
         */
        static ScrollManager *getInstance();
        /**
         * @brief Determina um ponto como centro da tela.
         *
         * @param center
         */
        void setCenter(Vector2 *center);
        /**
         * @brief Remove centro da tela.
         *
         */
        void removeCenter();
        /**
         * @brief Fornece o Tilemap.
         *
         * @param tileMap
         */
        void setTilemap(Tilemap *tileMap);

        /**
         * @brief Obtém o ponto central da tela.
         *
         */
        Vector2 *getCenter();
        /**
         * @brief Modifica um vetor de forma que seja desenhado na sua posição com relação
         * ao centro da tela.
         *
         * @param vector O vetor a ser modificado.
         */
        Vector2 *scrollVector(Vector2 *vector);
        /**
         * @brief Modifica um vetor de mouse de forma que esteja na sua posição com relação
         * ao centro da tela.
         *
         * @param vector O vetor a ser modificado.
         */
        Vector2 *scrollMouseVector(Vector2 *vector);
        /**
         * @brief Modifica um SDL_Rect de forma que seja posicionado com relação
         * ao centro da tela.
         *
         * @param rect O retângulo a ser modificado.
         */
        void scrollSDLRect(SDL_Rect *rect);
        /**
         * @brief Verifica se o centro não é determinado.
         *
         */
        bool isCenterNull();
        /**
         * @brief Verifica se a câmera está em um ponto de movimento no eixo X.
         *
         */
        bool isXScrolling();
        /**
         * @brief Verifica se a câmera está em um ponto de movimento no eixo Y.
         *
         */
        bool isYScrolling();
        /**
         * @brief Verifica se a câmera está em um ponto de movimento.
         *
         */
        bool isScrolling();
        Vector2 *center; /**< Centro da câmera. */

        static ScrollManager *singleton; /**< Instância singleton. */

        Vector2 translate; /**< Vetor de translação. */


private:
        Tilemap *tilemap; /**< Mapa. */
        int tilemapRightBorder; /**< Posição da borda da direita do mapa. */
        int tilemapDownBorder; /**< Posição da borda de baixo do mapa. */

        GameData *gameData; /**< GameData. */
};

#endif /* SCROLLMANAGER_H_ */
