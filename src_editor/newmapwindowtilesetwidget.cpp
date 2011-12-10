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



#include "newmapwindowtilesetwidget.h"
#include "ui_newmapwindowtilesetwidget.h"

NewMapWindowTilesetWidget::NewMapWindowTilesetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewMapWindowTilesetWidget)
{
    ui->setupUi(this);

}

NewMapWindowTilesetWidget::~NewMapWindowTilesetWidget()
{
    delete ui;
}

void NewMapWindowTilesetWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void NewMapWindowTilesetWidget::populaListaDisponiveis() {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::vector<TileSet*>* tileSetList;


    tileSetList = mapEditorController->getTilesetList();

    ui->listTilesetsDispon->clear();

    for(std::vector<TileSet*>::iterator it = tileSetList->begin(); it != tileSetList->end(); ++it) {
        TileSet *iterationItem;

        iterationItem = *it;

        if(std::find(map->tileSets->begin(), map->tileSets->end(), iterationItem) == map->tileSets->end()) {
            QListWidgetItem *newItem = new QListWidgetItem();
            newItem->setText(QString(iterationItem->name.c_str()));
            newItem->setData(Qt::UserRole, QVariant::fromValue((void*) iterationItem));
            ui->listTilesetsDispon->addItem(newItem);
        }


    }
}

void NewMapWindowTilesetWidget::populaListaEscolhidos() {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::vector<TileSet*>* tileSetList;


    tileSetList = map->tileSets;

    ui->listTilesetsEscolhidas->clear();

    for(std::vector<TileSet*>::iterator it = tileSetList->begin(); it != tileSetList->end(); ++it) {
        TileSet *iterationItem;

        iterationItem = *it;
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString(iterationItem->name.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) iterationItem));
        ui->listTilesetsEscolhidas->addItem(newItem);

    }
}

void NewMapWindowTilesetWidget::on_pushButton_clicked()
{




}

void NewMapWindowTilesetWidget::on_pushButton_pressed()
{
    if(ui->listTilesetsDispon->currentItem() != NULL) {
        QList<QListWidgetItem*> selectedItems = ui->listTilesetsDispon->selectedItems();

        TileSet* selectedTileset = (TileSet*) ui->listTilesetsDispon->currentItem()->data(Qt::UserRole).value<void*>();



        // o if abaixo verifica se o selectedTileset não está na lista de tilesets do map
        if(std::find(map->tileSets->begin(), map->tileSets->end(), selectedTileset) == map->tileSets->end()) {
            // agora verifica se todos os outros tem o mesmo tamanho deste
            bool sameSize = false;
            foreach(TileSet *otherTileset, *map->tileSets) {
                if(otherTileset->tileSize != selectedTileset->tileSize) {
                    sameSize = true;
                    break;
                }
            }


            if(!sameSize) {
                map->tileSets->push_back(selectedTileset);
            } else {
                MessageBoxes::showMessageBox(QString::fromUtf8("O tileset adicionado precisa ter o mesmo tamanho dos outros do mapa.").toStdString());
            }

        }

        populaListaDisponiveis();
        populaListaEscolhidos();
    }
}
