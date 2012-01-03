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



#include "skill.h"

Skill::Skill(int id, std::string name, std::string description, std::vector<int> objectTypes, bool hasObject, bool hasIntensity)
    : id(id), name(name), description(description), objectTypes(objectTypes), hasObject(hasObject), hasIntensity(hasIntensity) {
}

std::vector<Skill*>* Skill::getEditorSkills() {
    std::vector<Skill*> *skillList;


    skillList = new std::vector<Skill*>();

    skillList->push_back(createSkill(0, QApplication::tr("Atira objeto").toStdString(), "", true, true, 6,
                GameObject::CAR_MOVEMENT_OBJECT,
                GameObject::EIGHT_MOVEMENT_OBJECT,
                GameObject::FIGHTING_MOVEMENT_OBJECT,
                GameObject::MOUSE_MOVEMENT_OBJECT,
                GameObject::PLATFORM_MOVEMENT_OBJECT,
                GameObject::PONG_BALL_OBJECT));

    skillList->push_back(createSkill(1, QApplication::tr("Atira objeto (clique)").toStdString(), "", true, true, 6,
                GameObject::CAR_MOVEMENT_OBJECT,
                GameObject::EIGHT_MOVEMENT_OBJECT,
                GameObject::FIGHTING_MOVEMENT_OBJECT,
                GameObject::MOUSE_MOVEMENT_OBJECT,
                GameObject::PLATFORM_MOVEMENT_OBJECT,
                GameObject::PONG_BALL_OBJECT));

    skillList->push_back(createSkill(2, QApplication::tr("Usa espada").toStdString(), "", true, false, 6,
                GameObject::CAR_MOVEMENT_OBJECT,
                GameObject::EIGHT_MOVEMENT_OBJECT,
                GameObject::FIGHTING_MOVEMENT_OBJECT,
                GameObject::MOUSE_MOVEMENT_OBJECT,
                GameObject::PLATFORM_MOVEMENT_OBJECT,
                GameObject::PONG_BALL_OBJECT));

    skillList->push_back(createSkill(3, QApplication::tr("Pulo").toStdString(), "", false, true, 2,
                GameObject::CAR_MOVEMENT_OBJECT,
                GameObject::EIGHT_MOVEMENT_OBJECT));

    skillList->push_back(createSkill(4, QApplication::tr("Pulo duplo").toStdString(), "", false, true, 4,
                GameObject::CAR_MOVEMENT_OBJECT,
                GameObject::EIGHT_MOVEMENT_OBJECT,
                GameObject::FIGHTING_MOVEMENT_OBJECT,
                GameObject::PLATFORM_MOVEMENT_OBJECT));

    skillList->push_back(createSkill(5, QApplication::tr("Correr").toStdString(), "", false, true, 6,
                GameObject::CAR_MOVEMENT_OBJECT,
                GameObject::EIGHT_MOVEMENT_OBJECT,
                GameObject::FIGHTING_MOVEMENT_OBJECT,
                GameObject::MOUSE_MOVEMENT_OBJECT,
                GameObject::PLATFORM_MOVEMENT_OBJECT,
                GameObject::PONG_BALL_OBJECT));

    skillList->push_back(createSkill(6, QApplication::tr("Quicar paredes").toStdString(), "", false, true, 1,
                GameObject::PLATFORM_MOVEMENT_OBJECT));

    skillList->push_back(createSkill(7, QApplication::tr("Planar").toStdString(), "", false, true, 4,
                GameObject::CAR_MOVEMENT_OBJECT,
                GameObject::EIGHT_MOVEMENT_OBJECT,
                GameObject::FIGHTING_MOVEMENT_OBJECT,
                GameObject::PLATFORM_MOVEMENT_OBJECT));

    skillList->push_back(createSkill(8, QApplication::tr("Voar").toStdString(), "", false, true, 4,
                GameObject::CAR_MOVEMENT_OBJECT,
                GameObject::EIGHT_MOVEMENT_OBJECT,
                GameObject::FIGHTING_MOVEMENT_OBJECT,
                GameObject::PLATFORM_MOVEMENT_OBJECT));


    return skillList;
}

Skill* Skill::createSkill(int id, std::string name, std::string description, bool hasObject, bool hasIntensity, int count, ...) {
    va_list objectTypeArgs;
    va_start(objectTypeArgs, count);

    std::vector<int> objectTypes;

    for(int i = 0; i < count; i++) {
        int arg = va_arg(objectTypeArgs, int);
        objectTypes.push_back(arg);

    }

    Skill *skill = new Skill(id, name, description, objectTypes, hasObject, hasIntensity);

    return skill;
}

bool Skill::containsObjectType(int type) {
    for(std::vector<int>::iterator it = objectTypes.begin(); it != objectTypes.end(); ++it) {
        int value = *it;

        if(value == type) {
            return true;
        }
    }

    return false;
}
