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


#ifndef BACKGROUNDSGRAPHICSSCENE_H
#define BACKGROUNDSGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <vector>
#include <iostream>

#include <stdlib.h>

#include "background.h"
#include "backgroundlayer.h"
#include "gamedata.h"

class Background;
class BgLayer;
class GameData;

/**
 * @brief Cena para armazenar a imagem do fundo e todas as suas camadas.
 *
 * @see Background
 */
class BackgroundsGraphicsScene : public QGraphicsScene
{
public:
    /**
     * @brief Construtor da classe.
     *
     */
    BackgroundsGraphicsScene();

    /**
     * @brief Adiciona um fundo na cena e mostra nela.
     *
     * @param background o fundo a ser adicionado.
     */
    void setBackground(Background *background);
    /**
     * @brief Recarrega o fundo da cena.
     *
     */
    void reloadBackground();

    std::vector<QGraphicsPixmapItem*> pixmapItems; /**< Pixmaps de cada uma das camadas do fundo. */

    Background *background; /**< O fundo na cena. */


};

#endif // BACKGROUNDSGRAPHICSSCENE_H
