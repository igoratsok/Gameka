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


#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>

#include "backgroundlayer.h"

class BgLayer;

/**
 * @brief Entidade para guardar os fundos.
 *
 */
class Background
{
public:
    /**
     * @brief Construtor.
     *
     */
    Background();


    int id; /**< Número identificador. */
    std::string name; /**< Nome do fundo. */
    std::vector<BgLayer*> *layerList; /**< Lista de camadas do fundo. */

};

#endif // BACKGROUND_H
