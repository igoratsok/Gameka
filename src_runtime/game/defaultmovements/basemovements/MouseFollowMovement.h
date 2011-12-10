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
#ifndef MOUSEFOLLOWMOVEMENT_H_
#define MOUSEFOLLOWMOVEMENT_H_

#include "AcceleratedParticle.h"
#include "InputManager.h"

class InputManager;


/**
 * @brief Objeto com movimento que segue o mouse em determinadas maneiras.
 * Pode seguir ao clicar, sem clicar, ou estar sempre na posição do mouse,
 * ou apenas ao clicar.
 *
 */
class MouseFollowMovement: public AcceleratedParticle {
public:
        /**
         * @brief Construtor. (não mais utilizado)
         *
         * @param mouseMovementType
         */
        MouseFollowMovement(int mouseMovementType);
        /**
         * @brief Construtor.
         *
         * @param fileName Arquivo da imagem do objeto.
         * @param x Posição X
         * @param y Posição Y
         */
        MouseFollowMovement(std::string *fileName, commtypes::real x, commtypes::real y, int mouseMovementType);
        /**
         * @brief Construtor.
         *
         * @param gameObjectInstance GameObjectInstance da instância.
         */
        MouseFollowMovement(GameObjectInstance *gameObjectInstance);
        /**
         * @brief
         *
         */
        virtual ~MouseFollowMovement();

        /**
         * @brief Aplica mudanças na posição do objeto de acordo com o tipo de movimentação
         * levando-se em consideração o mouse.
         *
         * @param dt tempo do frame
         */
        int update(int dt);

        InputManager *inputManager; /**< TODO */
        int mouseMovementType; /**< TODO */

        Vector2 *followPoint; /**< TODO */
};

#endif /* MOUSEFOLLOWMOVEMENT_H_ */

