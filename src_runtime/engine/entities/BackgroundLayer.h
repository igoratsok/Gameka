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

#ifndef BACKGROUNDLAYER_H_
#define BACKGROUNDLAYER_H_

#include "SDL.h"
#include "SDL/SDL_image.h"

#include "BackgroundLayerData.h"
#include "GameData.h"
#include "Screen.h"
#include "Vector2.h"
#include "GameObject.h"
#include "ScrollManager.h"

class BackgroundLayerData;
class GameData;
class Screen;
class Vector2;
class GameObject;
class ScrollManager;

/**
 * @brief Camada de um fundo.
 *
 */
class BackgroundLayer {
public:
        /**
         * @brief
         *
         * @param bgLayerData
         * @param mainGameObjectm
         */
        BackgroundLayer(BackgroundLayerData *bgLayerData, GameObject *mainGameObjectm);
        /**
         * @brief
         *
         */
        virtual ~BackgroundLayer();

        /**
         * @brief Atualiza a camada.
         *
         * @param dt
         */
        void update(int dt);
        /**
         * @brief Renderiza a camada.
         *
         * @param screen
         */
        void render(Screen *screen);
        /**
         * @brief Renderiza as repetições à esqueda, se houverem.
         *
         * @param screen
         */
        void renderLeftRepetitions(Screen *screen);
        /**
         * @brief Renderiza as repetições à direita, se houverem.
         *
         * @param screen
         */
        void renderRightRepetitions(Screen *screen);
        /**
         * @brief Renderiza as repetições acima, se houverem.
         *
         * @param screen
         */
        void renderUpRepetitions(Screen *screen);
        /**
         * @brief Renderiza as repetições abaixo, se houverem.
         *
         * @param screen
         */
        void renderDownRepetitions(Screen *screen);

        Vector2 pos; /**< Posição real. */
        Vector2 posWithoutDisplacement; /**< Posição sem deslocamenteo. */
        Vector2 v; /**< Velocidade*/

        SDL_Surface *surface; /**< */
        SDL_Rect rect; /**<  */
        Rect preRect; /**<  */

        BackgroundLayerData *bgLayerData; /**<  */
        GameObject *mainGameObject; /**<  */
        ScrollManager *scrollManager; /**<  */

        static const int STATIC = 0; /**<  */
        static const int FLOATING = 1; /**<  */
        static const int FLOATING_RELATIVE_TO_CHARACTER_POSITION = 2; /**<  */
        static const int FLOATING_VELOCITY = 3; /**<  */
};

#endif /* BACKGROUNDLAYER_H_ */
