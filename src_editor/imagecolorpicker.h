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


#ifndef IMAGECOLORPICKER_H
#define IMAGECOLORPICKER_H

#include <stdlib.h>

#include <QDialog>
#include <QPixmap>

#include "imagecolorpickerscene.h"

class ImageColorPickerScene;

namespace Ui {
    class ImageColorPicker;
}

/**
 * @brief Janela para se obter uma cor de uma imagem. Usa um objeto
 * da classe ImageColorPickerScene para mostrar a imagem na tela e
 * obter a cor através do mouse.
 *
 */
class ImageColorPicker : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param imageFilePath O caminho da imagem.
     * @param parent
     */
    explicit ImageColorPicker(QString imageFilePath, QWidget *parent = 0);
    /**
     * @brief Construtor.
     *
     * @param image Imagem
     * @param parent
     */
    explicit ImageColorPicker(QPixmap image, QWidget *parent);
    /**
     * @brief
     *
     */
    ~ImageColorPicker();

    /**
     * @brief Determina uma cor.
     *
     * @param r Intensidade do vermelho (0..255)
     * @param g Intensidade do verde (0..255)
     * @param b Intensidade do azul (0..255)
     */
    void setColor(int r, int g, int b);

    /**
     * @brief Executa a janela e retorna a cor escolhida. NULL se tiver cancelado.
     *
     */
    QColor* exec();


private slots:
    /**
     * @brief
     *
     */
    void on_buttonBox_accepted();

    /**
     * @brief
     *
     */
    void on_buttonBox_rejected();

private:
    Ui::ImageColorPicker *ui; /**<  */

    QPixmap image; /**< */
    QString imageFilePath; /**<  */
    ImageColorPickerScene *imageColorPickerScene; /**<  */
    QColor *color; /**< A cor escolhida. */
};

#endif // IMAGECOLORPICKER_H
