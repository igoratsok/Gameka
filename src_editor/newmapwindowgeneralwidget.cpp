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



#include "newmapwindowgeneralwidget.h"
#include "ui_newmapwindowgeneralwidget.h"

NewMapWindowGeneralWidget::NewMapWindowGeneralWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewMapWindowGeneralWidget)
{
    ui->setupUi(this);

    ui->labelLoop->setVisible(false);
    ui->loop_combobox->setVisible(false);


}

void NewMapWindowGeneralWidget::preencheDados() {
    ui->nome_mapa->setText(QString(map->mapName.c_str()));
    ui->tamanho_height->setValue(map->height);
    ui->tamanho_width->setValue(map->width);
    ui->musica_input->setText(QString(map->music.c_str()));
    ui->som_input->setText(QString(map->sound.c_str()));

    if(map->background != NULL) {
        ui->lineEditBackground->setText(QString(map->background->name.c_str()));
    }

}

NewMapWindowGeneralWidget::~NewMapWindowGeneralWidget()
{
    delete ui;
}

void NewMapWindowGeneralWidget::changeEvent(QEvent *e)
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

QString NewMapWindowGeneralWidget::getNomeMapa() {
    return ui->nome_mapa->text();
}

int NewMapWindowGeneralWidget::getTamanhoWidth() {
    return ui->tamanho_width->value();
}

int NewMapWindowGeneralWidget::getTamanhoHeight() {
    return ui->tamanho_height->value();
}

void NewMapWindowGeneralWidget::on_toolButtonMusic_clicked()
{
    SoundPickerDialog *soundPickerDialog = new SoundPickerDialog(SoundPickerDialog::MUSICA, this);
    soundPickerDialog->exec();

    if(soundPickerDialog->okPressed()) {
        ui->musica_input->setText(QString(soundPickerDialog->getSelectedFile().c_str()));
        map->music = soundPickerDialog->getSelectedFile();
    }


    delete soundPickerDialog;
}

void NewMapWindowGeneralWidget::on_toolButtonSound_clicked()
{
    SoundPickerDialog *soundPickerDialog = new SoundPickerDialog(SoundPickerDialog::SOM, this);
    soundPickerDialog->exec();

    if(soundPickerDialog->okPressed()) {
        ui->som_input->setText(QString(soundPickerDialog->getSelectedFile().c_str()));
        map->sound = soundPickerDialog->getSelectedFile();
    }

}

void NewMapWindowGeneralWidget::on_toolButtonBackgroundChooser_pressed()
{
    if(mapEditorController->getBackgroundList()->empty()) {
        MessageBoxes::showMessageBox(QString::fromUtf8(tr("Nao existe nenhum fundo cadastrado.").toStdString().c_str()));
    } else {
        BackgroundPickerDialog *backgroundPickerDialog;
        backgroundPickerDialog = new BackgroundPickerDialog(mapEditorController, this);
        backgroundPickerDialog->setWindowTitle(tr("Selecionar fundo"));

        Background *bg = backgroundPickerDialog->exec();

        if(bg != NULL) {
            ui->lineEditBackground->setText(QString(bg->name.c_str()));
            map->background = bg;
        }
    }
}

void NewMapWindowGeneralWidget::on_toolButtonRemoveBackground_pressed()
{
    if(MessageBoxes::showConfirmBox(std::string(tr("Tem certeza que deseja remover o fundo do mapa?").toStdString().c_str()))) {
        map->background = NULL;
        ui->lineEditBackground->setText(QString(""));
    }

}

void NewMapWindowGeneralWidget::on_toolButtonRemoveMusic_pressed()
{
    if(MessageBoxes::showConfirmBox(std::string(tr("Tem certeza que deseja remover a musica do mapa?").toStdString().c_str()))) {
        map->music = std::string("");
        ui->musica_input->setText(QString(""));
    }
}

void NewMapWindowGeneralWidget::on_toolButtonRemoveSound_pressed()
{
    if(MessageBoxes::showConfirmBox(std::string(tr("Tem certeza que deseja remover o som do mapa?").toStdString().c_str()))) {
        map->sound = std::string("");
        ui->som_input->setText(QString(""));
    }
}

void NewMapWindowGeneralWidget::on_pushButtonDialogue_pressed()
{
    mapEditorController->openNewDialogueDialog(map);
}
