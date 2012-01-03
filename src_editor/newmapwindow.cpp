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



#include "newmapwindow.h"
#include "ui_newmapwindow.h"

NewMapWindow::NewMapWindow(MapEditorController *mapEditorController, Map *parameterMap, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMapWindow)
{
    ui->setupUi(this);
    this->mapEditorController = mapEditorController;

    if(parameterMap == NULL) {
        map = new Map();
        mode = MODE_NEW;
    } else {
        map = parameterMap;
        mode = MODE_EDIT;
    }


    this->ui->tab_geral->map = map;
    this->ui->tab_tilesets->map = map;
    this->ui->tab_objetos->map = map;

    this->ui->tab_geral->mapEditorController = mapEditorController;
    this->ui->tab_tilesets->mapEditorController = mapEditorController;

    this->ui->tab_geral->preencheDados();

    this->ui->tab_tilesets->populaListaDisponiveis();
    this->ui->tab_tilesets->populaListaEscolhidos();

    this->ui->tab_objetos->populaListaObjetosDisponiveis();
    this->ui->tab_objetos->populaListObjetosEscolhidos();
}

NewMapWindow::~NewMapWindow()
{
    delete ui;
}



void NewMapWindow::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



void NewMapWindow::on_buttonBox_2_accepted()
{
    map->mapName = ui->tab_geral->getNomeMapa().toStdString();

    if(ui->tab_geral->getNomeMapa().isEmpty()) {
        MessageBoxes::showMessageBox(QString::fromUtf8(tr("O mapa precisa ter nome!").toStdString().c_str()));
        return;
    }

    if(map->tileSets->empty()) {
        MessageBoxes::showMessageBox(QString::fromUtf8(tr("É necessário ter ao menos um Tileset escolhido.").toStdString().c_str()));
        ui->tabWidget->setCurrentIndex(1);
        return;
    }



    if(mode == MODE_NEW) {
        map->extent(ui->tab_geral->getTamanhoWidth(), ui->tab_geral->getTamanhoHeight(), 1);
        mapEditorController->createNewMap(map);
    } else {
        map->extent(ui->tab_geral->getTamanhoWidth(), ui->tab_geral->getTamanhoHeight(), map->layers);
        mapEditorController->refreshMapWidgets();
    }

    accept();
}

void NewMapWindow::on_buttonBox_2_rejected()
{
    reject();
}

