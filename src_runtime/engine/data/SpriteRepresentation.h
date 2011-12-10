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

#ifndef SPRITEREPRESENTATION_H_
#define SPRITEREPRESENTATION_H_

#include <string>

/**
 * @brief Classe para representação de uma imagem estática.
 *
 */
class SpriteRepresentation {
public:
    /**
     * @brief Construtor.
     *
     */
    SpriteRepresentation();
    virtual ~SpriteRepresentation();

    int id; /**< Identificador do Sprite. */
    std::string spriteFileName; /**< Nome do arquivo. */
    int direction; /**< Direção (usado na AnimationData) */

    /* dados pendentes de gravacao */
    bool hascolorkey; /**< Se tem colorkey (cor transparente). */
    int r_colorkey; /**< Vermelho da colorkey. */
    int b_colorkey; /**< Azul da colorkey */
    int g_colorkey; /**< Verde da colorkey */

    bool activated; /**< Se está ativado (usado na AnimationData) */
};

#endif /* SPRITEREPRESENTATION_H_ */
