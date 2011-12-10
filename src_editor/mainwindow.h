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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdlib.h>

#include <QtGui/QMainWindow>
#include <QDesktopWidget>
#include <QRect>
#include <QPoint>
#include <QDesktopServices>
#include <QUrl>

#include <QFileDialog>

#include "maincontroller.h"
#include "mapeditorcontroller.h"
#include "about.h"

class MainController;
class MapEditorController;
class About;

namespace Ui {
    class MainWindow;
}

/**
 * @brief Janela principal do programa.
 *
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param parent
     * @param mainController Controladora principal, para acesso à camada de negócio.
     */
    MainWindow(QWidget *parent = 0, MainController *mainController = NULL);
    /**
     * @brief
     *
     */
    ~MainWindow();

    /**
     * @brief Move a janela para o centro.
     *
     */
    void moveToCenter();
    /**
     * @brief Obtém o widget da janela principal.
     *
     */
    QWidget* getMainWindowWidget();

    /**
     * @brief Habilita os botões principais.
     *
     */
    void enableMainButtons();
    /**
     * @brief Habilita a barra de zoom (ainda não funcionando muito bem).
     *
     */
    void enableZoomBar();

    /**
     * @brief Ativa os ícones dos modos de editor.
     *
     * @param mode
     */
    void setEditorModeIconEnabled(int mode);
    /**
     * @brief Evento ao se fechar a janela. Manda salvar o projeto.
     *
     * @param
     */
    void closeEvent(QCloseEvent *);
    /**
     * @brief Determina o texto da Status Bar.
     *
     * @param text
     */
    void setStatusBarText(QString text);

protected:
    /**
     * @brief
     *
     * @param e
     */
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *m_ui; /**< TODO */
    MainController *mainController; /**< TODO */

private slots:
    /**
     * @brief
     *
     * @param checked
     */
    void on_actionEventMode_triggered(bool checked);
    /**
     * @brief
     *
     * @param checked
     */
    void on_actionObjectMode_triggered(bool checked);
    /**
     * @brief
     *
     * @param checked
     */
    void on_actionMapMode_triggered(bool checked);
    /**
     * @brief
     *
     */
    void on_actionRodar_triggered();
    /**
     * @brief
     *
     */
    void on_actionSalvar_Projeto_triggered();
    /**
     * @brief
     *
     */
    void on_actionAbrir_Projeto_triggered();
    /**
     * @brief
     *
     */
    void on_actionConfiguracoes_triggered();
    /**
     * @brief
     *
     */
    void on_actionSelecaoCirculo_activated();
    /**
     * @brief
     *
     */
    void on_actionSelecionaQuadrado_activated();
    /**
     * @brief
     *
     */
    void on_actionPintaCirculo_activated();
    /**
     * @brief
     *
     */
    void on_actionPintaBloco_activated();
    /**
     * @brief
     *
     */
    void on_actionPintaQuadrado_activated();
    /**
     * @brief
     *
     */
    void on_actionPintaBloco_triggered();
    /**
     * @brief
     *
     */
    void on_actionPintaTile_activated();
    /**
     * @brief
     *
     */
    void on_actionNovo_Projeto_triggered();
    /**
     * @brief
     *
     */
    void on_actionApagaBloco_activated();
    /**
     * @brief
     *
     */
    void on_actionDesfazer_triggered();
    /**
     * @brief
     *
     */
    void on_actionRefazer_triggered();
    /**
     * @brief
     *
     */
    void on_actionAbout_triggered();
    /**
     * @brief
     *
     */
    void on_actionPersonagens_triggered();
    /**
     * @brief
     *
     */
    void on_actionPersonagens_e_monstros_triggered();
    /**
     * @brief
     *
     */
    void on_actionQuestion_rio_01_triggered();
    /**
     * @brief
     *
     */
    void on_actionQuestion_rio_02_triggered();
    /**
     * @brief
     *
     */
    void on_actionQuestion_rio_03_triggered();
    /**
     * @brief
     *
     */
    void on_actionQuestion_rio_4_triggered();
    /**
     * @brief
     *
     * @param position
     */
    void on_horizontalSliderZoom_sliderMoved(int position);
    void on_actionSobre_Qt_triggered();
};

#endif // MAINWINDOW_H
