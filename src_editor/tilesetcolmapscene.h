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


#ifndef TILESETCOLMAPSCENE_H
#define TILESETCOLMAPSCENE_H

#include <math.h>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsSceneMouseEvent>

#include <QBitmap>

#include <boost/multi_array.hpp>
#include "tilesetlinesgenerator.h"

#include "tileset.h"

class TileSet;
class TilesetLinesGenerator;

/**
 * @brief Cena que mostra o mapa de colisão de um Tileset. Usado na aba
 * de Tilesets.
 *
 */
class TilesetColMapScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param tileset O tileset a ter seu mapa de colisão mostrado.
     * @param parent
     */
    explicit TilesetColMapScene(TileSet *tileset, QObject *parent = 0);


    /**
     * @brief Evento ao se pressionar o botão do mouse. Verifica qual célula
     * foi clicada e inverte o valor do mapa de colisão naquela célula.
     *
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief Inverte todos os valores do mapa de colisão.
     *
     */
    void invert();

    /**
     * @brief Coloca todos os valores como X.
     *
     */
    void allX();
    /**
     * @brief Coloca todos os valores como O.
     *
     */
    void allO();

    QGraphicsPixmapItem *tilesetPixmapItem; /**< O pixmap do Tileset */
    TileSet *tileset; /**< O Tileset que está mostrado o mapa de colisão. */

    boost::multi_array<QGraphicsTextItem*, 2> textArray; /**< Um array contendo cada uma das células
                                        contendo X ou O */

signals:

public slots:

};

#endif // TILESETCOLMAPSCENE_H
