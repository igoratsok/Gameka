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


#ifndef ANIMATIONGRAPHICSITEM_H
#define ANIMATIONGRAPHICSITEM_H

#include <QGraphicsRectItem>
#include <QImage>
#include <QPainter>
#include <QDebug>


#include <string>

#include "gamedata.h"

class GameData;

/**
 * @brief Um "GraphicItem" referente a uma animação. É responsável por
 * desenhar a pré-visualização da animação.
 *
 */
class AnimationGraphicsItem : public QGraphicsRectItem
{
public:
    /**
     * @brief Construtor da classe.
     *
     * @param string arquivo da animação
     * @param horizontalFrameNumber número de quadros na horizontal
     * @param verticalFrameNumber número de quadros na vertical
     * @param order ordem (0 esquerda-direita; 1 cima-baixo)
     * @param startX linha inicial da animação
     * @param startY coluna inicial da animação
     * @param endX linha final da animação
     * @param endY coluna final da animação
     * @param spacingX espaçamento no eixo x
     * @param spacingY espaçamento no eixo y
     */
    AnimationGraphicsItem(std::string string, int horizontalFrameNumber, int verticalFrameNumber, int order,
                          int startX, int startY, int endX, int endY, int spacingX, int spacingY);
    /**
     * @brief Construtor contendo apenas o arquivo da animação
     *
     * @param string nome do arquivo da animação.
     */
    AnimationGraphicsItem(std::string string);

    /**
     * @brief Atualiza o valor do retângulo para a próxima animação.
     *
     */
    void doStep();
private:
    QImage *image; /**< Imagem da animação. */
    QRect animationRect; /**< Retângulo da porção da animação a ser desenhada */

    int stepX, stepY; /**< Altura e largura do quadro */
    int animX, animY; /**< Posição x e y do quadro atual */
    int horizontalFrameNumber, verticalFrameNumber; /**< Número de frames na horizontal e vertical */
    int order; /**< Ordem (0 esquerda-direita; 1 cima-baixo) */
    bool isAnimation; /**< se é uma animação de fato ou é estático */

    int startX, startY, endX, endY; /**< linhas e colunas iniciais e finais */



protected:
    /**
     * @brief Desenha o item na tela.
     *
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ANIMATIONGRAPHICSITEM_H
