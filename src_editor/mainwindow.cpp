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



#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, MainController *mainController) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_ui->actionMapMode->setChecked(true);
    m_ui->actionPintaTile->setChecked(true);
    this->mainController = mainController;


    // PARA ATIVAR O ZOOM DO MAPA, RETIRAR AS LINHAS ABAIXO
    m_ui->horizontalSliderZoom->setVisible(false);
    m_ui->label_3->setVisible(false);

    m_ui->label->setVisible(false);
    m_ui->line->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::moveToCenter()
{
    QDesktopWidget desktopWidget;
    QPoint center;


    center = desktopWidget.availableGeometry(desktopWidget.primaryScreen()).center();
    center.setX(center.x() - (this->width()/2));
    center.setY(center.y() - (this->height()/2));
    move(center);
}

void MainWindow::setEditorModeIconEnabled(int mode) {
    if(mode == MapEditorController::MODE_MAP) {
        m_ui->actionMapMode->setChecked(true);
        m_ui->actionObjectMode->setChecked(false);
    } else if(mode == MapEditorController::MODE_OBJECT) {
        m_ui->actionMapMode->setChecked(false);
        m_ui->actionObjectMode->setChecked(true);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    mainController->saveProjectAtExitGameka(event);


    return;
}

void MainWindow::enableMainButtons()
{
    m_ui->actionConfiguracoes->setEnabled(true);
    m_ui->actionDesfazer->setEnabled(true);
    m_ui->actionPintaBloco->setEnabled(true);
    m_ui->actionApagaBloco->setEnabled(true);
    m_ui->actionPintaCirculo->setEnabled(true);
    m_ui->actionPintaQuadrado->setEnabled(true);
    m_ui->actionPintaTile->setEnabled(true);
    m_ui->actionRefazer->setEnabled(true);
    m_ui->actionRodar->setEnabled(true);
    m_ui->actionSalvar_Projeto->setEnabled(true);
    m_ui->actionSelecaoCirculo->setEnabled(true);
    m_ui->actionSelecionaQuadrado->setEnabled(true);
    m_ui->actionMapMode->setEnabled(true);
    m_ui->actionObjectMode->setEnabled(true);
    m_ui->actionEventMode->setEnabled(true);
}

void MainWindow::enableZoomBar() {
    m_ui->horizontalSliderZoom->setEnabled(true);
}

QWidget* MainWindow::getMainWindowWidget()
{
    return m_ui->mainWindowWidget;
}

void MainWindow::on_actionNovo_Projeto_triggered()
{
    mainController->reopenWelcomeScreen(true);
}

void MainWindow::on_actionPintaTile_activated()
{
    m_ui->actionPintaTile->setChecked(true);
    m_ui->actionApagaBloco->setChecked(false);
    m_ui->actionPintaBloco->setChecked(false);
    m_ui->actionPintaCirculo->setChecked(false);
    m_ui->actionPintaQuadrado->setChecked(false);
    m_ui->actionSelecaoCirculo->setChecked(false);
    m_ui->actionSelecionaQuadrado->setChecked(false);

    mainController->setEditorDrawMode(MapEditorController::DRAW_MODE_PENCIL);
}

void MainWindow::on_actionPintaQuadrado_activated()
{
    m_ui->actionPintaTile->setChecked(false);
    m_ui->actionApagaBloco->setChecked(false);
    m_ui->actionPintaBloco->setChecked(false);
    m_ui->actionPintaCirculo->setChecked(false);
    m_ui->actionPintaQuadrado->setChecked(true);
    m_ui->actionSelecaoCirculo->setChecked(false);
    m_ui->actionSelecionaQuadrado->setChecked(false);

    mainController->setEditorDrawMode(MapEditorController::DRAW_MODE_SQUARE);
}

void MainWindow::on_actionPintaBloco_activated()
{
    m_ui->actionPintaTile->setChecked(false);
    m_ui->actionApagaBloco->setChecked(false);
    m_ui->actionPintaBloco->setChecked(true);
    m_ui->actionPintaCirculo->setChecked(false);
    m_ui->actionPintaQuadrado->setChecked(false);
    m_ui->actionSelecaoCirculo->setChecked(false);
    m_ui->actionSelecionaQuadrado->setChecked(false);

    mainController->setEditorDrawMode(MapEditorController::DRAW_MODE_PAINT);
}

void MainWindow::on_actionPintaCirculo_activated()
{
    m_ui->actionPintaCirculo->setChecked(true);
    m_ui->actionApagaBloco->setChecked(false);
    m_ui->actionPintaTile->setChecked(false);
    m_ui->actionPintaBloco->setChecked(false);
    m_ui->actionPintaQuadrado->setChecked(false);
    m_ui->actionSelecaoCirculo->setChecked(false);
    m_ui->actionSelecionaQuadrado->setChecked(false);

    mainController->setEditorDrawMode(MapEditorController::DRAW_MODE_CIRCLE);
}

void MainWindow::on_actionSelecionaQuadrado_activated()
{
    m_ui->actionSelecionaQuadrado->setChecked(true);
    m_ui->actionApagaBloco->setChecked(false);
    m_ui->actionPintaTile->setChecked(false);
    m_ui->actionPintaBloco->setChecked(false);
    m_ui->actionPintaCirculo->setChecked(false);
    m_ui->actionPintaQuadrado->setChecked(false);
    m_ui->actionSelecaoCirculo->setChecked(false);

    mainController->setEditorDrawMode(MapEditorController::DRAW_MODE_SELECT_SQUARE);
}

void MainWindow::on_actionSelecaoCirculo_activated()
{
    m_ui->actionSelecaoCirculo->setChecked(true);
    m_ui->actionApagaBloco->setChecked(false);
    m_ui->actionPintaTile->setChecked(false);
    m_ui->actionPintaBloco->setChecked(false);
    m_ui->actionPintaCirculo->setChecked(false);
    m_ui->actionPintaQuadrado->setChecked(false);
    m_ui->actionSelecionaQuadrado->setChecked(false);

    mainController->setEditorDrawMode(MapEditorController::DRAW_MODE_SELECT_CIRCLE);
}

void MainWindow::on_actionApagaBloco_activated()
{
    m_ui->actionApagaBloco->setChecked(true);
    m_ui->actionSelecaoCirculo->setChecked(false);
    m_ui->actionPintaTile->setChecked(false);
    m_ui->actionPintaBloco->setChecked(false);
    m_ui->actionPintaCirculo->setChecked(false);
    m_ui->actionPintaQuadrado->setChecked(false);
    m_ui->actionSelecionaQuadrado->setChecked(false);

    mainController->setEditorDrawMode(MapEditorController::DRAW_MODE_ERASER);
}


void MainWindow::on_actionPintaBloco_triggered()
{

}

void MainWindow::on_actionConfiguracoes_triggered()
{
    mainController->openConfigsTabWindow();
}

void MainWindow::on_actionAbrir_Projeto_triggered()
{
    mainController->reopenWelcomeScreen(false);
}

void MainWindow::on_actionSalvar_Projeto_triggered()
{
    mainController->saveProject();
}

void MainWindow::on_actionRodar_triggered()
{
    mainController->runRuntime();
}

void MainWindow::on_actionMapMode_triggered(bool checked)
{
    m_ui->actionMapMode->setChecked(true);
    m_ui->actionObjectMode->setChecked(false);
    m_ui->actionEventMode->setChecked(false);
    mainController->setEditorMode(MapEditorController::MODE_MAP);
}

void MainWindow::on_actionObjectMode_triggered(bool checked)
{
    m_ui->actionMapMode->setChecked(false);
    m_ui->actionObjectMode->setChecked(true);
    m_ui->actionEventMode->setChecked(false);
    mainController->setEditorMode(MapEditorController::MODE_OBJECT);

}


void MainWindow::on_actionEventMode_triggered(bool checked)
{
    m_ui->actionMapMode->setChecked(false);
    m_ui->actionObjectMode->setChecked(false);
    m_ui->actionEventMode->setChecked(true);
    mainController->setEditorMode(MapEditorController::MODE_EVENT);
}


void MainWindow::on_actionDesfazer_triggered()
{
    mainController->editorUndo();
}

void MainWindow::on_actionRefazer_triggered()
{
    mainController->editorRedo();
}

void MainWindow::on_actionAbout_triggered()
{
    About *about = new About();
    about->setWindowTitle(QString::fromUtf8("Sobre o Gameka"));

    about->exec();

    delete about;
}

void MainWindow::on_actionPersonagens_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("http://translate.google.com/translate?sl=ja&tl=pt&js=n&prev=_t&hl=en&ie=UTF-8&layout=2&eotf=1&u=http%3A%2F%2Fwww.famitsu.com%2Ffreegame%2Ftool%2Fchibi%2Findex1.html")));

}

void MainWindow::on_actionPersonagens_e_monstros_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("http://translate.google.com/translate?hl=en&sl=ja&tl=pt&u=http%3A%2F%2Fjunkhunt.net%2Fvx%2Fcharachip.shtml")));
}

void MainWindow::on_actionQuestion_rio_01_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("https://spreadsheets1.google.com/spreadsheet/viewform?hl=pt_BR&hl=pt_BR&formkey=dFlQX0hPQ3FTRWVEbnZfaEJfcDVqMHc6MA#gid=0")));
}

void MainWindow::on_actionQuestion_rio_02_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("https://spreadsheets2.google.com/spreadsheet/viewform?hl=pt_BR&hl=pt_BR&formkey=dGtqbGJkV0ViUDJkYXlTRWtmOGM2ZkE6MQ#gid=0")));
}

void MainWindow::on_actionQuestion_rio_03_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("https://spreadsheets3.google.com/spreadsheet/viewform?hl=pt_BR&hl=pt_BR&formkey=dGtyaktmckNuS3JKcUlhZjI2UkN2Snc6MQ#gid=0")));
}

void MainWindow::on_actionQuestion_rio_4_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("https://spreadsheets3.google.com/spreadsheet/viewform?hl=pt_BR&hl=pt_BR&formkey=dEdiSTF2d1pQaEczeDR1c0txb2xnSHc6MQ#gid=0")));
}

void MainWindow::setStatusBarText(QString text) {
    m_ui->statusbar->showMessage(text);
}

void MainWindow::on_horizontalSliderZoom_sliderMoved(int position)
{
    mainController->setEditorZoom(position);
}

void MainWindow::on_actionSobre_Qt_triggered()
{
    QApplication::aboutQt();
}
