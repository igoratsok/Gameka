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


#ifndef SOUNDPICKERDIALOG_H
#define SOUNDPICKERDIALOG_H

#include <iostream>
#include <stdlib.h>

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QSound>


#include "gamedata.h"
#include "music.h"

class GameData;
class Music;

namespace Ui {
    class SoundPickerDialog;
}

/**
 * @brief Janela para se escolher um som ou música, e também para importar novos.
 *
 */
class SoundPickerDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param tipo Tipo: \n
                        - 0 (MUSICA): música, busca os arquivos na pasta musics;
                        - 1 (SOM): efeito sonoro, busca os arquivos na pasta sfx;
     * @param parent
     */
    explicit SoundPickerDialog(int tipo, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~SoundPickerDialog();

    /**
     * @brief Popula a lista de músicas de acordo com os arquivos na pasta musics do projeto.
     *
     */
    void populaListaMusica();
    /**
     * @brief Popula a lista de sons de acordo com os arquivos na pasta sfx do projeto.
     *
     */
    void populaListaSom();



    /**
     * @brief Obtém a música selecionada.
     *
     */
    std::string getSelectedFile();
    /**
     * @brief Se o botão OK foi pressionado.
     *
     */
    bool okPressed();

    int type; /**< Tipo: \n
                        - 0 (MÚSICA): música;
                        - 1 (SOM): efeito sonoro. */
    bool ok; /**< Se OK foi pressionado. */
    static const int MUSICA = 0; /**< Tipo de música, a ser usado na variável type. */
    static const int SOM = 1; /**< Tipo de som, a ser usado na variável type; */

    QSound *sound; /**< Som. */
    Music *currentMusic; /**< Música. */

private:
    Ui::SoundPickerDialog *ui; /**<  */
    std::string selectedSoundFile; /**< Nome do arquivo de som selecionado. */
    std::string selectedMusicFile; /**< Nome do arquivo de música selecionado. */

private slots:
    /**
     * @brief
     *
     * @param current
     * @param previous
     */
    void on_listWidgetSound_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    /**
     * @brief
     *
     * @param current
     * @param previous
     */
    void on_listWidgetMusic_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    /**
     * @brief
     *
     */
    void on_pushButton_2_clicked();
    /**
     * @brief
     *
     */
    void on_pushButton_3_clicked();
    /**
     * @brief
     *
     */
    void on_pushButton_clicked();
    /**
     * @brief
     *
     */
    void on_pushButton_6_clicked();
    /**
     * @brief
     *
     */
    void on_pushButton_5_clicked();
    /**
     * @brief
     *
     */
    void on_pushButton_4_clicked();
};

#endif // SOUNDPICKERDIALOG_H
