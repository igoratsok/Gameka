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

#ifndef PLAYERDATA_H_
#define PLAYERDATA_H_

#include <sstream>
#include <string>

#include "GameObject.h"
#include "Tilemap.h"
#include "Screen.h"
#include "Text.h"

class GameObject;
class Tilemap;
class Screen;
class Text;

/**
 * @brief Classe para armazenar e realizar operações com os dados
 * do jogador.
 *
 */
class PlayerData {
public:



        /**
         * @brief Determina qual o objeto principal (jogador).
         *
         * @param player
         */
        void setPlayer(GameObject *player);
        /**
         * @brief Adiciona pontos.
         *
         * @param points
         */
        void addPoints(int points);
        /**
         * @brief Adiciona vida.
         *
         * @param hp
         */
        void addHp(int hp);
        /**
         * @brief Adiciona magia.
         *
         * @param mp
         */
        void addMp(int mp);
        /**
         * @brief Adiciona dano.
         *
         * @param damager Quem está dando dano.
         * @param extraDamage Multiplicador de dano extra.
         */
        void addDamage(GameObject *damager, int extraDamage = 1);
        /**
         * @brief Adiciona número de vidas.
         *
         * @param lives
         */
        void addLives(int lives);

        /**
         * @brief Reinicia número de vidas.
         *
         */
        void resetLives();
        /**
         * @brief Reinicia hp.
         *
         */
        void resetHp();

        /**
         * @brief Se está morto (hp <= 0)
         *
         */
        bool isDead();

        /**
         * @brief Obtém o número de pintos.
         *
         */
        int getPoints();
        /**
         * @brief Obtém o HP.
         *
         */
        int getHp();
        /**
         * @brief Obtém o MP.
         *
         */
        int getMp();
        /**
         * @brief Obtém o número de vidas.
         *
         */
        int getLives();

        /**
         * @brief Determina posição de teletransporte para o próximo mapa.
         *
         * @param teleportPosition
         */
        void setTeleportPosition(Vector2 teleportPosition);
        /**
         * @brief Obtém a posição de teletransporte.
         *
         */
        Vector2* getTeleportPosition();
        /**
         * @brief Libera memória da posição de teletransporte.
         *
         */
        void freeTeleportPosition();

        /**
         * @brief Obtém o jogador principal.
         *
         */
        GameObject *getPlayer();
        /**
         * @brief Determina o mapa principal.
         *
         * @param map
         */
        void setCurrentMap(Tilemap *map);
        /**
         * @brief Obtém o mapa atual.
         *
         */
        Tilemap *getCurrentMap();

        /**
         * @brief Renderiza a HUD.
         *
         * @param screen
         */
        void renderHud(Screen *screen);

        /**
         * @brief Obtém instância do objeto singleton.
         *
         */
        static PlayerData* getInstance();



private:
        /**
         * @brief Construtor.
         *
         */
        PlayerData();
        /**
         * @brief
         *
         */
        virtual ~PlayerData();

        int points, hp, mp; /**<  */
        int lives; /**<  */
        GameObject *player; /**<  */
        Tilemap *currentMap; /**< */
        Vector2 *teleportPosition; /**<  */

        Text *pointsText, *hpText, *mpText, *livesText; /**<  */

        static PlayerData *singleton; /**<  */

};

#endif /* PLAYERDATA_H_ */
