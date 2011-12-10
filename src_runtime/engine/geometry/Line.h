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

#ifndef LINE_H_
#define LINE_H_

#include "Vector2.h"

class Vector2;


/**
 * @brief Representação de uma linha. Possui funções
 * para interpolar as posições dessa linha e retornar
 * os valores.
 *
 */
class Line {
public:
        /**
         * @brief Construtor da classe.
         *
         * @param start Ponto de início da linha.
         * @param end Ponto de fim da linha.
         */
        Line(Vector2 *start, Vector2 *end);
        /**
         * @brief
         *
         */
        virtual ~Line();

        /**
         * @brief Inicia interpolação.
         *
         */
        void startInterpolation();
        /**
         * @brief Obtém um valor da interpolação.
         *
         */
        Vector2 retrieveInterpolation();
        /**
         * @brief Se acabou a interpolação.
         *
         */
        bool finished();

        /**
         * @brief Obtém um valor Y baseado no valor X.
         *
         * @param x
         */
        float getY(float x);
        /**
         * @brief Obtém um valor X baseado no valor Y.
         *
         * @param y
         */
        float getX(float y);

        bool linhaVertical; /**<  */
        Vector2 pontoInterpolacao; /**< Ponto atual de interpolação. */
        Vector2 *start; /**< Ponto de início. */
        Vector2 *end; /**< Ponto de fim. */

        Vector2 dir; /**< Direção da interpolação. */

        float m; /**< Coeficiente angular da reta. */
        float q; /**< Coeficiente linear da reta. */
        float passo; /**< Passo da reta (o tanto que irá pular de uma interpolação a outra). */
};


#endif /* LINE_H_ */
