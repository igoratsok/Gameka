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

#ifndef ACCELERATEDPARTICLE_H_
#define ACCELERATEDPARTICLE_H_

#include <string>
#include <algorithm>

#include "GameObject.h"
#include "CommonTypes.h"
#include "Tilemap.h"
#include "Tile.h"


class Tilemap;
class Tile;

/**
 * @brief  Objeto de partícula acelerada. É um objeto de jogo,
 * só que no entanto possui valores de velocidade e aceleração
 * como vetores bidimensionais, sendo que a sua posição é modificada de acordo
 * com eles, usando fórmulas da física.
 * Além disso, existem métodos para verificar colisão dessas partículas
 * com o mapa.
 */
class AcceleratedParticle: public GameObject {
public:
        /**
         * @brief Construtor.
         *
         */
        AcceleratedParticle();
        /**
         * @brief Construtor.
         *
         * @param fileName Arquivo da imagem do objeto.
         * @param x Posição X
         * @param y Posição Y
         */
        AcceleratedParticle(std::string *fileName, commtypes::real x, commtypes::real y);
        /**
         * @brief Construtor.
         *
         * @param gameObjectInstance GameObjectInstance da instância.
         */
        AcceleratedParticle(GameObjectInstance *gameObjectInstance);

        /**
         * @brief
         *
         */
        virtual ~AcceleratedParticle();

        /**
         * @brief Realiza todos os cálculos quanto a velocidade e aceleração, atualiza a posição,
         * verifica colisão e resolve elas.
         *
         * @param dt tempo do frame
         */
        int update(int dt);

        /**
         * @brief Executa habilidade de pulo no eixo Z.
         *
         * @param skillData SkillData da habilidade.
         * @param intensity Intensidade da habilidade.
         * @param magicCost Custo de magia da habilidade.
         */
        void zJump(SkillData *skillData, int intensity, int magicCost);
        /**
         * @brief Executa habilidade de pulo duplo no eixo Z.
         *
         * @param skillData SkillData da habilidade.
         * @param intensity Intensidade da habilidade.
         * @param magicCost Custo de magia da habilidade.
         */
        void zDoubleJump(SkillData *skillData, int intensity, int magicCost);
        /**
         * @brief Executa habilidade de correr.
         *
         * @param skillData SkillData da habilidade.
         * @param intensity Intensidade da habilidade.
         * @param magicCost Custo de magia da habilidade.
         */
        void sprint(SkillData *skillData, int intensity, int magicCost);
        /**
         * @brief Executa habilidade de planar.
         *
         * @param skillData SkillData da habilidade.
         * @param intensity Intensidade da habilidade.
         * @param magicCost Custo de magia da habilidade.
         */
        void glide(SkillData *skillData, int intensity, int magicCost);
        /**
         * @brief Executa habilidade de voar.
         *
         * @param skillData SkillData da habilidade.
         * @param intensity Intensidade da habilidade.
         * @param magicCost Custo de magia da habilidade.
         */
        void fly(SkillData *skillData, int intensity, int magicCost);
        /**
         * @brief Executa habilidade de quicar.
         *
         * @param rect Retângulo do objeto em que quicou.
         * @param dt tempo do frame
         */
        void bounce(Rect rect, int dt);
        /**
         * @brief Executa bounce (inverte as velocidades x e y)
         *
         * @param dt tempo do frame
         */
        void bounceEvent(int dt);

        /**
         * @brief Resolve a colisão com um Tile.
         *
         * @param positionAnt
         * @param dt tempo do frame
         */
        void resolveBoxCollisionTile(Vector2 positionAnt, int dt);
        /**
         * @brief Segue um ponto.
         *
         * @param point Ponto a ser seguido.
         * @param dt tempo do frame
         */
        void follow(Vector2 point, int dt);
        /**
         * @brief Foge de um ponto.
         *
         * @param point Ponto a ser fugido.
         * @param dt tempo do frame
         */
        void moveAway(Vector2 point, int dt);
        /**
         * @brief Segue um ponto em uma velocidade.
         *
         * @param point Ponto a ser seguido.
         * @param dt tempo do frame
         * @param velocity
         */
        void follow(Vector2 point, int dt, float velocity);
        /**
         * @brief Foge de um ponto em uma velocidade.
         *
         * @param pointPonto a ser fugido.
         * @param dt tempo do frame
         * @param velocity
         */
        void moveAway(Vector2 point, int dt, float velocity);

        bool zDoubleJumping; /**< Se está dando pulo duplo no eixo z */
        float glideIntensity; /**< Se está planando */
        float sprintIntensity; /**< Se está correndo */
        float flightIntensity; /**< Se está voando */

        float initialGravity; /**< Gravidade inicial do objeto */




        int accMovementType; /**< Tipo de movimento acelerado ou uniforme. */

        Vector2 maxVelocity, accelerationValue, desaccelerationValue; /**< */

};

#endif /* ACCELERATEDPARTICLE_H_ */

