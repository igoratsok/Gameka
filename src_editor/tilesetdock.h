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


#ifndef TILESETDOCK_H
#define TILESETDOCK_H


#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QTabWidget>
#include <QSlider>

#include <vector>
#include <sstream>

#include "tilesetview.h"
#include "tilesetscene.h"
#include "mapeditorcontroller.h"
#include "gamedata.h"
#include "tileset.h"

class MapEditorController;
class TilesetScene;
class GameData;
class TileSet;

/**
 * @brief Dock de Tilesets, apresentada na tela principal do programa.
 * Utilizada no módulo de edição de mapas.
 *
 */
class TilesetDock : public QDockWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param parent
     * @param mapEditorController a controladora de edição de mapas, para acesso a camada de negócio.
     */
    TilesetDock(QWidget *parent, MapEditorController *mapEditorController);

    /**
     * @brief Chama o método homônimo da MapEditorController. Verificar documentação lá.
     *
     * @param iTile
     * @param jTile
     * @param diTile
     * @param djTile
     */
    void setDrawTile(int iTile, int jTile, int diTile, int djTile);
    /**
     * @brief Determina o modo do editor.
     *
     * @param mode
     */
    void setEditorMode(int mode);
    /**
     * @brief Inicia a cena.
     *
     */
    void initTileSetScene();

    QTabWidget *tabWidget; /**< TODO */
    QWidget *widget; /**< TODO */
    QSlider *layerSlider; /**< Slider de layers. Desativado no momento. */
    QLabel *layerNumberLabel; /**< Numeração de layers. Desativado no momento. */

    QWidget *layerButtons; /**< Widget com o botão dos layers. */
    QPushButton *layerButton1; /**< Botão 01. */
    QPushButton *layerButton2; /**< Botão 02. */
    QPushButton *layerButton3; /**< Botão 03. */
    QPushButton *layerButton4; /**< Botão 04. */
    QPushButton *layerButton5; /**< Botão 05. */

    /**
     * @brief Obtém o Tileset selecionado.
     *
     */
    TileSet* getSelectedTileset();

private:
    MapEditorController *mapEditorController; /**< */
    TilesetView *tilesetView; /**<  */
    TilesetScene *tilesetScene; /**<  */
    QVBoxLayout *layout; /**<  */

    /**
     * @brief Marca o botão do layer adequdamente.
     *
     * @param number
     */
    void checkLayerButton(int number);
    bool buttonsChangable; /**< TODO */

private slots:
    /**
     * @brief
     *
     * @param valor
     */
    void layerSliderMudada(int valor);

    /**
     * @brief
     *
     * @param value
     */
    void layerButton1_toggled(bool value);
    /**
     * @brief
     *
     * @param value
     */
    void layerButton2_toggled(bool value);
    /**
     * @brief
     *
     * @param value
     */
    void layerButton3_toggled(bool value);
    /**
     * @brief
     *
     * @param value
     */
    void layerButton4_toggled(bool value);
    /**
     * @brief
     *
     * @param value
     */
    void layerButton5_toggled(bool value);
};

#endif // TILESETDOCK_H
