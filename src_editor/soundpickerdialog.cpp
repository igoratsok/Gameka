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



#include "soundpickerdialog.h"
#include "ui_soundpickerdialog.h"

SoundPickerDialog::SoundPickerDialog(int tipo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoundPickerDialog)
{
    ui->setupUi(this);
    setWindowTitle(QString("Escolher som/musica."));

    populaListaMusica();
    populaListaSom();
    selectedMusicFile = std::string("");
    selectedSoundFile = std::string("");

    if(tipo == MUSICA) {
        ui->tabWidget->setCurrentIndex(MUSICA);
        ui->tab_sound->setEnabled(false);
        ui->tabWidget->removeTab(SOM);
    } else {
        ui->tabWidget->setCurrentIndex(SOM);
        ui->tab_music->setEnabled(false);
        ui->tabWidget->removeTab(MUSICA);
    }

    this->type = tipo;
    ok = false;
    sound = NULL;

    currentMusic = NULL;

    ui->verticalSlider->setVisible(false);
}

SoundPickerDialog::~SoundPickerDialog()
{
    if(currentMusic != NULL) {
        currentMusic->stop();
        delete currentMusic;
        currentMusic = NULL;
    }
    delete ui;
}


void SoundPickerDialog::populaListaSom() {
    GameData *gameData;
    gameData = GameData::getInstance();

    QDir *dir;
    QStringList files;
    QStringList filters;


    dir = new QDir(gameData->getProjectDirectory().append("/sfx/").c_str());
    filters << "*.wav" << "*.mp3" << "*.gif" << "*.bmp";


    dir->setNameFilters(filters);

    files = dir->entryList();


    ui->listWidgetSound->clear();
    for(QStringList::Iterator it = files.begin(); it != files.end(); ++it) {
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(*it);
        ui->listWidgetSound->addItem(newItem);
    }
}

void SoundPickerDialog::populaListaMusica() {
    GameData *gameData;
    gameData = GameData::getInstance();

    QDir *dir;
    QStringList files;
    QStringList filters;


    dir = new QDir(gameData->getProjectDirectory().append("/musics/").c_str());
    filters << "*.wav" << "*.mp3" << "*.gif" << "*.bmp";
    std::cout << gameData->getProjectDirectory().append("/musics/");


    dir->setNameFilters(filters);

    files = dir->entryList();


    ui->listWidgetMusic->clear();
    for(QStringList::Iterator it = files.begin(); it != files.end(); ++it) {
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(*it);
        ui->listWidgetMusic->addItem(newItem);
    }
}

/**
  Botão de selecionar
  */
void SoundPickerDialog::on_pushButton_4_clicked()
{
    ok = true;
    this->close();
}

/**
  Botão de importar
  */
void SoundPickerDialog::on_pushButton_5_clicked()
{
    GameData *gameData = GameData::getInstance();
    QStringList fileNames;


    fileNames = QFileDialog::getOpenFileNames(this, tr("Importar Musica"), "", tr("(*.wav *.mp3)"));


    for(QStringList::Iterator it = fileNames.begin(); it != fileNames.end(); ++it) {
        QString fileName = *it;

        if(!fileName.isEmpty()) {
            int posicaoUltimaBarra;

            posicaoUltimaBarra = fileName.toStdString().find_last_of("/");

            if(posicaoUltimaBarra == -1) {
                posicaoUltimaBarra = fileName.toStdString().find_last_of("\\");
            }

            std::string nome_arq = fileName.toStdString().substr(posicaoUltimaBarra);

            std::string diretorio;

            switch(type) {
            case 0:
                diretorio = gameData->getProjectDirectory().append("/musics/");
                break;

            case 1:
                diretorio = gameData->getProjectDirectory().append("/sfx/");

                break;
            }

            diretorio.append(nome_arq);

            QFile *file = new QFile(fileName);
            file->copy(diretorio.c_str());

            switch(type) {
            case 0:
                populaListaMusica();
                break;

            case 1:
                populaListaSom();
                break;
            }


        }
    }
}

/**
  Botão de cancelar
  */
void SoundPickerDialog::on_pushButton_6_clicked()
{

    this->close();
}

/**
  Botão de tocar
  */
void SoundPickerDialog::on_pushButton_clicked()
{
    GameData *gameData = GameData::getInstance();

    std::string diretorio;
    switch(type) {
    case MUSICA:
        diretorio = gameData->getProjectDirectory().append("/musics/");
        if(ui->listWidgetMusic->currentItem() != NULL) {
            diretorio.append(ui->listWidgetMusic->currentItem()->text().toStdString());
        }

        if(currentMusic != NULL) {
            currentMusic->stop();
            delete currentMusic;
        }

        currentMusic = new Music(&diretorio, Music::MUSICA);
        break;

    case SOM:
        diretorio = gameData->getProjectDirectory().append("/sfx/");
        if(ui->listWidgetSound->currentItem() != NULL) {
            diretorio.append(ui->listWidgetSound->currentItem()->text().toStdString());
        }

        if(currentMusic != NULL) {
            currentMusic->stop();
            delete currentMusic;
        }

        currentMusic = new Music(&diretorio, Music::SOM);
        break;
    }


    // TODO: tocar o som do diretorio aqui

    currentMusic->play(0);
}

/**
  Botão de pausar
  */
void SoundPickerDialog::on_pushButton_3_clicked()
{
    if(currentMusic != NULL) {
        currentMusic->pauseResume();
    }
}

/**
  Botão de parar
  */
void SoundPickerDialog::on_pushButton_2_clicked()
{
    if(currentMusic != NULL) {
        currentMusic->stop();
    }
}

void SoundPickerDialog::on_listWidgetMusic_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    selectedMusicFile = current->text().toStdString();
}

std::string SoundPickerDialog::getSelectedFile() {
    switch(type) {
    case MUSICA:
        return selectedMusicFile;
        break;

    case SOM:
        return selectedSoundFile;
        break;
    }

    return selectedMusicFile;
}

void SoundPickerDialog::on_listWidgetSound_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    selectedSoundFile = current->text().toStdString();
}

bool SoundPickerDialog::okPressed() {
    return ok;
}
