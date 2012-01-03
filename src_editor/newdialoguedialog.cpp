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



#include "newdialoguedialog.h"
#include "ui_newdialoguedialog.h"

NewDialogueDialog::NewDialogueDialog(OptionsController *optionsController, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDialogueDialog),
    optionsController(optionsController),
    dialogueData(new DialogueData()),
    gameObject(NULL)
{
    ui->setupUi(this);
    init();
}

NewDialogueDialog::NewDialogueDialog(OptionsController *optionsController, DialogueData *dialogueData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDialogueDialog),
    optionsController(optionsController),
    dialogueData(dialogueData),
    gameObject(NULL)
{
    ui->setupUi(this);
    init();
}

NewDialogueDialog::NewDialogueDialog(OptionsController *optionsController, GameObjectInstance *gameObject, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDialogueDialog),
    optionsController(optionsController),
    dialogueData(gameObject->dialogueData),
    gameObject(gameObject)
{
    ui->setupUi(this);
    init();

}

NewDialogueDialog::~NewDialogueDialog()
{
    delete ui;
}

void NewDialogueDialog::init() {
    if(dialogueData == NULL) {
        dialogueData = new DialogueData();
    } else {
        dialogueData = new DialogueData(*dialogueData);
    }

    populaListaDialogueItems();
    populaComboProcedures();
}

QListWidgetItem* NewDialogueDialog::createNewItem(DialogueItemData *dialogueItemData) {
    QListWidgetItem *newItem;
    if(dialogueItemData->type == DialogueItemData::TYPE_MESSAGE) {
        std::stringstream ss;
        ss << tr("Mensagem: ").toStdString() << dialogueItemData->message;

        newItem = new QListWidgetItem(QString(ss.str().c_str()));
    } else {
        std::stringstream ss;
        ss << tr("Chama procedimento: ").toStdString();

        if(dialogueItemData->procedureId > 0) {
            GameData *gameData = GameData::getInstance();
            ProcedureData *procedureData = gameData->getProcedureById(dialogueItemData->procedureId);

            if(procedureData != NULL) {
                ss << procedureData->name;
            }
        } else {
            if(gameObject != NULL) {
                ProcedureData *procedureData = gameObject->gameObject->getProcedureById(-dialogueItemData->procedureId);

                if(procedureData != NULL) {
                    ss << "(" << gameObject->gameObject->name << ") " << procedureData->name;
                }
            }
        }


        newItem = new QListWidgetItem(QString(ss.str().c_str()));
    }

    newItem->setData(Qt::UserRole, QVariant::fromValue((void*) dialogueItemData));

    return newItem;
}

void NewDialogueDialog::populaListaDialogueItems() {
    ui->listWidgetItems->clear();

    foreach(DialogueItemData *dialogueItemData, dialogueData->dialogueItems) {
        ui->listWidgetItems->addItem(createNewItem(dialogueItemData));

    }
}

void NewDialogueDialog::populaComboProcedures() {
    ui->comboBoxProcedure->clear();

    GameData *gameData = GameData::getInstance();

    foreach(ProcedureData *procedureData, *gameData->procedureList) {
        ui->comboBoxProcedure->addItem(QString(procedureData->name.c_str()), QVariant(procedureData->id));
    }

    if(gameObject != NULL) {
        foreach(ProcedureData *procedureData, *gameObject->gameObject->procedureList) {
            std::stringstream ss;
            ss << "(" << gameObject->gameObject->name << ") " << procedureData->name;
            ui->comboBoxProcedure->addItem(QString(ss.str().c_str()), QVariant(-procedureData->id));
        }
    }
}

void NewDialogueDialog::preencheCampos() {
    DialogueItemData *dialogueItemData = (DialogueItemData*) ui->listWidgetItems->currentItem()->data(Qt::UserRole).value<void*>();

    if(dialogueItemData->type == DialogueItemData::TYPE_MESSAGE) {
        ui->textEditMessage->setText(QString(dialogueItemData->message.c_str()));
        ui->checkBoxImageCenter->setChecked(dialogueItemData->associatedImageAtCenter);
        ui->lineEditImage->setText(QString(dialogueItemData->associatedImage.c_str()));
    } else {
        for(int i = 0; i < ui->comboBoxProcedure->count(); i++) {
            if(dialogueItemData->procedureId == ui->comboBoxProcedure->itemData(i, Qt::UserRole).toInt()) {
                ui->comboBoxProcedure->setCurrentIndex(i);

                break;
            }
        }


    }


}

DialogueData* NewDialogueDialog::exec() {
    QDialog::exec();





    return dialogueData;
}

void NewDialogueDialog::on_listWidgetItems_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(current != NULL) {
        DialogueItemData *dialogueItemData = (DialogueItemData*) current->data(Qt::UserRole).value<void*>();

        if(dialogueItemData->type == DialogueItemData::TYPE_MESSAGE) {
            ui->textEditMessage->setText(QString(dialogueItemData->message.c_str()));
            ui->textEditMessage->setEnabled(true);
            ui->lineEditImage->setEnabled(true);
            ui->toolButtonImage->setEnabled(true);
            ui->checkBoxImageCenter->setEnabled(true);
            ui->comboBoxProcedure->setEnabled(false);




        } else {

            ui->textEditMessage->setEnabled(false);
            ui->lineEditImage->setEnabled(false);
            ui->toolButtonImage->setEnabled(false);
            ui->checkBoxImageCenter->setEnabled(false);
            ui->comboBoxProcedure->setEnabled(true);

        }

        preencheCampos();
    }

}

void NewDialogueDialog::on_toolButtonImage_pressed()
{
    std::string *returnString;
    ConfigsImportDialog *configsImportDialog = new ConfigsImportDialog(optionsController, ConfigsImportDialog::IMPORT_LAYER, this);
    configsImportDialog->exec();
    returnString = configsImportDialog->getReturnString();

    DialogueItemData *dialogueItemData = (DialogueItemData*) ui->listWidgetItems->currentItem()->data(Qt::UserRole).value<void*>();
    dialogueItemData->associatedImage = std::string(*returnString);

    ui->lineEditImage->setText(QString(returnString->c_str()));

    delete returnString;
}

void NewDialogueDialog::on_pushButtonAddMessage_pressed()
{
    DialogueItemData *dialogueItemData = new DialogueItemData();

    dialogueItemData->type = DialogueItemData::TYPE_MESSAGE;

    dialogueData->dialogueItems.push_back(dialogueItemData);

    QListWidgetItem *newItem = createNewItem(dialogueItemData);

    ui->listWidgetItems->addItem(newItem);
    ui->listWidgetItems->setCurrentItem(newItem);

}

void NewDialogueDialog::on_pushButtonRemoveItem_pressed()
{
    DialogueItemData *dialogueItemData = (DialogueItemData*) ui->listWidgetItems->currentItem()->data(Qt::UserRole).value<void*>();

    dialogueData->dialogueItems.erase(std::find(dialogueData->dialogueItems.begin(), dialogueData->dialogueItems.end(), dialogueItemData));

    populaListaDialogueItems();
}

void NewDialogueDialog::on_textEditMessage_textChanged()
{
    if(!ui->textEditMessage->toPlainText().isEmpty()) {
        std::stringstream ss;
        ss << "Mensagem: " << ui->textEditMessage->toPlainText().toStdString().substr(0, 40);
        if(ui->textEditMessage->toPlainText().length() > 40) {
            ss << "...";
        }

        ui->listWidgetItems->currentItem()->setText(ss.str().c_str());
        DialogueItemData *dialogueItemData = (DialogueItemData*) ui->listWidgetItems->currentItem()->data(Qt::UserRole).value<void*>();
        dialogueItemData->message = QString::fromUtf8(ui->textEditMessage->toPlainText().toUtf8()).toStdString();
    }
}

void NewDialogueDialog::on_pushButtonAddProcedure_pressed()
{
    if(ui->comboBoxProcedure->count() == 0) {
        MessageBoxes::showMessageBox(QString::fromUtf8(tr("Não há procedimentos para adicionar.").toStdString().c_str()));
        return;
    }

    DialogueItemData *dialogueItemData = new DialogueItemData();

    dialogueItemData->type = DialogueItemData::TYPE_PROCEDURE;
    dialogueItemData->procedureId = ui->comboBoxProcedure->itemData(0, Qt::UserRole).toInt();

    dialogueData->dialogueItems.push_back(dialogueItemData);

    QListWidgetItem *newItem = createNewItem(dialogueItemData);

    ui->listWidgetItems->addItem(newItem);
    ui->listWidgetItems->setCurrentItem(newItem);


}

void NewDialogueDialog::on_toolButtonRemoveImage_pressed()
{
    ui->lineEditImage->setText(QString(""));

    DialogueItemData *dialogueItemData = (DialogueItemData*) ui->listWidgetItems->currentItem()->data(Qt::UserRole).value<void*>();
    dialogueItemData->associatedImage = std::string("");

}

void NewDialogueDialog::on_comboBoxProcedure_currentIndexChanged(int index)
{
    if(ui->listWidgetItems->currentItem() != NULL) {
        DialogueItemData *dialogueItemData = (DialogueItemData*) ui->listWidgetItems->currentItem()->data(Qt::UserRole).value<void*>();
        dialogueItemData->procedureId = ui->comboBoxProcedure->itemData(index, Qt::UserRole).toInt();

        std::stringstream ss;
        ss << tr("Chama procedimento: ").toStdString().c_str();

        if(dialogueItemData->procedureId > 0) {
            GameData *gameData = GameData::getInstance();
            ProcedureData *procedureData = gameData->getProcedureById(dialogueItemData->procedureId);

            if(procedureData != NULL) {
                ss << procedureData->name;
            }
        } else {
            if(gameObject != NULL) {
                ProcedureData *procedureData = gameObject->gameObject->getProcedureById(-dialogueItemData->procedureId);

                if(procedureData != NULL) {
                    ss << "(" << gameObject->gameObject->name << ") " << procedureData->name;
                }
            }
        }

        ui->listWidgetItems->currentItem()->setText(QString(ss.str().c_str()));
    }

}

void NewDialogueDialog::on_checkBox_toggled(bool checked)
{
    DialogueItemData *dialogueItemData = (DialogueItemData*) ui->listWidgetItems->currentItem()->data(Qt::UserRole).value<void*>();
    dialogueItemData->associatedImageAtCenter = checked;
}

void NewDialogueDialog::on_buttonBox_accepted()
{
    accept();
}

void NewDialogueDialog::on_buttonBox_rejected()
{
    delete dialogueData;
    dialogueData = NULL;
    reject();
}
