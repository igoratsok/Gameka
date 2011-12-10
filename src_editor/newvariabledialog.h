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


#ifndef NEWVARIABLEDIALOG_H
#define NEWVARIABLEDIALOG_H

#include <QDialog>

#include "variabledata.h"
#include "messageboxes.h"

class VariableData;
class MessageBoxes;

namespace Ui {
    class NewVariableDialog;
}

/**
 * @brief  Janela para criação de nova variável.
 *
 */
class NewVariableDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param variableData A variável a ser editada. NULL caso queira criar uma nova.
     * @param parent
     */
    explicit NewVariableDialog(VariableData *variableData, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~NewVariableDialog();

    /**
     * @brief Habilita elementos adequadamente.
     *
     */
    void habilitaElementos();
    /**
     * @brief Preenche campos adequadamente.
     *
     */
    void preencheCampos();

    /**
     * @brief Executa a janela e retorna a variável criada/editada. NULL se tiver cancelado.
     *
     */
    VariableData* exec();

private slots:
    /**
     * @brief
     *
     */
    void on_buttonBox_accepted();

    /**
     * @brief
     *
     * @param index
     */
    void on_comboBoxVariableType_currentIndexChanged(int index);

    void on_buttonBox_rejected();

private:
    Ui::NewVariableDialog *ui; /**<  */
    VariableData *variableData; /**<  */
};

#endif // NEWVARIABLEDIALOG_H
