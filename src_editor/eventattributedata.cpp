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



#include "eventattributedata.h"



EventAttributeData::EventAttributeData(std::string name, std::list<int> *conditions, std::list<int> *actions)
{
    this->name = name;
    this->conditions = conditions;
    this->actions = actions;

    type = 0;
    showNumberValueCombo = true;
    showVariableValueCombo = true;
    showObjectFieldCombo = true;
    specialComboType = 0;
    showDirectionInput = true;
    showObject02 = 0;

    std::cout << "Sizes: " << sizeof(id) + sizeof(name) + sizeof(conditions) + sizeof(actions) + sizeof(type) + sizeof(showNumberValueCombo) + sizeof(showVariableValueCombo) + sizeof(showObjectFieldCombo) + sizeof(showDirectionInput) + sizeof(showObject02) + sizeof(specialComboType) << std::endl;
    std::cout << "Sizeofint: " << sizeof(int) << std::endl;
    std::cout << "Sizeofbool: " << sizeof(bool) << std::endl;

}

EventAttributeData::EventAttributeData() {

}

bool EventAttributeData::isObjectType() {
    return !showNumberValueCombo && !showVariableValueCombo && !showObjectFieldCombo && !showDirectionInput && showObject02;
}

bool EventAttributeData::isNothingType() {
    return !showNumberValueCombo && !showVariableValueCombo && !showObjectFieldCombo && !showDirectionInput && !showObject02;
}

bool EventAttributeData::showValueGroup() {
    return showNumberValueCombo || showVariableValueCombo || showObjectFieldCombo || showDirectionInput || specialComboType != 0;
}
