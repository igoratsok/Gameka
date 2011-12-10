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


#ifndef CONFIGSTILESETWIDGET_H
#define CONFIGSTILESETWIDGET_H

#include <stdio.h>
#include <stdlib.h>

#include <QWidget>
#include <QColor>

#include <vector>
#include <QListWidgetItem>

#include "tileset.h"

#include "configsimportdialog.h"
#include "optionscontroller.h"

#include "tilesetcolmapscene.h"
#include "imagecolorpicker.h"

#include "messageboxes.h"

class ConfigsImportDialog;
class OptionsController;
class TileSet;
class TilesetColMapScene;
class ImageColorPicker;
class MessageBoxes;

namespace Ui {
    class ConfigsTilesetWidget;
}

/**
 * @brief Aba de configurações de Tilesets.
 *
 * @see Tileset
 */
class ConfigsTilesetWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param parnt
     */
    ConfigsTilesetWidget(QWidget *parnt = 0);
    /**
     * @brief
     *
     */
    ~ConfigsTilesetWidget();

    void disableAll();

    /**
     * @brief Fornece a controladora de opções para operações na camada de negócio.
     *
     * @param optionsController a controladora de opções
     */
    void setOptionsController(OptionsController *optionsController);

    /**
     * @brief Popula a lista de Tilesets.
     *
     */
    void populaLista();
    /**
     * @brief Seleciona o último Tileset da lista. Utilizado ao importar um novo Tileset.
     *
     */
    void selectLastTileset();

protected:
    /**
     * @brief
     *
     * @param e
     */
    void changeEvent(QEvent *e);

private:
    Ui::ConfigsTilesetWidget *ui; /**<  */
    OptionsController *optionsController; /**<  */

    TilesetColMapScene *tilesetColMapScene; /**< A cena para mostrar o mapa de colisão do Tileset. */


private slots:
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBox_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param QString
     */
    void on_lineEdit_textChanged(QString );
    /**
     * @brief
     *
     * @param current
     * @param previous
     */
    void on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    /**
     * @brief
     *
     */
    void on_pushButton_clicked();

    /**
     * @brief Evento ao pressionar o botão de "Inverter". Inverte todos os valores do mapa
     * de colisão.
     *
     */
    void on_pushButtonInvert_pressed();

    /**
     * @brief Evento ao pressionar o botão de "Marcar todos com X". Marca todos os valores do mapa
     * de colisão com X.
     *
     */
    void on_pushButtonAllX_pressed();

    /**
     * @brief Evento ao pressionar o botão de "Marcar todos com O". Marca todos os valores do mapa
     * de colisão com O.
     *
     */
    void on_pushButtonAllO_pressed();

    /**
     * @brief
     *
     */
    void on_pushButtonUpdateSizeValue_pressed();
    void on_pushButtonTransparentColor_pressed();
    void on_toolButton_pressed();
    void on_removeTilesetButton_pressed();
};

#endif // CONFIGSTILESETWIDGET_H



