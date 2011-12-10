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
#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <iostream>
#include <math.h>
#include <algorithm>

#include "Vector2.h"

class Vector2;


/**
 * @brief Representação de um retângulo.
 *
 */
class Rect {
public:
        /**
         * @brief Construtor inicializando tudo com zero.
         *
         */
        Rect();
        /**
         * @brief Construtor inicializando cada um dos parâmetros.
         *
         * @param x Posição x.
         * @param y Posição y.
         * @param w Largura.
         * @param h Altura.
         */
        Rect(int x, int y, int w, int h);
        /**
         * @brief
         *
         */
        virtual ~Rect();

        /**
         * @brief Teste de intersecção com outro retângulo.
         *
         * @param rectangle O outro retângulo.
         */
        bool intersectsWith(Rect *rectangle);
        /**
         * @brief Teste de intersecção com outro retângulo no eixo x apenas.
         *
         * @param rectangle O outro retângulo.
         */
        bool intersectsXAxisWith(Rect *rectangle);
        /**
         * @brief Teste de intersecção com outro retângulo no eixo y apenas.
         *
         * @param rectangle O outro retângulo.
         */
        bool intersectsYAxisWith(Rect *rectangle);
        /**
         * @brief Se contém o outro retângulo dentro.
         *
         * @param rectangle O outro retângulo.
         */
        bool contains(Rect *rectangle);
        /**
         * @brief Se contém um ponto dentro.
         *
         * @param vector O ponto.
         */
        bool contains(Vector2 vector);
        /**
         * @brief Obtém ponto esquerdo superior do retângulo.
         *
         */
        Vector2 getMin();
        /**
         * @brief Obtém ponto direito inferior do retângulo.
         *
         */
        Vector2 getMax();

        /**
         * @brief Verifica intersecção entre um raio (linha) com este retângulo.
         *
         * @param p Posição do raio.
         * @param f Direção do raio em magnitude (o quanto ele desloca).
         * @param tmin O tempo de intersecção, entre 0 e 1 no quadro.
         * @param q A posição de intersecção.
         */
        bool rayIntersection(Vector2 p, Vector2 f, float *tmin, Vector2 *q);

        /**
         * @brief Intersepta dois retângulos se movimentando.
         *
         * @param a Retângulo a.
         * @param b Retângulo b.
         * @param va Velocidade do retângulo a.
         * @param vb Velocidade do retângulo b.
         * @param tfirst Momento de colisão, entre 0 e 1 no quadro.
         * @param tlast Momento de fim de colisão, entre 0 e 1 no quadro.
         */
        static bool intersectMovingRectRect(Rect a, Rect b, Vector2 va, Vector2 vb,
			float *tfirst, float *tlast);
        /**
         * @brief Intersepta dois retângulos se movimentando (outra técnica).
         *
         * @param a Retângulo a.
         * @param b Retângulo b.
         * @param va Velocidade do retângulo a.
         * @param vb Velocidade do retângulo b.
         * @param tfirst Momento de colisão, entre 0 e 1 no quadro.
         * @param tlast Momento de fim de colisão, entre 0 e 1 no quadro.
         */
        static bool sweepTestRectRect(Rect a, Rect b, Vector2 va, Vector2 vb, float *tfirst, float *tlast);

        /**
         * @brief Intersepta dois retângulos se movimentando. Essa também retorna
         * o lado de intersecção.
         *
         * @param v Velocidade deste retângulo.
         * @param rect Outro retângulo.
         * @param tfirst Momento de colisão, entre 0 e 1 no quadro.
         * @param tlast Momento de fim de colisão, entre 0 e 1 no quadro.
         * @param lado Lado de colisão: \n
                        - 0: esquerda;
                        - 1: cima;
                        - 2: direita;
                        - 3: baixo.
         * @param movedRectCol Retângulo movido para a posição de colisão.
         */
        bool movingIntersectRect(Vector2 v, Rect rect, float *tfirst, float *tlast, int *lado, Rect *movedRectCol);

        int x; /**< Posição no eixo x. */
        int y; /**< Posição no eixo y. */
        int w; /**< Largura. */
        int h; /**< Altura. */


        static const int SIDE_LEFT = 0; /**<  */
        static const int SIDE_UP = 1; /**<  */
        static const int SIDE_RIGHT = 2; /**<  */
        static const int SIDE_DOWN = 3; /**<  */
};

#endif /* RECTANGLE_H_ */
