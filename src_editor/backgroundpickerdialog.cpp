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


#include "backgroundpickerdialog.h"
#include "ui_backgroundpickerdialog.h"

BackgroundPickerDialog::BackgroundPickerDialog(MapEditorController *mapEditorController, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BackgroundPickerDialog),
    mapEditorController(mapEditorController)
{
    ui->setupUi(this);

    backgroundGraphicsScene = new BackgroundsGraphicsScene();
    ui->graphicsView->setScene(backgroundGraphicsScene);

    chosenBackground = NULL;

    populaListaFundos();
}

BackgroundPickerDialog::~BackgroundPickerDialog()
{
    delete ui;
}

void BackgroundPickerDialog::populaListaFundos() {
    GameData *gameData = GameData::getInstance();

    ui->listWidget->clear();

    for(std::vector<Background*>::iterator it = mapEditorController->getBackgroundList()->begin(); it != mapEditorController->getBackgroundList()->end(); ++it) {
        Background *background = *it;

        QListWidgetItem *item = new QListWidgetItem(QString(background->name.c_str()));
        item->setData(Qt::UserRole, QVariant::fromValue((void*) background));
        ui->listWidget->addItem(item);
    }

    if(ui->listWidget->count() != 0) {
        ui->listWidget->setCurrentRow(0);
    }
}

void BackgroundPickerDialog::on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(current != NULL) {
        Background *bg = (Background*) current->data(Qt::UserRole).value<void*>();

        backgroundGraphicsScene->setBackground(bg);
    }

}

void BackgroundPickerDialog::on_buttonBox_accepted()
{
    if(ui->listWidget->currentItem() != NULL) {
        chosenBackground = (Background*) ui->listWidget->currentItem()->data(Qt::UserRole).value<void*>();
    } else {
        chosenBackground = NULL;
    }

}

void BackgroundPickerDialog::on_buttonBox_rejected()
{
    chosenBackground = NULL;
}

Background* BackgroundPickerDialog::exec() {
    QDialog::exec();

    return chosenBackground;
}

void BackgroundPickerDialog::on_buttonBox_clicked(QAbstractButton* button)
{

}
