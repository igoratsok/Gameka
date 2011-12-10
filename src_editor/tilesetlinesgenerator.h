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


#ifndef TILESETLINESGENERATOR_H
#define TILESETLINESGENERATOR_H

#include <QGraphicsLineItem>
#include <QGraphicsScene>

/**
 * @brief Gerador de linhas para Tileset.
 * Essas linhas irão separar visualmente seus Tiles uns dos outros.
 *
 */
class TilesetLinesGenerator
{
public:
    /**
     * @brief Construtor.
     *
     * @param scene Cena onde serão colocadas as linhas.
     * @param size Tamanho de cada bloco.
     * @param width Largura em número de blocos.
     * @param height Altura em número de blocos.
     * @param penStyle Estilo da linha.
     */
    TilesetLinesGenerator(QGraphicsScene *scene, int size, int width, int height, Qt::PenStyle penStyle);

    /**
     * @brief Adiciona as linhas na cena especificada no construtor.
     *
     */
    void addLinesToScene();

    QGraphicsLineItem **lines; /**< Linhas */
    QGraphicsScene *scene; /**< A cena na qual as linhas serão colocadas. */

    int width, height; /**< Largura e altura em número de blocos. */
};

#endif // TILESETLINESGENERATOR_H
