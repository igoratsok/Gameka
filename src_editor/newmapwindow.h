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


#ifndef NEWMAPWINDOW_H
#define NEWMAPWINDOW_H

#include <QDialog>

#include "map.h"
#include "mapeditorcontroller.h"
#include "messageboxes.h"

class Map;
class MapEditorController;
class MessageBoxes;

namespace Ui {
    class NewMapWindow;
}

/**
 * @brief Janela de novo mapa.
 *
 */
class NewMapWindow : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param mapEditorController Controladora de editor de mapas para comunicação com a camada de negócio.
     * @param map Mapa sendo editado (pode ser NULL, assim é um novo mapa).
     * @param parent
     */
    NewMapWindow(MapEditorController *mapEditorController, Map *map = NULL, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~NewMapWindow();

    Map *map; /**< Mapa sendo editado. */


protected:
    /**
     * @brief
     *
     * @param e
     */
    void changeEvent(QEvent *e);

private:
    Ui::NewMapWindow *ui; /**<  */
    MapEditorController *mapEditorController; /**<  */

    int mode; /**< Modo de mapa: \n
                    0 (MODE_NEW): novo mapa;
                    1 (MODE_EDIT): editar mapa */

    const static int MODE_NEW = 0; /**<  */
    const static int MODE_EDIT = 1; /**<  */

private slots:
    /**
     * @brief
     *
     */
    void on_buttonBox_2_accepted();
    /**
     * @brief
     *
     */
    void on_buttonBox_2_rejected();
};

#endif // NEWMAPWINDOW_H

