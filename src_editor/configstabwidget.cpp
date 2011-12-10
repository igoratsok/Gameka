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



#include "configstabwidget.h"
#include "ui_configstabwidget.h"

ConfigsTabWidget::ConfigsTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ConfigsTabWidget)
{
    ui->setupUi(this);
    getObjectTab()->setConfigsTabWidget(this);

}

ConfigsTabWidget::~ConfigsTabWidget()
{
    delete ui;
}

void ConfigsTabWidget::setOptionsController(OptionsController *optionsController) {
    this->optionsController = optionsController;
    ui->tab_tilesets->setOptionsController(optionsController);
    ui->tab_objetos->setOptionsController(optionsController);
    ui->tab_gerais->setOptionsController(optionsController);
    ui->tab_animations->setOptionsController(optionsController);
    ui->tab_fundos->setOptionsController(optionsController);
}

void ConfigsTabWidget::changeEvent(QEvent *e)
{
    QTabWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

ConfigsTilesetWidget* ConfigsTabWidget::getTilesetTab() {
    return (ConfigsTilesetWidget*) ui->tab_tilesets;
}

ConfigsObjectsWidget* ConfigsTabWidget::getObjectTab() {
    return (ConfigsObjectsWidget*) ui->tab_objetos;
}

ConfigsGeneralWidget* ConfigsTabWidget::getDadosGeraisTab() {
    return (ConfigsGeneralWidget*) ui->tab_gerais;
}

ConfigsAnimations* ConfigsTabWidget::getAnimationsTab() {
    return (ConfigsAnimations*) ui->tab_animations;
}

ConfigsBackgrounds* ConfigsTabWidget::getBackgroundsTab() {
    return (ConfigsBackgrounds*) ui->tab_fundos;
}

EventsWidget* ConfigsTabWidget::getEventsTab() {
    return (EventsWidget*) ui->tab_eventos_globais;
}

void ConfigsTabWidget::selectObject(GameObject *gameObject) {
    setCurrentWidget(ui->tab_objetos);
    getObjectTab()->selectObject(gameObject);
}

void ConfigsTabWidget::selectObjectEvent(int idObject) {
    setCurrentWidget(ui->tab_eventos_globais);
    getEventsTab()->selectObject(idObject);

}


