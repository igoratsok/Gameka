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

#ifndef BOUNCINGBALL_H_
#define BOUNCINGBALL_H_

#include "GameObject.h"
#include "CommonTypes.h"
#include "Tilemap.h"
#include "Tile.h"


class Tilemap;
class Tile;

/**
 * @brief BouncingBall é um objeto de jogo que bate nas paredes e quica.
 * Pode se mover horizontalmente e/ou verticalmente.
 *
 */
class BouncingBall: public GameObject {
public:
        /**
         * @brief Construtor.
         *
         */
        BouncingBall();
        /**
         * @brief Construtor.
         *
         * @param fileName Arquivo da imagem do objeto.
         * @param x Posição X
         * @param y Posição Y
         */
        BouncingBall(std::string *fileName, commtypes::real x, commtypes::real y);
        /**
         * @brief Construtor.
         *
         * @param gameObjectInstance GameObjectInstance da instância.
         */
        BouncingBall(GameObjectInstance *gameObjectInstance);
        /**
         * @brief
         *
         */
        virtual ~BouncingBall();

        /**
         * @brief Realiza os passos para simulação de bola saltitante estilo Pong.
         *
         * @param dt tempo do frame
         */
        int update(int dt);
        /**
         * @brief Renderiza o objeto.
         *
         * @param screen
         */
        void render(Screen *screen);
        /**
         * @brief Quica a bola de acordo com o retângulo da parede que colidiu.
         *
         * @param rect Retângulo do objeto que quicou
         * @param dt tempo do frame
         * @param velocity Velocidade do objeto com que colidiu. Pode ser NULL se for desconsiderado.
         */
        void bounce(Rect rect, int dt, Vector2 *velocity = NULL);

        /**
         * @brief Segue um ponto.
         *
         * @param point Ponto
         * @param dt tempo do frame
         */
        void follow(Vector2 point, int dt);
        /**
         * @brief Foge de um ponto.
         *
         * @param point Ponto
         * @param dt tempo do frame
         */
        void moveAway(Vector2 point, int dt);
        /**
         * @brief Segue um ponto com velocidade.
         *
         * @param point
         * @param dt tempo do frame
         * @param velocity
         */
        void follow(Vector2 point, int dt, float velocity);
        /**
         * @brief Foge de um ponto com velocidade.
         *
         * @param point
         * @param dt tempo do frame
         * @param velocity
         */
        void moveAway(Vector2 point, int dt, float velocity);

        /**
         * @brief Procedimento que ocorre ao quicar através de um evento.
         *
         * @param dt tempo do frame
         */
        void bounceEvent(int dt);


        Vector2 *velocity; /**< TODO */
        Vector2 maxVelocity; /**< TODO */
};

#endif /* BOUNCINGBALL_H_ */
