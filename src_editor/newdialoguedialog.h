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


#ifndef NEWDIALOGUEDIALOG_H
#define NEWDIALOGUEDIALOG_H

#include <stdlib.h>
#include <QDialog>

#include <sstream>

#include "dialoguedata.h"
#include "gameobject.h"
#include "configsimportdialog.h"
#include "optionscontroller.h"
#include "gamedata.h"
#include "messageboxes.h"

class DialogueData;
class GameObject;
class ConfigsImportDialog;
class OptionsController;
class GameData;
class MessageBoxes;

namespace Ui {
    class NewDialogueDialog;
}

/**
 * @brief Janela de novo diálogo.
 *
 */
class NewDialogueDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param optionsController A controladora de opções, para chamadas na camada de negócio.
     * @param parent
     */
    explicit NewDialogueDialog(OptionsController *optionsController, QWidget *parent = 0);

    /**
     * @brief Construtor.
     *
     * @param optionsController A controladora de opções, para chamadas na camada de negócio.
     * @param gameObject O GameObject a que pertence o diálogo.
     * @param parent
     */
    explicit NewDialogueDialog(OptionsController *optionsController, GameObjectInstance* gameObject, QWidget *parent = 0);
    /**
     * @brief
     *
     * @param optionsController A controladora de opções, para chamadas na camada de negócio.
     * @param dialogueData O DialogueData a ser editado.
     * @param parent
     */
    explicit NewDialogueDialog(OptionsController *optionsController, DialogueData* dialogueData, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~NewDialogueDialog();

    /**
     * @brief Inicia e popula as listas.
     *
     */
    void init();

    /**
     * @brief Cria um novo item de diálogo.
     *
     * @param dialogueItemData
     */
    QListWidgetItem *createNewItem(DialogueItemData *dialogueItemData);

    /**
     * @brief Popula a lista de itens de diálogo.
     *
     */
    void populaListaDialogueItems();

    /**
     * @brief Popula a lista de procedimentos.
     *
     */
    void populaComboProcedures();

    /**
     * @brief Preenche os campos de acordo com o diálogo passado no construtor, se não for NULL.
     *
     */
    void preencheCampos();

    /**
     * @brief Executa a janela e retorna o DialogueData criado. Retorna NULL se tiver cancelado a janela.
     *
     */
    DialogueData* exec();

private slots:
    /**
     * @brief
     *
     * @param current
     * @param previous
     */
    void on_listWidgetItems_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);

    /**
     * @brief
     *
     */
    void on_toolButtonImage_pressed();
    /**
     * @brief
     *
     */
    void on_pushButtonAddMessage_pressed();
    /**
     * @brief
     *
     */
    void on_pushButtonRemoveItem_pressed();

    /**
     * @brief
     *
     */
    void on_textEditMessage_textChanged();

    /**
     * @brief
     *
     */
    void on_pushButtonAddProcedure_pressed();

    /**
     * @brief
     *
     */
    void on_toolButtonRemoveImage_pressed();

    /**
     * @brief
     *
     * @param index
     */
    void on_comboBoxProcedure_currentIndexChanged(int index);

    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBox_toggled(bool checked);

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

private:
    Ui::NewDialogueDialog *ui; /**<  */

    GameObjectInstance *gameObject; /**<  */
    DialogueData *dialogueData; /**<  */
    OptionsController *optionsController; /**<  */
};

#endif // NEWDIALOGUEDIALOG_H
