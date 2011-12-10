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


#ifndef NEWPROJECTWINDOW_H
#define NEWPROJECTWINDOW_H

#include <QDialog>
#include <stdlib.h>

#include "maincontroller.h"
#include "messageboxes.h"

class MainController;
class MessageBoxes;

namespace Ui {
    class NewProjectWindow;
}

/**
 * @brief Janela de novo projeto.
 *
 */
class NewProjectWindow : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param parent
     * @param mainController controladora principal, para acesso a camada de negócio.
     */
    NewProjectWindow(QWidget *parent = 0, QString projectsDirectory = "", MainController *mainController = NULL);
    /**
     * @brief
     *
     */
    ~NewProjectWindow();

protected:
    /**
     * @brief
     *
     * @param e
     */
    void changeEvent(QEvent *e);

private:
    Ui::NewProjectWindow *ui; /**<  */
    MainController *mainController; /**<  */

    bool textNomeJogoChanged; /**< Se o nome do jogo foi mudado. */
    bool textNomePastaChanged; /**< Se o nome da pasta foi mudado */
    QString projectsDirectory;

private slots:
    /**
     * @brief
     *
     * @param QString
     */
    void on_textNomeJogo_textEdited(QString );
    /**
     * @brief
     *
     * @param QString
     */
    void on_textNomePasta_textEdited(QString );
    /**
     * @brief
     *
     * @param QString
     */
    void on_textNomeJogo_textChanged(QString );
    /**
     * @brief
     *
     * @param QString
     */
    void on_textNomePasta_textChanged(QString );
    /**
     * @brief
     *
     */
    void on_buttonBox_rejected();
    /**
     * @brief
     *
     */
    void on_buttonBox_accepted();
};

#endif // NEWPROJECTWINDOW_H
