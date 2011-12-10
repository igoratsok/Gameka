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


#ifndef IMAGECOLORPICKERSCENE_H
#define IMAGECOLORPICKERSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QRgb>
#include <QColor>

#include "imagecolorpicker.h"

class ImageColorPicker;

/**
 * @brief Cena para obter uma cor de uma imagem.
 * É usada na ImageColorPicker.
 */
class ImageColorPickerScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param image A imagem
     * @param parent A instância da ImageColorPicker
     */
    explicit ImageColorPickerScene(QPixmap image, QObject *parent = 0);

    /**
     * @brief
     *
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief
     *
     * @param event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief
     *
     * @param event
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QImage qimage; /**< TODO */
    ImageColorPicker *imageColorPicker; /**< TODO */
    bool mousePressed; /**< TODO */

signals:

public slots:


};

#endif // IMAGECOLORPICKERSCENE_H
