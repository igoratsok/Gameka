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


#include "configsnewobjectwindow.h"
#include "ui_configsnewobjectwindow.h"

ConfigsNewObjectWindow::ConfigsNewObjectWindow(OptionsController *optionsController, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigsNewObjectWindow), optionsController(optionsController)
{
    ui->setupUi(this);
}

ConfigsNewObjectWindow::~ConfigsNewObjectWindow()
{
    delete ui;
}

void ConfigsNewObjectWindow::changeEvent(QEvent *e)
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

void ConfigsNewObjectWindow::on_buttonBox_accepted()
{
    /* validação */
    if(ui->lineEditName->text().isEmpty()) {
        MessageBoxes::showMessageBox(QString::fromUtf8(tr("Necessita digitar o nome.").toStdString().c_str()));

        this->show();
    } else {
        optionsController->addObject(ui->lineEditName->text().toStdString(), ui->comboTipo->currentIndex());
    }
}
