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


#include "configsbackgrounds.h"
#include "ui_configsbackgrounds.h"

ConfigsBackgrounds::ConfigsBackgrounds(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigsBackgrounds)
{
    ui->setupUi(this);
    backgroundsGraphicsScene = new BackgroundsGraphicsScene();

    ui->graphicsView->setScene(backgroundsGraphicsScene);

    populaListaBackgrounds(true);
}

ConfigsBackgrounds::~ConfigsBackgrounds()
{
    delete ui;
}

void ConfigsBackgrounds::populaListaBackgrounds(bool firstTime = false) {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::vector<Background*> *backgroundList;


    backgroundList = optionsController->getBackgroundList();

    ui->listWidgetBgs->clear();

    for(std::vector<Background*>::iterator it = backgroundList->begin(); it != backgroundList->end(); ++it) {
        Background *iterationItem;

        iterationItem = *it;
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString(iterationItem->name.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) iterationItem));
        ui->listWidgetBgs->addItem(newItem);


    }

    if(ui->listWidgetBgs->count() > 0) {
        if(firstTime) {
            ui->listWidgetBgs->setCurrentRow(0);
        } else {
            ui->listWidgetBgs->setCurrentRow(ui->listWidgetBgs->count() - 1);
        }

    }
}

void ConfigsBackgrounds::populaListaLayers() {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::vector<BgLayer*> *layerList;


    layerList = ((Background*) ui->listWidgetBgs->currentItem()->data(Qt::UserRole).value<void*>())->layerList;

    ui->listWidgetLayers->clear();

    for(std::vector<BgLayer*>::iterator it = layerList->begin(); it != layerList->end(); ++it) {
        BgLayer *iterationItem;

        iterationItem = *it;
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString(iterationItem->fileName.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) iterationItem));
        ui->listWidgetLayers->addItem(newItem);

    }

    if(ui->listWidgetLayers->count() > 0) {
        ui->listWidgetLayers->setCurrentRow(0);
    }
}

void ConfigsBackgrounds::setOptionsController(OptionsController *optionsController) {
    this->optionsController = optionsController;
}

void ConfigsBackgrounds::on_pushButtonAddBg_clicked()
{
    ConfigsImportDialog *configsImportDialog = new ConfigsImportDialog(optionsController, ConfigsImportDialog::IMPORT_BACKGROUND);
    configsImportDialog->exec();
}

void ConfigsBackgrounds::on_listWidgetBgs_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(current != NULL) {
        populaListaLayers();
        ui->groupBoxBg->setEnabled(true);
        preencheCamposBg();

        Background *bg = ((Background*) ui->listWidgetBgs->currentItem()->data(Qt::UserRole).value<void*>());

        backgroundsGraphicsScene->setBackground(bg);
    }


}

void ConfigsBackgrounds::preencheCamposBg() {
    Background *bg = ((Background*) ui->listWidgetBgs->currentItem()->data(Qt::UserRole).value<void*>());
    ui->lineEditName->setText(QString(bg->name.c_str()));
}

void ConfigsBackgrounds::preencheCamposLayer() {
    ui->groupBoxLayer->setEnabled(true);
    ui->groupBoxVisual->setEnabled(true);

    BgLayer *bgLayer = ((BgLayer*) ui->listWidgetLayers->currentItem()->data(Qt::UserRole).value<void*>());

    ui->checkBoxRepeatHor->setChecked(bgLayer->repeatsHorizontally);
    ui->checkBoxRepeatVer->setChecked(bgLayer->repeatsVertically);
    ui->spinBoxDx->setValue(bgLayer->displacementX);
    ui->spinBoxDy->setValue(bgLayer->displacementY);
    ui->spinBoxVx->setValue(bgLayer->vx);
    ui->spinBoxVy->setValue(bgLayer->vy);
    ui->comboBoxBehavior->setCurrentIndex(bgLayer->behavior);
    ui->lineEditImageFile->setText(QString(bgLayer->fileName.c_str()));

    if(ui->comboBoxBehavior->currentIndex() < 2) {
        ui->spinBoxVx->setEnabled(false);
        ui->spinBoxVy->setEnabled(false);
    } else {
        ui->spinBoxVx->setEnabled(true);
        ui->spinBoxVy->setEnabled(true);
    }
}

void ConfigsBackgrounds::on_lineEditName_textChanged(QString text)
{
    Background *bg = ((Background*) ui->listWidgetBgs->currentItem()->data(Qt::UserRole).value<void*>());
    if(!text.isEmpty()) {
        bg->name = text.toStdString();
        ui->listWidgetBgs->currentItem()->setText(text);
    }

}

void ConfigsBackgrounds::on_listWidgetLayers_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(current != NULL) {
        preencheCamposLayer();
    }

}

void ConfigsBackgrounds::on_pushButton_clicked()
{
    std::string *returnString;
    ConfigsImportDialog *configsImportDialog = new ConfigsImportDialog(optionsController, ConfigsImportDialog::IMPORT_LAYER, this);
    configsImportDialog->exec();
    returnString = configsImportDialog->getReturnString();

    if(returnString != NULL) {
        BgLayer *bgLayer = ((BgLayer*) ui->listWidgetLayers->currentItem()->data(Qt::UserRole).value<void*>());
        ui->lineEditImageFile->setText(QString(returnString->c_str()));
        bgLayer->fileName = std::string("images/").append(returnString->c_str());

        delete returnString;
    }



    delete configsImportDialog;

    backgroundsGraphicsScene->reloadBackground();
}

void ConfigsBackgrounds::on_spinBoxDx_valueChanged(int value)
{
    BgLayer *bgLayer = ((BgLayer*) ui->listWidgetLayers->currentItem()->data(Qt::UserRole).value<void*>());
    bgLayer->displacementX = value;
    backgroundsGraphicsScene->reloadBackground();
}

void ConfigsBackgrounds::on_spinBoxDy_valueChanged(int value)
{
    BgLayer *bgLayer = ((BgLayer*) ui->listWidgetLayers->currentItem()->data(Qt::UserRole).value<void*>());
    bgLayer->displacementY = value;
    backgroundsGraphicsScene->reloadBackground();
}

void ConfigsBackgrounds::on_checkBoxRepeatHor_toggled(bool checked)
{
    BgLayer *bgLayer = ((BgLayer*) ui->listWidgetLayers->currentItem()->data(Qt::UserRole).value<void*>());
    bgLayer->repeatsHorizontally = checked;
    backgroundsGraphicsScene->reloadBackground();
}

void ConfigsBackgrounds::on_checkBoxRepeatVer_toggled(bool checked)
{
    BgLayer *bgLayer = ((BgLayer*) ui->listWidgetLayers->currentItem()->data(Qt::UserRole).value<void*>());
    bgLayer->repeatsVertically = checked;
    backgroundsGraphicsScene->reloadBackground();
}

void ConfigsBackgrounds::on_comboBoxBehavior_currentIndexChanged(int index)
{
    BgLayer *bgLayer = ((BgLayer*) ui->listWidgetLayers->currentItem()->data(Qt::UserRole).value<void*>());
    bgLayer->behavior = index;
    backgroundsGraphicsScene->reloadBackground();

    if(index < 2) {
        ui->spinBoxVx->setEnabled(false);
        ui->spinBoxVy->setEnabled(false);
    } else {
        ui->spinBoxVx->setEnabled(true);
        ui->spinBoxVy->setEnabled(true);
    }
}

void ConfigsBackgrounds::on_spinBoxVx_valueChanged(int value)
{
    BgLayer *bgLayer = ((BgLayer*) ui->listWidgetLayers->currentItem()->data(Qt::UserRole).value<void*>());
    bgLayer->vx = value;
    backgroundsGraphicsScene->reloadBackground();
}

void ConfigsBackgrounds::on_spinBoxVy_valueChanged(int value)
{
    BgLayer *bgLayer = ((BgLayer*) ui->listWidgetLayers->currentItem()->data(Qt::UserRole).value<void*>());
    bgLayer->vy = value;
    backgroundsGraphicsScene->reloadBackground();
}

void ConfigsBackgrounds::on_listWidgetLayers_itemChanged(QListWidgetItem* item)
{

}

void ConfigsBackgrounds::on_pushButtonAddLayer_clicked()
{

}

void ConfigsBackgrounds::on_pushButtonAddLayer_pressed()
{
    std::string *returnString;
    ConfigsImportDialog *configsImportDialog = new ConfigsImportDialog(optionsController, ConfigsImportDialog::IMPORT_LAYER, this);
    configsImportDialog->exec();
    returnString = configsImportDialog->getReturnString();

    if(returnString != NULL) {
        BgLayer *bgLayer = new BgLayer();
        Background *bg = ((Background*) ui->listWidgetBgs->currentItem()->data(Qt::UserRole).value<void*>());

        bgLayer->fileName = std::string("images/").append(returnString->c_str());
        bg->layerList->push_back(bgLayer);

        delete returnString;
    }



    delete configsImportDialog;

    populaListaLayers();
    backgroundsGraphicsScene->reloadBackground();
}

void ConfigsBackgrounds::on_pushButtonRemoveLayer_pressed()
{
    if(ui->listWidgetLayers->count() == 1) {
        MessageBoxes::showMessageBox(QString::fromUtf8("Necessária ao menos uma camada."));
    } else {
        if(ui->listWidgetLayers->currentItem() != NULL) {
            BgLayer *bgLayer = ((BgLayer*) ui->listWidgetLayers->currentItem()->data(Qt::UserRole).value<void*>());
            Background *bg = ((Background*) ui->listWidgetBgs->currentItem()->data(Qt::UserRole).value<void*>());

            if(bgLayer != NULL) {
                ui->listWidgetLayers->removeItemWidget(ui->listWidgetLayers->currentItem());
                bg->layerList->erase(std::find(bg->layerList->begin(), bg->layerList->end(), bgLayer));

            }
        }
    }


    populaListaLayers();
    backgroundsGraphicsScene->reloadBackground();



}

void ConfigsBackgrounds::on_buttonRemoveBg_pressed()
{
    GameData *gameData = GameData::getInstance();

    if(ui->listWidgetBgs->currentItem() != NULL) {
        Background *bg = ((Background*) ui->listWidgetBgs->currentItem()->data(Qt::UserRole).value<void*>());
        if(bg != NULL) {
            if(MessageBoxes::showConfirmBox(QString::fromUtf8("Deseja remover o fundo?").toStdString())) {
                if(gameData->verifyBackgroundUsed(bg->id)) {
                    if(!MessageBoxes::showConfirmBox(QString::fromUtf8("O fundo é utilizado em um mapa. Deseja remover mesmo assim?").toStdString())) {
                        return;
                    }


                }

                optionsController->removeBackground(bg);

                populaListaBackgrounds();

                if(ui->listWidgetBgs->count() == 0) {
                    ui->groupBoxBg->setEnabled(false);
                    ui->groupBoxVisual->setEnabled(false);
                    ui->groupBoxLayer->setEnabled(false);
                }

            }

        }
    }

}
