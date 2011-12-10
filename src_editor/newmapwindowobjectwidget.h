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


#ifndef NEWMAPWINDOWOBJECTWIDGET_H
#define NEWMAPWINDOWOBJECTWIDGET_H

#include <stdlib.h>

#include <QWidget>
#include <QListWidgetItem>
#include <vector>


#include "gamedata.h"
#include "gameobject.h"
#include "map.h"

class GameData;
class GameObject;

namespace Ui {
    class NewMapWindowObjectWidget;
}

/**
 * @brief Aba de Objetos da janela de novo mapa. Não é mais utilizada.
 *
 * @see NewMapWindow
 */
class NewMapWindowObjectWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit NewMapWindowObjectWidget(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~NewMapWindowObjectWidget();

    /**
     * @brief
     *
     */
    void populaListaObjetosDisponiveis();
    /**
     * @brief
     *
     */
    void populaListObjetosEscolhidos();
    Map *map; /**< TODO */

private:
    Ui::NewMapWindowObjectWidget *ui; /**< TODO */


private slots:
    /**
     * @brief
     *
     */
    void on_pushButton_clicked();
};

#endif // NEWMAPWINDOWOBJECTWIDGET_H
