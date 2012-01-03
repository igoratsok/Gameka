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



#include "newprojectwindow.h"
#include "ui_newprojectwindow.h"

NewProjectWindow::NewProjectWindow(QWidget *parent, QString projectsDirectory, MainController *mainController) :
    QDialog(parent),
    ui(new Ui::NewProjectWindow)
{
    ui->setupUi(this);
    this->mainController = mainController;
    this->projectsDirectory = projectsDirectory;

    textNomeJogoChanged = false;
    textNomePastaChanged = false;

    ui->groupBoxProjectFolder->setVisible(false);
}

NewProjectWindow::~NewProjectWindow()
{
    delete ui;
}

void NewProjectWindow::changeEvent(QEvent *e)
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

void NewProjectWindow::on_buttonBox_accepted()
{
    if(ui->textNomeJogo->text().isEmpty() || ui->textNomePasta->text().isEmpty()) {
        MessageBoxes::showMessageBox(QString::fromUtf8(tr("Preencha todos os campos.").toStdString().c_str()));
        this->show();
    } else {
        if(QDir(QString(projectsDirectory).append("/").append(ui->textNomePasta->text())).exists()) {
            MessageBoxes::showMessageBox(QString::fromUtf8(tr("Pasta de projeto já existe.").toStdString().c_str()));
            this->show();
            return;
        }
        mainController->openNewProject(ui->textNomeJogo->text().toStdString(), ui->textNomePasta->text().toStdString(), projectsDirectory, ui->comboBox->currentIndex());
    }

}

void NewProjectWindow::on_buttonBox_rejected()
{

}

void NewProjectWindow::on_textNomePasta_textChanged(QString )
{
    if(!textNomeJogoChanged) {
        ui->textNomeJogo->setText(ui->textNomePasta->text());
    }
}

void NewProjectWindow::on_textNomeJogo_textChanged(QString )
{
    if(!textNomePastaChanged) {
        ui->textNomePasta->setText(ui->textNomeJogo->text());
    }
}

void NewProjectWindow::on_textNomePasta_textEdited(QString )
{
    textNomePastaChanged = true;
}

void NewProjectWindow::on_textNomeJogo_textEdited(QString )
{
    textNomeJogoChanged = true;
}
