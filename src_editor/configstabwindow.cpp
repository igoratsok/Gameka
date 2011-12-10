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



#include "configstabwindow.h"
#include "ui_configstabwindow.h"

ConfigsTabWindow::ConfigsTabWindow(OptionsController *optionsController,  EventsEditorController *eventsEditorController, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigsTabWindow)
{
    ui->setupUi(this);
    this->optionsController = optionsController;

    ui->pushButton->setVisible(false);


   ui->widget->setOptionsController(optionsController);
   getEventsTab()->setEventsEditorController(eventsEditorController);
}

ConfigsTabWindow::~ConfigsTabWindow()
{
    delete ui;
}

void ConfigsTabWindow::selectObject(GameObject *gameObject) {
    ui->widget->selectObject(gameObject);
}

void ConfigsTabWindow::changeEvent(QEvent *e)
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

ConfigsGeneralWidget* ConfigsTabWindow::getDadosGeraisTab() {
    return ui->widget->getDadosGeraisTab();
}

ConfigsTilesetWidget* ConfigsTabWindow::getTilesetTab() {
    return ui->widget->getTilesetTab();
}

ConfigsObjectsWidget* ConfigsTabWindow::getObjectTab() {
    return ui->widget->getObjectTab();
}

ConfigsAnimations* ConfigsTabWindow::getAnimationsTab() {
    return ui->widget->getAnimationsTab();
}

ConfigsBackgrounds* ConfigsTabWindow::getBackgroundsTab() {
    return ui->widget->getBackgroundsTab();
}

EventsWidget* ConfigsTabWindow::getEventsTab() {
    return ui->widget->getEventsTab();
}

void ConfigsTabWindow::on_pushButton_pressed()
{
    this->accept();
}
