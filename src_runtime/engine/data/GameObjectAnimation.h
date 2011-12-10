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

#ifndef GAMEOBJECTANIMATION_H_
#define GAMEOBJECTANIMATION_H_

#include <vector>
#include <string>
#include <iostream>

#include "SpriteRepresentation.h"
#include "AnimationData.h"
#include "Vector2.h"

class SpriteRepresentation;
class AnimationData;
class Vector2;

/**
 * @brief Entidade para guardar animações de um objeto.
 *
 */
class GameObjectAnimation {
public:
       /**
        * @brief Construtor.
        *
        */
	GameObjectAnimation();
	virtual ~GameObjectAnimation();

        int id; /**< Identificador. */
        int type; /**< Tipo: \n
                        1: Estático;
                        2: Animado. */

        std::string name; /**< Nome. */

        std::vector<SpriteRepresentation*> *sprites; /**< Array de 32 direções para sprites. */
        std::vector<AnimationData*> *animations; /**< Array de 32 direções para animações. */
        std::vector<int> *types; /**< Array de 32 posições pra dizer se deve acessar o array
                            de sprites ou de animação de acordo com o tipo  */
        std::vector<bool> horizontalInvert; /**< Inverte horizontalmente a animação (32 posições, para cada direção). */
        std::vector<bool> verticalInvert; /**< Inverte verticalmente a animação (32 posições, para cada direção). */
        std::vector<Vector2> adjustments; /**< Ajustes no ponto de desenho (32 posições, para cada direção). */


        int numDirectionFactor; /**< Não mais utilizado. */

        static const int NON_EXISTANT = 0;
        static const int STATIC = 1; /**<  */
        static const int ANIMATED = 2; /**<  */

};

#endif /* GAMEOBJECTANIMATION_H_ */
