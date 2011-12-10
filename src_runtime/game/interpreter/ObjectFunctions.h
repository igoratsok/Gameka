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
#ifndef OBJECTFUNCTIONS_H_
#define OBJECTFUNCTIONS_H_

#include <vector>
#include <list>
#include <algorithm>

#include "GameObject.h"
#include "GameObjectClass.h"
#include "ObjectFactory.h"
#include "ItemMovementObject.h"
#include "InputManager.h"
#include "PlayerData.h"

class GameObject;
class GameObjectClass;
class ObjectFactory;

class ItemMovementObject;
class InputManager;

class PlayerData;

/**
 * @brief Classe contendo uma série de funções para manipulação genérica de objetos,
 * e também para verificação e execução das habilidades dos objetos.
 *
 */
class ObjectFunctions {
public:
        /**
         * @brief
         *
         */
        virtual ~ObjectFunctions();

        /**
         * @brief Fornece a lista de isntâncias de objetos.
         *
         * @param gameObjectList
         */
        void setGameObjectList(std::list<GameObject*> *gameObjectList);
        /**
         * @brief Fornece a lista de objetos a serem adicionados no quadro.
         *
         * @param addGameObjectList
         */
        void setAddGameObjectList(std::vector<GameObject*> *addGameObjectList);

        /**
         * @brief Atira um objeto.
         *
         * @param thrower A instância que está atirando.
         * @param throwable A classe do objeto a ser atirada.
         * @param intensity A intensidade do tiro.
         * @param magicCost O custo de magia.
         */
        void throwObject(GameObject *thrower, GameObjectClass *throwable, int intensity, int magicCost);
        /**
         * @brief Atira um objeto na direção de uma posição.
         *
         * @param thrower A instância que está atirando.
         * @param throwable A classe do objeto a ser atirada.
         * @param intensity A intensidade do tiro.
         * @param position A posição para onde está atirando.
         * @param magicCost O custo de magia.
         */
        void throwObject(GameObject *thrower, GameObjectClass *throwable, int intensity, Vector2 position, int magicCost);
        /**
         * @brief
         *
         * @param thrower A instância que está atirando.
         * @param throwable A classe do objeto a ser atirada.
         * @param magicCost O custo de magia.
         */
        void throwSwordObject(GameObject *thrower, GameObjectClass *throwable, int magicCost);

        /**
         * @brief Processa todas as habilidades de uma instância de objeto e executa.
         *
         * @param gameObject
         */
        void processSkills(GameObject *gameObject);

        /**
         * @brief Obtém instância singleton.
         *
         */
        static ObjectFunctions* getInstance();
private:
        /**
         * @brief
         *
         */
        ObjectFunctions();

        static ObjectFunctions *singleton; /**<  */
        std::list<GameObject*> *gameObjectList; /**< Lista de instâncias. */
        std::vector<GameObject*> *addGameObjectList; /**< Instâncias a serem adicionadas. */
        InputManager *inputManager; /**<  */
};

#endif /* OBJECTFUNCTIONS_H_ */
