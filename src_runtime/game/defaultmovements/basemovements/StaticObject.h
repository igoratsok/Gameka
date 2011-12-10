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

#ifndef STATICOBJECT_H_
#define STATICOBJECT_H_

#include "AcceleratedParticle.h"

/**
 * @brief Objeto estático. Fica parado. Pode ser manipulado via eventos.
 *
 */
class StaticObject : public AcceleratedParticle {
public:
        /**
         * @brief Construtor.
         *
         */
        StaticObject();
        /**
         * @brief Construtor.
         *
         * @param fileName Arquivo da imagem do objeto.
         * @param x Posição X
         * @param y Posição Y
         */
        StaticObject(std::string *fileName, commtypes::real x, commtypes::real y);
        /**
         * @brief Construtor.
         *
         * @param gameObjectInstance GameObjectInstance da instância.
         */
        StaticObject(GameObjectInstance *gameObjectInstance);
        /**
         * @brief
         *
         */
        virtual ~StaticObject();

        /**
         * @brief Nada faz, apenas chama o update da classe pai.
         *
         * @param dt tempo do frame
         */
        int update(int dt);
};

#endif /* STATICOBJECT_H_ */
