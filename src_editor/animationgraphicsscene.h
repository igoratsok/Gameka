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


#ifndef ANIMATIONGRAPHICSSCENE_H
#define ANIMATIONGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QRgb>
#include <QBrush>

#include <iostream>

#include "animationgraphicsitem.h"
#include "animationdata.h"

class AnimationGraphicsItem;
class AnimationData;

/**
 * @brief O "QGraphicsScene" onde irá ser colocado o AnimationGraphicsItem.
 * Ela é utilizada nos diversos painéis da ferramenta onde mostram animações ou
 * sprites.
 *
 * @see AnimationGraphicsItem
 */
class AnimationGraphicsScene : public QGraphicsScene
{
public:
    /**
     * @brief O construtor para o AnimationGraphicsScene.
     *
     * @param graphicsView a view do QGraphicsScene
     */
    AnimationGraphicsScene(QGraphicsView *graphicsView);
    /**
     * @brief
     *
     */
    ~AnimationGraphicsScene();

    AnimationGraphicsItem *animationGraphicsItem; /**< A AnimationGraphicsItem da cena. */
    QGraphicsView *graphicsView; /**< O view da cena. */

    /**
     * @brief Adiciona uma AnimationData na cenas, mostrando uma animação na tela através de uma AnimationGraphicsItem.
     *
     * @param animationData
     *
     * @see AnimationData
     * @see AnimationGraphicsItem
     */
    void addAnimationData(AnimationData *animationData);
    /**
     * @brief Adiciona uma imagem estática na cena
     *
     * @param sprite caminho para a imagem
     */
    void addSpriteData(std::string sprite);
    /**
     * @brief Determina o ponto de ajuste (é uma cruz).
     *
     * @param x posição x
     * @param y posição y
     */
    void setAdjustPoint(int x, int y);
    /**
     * @brief Remove os gráficos da cena
     *
     */
    void removeGraphics();
    int timerId; /**< Uma forma de guardar a id do timer da animação, para depois pará-la. */

    QGraphicsLineItem *crossLine1; /**< Linha na horizontal. */
    QGraphicsLineItem *crossLine2; /**< Linha na vertical. */




protected:
    /**
     * @brief Evento do timer. Executa o doStep da AnimationGraphicsItem.
     *
     * @param
     *
     * @see AnimationGraphicsItem
     */
    void timerEvent(QTimerEvent *);
};

#endif // ANIMATIONGRAPHICSSCENE_H
