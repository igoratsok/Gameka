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


#ifndef EVENTATTRIBUTEDATA_H
#define EVENTATTRIBUTEDATA_H


#include <iostream>

#include <string>
#include <list>

/**
 * @brief Dados sobre um atributo de um objeto. Vários desses objetos são criados e
 * são utilizados para saber como é o comportamento do atributo, quais combos ativar,
 * quais as condições e ações que a ele pertencem.
 * A lista contendo eles é criada em EventComboDataProvider.
 *
 * @see EventComboDataProvider
 */
class EventAttributeData
{
public:
    /**
     * @brief Construtor.
     *
     * @param name Nome do atributo.
     * @param conditions Lista de condições do atributo.
     * @param actions Lista de ações do atributo.
     */
    EventAttributeData(std::string name, std::list<int> *conditions, std::list<int> *actions);
    /**
     * @brief
     *
     */
    EventAttributeData();


    std::list<int> *conditions; /**< Lista de condições do atributo. */
    std::list<int> *actions; /**< Lista de ações do atributo. */

    int id; /**< Número identificador do atributo. */
    std::string name; /**< Nome do atributo. */

    int type; /**< Tipo do atributo (ver constantes TYPE_X */
    int specialComboType; /**< Tipo especial (teclado, som, música, etc) */
    int test1; /**< Dummy (usado para testes) */
    int test2; /**< Dummy (usado para testes) */
    int test3; /**< Dummy (usado para testes) */
    bool showNumberValueCombo; /**< Mostra valor de número. */
    bool showVariableValueCombo; /**< Mostra valor de variáveis. */
    bool showObjectFieldCombo; /**< Mostra valor de campo de objeto 02. */
    bool showDirectionInput; /**< Mostra valor de direção. */
    bool showObject02; /**< Mostra lista de objeto 02. */
    bool dummy; /**< Dummy. (usado para testes) */




    /**
     * @brief Se é do tipo "valor de apenas objeto"
     *
     */
    bool isObjectType();
    /**
     * @brief Se é do tipo "Nenhum valor".
     *
     */
    bool isNothingType();
    /**
     * @brief Se mostra valor do grupo.
     *
     */
    bool showValueGroup();


    static const int COMBO_TYPE_NONE            = 0; /**<  */
    static const int COMBO_TYPE_KEY             = 4; /**<  */
    static const int COMBO_TYPE_MOUSE           = 5; /**<  */
    static const int COMBO_TYPE_MUSIC           = 6; /**<  */
    static const int COMBO_TYPE_SOUND           = 7; /**<  */
    static const int COMBO_TYPE_MAP             = 8; /**< */
    static const int COMBO_TYPE_PROCEDURE             = 9; /**<  */

};

#endif // EVENTATTRIBUTEDATA_H
