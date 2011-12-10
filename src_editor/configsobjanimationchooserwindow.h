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


#ifndef CONFIGSOBJANIMATIONCHOOSERWINDOW_H
#define CONFIGSOBJANIMATIONCHOOSERWINDOW_H

#include <QDialog>

#include <vector>
#include <string>

#include "optionscontroller.h"
#include "gameobject.h"
#include "gamedata.h"
#include "gameobjectanimation.h"
#include "configsimportdialog.h"
#include "animationgraphicsscene.h"
#include "messageboxes.h"
#include "imagecolorpickerscene.h"

class OptionsController;
class GameObject;
class GameData;
class GameObjectAnimation;
class ConfigsImportDialog;
class AnimationGraphicsScene;
class MessageBoxes;
class ImageColorPickerScene;

namespace Ui {
    class ConfigsObjAnimationChooserWindow;
}

/**
 * @brief Janela para escolha da animação de um objeto.
 *
 */
class ConfigsObjAnimationChooserWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param optionsController a controladora de opções.
     * @param gameObject o objeto cuja animação será escolhida.
     * @param currentListItem o item da lista correspondente ao objeto
     * @param parent
     */
    explicit ConfigsObjAnimationChooserWindow(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsObjAnimationChooserWindow();

    /**
     * @brief Popula a lista de estados.
     *
     */
    void populaListaEstados();
    /**

     * @brief Popula a lista de animações.
     *
     */
    void populaListaAnimacoes();

    /**
     * @brief Copia as animações do GameObject, para serem editadas.
     *
     */
    void copyGameObjectAnimation();
    /**
     * @brief Preenche campos da direção atual.
     *
     */
    void preencheCamposCurrentDirection();
    /**
     * @brief Mostra a animação selecionada na view.
     *
     */
    void mostraAnimacaoVisualizacao();
    /**
     * @brief Mostra o sprite selecionado na view.
     *
     */
    void mostraSpriteVisualizacao();
    /**
     * @brief Atualiza a visualização.
     *
     */
    void atualizaVisualizacao();

    /**
     * @brief Verifica se o estado "Parado" tem animação. É importante porque,
     * ao aceitar no final a animação, é necessário que ao menos tenha uma direção
     * preenchida no estado "Parado".
     *
     */
    bool verificaSeParadoTemAnimacao();


    /**
     * @brief Corrige dados de armazenamento, caso uma aba tenha sido escolhida mas existem dados
     * preenchidos na outra aba.
     *
     */
    void corrigeDadosArmazenamento();

    /**
     * @brief Limpa os dados antigos correspondentes às cópias das animações,
     * feitas para se poder escolher "cancelar" e não atualizá-las.
     *
     */
    void limpaDadosAntigos();

private:
    Ui::ConfigsObjAnimationChooserWindow *ui; /**< */
    OptionsController *optionsController; /**< */
    GameObject *gameObject; /**< O objeto cuja animação está sendo editada. */
    QListWidgetItem *currentListItem; /**<  */

    std::vector<GameObjectAnimation*> *gameObjectAnimations; /**< Cópia das animações sendo editadas. */

    GameObjectAnimation *currentGameObjectAnimation; /**<  */
    AnimationGraphicsScene *animationGraphicsScene; /**<  */

    /**
     * @brief Converte o valor da widget dial para um valor de direção
     * adequadamente, de acordo com a sua precisão.
     *
     */
    int getDialConvertedValue();




private slots:
    /**
     * @brief
     *
     * @param int
     */
    void on_spinBoxAdjustY2_valueChanged(int );
    /**
     * @brief
     *
     * @param int
     */
    void on_spinBoxAdjustX2_valueChanged(int );
    /**
     * @brief
     *
     * @param int
     */
    void on_spinBoxAdjustY_valueChanged(int );
    /**
     * @brief
     *
     * @param int
     */
    void on_spinBoxAdjustX_valueChanged(int );
    /**
     * @brief
     *
     */
    void on_buttonBox_accepted();
    /**
     * @brief
     *
     * @param current
     * @param previous
     */
    void on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    /**
     * @brief
     *
     */
    void on_pushButtonSpriteChooser_pressed();
    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxInvertVertically2_toggled(bool checked);
    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxInvertHorizontal2_toggled(bool checked);
    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxInvertVertical_toggled(bool checked);
    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxInvertHorizontal_toggled(bool checked);
    /**
     * @brief
     *
     * @param index
     */
    void on_tabWidgetSpriteAnim_currentChanged(int index);
    /**
     * @brief
     *
     * @param current
     * @param previous
     */
    void on_listWidgetEstados_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    /**
     * @brief
     *
     * @param value
     */
    void on_dial_valueChanged(int value);
    /**
     * @brief
     *
     * @param value
     */
    void on_horizontalSliderDirectionNumber_valueChanged(int value);
    void on_toolButtonColorkey_pressed();
    void on_toolButton_pressed();
};

#endif // CONFIGSOBJANIMATIONCHOOSERWINDOW_H

