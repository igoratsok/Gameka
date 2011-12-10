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

#ifndef EIGHTMOVEMENTOBJECT_H_
#define EIGHTMOVEMENTOBJECT_H_

#include <string>
#include <math.h>


#include "CommonTypes.h"
#include "AcceleratedParticle.h"
#include "InputManager.h"
#include "Tilemap.h"


class InputManager;
class Tilemap;


/**
 * @brief Objeto de movimento em oito direções.
 *
 * Este objeto movimenta-se nas diversas direções
 * de acordo com o input do teclado. Herda de
 * Accelerated particle, portanto, decide-se para que direção
 * ele se movimenta alterando seu valor da aceleração.
 *
 * A detecção de colisão está implementada na classe pai.
 *
 */
class EightMovementObject : public AcceleratedParticle {
public:
        /**
         * @brief
         *
         */
        EightMovementObject();
        /**
         * @brief Construtor.
         *
         * @param fileName Arquivo da imagem do objeto.
         * @param x Posição X
         * @param y Posição Y
         */
        EightMovementObject(std::string *fileName, commtypes::real x, commtypes::real y);
        /**
         * @brief Construtor.
         *
         * @param gameObjectInstance GameObjectInstance da instância.
         */
        EightMovementObject(GameObjectInstance *gameObjectInstance);
        /**
         * @brief
         *
         */
        virtual ~EightMovementObject();

        /**
         * @brief
         *
         * @param dt tempo do frame
         */
        int update(int dt);

        /**
         * @brief
         *
         * @param value
         */
        void setAutomaticRotation(bool value);




        InputManager *inputManager; /**< TODO */



private:
        bool automaticRotation; /**< TODO */

};

#endif /* EIGHTMOVEMENTOBJECT_H_ */

