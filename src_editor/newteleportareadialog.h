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


#ifndef NEWTELEPORTAREADIALOG_H
#define NEWTELEPORTAREADIALOG_H

#include <QDialog>
#include <vector>
#include <string>
#include <sstream>

#include "gamedata.h"
#include "map.h"
#include "teleportarea.h"
#include "mapeditorcontroller.h"

class GameData;
class Map;
class TeleportArea;
class MapEditorController;

namespace Ui {
    class NewTeleportAreaDialog;
}

/**
 * @brief Janela de edição de área de teletransporte.
 *
 */
class NewTeleportAreaDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Janela de nova área de teletransporte.
     *
     * @param mapEditorController Controladora do editor de mapas, para operações na camada de negócio.
     * @param parent
     */
    explicit NewTeleportAreaDialog(MapEditorController *mapEditorController, QWidget *parent = 0);
    /**
     * @brief Janela de nova área de teletransporte.
     *
     * @param mapEditorController Controladora do editor de mapas, para operações na camada de negócio.
     * @param teleportArea Área de teletransporte a ser editada.
     * @param parent
     */
    explicit NewTeleportAreaDialog(MapEditorController *mapEditorController, TeleportArea *teleportArea, QWidget *parent = 0);

    /**
     * @brief
     *
     */
    ~NewTeleportAreaDialog();

    /**
     * @brief Popula combo do mapa.
     *
     */
    void populaComboMapa();

    /**
     * @brief Popula combo dos mapas (percorre a árvore).
     *
     * @param mapList
     * @param prefix
     */
    void populaComboMapaPercorreArvore(std::vector<Map*> *mapList, std::string prefix);

    /**
     * @brief Executa a jenela e retorna um TeleportArea. Se for cancelada, retorna NULL.
     *
     */
    TeleportArea* exec();

private:
    Ui::NewTeleportAreaDialog *ui; /**<  */
    TeleportArea *teleportArea; /**<  */
    MapEditorController *mapEditorController; /**<  */
};

#endif // NEWTELEPORTAREADIALOG_H
