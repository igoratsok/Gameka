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


#ifndef OBJECTSDOCK_H
#define OBJECTSDOCK_H

#include <vector>

#include <QDockWidget>
#include <QCursor>

#include "mapeditorcontroller.h"
#include "gamedata.h"
#include "gameobject.h"
#include "easynewgameobjectdialog.h"

class MapEditorController;
class GameData;
class GameObject;
class EasyNewGameObjectDialog;

namespace Ui {
    class ObjectsDock;
}

/**
 * @brief Dock do Seletor de Objetos.
 *
 */
class ObjectsDock : public QDockWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param mapEditorController Controladora do editor de mapas, para operações na camada de negócio.
     * @param parent
     */
    explicit ObjectsDock(MapEditorController *mapEditorController, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ObjectsDock();

    /**
     * @brief Popula a árvore de objetos.
     *
     */
    void populaArvoreObjetos();

    /**
     * @brief Inicia e habilita o dock.
     *
     */
    void initDock();

    /**
     * @brief Obtém o objeto selecionado. Se não houver nenhum, retorna NULL.
     *
     */
    GameObject* getCurrentObject();

    /**
     * @brief Desseleciona um objeto.
     *
     */
    void unselectObject();

private:
    Ui::ObjectsDock *ui; /**< */
    MapEditorController *mapEditorController; /**<  */

private slots:
    /**
     * @brief
     *
     * @param pos
     */
    void on_treeWidget_customContextMenuRequested(QPoint pos);
    /**
     * @brief
     *
     * @param item
     * @param column
     */
    void on_treeWidget_itemClicked(QTreeWidgetItem* item, int column);
    /**
     * @brief
     *
     */
    void on_pushButtonCreateObject_pressed();
};

#endif // OBJECTSDOCK_H
