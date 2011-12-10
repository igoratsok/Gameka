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


#include "configsgeneralwidget.h"
#include "ui_configsgeneralwidget.h"

ConfigsGeneralWidget::ConfigsGeneralWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigsGeneralWidget)
{
    ui->setupUi(this);
    ui->editResolutionHeight->setValidator(new QIntValidator());
    ui->editResolutionWidth->setValidator(new QIntValidator());
    preencheDadosGerais();
    atualizaImagensTelas();
    atualizaVisualizacaoEditsResolucao();
    preencheEditsResolucao();
    preencheEditsMusicas();

    ativaMudancaComboMapaInicial = false;
    populaComboMapaInicial();
    ativaMudancaComboMapaInicial = true;
    preencheCurrentIndexComboInicialMap();

    populaGroupsDeath();
    habilitaCamposDeath();
}

ConfigsGeneralWidget::~ConfigsGeneralWidget()
{
    delete ui;
}

void ConfigsGeneralWidget::changeEvent(QEvent *e)
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

void ConfigsGeneralWidget::setOptionsController(OptionsController *optionsController) {
    this->optionsController = optionsController;
}

void ConfigsGeneralWidget::atualizaImagensTelas() {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::cout << gameData->getProjectDirectory().append("/images/").append(gameData->gameoverScreenFile) << std::endl;

    QPixmap pixmap1, pixmap2, pixmap3;
    pixmap1 = QPixmap(QString(gameData->getProjectDirectory().append("/images/").append(gameData->titleScreenData.backgroundFile).c_str()));

    ui->labelTelaInicial->setPixmap(pixmap1.scaled(100, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    pixmap2 = QPixmap(QString(gameData->getProjectDirectory().append("/images/").append(gameData->optionsScreenFile).c_str()));

    ui->labelTelaOpcoes->setPixmap(pixmap2.scaled(100, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    pixmap3 = QPixmap(QString(gameData->getProjectDirectory().append("/images/").append(gameData->gameoverScreenFile).c_str()));

    ui->labelTelaGameOver->setPixmap(pixmap3.scaled(100, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ConfigsGeneralWidget::on_buttonAlterarTelaInicial_clicked()
{
    ConfigsImportDialog *newDialog;
    newDialog = new ConfigsImportDialog(optionsController, ConfigsImportDialog::IMPORT_TITLESCREENS, EditorConstants::IMPORT_OPTION_TITLE_SCREEN);
    newDialog->setWindowTitle("Alterar tela inicial");
    newDialog->setModal(true);
    newDialog->show();
}

void ConfigsGeneralWidget::on_buttonAlterarTelaOpcoes_clicked()
{
    ConfigsImportDialog *newDialog;
    newDialog = new ConfigsImportDialog(optionsController, ConfigsImportDialog::IMPORT_TITLESCREENS, EditorConstants::IMPORT_OPTION_OPTION_SCREEN);
    newDialog->setWindowTitle("Alterar tela de opções");
    newDialog->setModal(true);
    newDialog->show();
}

void ConfigsGeneralWidget::on_buttonAlterarTelaGameOver_clicked()
{
    ConfigsImportDialog *newDialog;
    newDialog = new ConfigsImportDialog(optionsController, ConfigsImportDialog::IMPORT_TITLESCREENS, EditorConstants::IMPORT_OPTION_GAME_OVER_SCREEN);
    newDialog->setWindowTitle("Alterar tela de Game Over");
    newDialog->setModal(true);
    newDialog->show();
}

void ConfigsGeneralWidget::atualizaVisualizacaoEditsResolucao() {
    if(ui->comboResolution->currentIndex() == 6) {
        ui->editResolutionHeight->setEnabled(true);
        ui->editResolutionWidth->setEnabled(true);
    } else {
        ui->editResolutionHeight->setEnabled(false);
        ui->editResolutionWidth->setEnabled(false);
    }
}

void ConfigsGeneralWidget::preencheDadosGerais() {
    GameData *gameData = GameData::getInstance();
    ui->editGameName->setText(QString(gameData->gameName->c_str()));

    if(gameData->resWidth == 320 && gameData->resHeight == 240) {
        ui->comboResolution->setCurrentIndex(0);
    } else if(gameData->resWidth == 640 && gameData->resHeight == 480) {
        ui->comboResolution->setCurrentIndex(1);
    } else if(gameData->resWidth == 640 && gameData->resHeight == 400) {
        ui->comboResolution->setCurrentIndex(2);
    } else if(gameData->resWidth == 800 && gameData->resHeight == 600) {
        ui->comboResolution->setCurrentIndex(3);
    } else if(gameData->resWidth == 1024 && gameData->resHeight == 786) {
        ui->comboResolution->setCurrentIndex(4);
    } else if(gameData->resWidth == 1280 && gameData->resHeight == 800) {
        ui->comboResolution->setCurrentIndex(5);
    } else {
        ui->comboResolution->setCurrentIndex(6);


        std::ostringstream resWidth, resHeight;

        resWidth << gameData->resWidth;
        resHeight << gameData->resHeight;

        ui->editResolutionWidth->setText(QString(resWidth.str().c_str()));
        ui->editResolutionHeight->setText(QString(resHeight.str().c_str()));
    }
}

void ConfigsGeneralWidget::preencheEditsResolucao() {
    switch(ui->comboResolution->currentIndex()) {
    case 0:
        ui->editResolutionWidth->setText("320");
        ui->editResolutionHeight->setText("240");
        break;
    case 1:
        ui->editResolutionWidth->setText("640");
        ui->editResolutionHeight->setText("480");
        break;
    case 2:
        ui->editResolutionWidth->setText("640");
        ui->editResolutionHeight->setText("400");
        break;
    case 3:
        ui->editResolutionWidth->setText("800");
        ui->editResolutionHeight->setText("600");
        break;
    case 4:
        ui->editResolutionWidth->setText("1024");
        ui->editResolutionHeight->setText("786");
        break;
    case 5:
        ui->editResolutionWidth->setText("1280");
        ui->editResolutionHeight->setText("800");
        break;
    }
}

void ConfigsGeneralWidget::preencheEditsMusicas() {
    GameData *gameData = GameData::getInstance();
    ui->lineEditMusicaTelaGameOver->setText(QString(gameData->gameOverScreenMusic.c_str()));
    ui->lineEditMusicaTelaInicial->setText(QString(gameData->titleScreenMusic.c_str()));
    std::cout << "Titlescreen Music: " << gameData->titleScreenMusic.c_str() << std::endl;
    ui->lineEditMusicaTelaOpcoes->setText(QString(gameData->optionsScreenMusic.c_str()));
}

void ConfigsGeneralWidget::on_comboResolution_currentIndexChanged(int index)
{
    atualizaVisualizacaoEditsResolucao();
    preencheEditsResolucao();
    optionsController->determinaValorResolucaoCombo(index);

}

void ConfigsGeneralWidget::on_editGameName_textChanged(QString string)
{
    GameData *gameData = GameData::getInstance();
    if(!string.isEmpty()) {
        delete gameData->gameName;
        gameData->gameName = new std::string(string.toStdString().c_str());
    }

}

void ConfigsGeneralWidget::on_editResolutionWidth_textChanged(QString string)
{
    GameData *gameData = GameData::getInstance();
    if(!string.isEmpty()) {
        gameData->resWidth = string.toInt();
    }
}

void ConfigsGeneralWidget::on_editResolutionHeight_textChanged(QString string)
{
    GameData *gameData = GameData::getInstance();
    if(!string.isEmpty()) {
        gameData->resHeight = string.toInt();
    }
}

void ConfigsGeneralWidget::populaComboMapaInicial() {

    ui->comboInitialMap->clear();
    populaComboMapaInicialPercorreArvore(optionsController->getMaplist(), std::string(""));
}

void ConfigsGeneralWidget::populaComboMapaInicialPercorreArvore(std::vector<Map*> *mapList, std::string prefix) {
    for(std::vector<Map*>::iterator it = mapList->begin(); it != mapList->end(); ++it) {
        Map* map = *it;
        if(map->isFolder()) {
            populaComboMapaInicialPercorreArvore(map->filhos, std::string(prefix.c_str()).append(map->mapName).append(" > "));
        } else {
            ui->comboInitialMap->addItem(QString(prefix.c_str()).append(map->mapName.c_str()), QVariant(map->id));
            std::cout << "map-key: " << map->id << std::endl;
        }
    }
}

void ConfigsGeneralWidget::populaGroupsDeath() {
    GameData *gameData = GameData::getInstance();

    switch(gameData->deathAction) {
    case GameData::DEATH_ACTION_RESET_MAP:
        ui->radioButtonDieResetMap->setChecked(true);
        break;
    case GameData::DEATH_ACTION_RESET_GAME:
        ui->radioButtonDieResetGame->setChecked(true);
        break;
    }

    ui->checkBoxDieLooseLife->setChecked(gameData->looseLifes);

    ui->spinBoxLives->setValue(gameData->totalLives);

    switch(gameData->gameOverAction) {
    case GameData::DEATH_ACTION_RESET_MAP:
        ui->radioButtonGoverResetMap->setChecked(true);
        break;
    case GameData::DEATH_ACTION_RESET_GAME:
        ui->radioButtonGoverResetGame->setChecked(true);
        break;
    case GameData::DEATH_ACTION_SHUTDOWN_GAME:
        ui->radioButtonGoverTurnoffGame->setChecked(true);
        break;
    }
}

void ConfigsGeneralWidget::habilitaCamposDeath() {
    ui->spinBoxLives->setEnabled(ui->checkBoxDieLooseLife->isChecked());
    ui->groupBoxIfLooseAllLives->setEnabled(ui->checkBoxDieLooseLife->isChecked());

}

void ConfigsGeneralWidget::preencheCurrentIndexComboInicialMap() {
    GameData *gameData = GameData::getInstance();

    /* procurando na comboInicialMap uma ocorrencia do index gravado
       no GameData */

    int i;
    for(i = 0; i < ui->comboInitialMap->count(); i++) {
        int id = ui->comboInitialMap->itemData(i).toInt();
        if(id == gameData->idFirstMap) {
            ui->comboInitialMap->setCurrentIndex(i);
            break;
        }
    }

    // TODO: fazer ele verificar se um mapa não foi deletado
}

void ConfigsGeneralWidget::on_comboInitialMap_currentIndexChanged(int index)
{
    if(ativaMudancaComboMapaInicial) {
        GameData *gameData = GameData::getInstance();
        int idMapa = ui->comboInitialMap->itemData(index).toInt();
        gameData->idFirstMap = idMapa;
        std::cout << "idMapa: " << idMapa << std::endl;
    }

}

void ConfigsGeneralWidget::on_toolButtonMusicaTelaInicial_clicked()
{
    GameData *gameData = GameData::getInstance();

    SoundPickerDialog *soundPickerDialog = new SoundPickerDialog(SoundPickerDialog::MUSICA, this);
    soundPickerDialog->setWindowTitle(QString::fromUtf8("Música da tela inicial"));
    soundPickerDialog->exec();

    if(soundPickerDialog->okPressed()) {
        ui->lineEditMusicaTelaInicial->setText(QString(soundPickerDialog->getSelectedFile().c_str()));
        gameData->titleScreenMusic = std::string(soundPickerDialog->getSelectedFile().c_str());
    }


    delete soundPickerDialog;
}

void ConfigsGeneralWidget::on_toolButtonMusicaTelaOpcoes_clicked()
{
    GameData *gameData = GameData::getInstance();

    SoundPickerDialog *soundPickerDialog = new SoundPickerDialog(SoundPickerDialog::MUSICA, this);
    soundPickerDialog->setWindowTitle(QString::fromUtf8("Música da tela de opções"));
    soundPickerDialog->exec();

    if(soundPickerDialog->okPressed()) {
        ui->lineEditMusicaTelaOpcoes->setText(QString(soundPickerDialog->getSelectedFile().c_str()));
        gameData->optionsScreenMusic = std::string(soundPickerDialog->getSelectedFile().c_str());
    }


    delete soundPickerDialog;
}

void ConfigsGeneralWidget::on_toolButtonMusicaTelaGameOver_clicked()
{
    GameData *gameData = GameData::getInstance();

    SoundPickerDialog *soundPickerDialog = new SoundPickerDialog(SoundPickerDialog::MUSICA, this);
    soundPickerDialog->setWindowTitle(QString::fromUtf8("Música da tela de Game Over"));
    soundPickerDialog->exec();

    if(soundPickerDialog->okPressed()) {
        ui->lineEditMusicaTelaGameOver->setText(QString(soundPickerDialog->getSelectedFile().c_str()));
        gameData->gameOverScreenMusic = std::string(soundPickerDialog->getSelectedFile().c_str());
    }


    delete soundPickerDialog;
}

void ConfigsGeneralWidget::on_radioButtonDieResetMap_toggled(bool checked)
{
    if(checked) {
        GameData *gameData = GameData::getInstance();
        gameData->deathAction = GameData::DEATH_ACTION_RESET_MAP;
    }
}

void ConfigsGeneralWidget::on_radioButtonDieResetGame_toggled(bool checked)
{
    if(checked) {
        GameData *gameData = GameData::getInstance();
        gameData->deathAction = GameData::DEATH_ACTION_RESET_GAME;
    }
}

void ConfigsGeneralWidget::on_checkBoxDieLooseLife_toggled(bool checked)
{
    GameData *gameData = GameData::getInstance();
    gameData->looseLifes = checked;

    habilitaCamposDeath();
}

void ConfigsGeneralWidget::on_spinBoxLives_valueChanged(int value)
{
    GameData *gameData = GameData::getInstance();
    gameData->totalLives = value;
}

void ConfigsGeneralWidget::on_radioButtonGoverResetMap_toggled(bool checked)
{
    if(checked) {
        GameData *gameData = GameData::getInstance();
        gameData->gameOverAction = GameData::DEATH_ACTION_RESET_MAP;
    }
}

void ConfigsGeneralWidget::on_radioButtonGoverResetGame_toggled(bool checked)
{
    if(checked) {
        GameData *gameData = GameData::getInstance();
        gameData->gameOverAction = GameData::DEATH_ACTION_RESET_GAME;
    }
}

void ConfigsGeneralWidget::on_radioButtonGoverTurnoffGame_toggled(bool checked)
{
    if(checked) {
        GameData *gameData = GameData::getInstance();
        gameData->gameOverAction = GameData::DEATH_ACTION_SHUTDOWN_GAME;
    }
}
