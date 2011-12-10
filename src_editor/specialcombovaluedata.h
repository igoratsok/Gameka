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


#ifndef SPECIALCOMBOVALUEDATA_H
#define SPECIALCOMBOVALUEDATA_H

#include <string>

/**
 * @brief Strings para popular as combos especiais de valores na tela de novo evento.
 * A tela de novo evento tem um tipo de valor dentro de uma "Combo especial". Essa combo
 * é preenchida com os mais diversos tipos de valores, como teclas, botões do mouse, músicas e etc.
 * Esta classe é utilizada para armazenar pares de strings e códigos que representam os valores
 * que podem ser usados nessa combo.
 *
 */
class SpecialComboValueData
{
public:
    /**
     * @brief Construtor.
     *
     */
    SpecialComboValueData();

    int code; /**< O código representativo do valor. */
    std::string string; /**< A string representativa do valor. */
};

#endif // SPECIALCOMBOVALUEDATA_H
