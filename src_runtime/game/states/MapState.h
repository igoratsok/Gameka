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
#ifndef MAPSTATE_H_
#define MAPSTATE_H_

#include <iostream>
#include <list>

#include "State.h"

#include "GameData.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Screen.h"
#include "Tilemap.h"
#include "PlayerData.h"
#include "BackgroundLayer.h"
#include "GameObjectInstance.h"
#include "StateManager.h"
#include "SoundManager.h"
#include "ObjectFactory.h"
#include "ObjectFunctions.h"
#include "Music.h"
#include "Interpreter.h"
#include "SpatialHashmap.h"
#include "ModalManager.h"
#include "DialogueText.h"

class GameData;
class GameObject;
class Sprite;
class Screen;
class Tilemap;
class PlayerData;
class BackgroundLayer;
class GameObjectInstance;
class StateManager;
class ObjectFactory;
class Music;
class Interpreter;
class SpatialHashmap;
class SoundManager;
class ModalStack;
class DialogueText;


/**
 * @brief Estado de mapa/cenário do jogo.
 *
 */
class MapState : public State {
public:
        /**
         * @brief Construtor.
         *
         * @param stateManager Instância da StateManager.
         */
        MapState(StateManager *stateManager);
        /**
         * @brief
         *
         */
        virtual ~MapState();

        /**
         * @brief Determina o número da fase do mapa a ser carregado.
         *
         * @param idLevel Identificador do mapa.
         */
        void setLevel(int idLevel);

        int idLevel; /**< Número identificador do mapa. */

        Tilemap *map; /**< Instância do mapa. */

        std::list<GameObject*> mapObjects; /**< Objetos existentes no mapa. */
        std::vector<GameObject*> addMapObjects; /**< Objetos a serem adicionados em um quadro de jogo. */



        /**
         * @brief Monta objetos
         *
         */
        void mountObjects();
        /**
         * @brief Corrige a posição dos objetos que estiverem dentro de paredes.
         *
         */
        void correctObjectPositions();
        /**
         * @brief Checa se o objeto entrou em uma TeleportArea e teletransporta, se for o caso.
         *
         */
        void checkMainObjectDefaultEvents();
        /**
         * @brief Adiciona um objeto no mapa.
         *
         * @param gameObject
         */
        void pushObject(GameObject *gameObject);
        /**
         * @brief Remove um objeto do mapa.
         *
         * @param it Iterador apontando para o objeto.
         */
        void removeObject(std::list<GameObject*>::iterator it);




        /**
         * @brief Carrega todos os recursos do mapa, o que inclui o Tilemap,
         * fundos, objetos e músicas.
         *
         */
        void load();
        /**
         * @brief Descarrega os recursos do mapa.
         *
         */
        void unload();
        /**
         * @brief Realiza o passo de atualização do estado.
         * Os passos realizados nessa fase são: \n
         * - Se houver um elemento na ModalStack, executa o Modal que estiver no topo; \n
         * - Se o elemento da ModalStack finalizar, remove um elemento da pilha e reinicia o loop; \n
         * - Se a ModalStack estiver vazia: \n
         *  -- Atualiza a SpatialHashmap; \n
         *  -- Percorre a lista de instâncias de objetos executando o método update de cada uma; \n
         *  -- Verifica se uma instância foi destruída e, se for o caso, retira ela da lista e libera memória; \n
         *  -- Se a instância destruída for o objeto principal do mapa, aplica as regras definidas no Editor; \n
         *  -- Executa as habilidades de cada uma das instâncias de objetos no mapa; \n
         *  -- Executa o procedimento global "Sempre"; \n
         *  -- Se um sinal para troca de estado tiver sido enviado, então invoca o método da StateManager para mudança de mapa;
         *
         * @param dt
         */
        int update(int dt);

        /**
         * @brief Renderiza tudo do mapa.
         *
         * @param screen
         */
        void render(Screen *screen);

        ObjectFunctions *objectFunctions; /**< Ponteiro para o ObjectFunctions. */

        GameObject *mainObject; /**< Ponteiro para o objeto principal. */
        SoundManager *soundManager; /**<  */
        PlayerData *playerData; /**<  */
        Music *backgroundMusic; /**< Música de fundo. */
        StateManager *stateManager; /**<  */
        ModalStack *modalManager; /**<  */


        std::list<BackgroundLayer*> backgroundLayers; /**< Fundos do mapa. */
        Interpreter *interpreter; /**< Interpretador dos eventos do mapa. */
        SpatialHashmap *spatialHashmap; /**< SpatialHashmap para otimização de colisões. */

};

#endif /* MAPSTATE_H_ */
