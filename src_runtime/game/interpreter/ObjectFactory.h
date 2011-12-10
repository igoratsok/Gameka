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
#ifndef OBJECTFACTORY_H_
#define OBJECTFACTORY_H_

#include "../../engine/data/GameObjectInstance.h"

#include "EightMovementObject.h"
#include "PlatformerMovement.h"
#include "VehicleMovement.h"
#include "StaticObject.h"
#include "BouncingBall.h"
#include "MouseFollowMovement.h"
#include "ItemMovementObject.h"
#include "NpcMovementObject.h"
#include "EnemyMovementObject.h"

class GameObjectInstance;

class EightMovementObject;
class PlatformerMovement;
class VehicleMovement;
class StaticObject;
class BouncingBall;
class MouseFollowMovement;
class ItemMovementObject;
class NpcMovementObject;
class EnemyMovementObject;

/**
 * @brief Fábrica de instâncias de objetos.
 *
 */
class ObjectFactory {
public:
        /**
         * @brief
         *
         */
        ObjectFactory();
        /**
         * @brief
         *
         */
        virtual ~ObjectFactory();

        /**
         * @brief Cria uma istância de objeto em oito direções.
         *
         * @param gameObjectInstance
         */
        static EightMovementObject* mountEightMovement(GameObjectInstance *gameObjectInstance);
        /**
         * @brief Cria uma istância de um objeto de plataforma.
         *
         * @param gameObjectInstance
         */
        static PlatformerMovement* mountPlatformerMovement(GameObjectInstance *gameObjectInstance);
        /**
         * @brief Cria uma istância de um objeto de carro.
         *
         * @param gameObjectInstance
         */
        static VehicleMovement* mountVehicleMovement(GameObjectInstance *gameObjectInstance);
        /**
         * @brief Cria uma istância de um objeto estático.
         *
         * @param gameObjectInstance
         */
        static StaticObject* mountStaticObject(GameObjectInstance *gameObjectInstance);
        /**
         * @brief Cria uma istância de um objeto de bola saltitante.
         *
         * @param gameObjectInstance
         */
        static BouncingBall* mountBouncingBallObject(GameObjectInstance *gameObjectInstance);
        /**
         * @brief Cria uma istância de objeto com movimento baseado no mouse.
         *
         * @param gameObjectInstance
         */
        static MouseFollowMovement* mountMouseFollowMovementObject(GameObjectInstance *gameObjectInstance);
        /**
         * @brief Cria uma istância de item.
         *
         * @param gameObjectInstance
         */
        static ItemMovementObject* mountItemMovementObject(GameObjectInstance *gameObjectInstance);
        /**
         * @brief Cria uma istância de NPC aliado.
         *
         * @param gameObjectInstance
         */
        static NpcMovementObject* mountNpcMovementObject(GameObjectInstance *gameObjectInstance);
        /**
         * @brief Cria uma istância de NPC inimigo.
         *
         * @param gameObjectInstance
         */
        static EnemyMovementObject* mountEnemyMovementObject(GameObjectInstance *gameObjectInstance);

};

#endif /* OBJECTFACTORY_H_ */
