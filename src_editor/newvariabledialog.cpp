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



#include "newvariabledialog.h"
#include "ui_newvariabledialog.h"

NewVariableDialog::NewVariableDialog(VariableData *variableData, QWidget *parent) :
    QDialog(parent),
    variableData(variableData),
    ui(new Ui::NewVariableDialog)
{
    ui->setupUi(this);

    habilitaElementos();
    preencheCampos();

}

NewVariableDialog::~NewVariableDialog()
{
    delete ui;
}

VariableData* NewVariableDialog::exec() {
    QDialog::exec();


    return variableData;
}

void NewVariableDialog::habilitaElementos() {
    if(ui->comboBoxVariableType->currentIndex() == 0) {
        ui->spinBoxValue->setVisible(true);
        ui->comboBoxBooleanValue->setVisible(false);
    } else {
        ui->spinBoxValue->setVisible(false);
        ui->comboBoxBooleanValue->setVisible(true);
    }
}

void NewVariableDialog::preencheCampos() {

    if(variableData != NULL) {
        ui->lineEditVariableName->setText(QString(variableData->name.c_str()));
        ui->comboBoxVariableType->setCurrentIndex(variableData->type);
        if(variableData->type == VariableData::TYPE_NUMBER) {
            ui->spinBoxValue->setValue(variableData->value);
        } else {
            ui->comboBoxBooleanValue->setCurrentIndex(!((int) variableData->value));
        }


    }

}

void NewVariableDialog::on_buttonBox_accepted()
{
    if(ui->lineEditVariableName->text().isEmpty()) {
        MessageBoxes::showMessageBox(QString::fromUtf8(tr("É necessário que a variável tenha um nome!").toStdString().c_str()));
        return;
    }

    if(variableData == NULL) {
        variableData = new VariableData();
    }

    variableData->name =ui->lineEditVariableName->text().toStdString();
    variableData->type = ui->comboBoxVariableType->currentIndex();

    if(variableData->type == VariableData::TYPE_NUMBER) {
        variableData->value = ui->spinBoxValue->value();
    } else {
        variableData->value = !ui->comboBoxBooleanValue->currentIndex();
    }


    accept();
}



void NewVariableDialog::on_comboBoxVariableType_currentIndexChanged(int index)
{
    habilitaElementos();
}

void NewVariableDialog::on_buttonBox_rejected()
{
    reject();
}
