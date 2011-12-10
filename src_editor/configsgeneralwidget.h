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


#ifndef CONFIGSGENERALWIDGET_H
#define CONFIGSGENERALWIDGET_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <QWidget>
#include <iostream>
#include <vector>

#include "optionscontroller.h"
#include "gamedata.h"
#include "configsimportdialog.h"
#include "editorconstants.h"
#include "map.h"
#include "soundpickerdialog.h"

class OptionsController;
class GameData;
class ConfigsImportDialog;
class EditorConstants;
class Map;
class SoundPickerDialog;

namespace Ui {
    class ConfigsGeneralWidget;
}

/**
 * @brief Aba de configurações de dados iniciais.
 *
 */
class ConfigsGeneralWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param parent
     */
    ConfigsGeneralWidget(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsGeneralWidget();

    /**
     * @brief Fornece a controladora de opções, para chamadas na camada de negócio.
     *
     * @param optionsController
     */
    void setOptionsController(OptionsController *optionsController);


    /**
     * @brief Preenche dados gerais.
     *
     */
    void preencheDadosGerais();


    /**
     * @brief
     *
     */
    void preencheEditsResolucao();


    /**
     * @brief Preenche os line edits de resolução.
     *
     */
    void preencheEditsMusicas();


    /**
     * @brief Preenche o index atual do combo do mapa inicial.
     *
     */
    void preencheCurrentIndexComboInicialMap();


    /**
     * @brief Atualiza as imagens nas telas.
     *
     */
    void atualizaImagensTelas();


    /**
     * @brief Atualiza visualização de editores de resolução.
     *
     */
    void atualizaVisualizacaoEditsResolucao();


    /**
     * @brief Popula a combo do mapa inicial.
     *
     */
    void populaComboMapaInicial();


    /**
     * @brief Função utilizada pela anterior para percorrer a árvore de mapas e popular.
     *
     * @param mapList
     * @param prefix
     */
    void populaComboMapaInicialPercorreArvore(std::vector<Map*> *mapList, std::string prefix);


    /**
     * @brief Preenche os grupos sobre configurações de perda de jogo.
     *
     */
    void populaGroupsDeath();


    /**
     * @brief habilita os campos sobre configurações de perda de jogo.
     *
     */
    void habilitaCamposDeath();

    bool ativaMudancaComboMapaInicial; /**< Mecanismo para ativação da mudança da combo do mapa inicial */

protected:
    /**
     * @brief
     *
     * @param e
     */
    void changeEvent(QEvent *e);

private:
    Ui::ConfigsGeneralWidget *ui; /**<  */
    OptionsController *optionsController; /**< */

private slots:
    /**
     * @brief Evento ao pressionar o botão de escolher música da tela de Game Over.
     * Utiliza a SoundPickerDialog para obter a música adeaquada.
     *
     * @see SoundPickerDialog
     */
    void on_toolButtonMusicaTelaGameOver_clicked();


    /**
     * @brief Evento ao pressionar o botão de escolher música da tela de Opções.
     * Utiliza a SoundPickerDialog para obter a música adeaquada.
     *
     * @see SoundPickerDialog
     */
    void on_toolButtonMusicaTelaOpcoes_clicked();


    /**
     * @brief Evento ao pressionar o botão de escolher música da tela Inicial.
     * Utiliza a SoundPickerDialog para obter a música adeaquada.
     *
     * @see SoundPickerDialog
     */
    void on_toolButtonMusicaTelaInicial_clicked();

    /**
     * @brief Evento ativado se a a combo do mapa inicial for mudada.
     * Muda o valor do identificador do mapa inicial na GameData de acordo.
     *
     * @param index
     */
    void on_comboInitialMap_currentIndexChanged(int index);


    /**
     * @brief Evento de atualização de valor.
     *
     * @param QString
     */
    void on_editResolutionHeight_textChanged(QString );


    /**
     * @brief Evento de atualização de valor.
     *
     * @param QString
     */
    void on_editResolutionWidth_textChanged(QString );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param QString
     */
    void on_editGameName_textChanged(QString );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboResolution_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     */
    void on_buttonAlterarTelaGameOver_clicked();
    /**
     * @brief Evento de atualização de valor.
     *
     */
    void on_buttonAlterarTelaOpcoes_clicked();
    /**
     * @brief Evento de atualização de valor.
     *
     */
    void on_buttonAlterarTelaInicial_clicked();
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_radioButtonDieResetMap_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_radioButtonDieResetGame_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxDieLooseLife_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxLives_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_radioButtonGoverResetMap_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_radioButtonGoverResetGame_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_radioButtonGoverTurnoffGame_toggled(bool checked);
};

#endif // CONFIGSGENERALWIDGET_H
