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

#ifndef GAMEOBJECTINSTANCE_H_
#define GAMEOBJECTINSTANCE_H_

#include "GameObjectClass.h"

#include "DialogueData.h"

class GameObjectClass;
class DialogueData;

/**
 * @brief Entidade para representar uma instância de objeto.
 *
 */
class GameObjectInstance {
public:
    /**
     * @brief Construtor.
     *
     * @param gameObject Classe de objeto a que pertence a instância.
     */
    GameObjectInstance();
    virtual ~GameObjectInstance();

    unsigned int id; /**< Número identificador da instância. */
    GameObjectClass *gameObject; /**< Classe de objeto a que pertence a instância. */

    int x; /**<  Posição X da instância no mapa. */
    int y; /**<  Posição Y da instância no mapa. */

    int nroEventos; /**< Número de eventos (não é utilizado mais). */
    int nroFalas; /**< Número de fatas (não é utilizado mais). */

    /* modificacoes M01 */
    bool isCenter; /**< Se é centro do mapa. */
    bool isMainObject; /**< Se é objeto principal. */

    /* diálogos do NPC */
    DialogueData *dialogueData; /**< Diálogo, caso seja um NPC. */
};

#endif /* GAMEOBJECTINSTANCE_H_ */
