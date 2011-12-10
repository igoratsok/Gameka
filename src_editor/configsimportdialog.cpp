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


#include "configsimportdialog.h"
#include "ui_configsimportdialog.h"

ConfigsImportDialog::ConfigsImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigsImportDialog) {
    this->optionsController = NULL;
    this->importType = IMPORT_RETURN_EXEC;
    ui->setupUi(this);
    populaLista();
}

ConfigsImportDialog::ConfigsImportDialog(OptionsController *optionsController, int importType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigsImportDialog)
{
    this->optionsController = optionsController;
    this->importType = importType;
    ui->setupUi(this);
    populaLista();

    returnString = NULL;

    if(importType != IMPORT_ANIMATIONS) {
        ui->comboBoxTipo->setVisible(false);
        ui->labelTipo->setVisible(false);
    }

    animationImportPattern = 0;
}

ConfigsImportDialog::ConfigsImportDialog(OptionsController *optionsController, int importType, int importOption, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigsImportDialog)
{
    this->optionsController = optionsController;
    this->importType = importType;
    this->importOption = importOption;
    ui->setupUi(this);
    populaLista();

    returnString = NULL;

    animationImportPattern = 0;
}

ConfigsImportDialog::~ConfigsImportDialog()
{
    delete ui;
}

void ConfigsImportDialog::populaLista() {
    GameData *gameData;
    gameData = GameData::getInstance();

    QDir *dir;
    QStringList files;
    QStringList filters;

    switch(importType) {
    case IMPORT_TILESETS:
        dir = new QDir(gameData->getProjectDirectory().append("/tilesets/").c_str());
        filters << "*.png" << "*.jpg" << "*.gif" << "*.bmp";

        break;

    case IMPORT_TITLESCREENS:
        dir = new QDir(gameData->getProjectDirectory().append("/images/").c_str());
        filters << "*.png" << "*.jpg" << "*.gif" << "*.bmp";

        break;
    case IMPORT_ANIMATIONS:
        dir = new QDir(gameData->getProjectDirectory().append("/animations/").c_str());
        filters << "*.png" << "*.jpg" << "*.gif" << "*.bmp";

        break;
    case IMPORT_SPRITE:
        dir = new QDir(gameData->getProjectDirectory().append("/objects/").c_str());
        filters << "*.png" << "*.jpg" << "*.gif" << "*.bmp";

        break;
    case IMPORT_BACKGROUND:
        dir = new QDir(gameData->getProjectDirectory().append("/images/").c_str());
        filters << "*.png" << "*.jpg" << "*.gif" << "*.bmp";

        break;

    case IMPORT_LAYER:
        dir = new QDir(gameData->getProjectDirectory().append("/images/").c_str());
        filters << "*.png" << "*.jpg" << "*.gif" << "*.bmp";

        break;
    }




    dir->setNameFilters(filters);

    files = dir->entryList();


    ui->listWidget->clear();
    for(QStringList::Iterator it = files.begin(); it != files.end(); ++it) {
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(*it);
        ui->listWidget->addItem(newItem);
    }
}

void ConfigsImportDialog::on_botaoSelecionar_clicked()
{
    if(ui->listWidget->currentItem() == NULL) {
        MessageBoxes::showMessageBox(QString::fromUtf8("Necessário importar um recurso antes."));
    } else {
        switch(importType) {
        case IMPORT_TILESETS:
            optionsController->addTileset(ui->listWidget->currentItem()->text().toStdString());
            break;

        case IMPORT_TITLESCREENS:
            optionsController->setGameScreen(ui->listWidget->currentItem()->text().toStdString(), importOption);
            break;

        case IMPORT_ANIMATIONS:
            optionsController->addAnimation(ui->listWidget->currentItem()->text().toStdString(), animationImportPattern);
            break;

        case IMPORT_SPRITE:
            returnString = new std::string(ui->listWidget->currentItem()->text().toStdString().c_str());
            break;
        case IMPORT_BACKGROUND:
            optionsController->addBackground(ui->listWidget->currentItem()->text().toStdString());
            break;

        case IMPORT_LAYER:
            returnString = new std::string(ui->listWidget->currentItem()->text().toStdString().c_str());
            break;
        }



        this->close();
    }
}

void ConfigsImportDialog::on_botaoImportar_clicked()
{
    QStringList fileNames;


    fileNames = QFileDialog::getOpenFileNames(this, tr("Open Project"), "", tr("(*.png *.jpg *.bmp *.gif)"));


    for(QStringList::Iterator it = fileNames.begin(); it != fileNames.end(); ++it) {
        QString fileName = *it;

        if(!fileName.isEmpty()) {
            optionsController->importResource(fileName.toStdString(), importType);
            populaLista();
            for(int i = 0; i < ui->listWidget->count(); i++) {
                if(ui->listWidget->itemAt(i, 0)->text().compare(fileName)) {
                    ui->listWidget->setCurrentItem(ui->listWidget->itemAt(i, 0));
                }
            }
        }
    }
}

void ConfigsImportDialog::on_botaoCancelar_clicked()
{
    this->close();
}

void ConfigsImportDialog::on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    QPixmap image;
    std::string diretorio;
    GameData *gameData;

    if(current != NULL) {
        gameData = GameData::getInstance();

        switch(importType) {
        case IMPORT_TILESETS:
            diretorio = gameData->getProjectDirectory().append("/tilesets/");
            break;
        case IMPORT_TITLESCREENS:
            diretorio = gameData->getProjectDirectory().append("/images/");
            break;
        case IMPORT_ANIMATIONS:
            diretorio = gameData->getProjectDirectory().append("/animations/");
            break;
        case IMPORT_SPRITE:
            diretorio = gameData->getProjectDirectory().append("/objects/");
            break;
        case IMPORT_BACKGROUND:
            diretorio = gameData->getProjectDirectory().append("/images/");
            break;
        case IMPORT_LAYER:
            diretorio = gameData->getProjectDirectory().append("/images/");
            break;
        }


        diretorio.append(current->text().toStdString().c_str());

        image = QPixmap(diretorio.c_str());



        ui->imagethumbnail->setPixmap(image.scaledToWidth(200 , Qt::SmoothTransformation));
    }
}

std::string *ConfigsImportDialog::getReturnString() {
    return returnString;
}

void ConfigsImportDialog::on_comboBoxTipo_currentIndexChanged(int index)
{
    animationImportPattern = index;
}
