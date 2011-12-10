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
#ifndef PLATFORMERMOVEMENT_H_
#define PLATFORMERMOVEMENT_H_

#include "AcceleratedParticle.h"
#include "InputManager.h"
#include "Tilemap.h"

class InputManager;
class Tilemap;

/**
 * @brief Movimento de jogo de plataforma. Existe uma gravidade
 * que sempre joga o objeto para baixo e, ao encostar com fundo,
 * ele pode pular.
 *
 */
class PlatformerMovement: public AcceleratedParticle {
public:
        /**
         * @brief Construtor.
         *
         * @param fileName Arquivo da imagem do objeto.
         * @param x Posição X
         * @param y Posição Y
         */
        PlatformerMovement(std::string *fileName, commtypes::real x, commtypes::real y);
        /**
         * @brief Construtor.
         *
         * @param gameObjectInstance GameObjectInstance da instância.
         */
        PlatformerMovement(GameObjectInstance *gameObjectInstance);
        /**
         * @brief
         *
         */
        virtual ~PlatformerMovement();

        /**
         * @brief Verifica qual animação mostrar, decide os valores da velocidade
         * conforme entrada do teclado,
         * verifica se pode pular e se está pulando em cima de um inimigo.
         *
         * @param dt tempo do frame
         */
        int update(int dt);

        /**
         * @brief Executa habilidade de pulo duplo.
         *
         * @param skillData SkillData da habilidade.
         * @param intensity Intensidade da habilidade.
         * @param magicCost Custo de magia da habilidade.
         */
        void doubleJump(SkillData *skillData, int intensity, int magicCost);
        /**
         * @brief Executa habilidade de quicar paredes.
         *
         * @param skillData SkillData da habilidade.
         * @param intensity Intensidade da habilidade.
         * @param magicCost Custo de magia da habilidade.
         */
        void wallKick(SkillData *skillData, int intensity, int magicCost);

        InputManager *inputManager; /**< */
        bool automaticRotation; /**< Se o objeto tem rotação automática. */




        int estadoObjeto; /**< Estado em que o objeto está: \n
                                - 0 (ESTADO_PARADO);
                                - 1 (ESTADO_ANDANDO);
                                - 2 (ESTADO_CORRENDO);
                                - 3 (ESTADO_PULANDO);
                                - 4 (ESTADO_CAINDO);
                                - 5 (ESTADO_ATACANDO);
                                - 6 (ESTADO_LEVANDO_DANO);
                                - 7 (ESTADO_MORRENDO); */

        bool doubleJumping; /**< Se está realizando um pulo duplo. */

        static const int ESTADO_PARADO = 0; /**<  */
        static const int ESTADO_ANDANDO = 1; /**<  */
        static const int ESTADO_CORRENDO = 2; /**<  */
        static const int ESTADO_PULANDO = 3; /**<  */
        static const int ESTADO_CAINDO = 4; /**<  */
        static const int ESTADO_ATACANDO = 5; /**<  */
        static const int ESTADO_LEVANDO_DANO = 6; /**<  */
        static const int ESTADO_MORRENDO = 7; /**<  */
};

#endif /* PLATFORMERMOVEMENT_H_ */
