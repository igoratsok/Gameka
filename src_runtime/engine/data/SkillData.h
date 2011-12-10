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

#ifndef SKILLDATA_H_
#define SKILLDATA_H_

#include <stdlib.h>

#include <string>

#include "GameObjectClass.h"
#include "SoundManager.h"
#include "DialogueData.h"

class GameObjectClass;
class SoundManager;
class DialogueData;

/**
 * @brief Entidade para guardar dados de uma habilidade.
 *
 */
class SkillData {
public:
    /**
     * @brief Construtor.
     *
     */
    SkillData();
    virtual ~SkillData();

    int id; /**< Identificador da SkillData. */
    int nroSkill; /**< Número da habilidade que ela representa. */

    GameObjectClass *skillObject; /**< Objeto envolvido na habilidade. (exemplo: objeto que ele atira) */
    GameObjectClass *skillProvider; /**< Item que dá a habilidade ao objeto. */

    int level; /**< Nível. */
    int intensity; /**< Intensidade. */
    int magicCost; /**< Custo de magia. */
    bool isMagical; /**< Se é mágico. Influencia no dano (usa inteligência ao invés de força) */

    std::string sound; /**< Arquivo de som da habilidade. */

    /**
     * @brief Toca o som especial da habilidade.
     *
     */
    void playSound();

    static std::vector<DialogueData*> *getSkillMessages();

    static const int THROW_OBJECT = 0;
    static const int THROW_OBJECT_MOUSE = 1;
    static const int THROW_SWORD = 2;
    static const int JUMP = 3;
    static const int DOUBLE_JUMP = 4;
    static const int SPRINT = 5;
    static const int WALL_KICK = 6;
    static const int GLIDE = 7;
    static const int FLY = 8;


private:
    static std::vector<DialogueData*> *skillMessages;
};

#endif /* SKILLDATA_H_ */
