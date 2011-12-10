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
#ifndef ITEMMOVEMENTOBJECT_H_
#define ITEMMOVEMENTOBJECT_H_

#include "NpcMovementObject.h"
#include "PlayerData.h"
#include "Interpreter.h"

class PlayerData;
class Interpreter;

/**
 * @brief Objeto referente a Itens. Podem ser pegos no cenário
 * e possuem um determinado efeito.
 *
 */
class ItemMovementObject : public NpcMovementObject {
public:
        /**
         * @brief Construtor.
         *
         */
        ItemMovementObject();
        /**
         * @brief Construtor.
         *
         * @param gameObjectInstance GameObjectInstance da instância.
         */
        ItemMovementObject(GameObjectInstance *gameObjectInstance);

        virtual ~ItemMovementObject();

        /**
         * @brief Determina modo de espada para o Item, caso ele seja
         * uma espada.
         *
         */
        void setSwordMode();

        /**
         * @brief Verifica se o item foi pego por um objeto e aplica os efeitos.
         *
         * @param dt tempo do frame
         */
        int update(int dt);


        PlayerData *playerData; /**<  */
        GameObject *thrower; /**< Atirador do item, caso tenha um. */

        bool isSword; /**< Se é uma espada. */
        int timer; /**< Timer da espada. */
};

#endif /* ITEMMOVEMENTOBJECT_H_ */

