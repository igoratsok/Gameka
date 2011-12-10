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

#ifndef GAMEOBJECTCREATIONDATA_H_
#define GAMEOBJECTCREATIONDATA_H_

#include "GameObjectClass.h"
#include "GameObject.h"

class GameObjectClass;
class GameObject;

/**
 * @brief Classe para armazenamento de objetos a serem criados no frame.
 * É utilizado em eventos.
 */
class GameObjectCreationData {
public:
        /**
         * @brief Construtor.
         *
         * @param thrower Objeto que está atirando.
         * @param throwable Classe do objeto a ser atirada.
         * @param throwIntensity Intensidade.
         */
        GameObjectCreationData(GameObject *thrower, GameObjectClass *throwable, int throwIntensity);
        /**
         * @brief
         *
         */
        virtual ~GameObjectCreationData();

        GameObject *thrower; /**< Objeto que está atirando. */
        GameObjectClass *throwable; /**< Classe de objeto a ser atirada. */
        int throwIntensity; /**< Intensidade. */
};

#endif /* GAMEOBJECTCREATIONDATA_H_ */
