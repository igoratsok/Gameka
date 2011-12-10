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


#ifndef CONFIGSBACKGROUNDS_H
#define CONFIGSBACKGROUNDS_H

#include <QWidget>

#include "optionscontroller.h"
#include "configsimportdialog.h"
#include "backgroundsgraphicsscene.h"
#include "messageboxes.h"


class OptionsController;
class ConfigsImportDialog;
class BackgroundsGraphicsScene;
class MessageBoxes;

namespace Ui {
    class ConfigsBackgrounds;
}

/**
 * @brief Aba de configurações de fundos.
 *
 */
class ConfigsBackgrounds : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param parent
     */
    explicit ConfigsBackgrounds(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsBackgrounds();

    /**
     * @brief Popula lista de fundos.
     *
     * @param firstTime se for a primeira vez ao ativar a aba, então seleciona o primeiro elemento;
     *        caso contrário, seleciona o último elemento da lista.
     */
    void populaListaBackgrounds(bool firstTime);
    /**
     * @brief Popula lista de camadas.
     *
     */
    void populaListaLayers();

    /**
     * @brief Preenche os campos do fundo.
     *
     */
    void preencheCamposBg();
    /**
     * @brief Preenche os campos da camada de acordo com a camada escolhida.
     *
     */
    void preencheCamposLayer();

    /**
     * @brief Determina a controladora de opções para operações com a camada de negócio.
     *
     * @param optionsController
     *
     * @see OptionsController
     */
    void setOptionsController(OptionsController *optionsController);

private:
    Ui::ConfigsBackgrounds *ui; /**<  */
    OptionsController *optionsController; /**< Controladora de opções */
    BackgroundsGraphicsScene *backgroundsGraphicsScene; /**< Cena */

private slots:
    /**
     * @brief Evento ao pressionar o botão de remover camada.
     *
     */
    void on_pushButtonRemoveLayer_pressed();
    /**
     * @brief Evento ao pressionar o botão de adicionar camada.
     *
     */
    void on_pushButtonAddLayer_pressed();
    /**
     * @brief
     *
     */
    void on_pushButtonAddLayer_clicked();
    /**
     * @brief
     *
     * @param item
     */
    void on_listWidgetLayers_itemChanged(QListWidgetItem* item);
    /**
     * @brief Evento ao escolher uma camada.
     *
     * @param int
     */
    void on_spinBoxVy_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxVx_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboBoxBehavior_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxRepeatVer_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxRepeatHor_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxDy_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxDx_valueChanged(int );
    /**
     * @brief Evento ao pressionar o botão de escolha da imagem da camada.
     * Utiliza um ConfigsImportDialog para obter a imagem.
     *
     * @see ConfigsImportDialog
     */
    void on_pushButton_clicked();
    /**
     * @brief Evento ao escolher uma camada da lista.
     *
     * @param current
     * @param previous
     *
     *
     */
    void on_listWidgetLayers_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    /**
     * @brief  Evento de atualização de valor.
     *
     * @param QString
     */
    void on_lineEditName_textChanged(QString );
    /**
     * @brief Evento ao escolher um fundo da lista.
     *
     * @param current
     * @param previous
     */
    void on_listWidgetBgs_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    /**
     * @brief Evento ao pressionar o botão de adicionar fundo.
     *
     */
    void on_pushButtonAddBg_clicked();
    void on_buttonRemoveBg_pressed();
};

#endif // CONFIGSBACKGROUNDS_H
