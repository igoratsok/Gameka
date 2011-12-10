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

#ifndef VEHICLEMOVEMENT_H_
#define VEHICLEMOVEMENT_H_

#include <string>
#include <math.h>

#include "AcceleratedParticle.h"
#include "CommonTypes.h"
#include "InputManager.h"
#include "AuxiliarMath.h"

class InputManager;
class AuxiliarMath;


/**
 * @brief Movimentação de veículo.
 * Ao pressionar para esquerda ou direita, ele muda a direção.
 * Ao pressionar para frente, ele se move na direção.
 * Ao pressionar para trás, se move no sentido contrário à direção.
 *
 */
class VehicleMovement: public AcceleratedParticle {
public:
        /**
         * @brief
         *
         */
        VehicleMovement();
        /**
         * @brief Construtor.
         *
         * @param fileName Arquivo da imagem do objeto.
         * @param x Posição X
         * @param y Posição Y
         */
        VehicleMovement(std::string *fileName, commtypes::real x, commtypes::real y);
        /**
         * @brief Construtor.
         *
         * @param gameObjectInstance GameObjectInstance da instância.
         */
        VehicleMovement(GameObjectInstance *gameObjectInstance);
        /**
         * @brief
         *
         */
        virtual ~VehicleMovement();

        /**
         * @brief Muda o ângulo do veículo se pressionar para esquerda ou direita, mudando
         * a sua direção.
         * Ao pressionar para frente, ele se move na direção.
         * Ao pressionar para trás, se move no sentido contrário à direção.
         *
         * @param dt tempo do frame
         */
        int update(int dt);

        commtypes::real angle, angularVelocity; /**< TODO */
        bool isCar; /**< TODO */

        InputManager *inputManager; /**< TODO */
        AuxiliarMath *auxiliarMath; /**< TODO */

};

#endif /* VEHICLEMOVEMENT_H_ */
