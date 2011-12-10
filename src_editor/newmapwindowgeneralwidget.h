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


#ifndef NEWMAPWINDOWGENERALWIDGET_H
#define NEWMAPWINDOWGENERALWIDGET_H

#include <QWidget>

#include "map.h"
#include "soundpickerdialog.h"
#include "backgroundpickerdialog.h"
#include "gamedata.h"
#include "messageboxes.h"
#include "background.h"
#include "mapeditorcontroller.h"

class Map;
class SoundPickerDialog;
class BackgroundPickerDialog;
class GameData;
class MessageBoxes;
class Background;
class MapEditorController;

namespace Ui {
    class NewMapWindowGeneralWidget;
}

/**
 * @brief Aba geral da janela de novo mapa.
 *
 * @see NewMapWindow
 */
class NewMapWindowGeneralWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param parent
     */
    NewMapWindowGeneralWidget(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~NewMapWindowGeneralWidget();

    /**
     * @brief Obtém o nome do mapa.
     *
     */
    QString getNomeMapa();
    /**
     * @brief Obtém tamanho em largura em número de blocos.
     *
     */
    int getTamanhoWidth();
    /**
     * @brief Obtém tamanho em altura em número de blocos.
     *
     */
    int getTamanhoHeight();

    /**
     * @brief Preenche os dados adequdamente de acordo com o mapa passado, se não for NULL.
     *
     */
    void preencheDados();



    Map *map; /**<  */
    MapEditorController *mapEditorController; /**<  */
protected:
    /**
     * @brief
     *
     * @param e
     */
    void changeEvent(QEvent *e);


private:
    Ui::NewMapWindowGeneralWidget *ui; /**<  */

private slots:
    /**
     * @brief
     *
     */
    void on_toolButtonRemoveSound_pressed();
    /**
     * @brief
     *
     */
    void on_toolButtonRemoveMusic_pressed();
    /**
     * @brief
     *
     */
    void on_toolButtonRemoveBackground_pressed();
    /**
     * @brief
     *
     */
    void on_toolButtonBackgroundChooser_pressed();
    /**
     * @brief
     *
     */
    void on_toolButtonSound_clicked();
    /**
     * @brief
     *
     */
    void on_toolButtonMusic_clicked();
    /**
     * @brief
     *
     */
    void on_pushButtonDialogue_pressed();
};

#endif // NEWMAPWINDOWGENERALWIDGET_H
