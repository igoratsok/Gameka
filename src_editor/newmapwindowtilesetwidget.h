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


#ifndef NEWMAPWINDOWTILESETWIDGET_H
#define NEWMAPWINDOWTILESETWIDGET_H

#include <QWidget>
#include <vector>

#include "gamedata.h"
#include "tileset.h"
#include "map.h"
#include "mapeditorcontroller.h"
#include "messageboxes.h"

#include "boost/foreach.hpp"

class GameData;
class TileSet;
class Map;
class MapEditorController;
class MessageBoxes;

namespace Ui {
    class NewMapWindowTilesetWidget;
}

/**
 * @brief Aba de Tilesets da janela de novo mapa.
 *
 * @see NewMapWindow
 */
class NewMapWindowTilesetWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param parent
     */
    NewMapWindowTilesetWidget(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~NewMapWindowTilesetWidget();


    /**
     * @brief Popula lista de Tilesets disponíveis a se adicionar.
     *
     */
    void populaListaDisponiveis();
    /**
     * @brief Popula lista de Tilesets que foram escolhidos.
     *
     */
    void populaListaEscolhidos();

    Map *map; /**< Mapa sendo editado. */
    MapEditorController *mapEditorController; /**< Controladora. */

protected:
    /**
     * @brief
     *
     * @param e
     */
    void changeEvent(QEvent *e);

private:
    Ui::NewMapWindowTilesetWidget *ui; /**< TODO */



private slots:
    /**
     * @brief
     *
     */
    void on_pushButton_clicked();
    /**
     * @brief
     *
     */
    void on_pushButton_pressed();
};

#endif // NEWMAPWINDOWTILESETWIDGET_H
