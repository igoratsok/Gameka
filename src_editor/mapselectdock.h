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


#ifndef MAPSELECTDOCK_H
#define MAPSELECTDOCK_H

#include <QObject>
#include <QDockWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringListModel>
#include <QPushButton>

#include <vector>

#include <stdio.h>
#include <stdlib.h>

#include "mapeditorcontroller.h"
#include "gamedata.h"
#include "map.h"

class MapEditorController;
class GameData;
class Map;


/**
 * @brief Dock do seletor de mapas.
 *
 */
class MapSelectDock : public QDockWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param parent
     * @param mapEditorController controladora do editor de mapas.
     */
    MapSelectDock(QWidget *parent, MapEditorController *mapEditorController);

    MapEditorController *mapEditorController; /**<  */

    QTreeView *treeView; /**<  */
    QTreeWidget *treeWidget; /**<  */
    QVBoxLayout *vboxLayout; /**<  */
    QHBoxLayout *hboxLayout; /**<  */
    QStringListModel *model; /**<  */

    QPushButton *botaoCriaMapa, *botaoEditaMapa, *botaoDeletaMapa, *botaoCriaPasta; /**<  */

    QWidget *widget; /**<  */

    /**
     * @brief Inicializa a cena.
     *
     */
    void initMapSelectScene();

    /**
     * @brief Popula a árvore de mapas.
     *
     */
    void populaArvore();
    /**
     * @brief Obtém o mapa que estiver selecionado.
     *
     */
    Map* getMapaSelecionado();



private:
    /**
     * @brief Popula as subpastas dos mapas.
     *
     * @param subarvore listas dos mapas da subpasta
     * @param item
     */
    void populaSubpastas(std::vector<Map*> *subarvore, QTreeWidgetItem* item);

private slots:
    /**
     * @brief
     *
     */
    void botaoCriaMapaClicked();
    /**
     * @brief
     *
     */
    void botaoCriaPastaClicked();
    /**
     * @brief
     *
     */
    void botaoEditaMapaClicked();
    /**
     * @brief
     *
     * @param
     * @param int
     */
    void treeWidgetItemClicked(QTreeWidgetItem*,int);

};

#endif // MAPSELECTDOCK_H
