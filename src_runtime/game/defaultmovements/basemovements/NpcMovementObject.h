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
#ifndef NPCMOVEMENTOBJECT_H_
#define NPCMOVEMENTOBJECT_H_

#include <math.h>

#include "AcceleratedParticle.h"
#include "PlayerData.h"
#include "DialogueText.h"

class PlayerData;
class DialogueText;

/**
 * @brief Objeto do tipo NPC (Non-Player Character). Possui formas
 * de movimentação e pode emitir diálogos.
 *
 */
class NpcMovementObject : public AcceleratedParticle {
public:
        /**
         * @brief Construtor.
         *
         */
        NpcMovementObject();
        /**
         * @brief Construtor.
         *
         * @param gameObjectInstance GameObjectInstance da instância.
         */
        NpcMovementObject(GameObjectInstance *gameObjectInstance);
        /**
         * @brief
         *
         */
        virtual ~NpcMovementObject();

        /**
         * @brief Realiza o tipo de movimento do NPC de acordo com
         * o tipo pré-determinado, e verifica se algum personagem
         * pressionou "X" ou "Espaço" próximo dele e, neste caso, emite mensagem.
         *
         * @param dt tempo do frame
         */
        int update(int dt);

        int direction; /**< Direção; */
        int movementType; /**< Tipo de movimentação: \n
                        - 0 (PARADO)
                        - 1 (SEGUE_PERSONAGEM)
                        - 2 (FOGE_PERSONAGEM)
                        - 3 (MOVE_ESQUERDA_DIREITA)
                        - 4 (MOVE_CIMA_BAIXO)
                        - 5 (MOVIMENTO_CIRCULAR)*/
        int movementRadius; /**< Raio de movimentação; */
        PlayerData *playerData; /**<  */

        commtypes::real movementAngle; /**< Ângulo de movimentação. */
        commtypes::real angularVelocity; /**< Velocidade angular. */

        static const int PARADO = 0; /**<  */
        static const int SEGUE_PERSONAGEM = 1; /**<  */
        static const int FOGE_PERSONAGEM = 2; /**<  */
        static const int MOVE_ESQUERDA_DIREITA = 3; /**<  */
        static const int MOVE_CIMA_BAIXO = 4; /**<  */
        static const int MOVIMENTO_CIRCULAR = 5; /**<  */

};

#endif /* NPCMOVEMENTOBJECT_H_ */
