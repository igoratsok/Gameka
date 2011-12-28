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


#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QSplashScreen>
#include <QPixmap>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QProcess>


#include <string>


#include "mapeditorcontroller.h"
#include "optionscontroller.h"
#include "wizardcontroller.h"
#include "eventseditorcontroller.h"
#include "updatemanagercontroller.h"
#include "mainwindow.h"
#include "newprojectwindow.h"
#include "gamedata.h"
#include "datawriter.h"
#include "dataloader.h"
#include "welcomescreen.h"

class MapEditorController;
class OptionsController;
class WizardController;
class EventsEditorController;
class UpdateManagerController;
class MainWindow;
class NewProjectWindow;
class DataWriter;
class DataLoader;
class WelcomeScreen;


/**
 * @brief Controladora principal. Possui funções da camada de negócio relativas a janela principal e para
 * comunicação entre as controladoras.
 *
 */
class MainController
{
public:
    /**
     * @brief Contrutor.
     *
     */
    MainController();

    /**
     * @brief Determina a controladora do mapa.
     *
     * @param
     */
    void setMapEditorController(MapEditorController*);
    /**
     * @brief Determina a controladora de opções.
     *
     * @param
     */
    void setOptionsController(OptionsController*);
    /**
     * @brief Determina a controladora do wizard.
     *
     * @param
     */
    void setWizardController(WizardController*);
    /**
     * @brief Determina a controladora de eventos.
     *
     * @param
     */
    void setEventsEditorController(EventsEditorController*);

    void setUpdateManagerController(UpdateManagerController*);

    /**
     * @brief Determina o modo do editor.
     *
     * @param mode
     */
    void setEditorMode(int mode);
    /**
     * @brief Habilita os ícones do modo de editor.
     *
     * @param mode
     */
    void setEditorModeIconEnabled(int mode);
    /**
     * @brief Determina o modo de pintura do editor.
     *
     * @param mode
     */
    void setEditorDrawMode(int mode);
    /**
     * @brief Determina o zoom do editor.
     *
     * @param zoom
     */
    void setEditorZoom(int zoom);

    /**
     * @brief Habilita a barra de zoom.
     *
     */
    void enableZoomBar();

    /**
     * @brief Abre uma janela de novo projeto.
     *
     */
    void openNewProjectWindow(QString projectsDirectory,  QWidget *parent);
    /**
     * @brief Abre a janela de novas configurações.
     *
     */
    void openConfigsTabWindow();
    /**
     * @brief Abre a janela de configurações em um objeto.
     *
     * @param gameObject Objeto que estará selecionado quando abrir a aba.
     */
    void openConfigsTabWindow(GameObject* gameObject);
    /**
     * @brief Cria novo projeto.
     *
     * @param nomeJogo Nome do projeto.
     * @param nomePasta Nome da pasta do projeto.
     * @param preProjectId Identificador de pré-projeto (por enquanto tem 2, mas há de aumentar).
     */
    void openNewProject(std::string nomeJogo, std::string nomePasta, QString projectsDirectory, int preProjectId);
    /**
     * @brief Trocar o título da janela.
     *
     */
    void changeWindowTitle();
    /**
     * @brief Carrega projeto.
     *
     * @param fileName Arquivo do projeto.
     */
    void loadProject(std::string fileName);
    /**
     * @brief Salva o projeto.
     *
     */
    void saveProject();

    void saveProjectAtExitGameka(QCloseEvent *event);
    /**
     * @brief Roda o runtime.
     *
     */
    void runRuntime();

    /**
     * @brief Recarrega a interface do editor.
     *
     */
    void reloadEditorInterface();

    /**
     * @brief Abre a janela de criação de objetos fácil.
     *
     */
    void openEasyNewGameObjectDialog();
    /**
     * @brief Abre uma janela de novo diálogo.
     *
     */
    void openNewDialogueDialog();
    /**
     * @brief Abre uma janela de novo diálogo.
     *
     * @param gameObject Objeto a que pertence o diálogo.
     */
    void openNewDialogueDialog(GameObjectInstance *gameObject);
    /**
     * @brief Abre uma janela de editar diálogo.
     *
     * @param dialogueData Diálogo a ser editado.
     */
    void openNewDialogueDialog(DialogueData *dialogueData);
    /**
     * @brief Abre uma janela de novo diálogo.
     *
     * @param map Mapa a que pertence o diálogo.
     */
    void openNewDialogueDialog(Map *map);
    /**
     * @brief Abre uma janela de novo diálogo.
     *
     * @param eventData Evento a que pertence o diálogo.
     */
    void openNewDialogueDialog(EventData *eventData);

    /**
     * @brief Ativa o "desfazer" do editor.
     *
     */
    void editorUndo();
    /**
     * @brief Ativa o "refazer" do editor.
     *
     */
    void editorRedo();

    /**
     * @brief Determina o texto da barra de status.
     *
     * @param text
     */
    void setStatusBarText(QString text);


    /**
     * @brief Inicializa cada um  dos módulos.
     *
     */
    void init();

    void reopenWelcomeScreen(bool openNewProject);

    void openUpdateManagerWindow();
private:
    /**
     * @brief Cria uma instância da GameData.
     *
     * @param preProjectId Identificador de pré-projeto.
     * @param gameName Nome do jogo.
     * @param folderName Nome da pasta do jogo.
     * @param gameData Ponteiro para a GameData.
     */
    void createGameDataInstance(int preProjectId, std::string gameName, std::string folderName, QString projectsDirectory, GameData *gameData);

    /**
     * @brief Cria a estrutura de diretórios do projeto.
     *
     * @param filePath
     */
    void createDirectoryStructure(std::string *filePath);
    /**
     * @brief Cria um subdiretório.
     *
     * @param filePath
     * @param dir
     */
    void createSubDirectory(std::string *filePath, std::string dir);
    /**
     * @brief Copia uma pasta.
     *
     * @param folder
     * @param destPath
     */
    void copyFolder(QString folder, std::string destPath);


    /**
     * @brief Copia as DLLs de Windows para a pasta do projeto.
     *
     * @param destPath
     */
    void copyWin32dll(QString destPath);

    /**
     * @brief Copia arquivo para o projeto.
     *
     * @param path
     * @param destPath
     */
    void copyFileToProject(QString path, std::string destPath);





    MapEditorController *mapEditorController; /**<  */
    OptionsController *optionsController; /**<  */
    WizardController *wizardController; /**<  */
    EventsEditorController *eventsEditorController; /**<  */
    UpdateManagerController *updateManagerController;


    MainWindow *mainWindow; /**<  */
    WelcomeScreen *welcomeScreen;
    NewProjectWindow *newProjectWindow; /**<  */

    QVBoxLayout *layout; /**<  */

    QString dataFolder;
};

#endif // MAINCONTROLLER_H
