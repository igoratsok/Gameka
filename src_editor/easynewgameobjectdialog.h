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


#ifndef EASYNEWGAMEOBJECTDIALOG_H
#define EASYNEWGAMEOBJECTDIALOG_H

#include <QDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "gameobject.h"
#include "gamedata.h"
#include "messageboxes.h"
#include "configsobjanimationchooserwindow.h"
#include "optionscontroller.h"

class GameObject;
class GameData;
class MessageBoxes;
class ConfigsObjAnimationChooserWindow;
class OptionsController;

namespace Ui {
    class EasyNewGameObjectDialog;
}

/**
 * @brief Janela para criação simplificada de um objeto.
 *
 */
class EasyNewGameObjectDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param optionsController a controladora de opções.
     * @param parent
     */
    explicit EasyNewGameObjectDialog(OptionsController *optionsController, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~EasyNewGameObjectDialog();

    /**
     * @brief Popula as combos de objetos.
     *
     */
    void populaCombosObjetos();
    /**
     * @brief Habilita adequadamente as check boxes das habilidades
     * de acordo com o tipo de objeto escolhido.
     *
     */
    void habilitaCheckBoxes();

    /**
     * @brief Preenche as combos de estilos de movimento.
     *
     */
    void preencheComboMovementStyle();


    /**
     * @brief Executa a janela.
     *
     * @return GameObject \n
                    - Instância do GameObject criado, se pressionar OK.
                    - NULL, se a janela for cancelada.
     */
    GameObject* exec();


private slots:
    /**
     * @brief
     *
     * @param index
     */
    void on_comboBoxType_currentIndexChanged(int index);

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

    /**
     * @brief
     *
     */
    void on_pushButtonEditGraphics_pressed();

private:
    Ui::EasyNewGameObjectDialog *ui; /**<  */


    GameObject *gameObject; /**<  */
    QGraphicsPixmapItem *item; /**<  */
    QGraphicsScene *scene; /**<  */
    OptionsController *optionsController; /**<  */


    static const int MOVEMENT_SSLOW = 0; /**< Velocidade de movimento: super lento. */
    static const int MOVEMENT_SLOW = 1; /**< Velocidade de movimento: lento */
    static const int MOVEMENT_FAST = 2; /**< Velocidade de movimento: rápido */
    static const int MOVEMENT_FFAST = 3; /**< Velocidade de movimento: bem rápido */
    static const int MOVEMENT_SFAST = 4; /**< Velocidade de movimento: super rápido */
};

#endif // EASYNEWGAMEOBJECTDIALOG_H
