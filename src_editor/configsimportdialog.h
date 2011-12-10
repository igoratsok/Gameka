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


#ifndef CONFIGSIMPORTDIALOG_H
#define CONFIGSIMPORTDIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QListWidgetItem>

#include "gamedata.h"
#include "messageboxes.h"
#include "optionscontroller.h"

class GameData;
class MessageBoxes;
class OptionsController;


namespace Ui {
    class ConfigsImportDialog;
}

/**
 * @brief Tela de importação de imagens. Pode ser usada para importar
 * Tilesets, telas de título, animações, sprites, fundos ou camadas.
 * Dependendo do tipo, a importação é feita automaticamente via
 * controladora de opções. No tipo IMPORT_RETURN_EXEC,
 * esta janela retorna uma string com o caminho para
 * o recurso escolhido.
 *
 */
class ConfigsImportDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor padrão.
     *
     * @param parent
     */
    explicit ConfigsImportDialog(QWidget *parent = 0);
    /**
     * @brief Construtor que leva em consideração o tipo de importação.
     *
     * @param optionsController a controladora de opções
     * @param importType o tipo de importação. Usar as constantes IMPORT_x
     *        desta classe.
     * @param parent
     */
    explicit ConfigsImportDialog(OptionsController *optionsController, int importType, QWidget *parent = 0);


    /**
     * @brief Construtor que leva em consideração o tipo de importação e uma opção a mais.
     *
     * @param optionsController a controladora de opções
     * @param importType o tipo de importação. Usar as constantes IMPORT_x
     *        desta classe.
     * @param importOption usado para importar telas, sendo: \n
                - 0: tela de título;
                - 1: tela de opções;
                - 2: tela de Game Over
     * @param parent
     */
    explicit ConfigsImportDialog(OptionsController *optionsController, int importType, int importOption, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsImportDialog();

    /**
     * @brief Popula lista de recursos de acordo com o tipo de importação fornecido no construtor.
     *
     */
    void populaLista();

    /**
     * @brief Obtém a string do recurso desejado.
     *
     */
    std::string *getReturnString();

    int importType; /**< tipo de importação. Usar constantes IMPORT_x da classe.*/
    int importOption; /**< opção de importação. Se importType = 1: \n
                    - 0: tela de título;
                    - 1: tela de opções;
                    - 2: tela de Game Over */

    int animationImportPattern; /**< Qual tipo de animação: \n
                                - 0: nenhuma;
                                - 1: RPG Maker VX */

    static const int IMPORT_TILESETS = 0; /**< Importação de Tilesets, para usar em importType. */
    static const int IMPORT_TITLESCREENS = 1; /**< Importação de telas de título, para usar em importType. */
    static const int IMPORT_ANIMATIONS = 2; /**< Importação de animações, para usar em importType. */
    static const int IMPORT_SPRITE = 3; /**< Importação de sprites, para usar em importType. */
    static const int IMPORT_BACKGROUND = 4; /**< Impotação de fundos, para usar em importType. */
    static const int IMPORT_LAYER = 5; /**< Importação de camadas, para usar em importType. */
    static const int IMPORT_RETURN_EXEC = 6; /**< Importação a ser retornada uma string, para usar em importType. */
    static const int REIMPORT_ANIMATION = 7; /**< Reimportação a ser retornada uma string, para usar em importType. */

private:
    Ui::ConfigsImportDialog *ui; /**<  */
    OptionsController *optionsController; /**<  */

    std::string *returnString; /**<  */

private slots:
    /**
     * @brief Evento ativado quando item da combo do tipo de animação for escolhido.
     *
     * @param index
     */
    void on_comboBoxTipo_currentIndexChanged(int index);
    /**
     * @brief Evento ativado quando item da combo de recurso atual for escolhido.
     *
     * @param current
     * @param previous
     */
    void on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    /**
     * @brief
     *
     */
    void on_botaoCancelar_clicked();
    /**
     * @brief
     *
     */
    void on_botaoImportar_clicked();
    /**
     * @brief
     *
     */
    void on_botaoSelecionar_clicked();
};

#endif // CONFIGSIMPORTDIALOG_H
