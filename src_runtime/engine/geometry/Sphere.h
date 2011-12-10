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
#ifndef SPHERE_H_
#define SPHERE_H_

#include "CommonTypes.h"
#include "Vector2.h"
#include "Rectangle.h"

class Vector2;
class Rect;

/**
 * @brief Representação de esfera.
 *
 */
class Sphere {
public:
        /**
         * @brief Construtor.
         *
         * @param c Centro da esfera.
         * @param r Raio da esfera.
         */
        Sphere(Vector2 c, commtypes::real r);
        /**
         * @brief
         *
         */
        virtual ~Sphere();

        /**
         * @brief Testa colisão entre uma esfera se movendo com um retângulo (função ainda não completa).
         *
         * @param s Esfera.
         * @param f Velocidade da esfera.
         * @param b Retângulo.
         * @param t Tempo de colisão.
         * @param p Ponto de colisão.
         * @param side Lado de colisão:
         */
        static bool testMovingSphereRect(Sphere s, Vector2 f, Rect b, float *t, Vector2 *p, int *side);

        Vector2 c; /**< TODO */
        commtypes::real r; /**< TODO */

        static const int SIDE_LEFT = 0; /**< TODO */
        static const int SIDE_UP = 1; /**< TODO */
        static const int SIDE_RIGHT = 2; /**< TODO */
        static const int SIDE_DOWN = 3; /**< TODO */
};

#endif /* SPHERE_H_ */
