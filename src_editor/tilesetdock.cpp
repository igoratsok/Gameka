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



#include "tilesetdock.h"

TilesetDock::TilesetDock(QWidget *parent, MapEditorController *mapEditorController)
        : QDockWidget(parent)
{
    widget = new QWidget(this);
    this->mapEditorController = mapEditorController;

    setMinimumSize(285, 300);

    QSpacerItem *spacer = new QSpacerItem(0, 100);

    /* inicializando o layout */
    layout = new QVBoxLayout(widget);
    layout->setMargin(5);
    layout->setSpacing(0);

    tabWidget = new QTabWidget(widget);
    tabWidget->setTabPosition(QTabWidget::South);

    layerSlider = new QSlider(Qt::Horizontal, this);
    layerSlider->setMinimum(0);
    layerSlider->setMaximum(4);







    /* adicionando o tilesetview e o tilesetscene */

    QObject::connect(layerSlider, SIGNAL(valueChanged(int)), this, SLOT(layerSliderMudada(int)));

    QLabel *layerLabel = new QLabel(this);
    layerLabel->setText(QString("Camada: "));

    layout->addWidget(tabWidget);
    layout->addWidget(layerLabel);
    layout->addWidget(layerSlider);

    tabWidget->setEnabled(false);

    std::stringstream ss;
    ss << QString::fromUtf8("Número da camada: ").toStdString() << layerSlider->value() + 1;

    layerSlider->setToolTip(QString(ss.str().c_str()));
    layerSlider->setEnabled(false);

    layerNumberLabel = new QLabel(QString(ss.str().c_str()));

    layout->addWidget(layerNumberLabel);

    layerButtons = new QWidget();
    layerButtons->setLayout(new QHBoxLayout(this));

    layerButton1 = new QPushButton("1");
    layerButton1->setMaximumWidth(30);
    layerButton1->setCheckable(true);

    layerButton2 = new QPushButton("2");
    layerButton2->setMaximumWidth(30);
    layerButton2->setCheckable(true);

    layerButton3 = new QPushButton("3");
    layerButton3->setMaximumWidth(30);
    layerButton3->setCheckable(true);

    layerButton4 = new QPushButton("4");
    layerButton4->setMaximumWidth(30);
    layerButton4->setCheckable(true);

    layerButton5 = new QPushButton("5");
    layerButton5->setMaximumWidth(30);
    layerButton5->setCheckable(true);

    QObject::connect(layerButton1, SIGNAL(toggled(bool)), this, SLOT(layerButton1_toggled(bool)));
    QObject::connect(layerButton2, SIGNAL(toggled(bool)), this, SLOT(layerButton2_toggled(bool)));
    QObject::connect(layerButton3, SIGNAL(toggled(bool)), this, SLOT(layerButton3_toggled(bool)));
    QObject::connect(layerButton4, SIGNAL(toggled(bool)), this, SLOT(layerButton4_toggled(bool)));
    QObject::connect(layerButton5, SIGNAL(toggled(bool)), this, SLOT(layerButton5_toggled(bool)));

    layerButtons->layout()->addWidget(new QLabel(QString("Camada:")));
    layerButtons->layout()->addWidget(layerButton1);
    layerButtons->layout()->addWidget(layerButton2);
    layerButtons->layout()->addWidget(layerButton3);
    layerButtons->layout()->addWidget(layerButton4);
    layerButtons->layout()->addWidget(layerButton5);


    layout->addWidget(layerButtons);

    layerButtons->setEnabled(false);



    setWidget(widget);
    setWindowTitle(tr("Tileset"));

    tilesetScene = NULL;



    buttonsChangable = true;

    checkLayerButton(0);

    layerSlider->setVisible(false);
    layerLabel->setVisible(false);
    layerNumberLabel->setVisible(false);



}


void TilesetDock::setDrawTile(int iTile, int jTile, int diTile, int djTile) {
    mapEditorController->setDrawTile(iTile, jTile, diTile, djTile);
}

void TilesetDock::setEditorMode(int mode) {
    mapEditorController->setEditorMode(mode);
}

void TilesetDock::initTileSetScene() {
    GameData *gameData = GameData::getInstance();

    std::vector<TileSet*> *listaTilesets = gameData->editingMap->tileSets;

    tabWidget->clear();

    for(std::vector<TileSet*>::iterator it = listaTilesets->begin(); it != listaTilesets->end(); ++it) {
        TileSet* tileset = (*it);


        tilesetView = new TilesetView(widget);
        tilesetView->hide();


        tilesetScene = new TilesetScene(this, tileset);
        tilesetView->setScene(tilesetScene);
        tilesetView->setAlignment(Qt::AlignLeft);


        tabWidget->addTab(tilesetView, tileset->name.c_str());






        tilesetView->show();

    }

    tabWidget->setEnabled(true);
    layerSlider->setEnabled(true);

    layerButtons->setEnabled(true);




}

TileSet* TilesetDock::getSelectedTileset() {
    TilesetView *currentView;
    TilesetScene *currentScene;
    currentView = (TilesetView*) tabWidget->currentWidget();

    if(currentView == NULL) return NULL;

    currentScene = (TilesetScene*) currentView->scene();

    return currentScene->tileSet;
}

void TilesetDock::layerSliderMudada(int valor) {
    std::stringstream ss;
    ss << QString::fromUtf8("Número da camada: ").toStdString() << layerSlider->value() + 1;
    layerSlider->setToolTip(QString(ss.str().c_str()));

    layerNumberLabel->setText(QString(ss.str().c_str()));

    layerSlider->setValue(mapEditorController->setMapEditorLayer(valor));
}

void TilesetDock::layerButton1_toggled(bool value) {
    if(buttonsChangable) {
        if(value) {
            int checkNumber = mapEditorController->setMapEditorLayer(0);
            checkLayerButton(checkNumber);
        } else {
            layerButton1->setChecked(true);
        }
    }


}

void TilesetDock::layerButton2_toggled(bool value) {
    if(buttonsChangable) {
        if(value) {
            int checkNumber = mapEditorController->setMapEditorLayer(1);
            checkLayerButton(checkNumber);
        } else {
            layerButton2->setChecked(true);
        }
    }
}

void TilesetDock::layerButton3_toggled(bool value) {
    if(buttonsChangable) {
        if(value) {
            int checkNumber = mapEditorController->setMapEditorLayer(2);
            checkLayerButton(checkNumber);
        } else {
            layerButton3->setChecked(true);
        }
    }
}

void TilesetDock::layerButton4_toggled(bool value) {
    if(buttonsChangable) {
        if(value) {
            int checkNumber = mapEditorController->setMapEditorLayer(3);
            checkLayerButton(checkNumber);
        } else {
            layerButton4->setChecked(true);
        }
    }
}

void TilesetDock::layerButton5_toggled(bool value) {
    if(buttonsChangable) {
        if(value) {
            int checkNumber = mapEditorController->setMapEditorLayer(4);
            checkLayerButton(checkNumber);
        } else {
            layerButton5->setChecked(true);
        }
    }
}

void TilesetDock::checkLayerButton(int number) {
    buttonsChangable = false;
    switch(number){
    case 0:
        layerButton1->setChecked(true);
        layerButton2->setChecked(false);
        layerButton3->setChecked(false);
        layerButton4->setChecked(false);
        layerButton5->setChecked(false);
        break;
    case 1:
        layerButton1->setChecked(false);
        layerButton2->setChecked(true);
        layerButton3->setChecked(false);
        layerButton4->setChecked(false);
        layerButton5->setChecked(false);
        break;
    case 2:
        layerButton1->setChecked(false);
        layerButton2->setChecked(false);
        layerButton3->setChecked(true);
        layerButton4->setChecked(false);
        layerButton5->setChecked(false);
        break;
    case 3:
        layerButton1->setChecked(false);
        layerButton2->setChecked(false);
        layerButton3->setChecked(false);
        layerButton4->setChecked(true);
        layerButton5->setChecked(false);
        break;
    case 4:
        layerButton1->setChecked(false);
        layerButton2->setChecked(false);
        layerButton3->setChecked(false);
        layerButton4->setChecked(false);
        layerButton5->setChecked(true);
        break;
    }

    buttonsChangable = true;
}
