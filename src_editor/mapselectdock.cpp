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



#include "mapselectdock.h"


MapSelectDock::MapSelectDock(QWidget *parent, MapEditorController *mapEditorController) : QDockWidget(parent)
{

    setWindowTitle(tr("Mapas"));
    setMinimumHeight(100);

    this->mapEditorController = mapEditorController;

    widget = new QWidget(this);


    /* inicializando o layout */
    vboxLayout = new QVBoxLayout(widget);
    vboxLayout->setMargin(5);
    vboxLayout->setSpacing(0);


    treeWidget = new QTreeWidget(this);
    treeWidget->setColumnCount(1);

    treeWidget->setDragEnabled(true);

    treeWidget->setHeaderHidden(true);

    vboxLayout->addWidget(treeWidget);

    /*
    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 10; ++i) {
        QTreeWidgetItem* newItem;
        newItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i)));
        newItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled);
        if(i == 3) {
            newItem->insertChild(0, new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item filho"))));
        }

        items.append(newItem);
    }

    treeWidget->insertTopLevelItems(0, items);
    */
    populaArvore();



    //treeView = new QTreeView(this);

    /*
    model = new QStringListModel(this);
    QStringList stringList;
    stringList.append("Mapa 01");
    model->setStringList(stringList);
    treeView->setModel(model);

    */
    /* inicializando o hBoxLayout dos botões */
    hboxLayout = new QHBoxLayout(widget);
    hboxLayout->setMargin(0);
    vboxLayout->setSpacing(0);

    vboxLayout->addLayout(hboxLayout);

    /* inicializando os botoes */
    botaoCriaMapa = new QPushButton(tr("Cria Mapa"), widget);
    botaoEditaMapa = new QPushButton(tr("Edita Mapa"), widget);
    botaoDeletaMapa = new QPushButton(tr("Deleta Mapa"), widget);
    botaoCriaPasta = new QPushButton(tr("Cria Pasta"), widget);

    QObject::connect(botaoCriaMapa, SIGNAL(clicked()), this, SLOT(botaoCriaMapaClicked()));
    QObject::connect(botaoCriaPasta, SIGNAL(clicked()), this, SLOT(botaoCriaPastaClicked()));
    QObject::connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(treeWidgetItemClicked(QTreeWidgetItem*,int)));
    QObject::connect(botaoEditaMapa, SIGNAL(clicked()), this, SLOT(botaoEditaMapaClicked()));
    QObject::connect(botaoDeletaMapa, SIGNAL(clicked()), this, SLOT(botaoDeletaMapaClicked()));

    hboxLayout->addWidget(botaoCriaMapa);
    hboxLayout->addWidget(botaoEditaMapa);
    hboxLayout->addWidget(botaoDeletaMapa);

    vboxLayout->addWidget(botaoCriaPasta);



    setWidget(widget);
}

void MapSelectDock::botaoCriaMapaClicked() {
    mapEditorController->openNewMapWindow();
}

void MapSelectDock::botaoCriaPastaClicked() {
    mapEditorController->createFolder();
}

void MapSelectDock::initMapSelectScene() {

}


void MapSelectDock::populaArvore() {
    GameData *gameData = GameData::getInstance();

    std::vector<Map *> *arvoreMapas;

    arvoreMapas = mapEditorController->getMaplist();

    QList<QTreeWidgetItem *> items;

    treeWidget->clear();

    QTreeWidgetItem* firstItem = NULL;

    for(std::vector<Map*>::iterator it = arvoreMapas->begin(); it != arvoreMapas->end(); ++it) {
        Map *mapa = (Map*)(*it);

        QTreeWidgetItem* newItem;
        newItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(mapa->mapName.c_str())));
        newItem->setData(0, Qt::UserRole, QVariant::fromValue((void*) mapa));
        newItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled);



        if(mapa->filhos != NULL) {
            newItem->setIcon(0, QIcon::fromTheme("folder"));
            populaSubpastas(mapa->filhos, newItem);
        } else {
            newItem->setIcon(0, QIcon::fromTheme("document"));

            if(firstItem == NULL) {
                firstItem = newItem;
            }
        }

        items.append(newItem);

    }

    treeWidget->insertTopLevelItems(0, items);

    if(firstItem != NULL) {
        treeWidget->setCurrentItem(firstItem, 0);
    }

}

void MapSelectDock::populaSubpastas(std::vector<Map *> *subarvore, QTreeWidgetItem *item) {

    for(std::vector<Map *>::iterator it = subarvore->begin(); it != subarvore->end(); ++it) {
        Map *mapa = (Map*)(*it);

        QTreeWidgetItem* newItem;
        newItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(mapa->mapName.c_str())));
        newItem->setData(0, Qt::UserRole, QVariant::fromValue((void*) mapa));
        newItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled);

        if(mapa->filhos != NULL) {
            newItem->setIcon(0, QIcon::fromTheme("folder"));
            populaSubpastas(mapa->filhos, newItem);
        } else {
            newItem->setIcon(0, QIcon::fromTheme("document"));
        }

        item->addChild(newItem);
    }
}

Map* MapSelectDock::getMapaSelecionado() {

    if(treeWidget->currentItem() == NULL) {
        return NULL;
    } else {
        return (Map*) treeWidget->currentItem()->data(0, Qt::UserRole).value<void*>();
    }

}

void MapSelectDock::treeWidgetItemClicked(QTreeWidgetItem *item, int index) {
    mapEditorController->selectMap((Map*) treeWidget->currentItem()->data(0, Qt::UserRole).value<void*>());

}

void MapSelectDock::botaoEditaMapaClicked() {
    if(treeWidget->currentItem() != NULL) {
        mapEditorController->openEditMapWindow((Map*) treeWidget->currentItem()->data(0, Qt::UserRole).value<void*>());
    }
}

void MapSelectDock::botaoDeletaMapaClicked() {
    GameData *gameData = GameData::getInstance();
    if(treeWidget->currentItem() != NULL) {
        Map *currentMap = (Map*) treeWidget->currentItem()->data(0, Qt::UserRole).value<void*>();

        if(currentMap != NULL && !currentMap->isFolder()) {
            if(MessageBoxes::showConfirmBox(QString::fromUtf8(tr("Deseja remover o mapa?").toStdString().c_str()).toStdString())) {
                if(gameData->verifyIfMapUsedById(currentMap->id)) {
                    MessageBoxes::showMessageBox(QString::fromUtf8(tr("Não é possível deletar o mapa, pois ele é referenciado em outro lugar.").toStdString().c_str()));
                } else {
                    gameData->removeMap(currentMap->id);
                    populaArvore();
                    mapEditorController->selectMap(NULL);
                }
            }

        } else {
            MessageBoxes::showMessageBox(QString::fromUtf8(QApplication::tr("Ainda não é possível deletar pastas.").toStdString().c_str()));
        }
    }
}
