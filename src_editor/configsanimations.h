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


#ifndef CONFIGSANIMATIONS_H
#define CONFIGSANIMATIONS_H

#include <QWidget>

#include "gamedata.h"
#include "optionscontroller.h"
#include "animationdata.h"
#include "configsimportdialog.h"
#include "animationgraphicsscene.h"
#include "imagecolorpicker.h"
#include "messageboxes.h"

class GameData;
class OptionsController;
class AnimationData;
class ConfigsImportDialog;
class AnimationGraphicsScene;
class ImageColorPicker;
class MessageBoxes;

namespace Ui {
    class ConfigsAnimations;
}

/**
 * @brief Aba de configurações de animações.
 *
 */
class ConfigsAnimations : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param parent
     */
    explicit ConfigsAnimations(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsAnimations();

    /**
     * @brief Popula a lista de animações da tela.
     *
     */
    void populaListaAnimation();
    /**
     * @brief Popula os campos da tela.
     *
     */
    void populaCampos();

    /**
     * @brief Determina a controladora de opções para operações com a camada de negócio.
     *
     * @param optionsController
     */
    void setOptionsController(OptionsController *optionsController);
    /**
     * @brief Seleciona o último item da lista.
     *
     */
    void selectLastItem();


private:
    Ui::ConfigsAnimations *ui; /**<  */
    OptionsController *optionsController; /**<  */
    AnimationData* currentAnimationData; /**<  */
    AnimationGraphicsScene *animationsGraphicsScene; /**< */

    bool ativaMudancas; /**< Mecanismo para controlar mudanças de valores. */

private slots:
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxLinhaFinal_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxColunaFinal_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxLinhaInicial_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxColunaInicial_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboBoxOrder_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxFrameLoop_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBox_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param value
     */
    void on_horizontalSliderVelocity_valueChanged(int value);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxVerticalSpacing_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxHorizontalSpacing_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxVerticalFrameNumber_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxHorizontalFramesNumber_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param current
     * @param previous
     */
    void on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    /**
     * @brief Evento ativado ao apertar o botão "Adicionar Animação".
     * Vai abrir o importador de animações.
     *
     * @see ConfigsImportDialog
     */
    void on_pushButtonAddAnimation_clicked();
    void on_toolButtonColorkey_pressed();
    void on_toolButtonColorkeyX_pressed();
    void on_removeButton_pressed();
};

#endif // CONFIGSANIMATIONS_H





