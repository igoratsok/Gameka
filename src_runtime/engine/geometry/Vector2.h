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

#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <math.h>
#include <stdio.h>

#include "CommonTypes.h"


/**
 * @brief Representação de vetor (grandeza física) tridimensional.
 *
 * Obs.: foi antes chamado de Vector2 pois, inicialmente, era bidimensional.
 *
 */
class Vector2 {
public:
        /**
         * @brief Construtor inicializando tudo com zero.
         *
         */
        Vector2();
        /**
         * @brief Construtor inicializando x e y, z = 0.
         *
         * @param x
         * @param y
         */
        Vector2(commtypes::real x, commtypes::real y);
        /**
         * @brief Construtor inicializando x, y e z.
         *
         * @param x
         * @param y
         * @param z
         */
        Vector2(commtypes::real x, commtypes::real y,  commtypes::real z);
        /**
         * @brief
         *
         */
        virtual ~Vector2();

        /**
         * @brief Obtém módulo do vetor.
         *
         */
        commtypes::real magnitude();
        /**
         * @brief Adiciona a um vetor com cada elemento multiplicado por uma escala.
         *
         * @param vector O vetor a ser adicionado.
         * @param scale A escala do vetor vector.
         */
        void addScaledVector(const Vector2 *vector, commtypes::real scale);
        /**
         * @brief Limita um vetor, não deixando ele passar de um certo valor.
         *
         * @param vector
         */
        void limitVector(const Vector2 *vector);
        /**
         * @brief Obtém a direção de um vetor.
         *
         */
        Vector2 getDirecao();

        commtypes::real x; /**< Intensidade no eixo x. */
        commtypes::real y; /**< Intensidade no eixo y. */
        commtypes::real z; /**< Intensidade no eixo z. */

        /**
         * @brief Obtém a intensidade de um eixo por um número.
         *
         * @param no Número do eixo: \n
                            - 0: eixo x;
                            - 1: eixo y;
                            - 2: eixo z;
         */
        commtypes::real getAxisByNo(int no);
        /**
         * @brief Determina a intensidade de um eixo por um número.
         *
         * @param no
         * @param value
         */
        void setAxisByNo(int no, commtypes::real value);
};

#endif /* VECTOR2_H_ */
