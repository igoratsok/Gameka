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

#ifndef VARIABLEDATA_H
#define VARIABLEDATA_H

#include <string>

/**
 * @brief Entidade para armazenar dados de uma variável de jogo.
 *
 */
class VariableData
{
public:
    /**
     * @brief Construtor.
     *
     */
    VariableData();
    virtual ~VariableData();

    int id; /**< Número identificador da variável. */
    std::string name; /**< Nome da variável. */
    int type; /**< Tipo: \n
                        - 0 (TYPE_NUMBER): número;
                        - 1 (TYPE_FLAG): booleano */
    float value; /**< Valor inicial da variável */


    static const int TYPE_NUMBER = 0; /**< Tipo número. */
    static const int TYPE_FLAG = 1; /**< Tipo booleano. */
protected:
private:
};

#endif // VARIABLEDATA_H
