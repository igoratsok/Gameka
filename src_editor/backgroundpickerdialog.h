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


#ifndef BACKGROUNDPICKERDIALOG_H
#define BACKGROUNDPICKERDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QAbstractButton>
#include <QDialogButtonBox>

#include <iostream>

#include "gamedata.h"
#include "background.h"
#include "backgroundsgraphicsscene.h"

class GameData;
class Background;
class BackgroundsGraphicsScene;

namespace Ui {
    class BackgroundPickerDialog;
}

/**
 * @brief Tela para escolher fundos. Ela aparece na tela de novo mapa. Retorna um objeto
 * da classe Background em seu método exec().
 *
 * @see Background
 */
class BackgroundPickerDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor recebe o mapEditorController para chamadas na camada de negócio.
     *
     * @param mapEditorController  A controladora do editor de mapas.
     * @param parent
     */
    explicit BackgroundPickerDialog(MapEditorController *mapEditorController, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~BackgroundPickerDialog();

    /**
     * @brief Popula a lista de fundos da tela.
     *
     */
    void populaListaFundos();
    /**
     * @brief Executa a janela e retorna o fundo escolhido. Se tiver sido cancelada, retorna NULL.
     *
     */
    Background* exec();

private:
    Ui::BackgroundPickerDialog *ui; /**<  */
    BackgroundsGraphicsScene *backgroundGraphicsScene; /**< */

    Background *chosenBackground; /**< Fundo escolhido. */
    MapEditorController *mapEditorController; /**< A controladora do editor de mapas. */


private slots:
    /**
     * @brief
     *
     * @param button
     */
    void on_buttonBox_clicked(QAbstractButton* button);
    /**
     * @brief Evento ativado caso a janela seja rejeitada.
     *
     */
    void on_buttonBox_rejected();
    /**
     * @brief Evento ativado caso a janela seja aceita..
     *
     */
    void on_buttonBox_accepted();
    /**
     * @brief Evento ativado para o caso em que um item da lista é escolhido.
     *
     * @param current
     * @param previous
     */
    void on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
};

#endif // BACKGROUNDPICKERDIALOG_H
