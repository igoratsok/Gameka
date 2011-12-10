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
#ifndef ENEMYMOVEMENTOBJECT_H_
#define ENEMYMOVEMENTOBJECT_H_

#include "NpcMovementObject.h"

#include "ObjectFunctions.h"

class ObjectFunctions;

/**
 * @brief Objeto de movimento de inimigos. Ele pode se mover e atacar
 * o personagem e outros objetos da tela.
 *
 */
class EnemyMovementObject: public NpcMovementObject {
public:
        /**
         * @brief
         *
         */
        EnemyMovementObject();
        /**
         * @brief Construtor.
         *
         * @param gameObjectInstance GameObjectInstance da instância.
         */
        EnemyMovementObject(GameObjectInstance *gameObjectInstance);
        /**
         * @brief
         *
         */
        virtual ~EnemyMovementObject();

        /**
         * @brief Atualiza o movimento do inimigo e executa os seus ataques.
         *
         * @param dt tempo do frame
         */
        int update(int dt);

        int attackTimer; /**< TODO */
};

#endif /* ENEMYMOVEMENTOBJECT_H_ */
