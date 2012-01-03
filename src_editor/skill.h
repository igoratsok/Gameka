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


#ifndef SKILL_H
#define SKILL_H

#include <QApplication>
#include <string>
#include <vector>

#include <stdarg.h>

#include "gameobject.h"

class GameObject;

/**
 * @brief Representação de uma habilidade. O importante nessa classe é que ela contém
 * o número identificador da habilidade e outros dados para uso na interface.
 *
 *
 */
class Skill
{
public:
    /**
     * @brief Construtor.
     *
     * @param id Identificador;
     * @param name Nome.
     * @param description Descrição;
     * @param objectTypes Tipos de objetos que podem ter essa habilidade.
     * @param hasObject Se tem um objeto associado.
     * @param hasIntensity Se tem intensidade associada.
     */
    Skill(int id, std::string name, std::string description, std::vector<int> objectTypes, bool hasObject, bool hasIntensity);

    int id; /**< Número identificador: \n
                        - 0: Atirar objeto;
                        - 1: Atirar objeto com clique;
                        - 2: Usar espada;
                        - 3: Pular;
                        - 4: Pulo duplo;
                        - 5: Correr;
                        - 6: Quicar paredes;
                        - 7: Planar;
                        - 8: Voar */
    std::string name; /**< Nome da habilidade. */
    std::string description; /**< Descrição. */
    std::vector<int> objectTypes; /**< Tipos de objetos que podem ter essa habilidade. */

    bool hasObject; /**< Se tem objeto associado. */
    bool hasIntensity; /**< Se é associado a intensidade. */

    /**
     * @brief Se contém um tipo de objeto.
     *
     * @param type
     */
    bool containsObjectType(int type);

    /**
     * @brief Obtém todas as Skills do editor, preenchidas adequadamente para serem
     * usadas na interface de forma a preencher e habilitar os campos adequadamente.
     *
     */
    static std::vector<Skill*>* getEditorSkills();

    static const int SKILL_THROW_OBJECT = 0; /**< Habilidade de atirar objeto. */
    static const int SKILL_THROW_OBJECT_CLICK = 1; /**< Habilidade de atirar objeto clicando. */
    static const int SKILL_USE_SWORD = 2; /**< Habilidade de usar espada. */
    static const int SKILL_JUMP = 3; /**< Habilidade de pular. */
    static const int SKILL_DOUBLE_JUMP = 4; /**< Habilidade de pulo duplo. */
    static const int SKILL_RUN = 5; /**< Habilidade de correr. */
    static const int SKILL_WALL_KICK = 6; /**< Habilidade de quicar paredes. */
    static const int SKILL_GLIDE = 7; /**< Habilidade de planar. */
    static const int SKILL_FLY = 8; /**< Habilidade de voar. */

private:
    /**
     * @brief
     *
     * @param id
     * @param name
     * @param description
     * @param hasObject
     * @param hasIntensity
     * @param objectType...
     */
    static Skill* createSkill(int id, std::string name, std::string description, bool hasObject, bool hasIntensity, int objectType, ...);
};

#endif // SKILL_H
