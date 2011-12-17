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



#include "maincontroller.h"

MainController::MainController()
{
}


void MainController::setEventsEditorController(EventsEditorController *eventsEditorController)
{
    this->eventsEditorController = eventsEditorController;
}

void MainController::setMapEditorController(MapEditorController *mapEditorController)
{
    this->mapEditorController = mapEditorController;
}

void MainController::setOptionsController(OptionsController *optionsController)
{
    this->optionsController = optionsController;
}

void MainController::setWizardController(WizardController *wizardController)
{
    this->wizardController = wizardController;
}

void MainController::setUpdateManagerController(UpdateManagerController *updateManagerController) {
    this->updateManagerController = updateManagerController;
}



void MainController::init()
{


    mainWindow = new MainWindow(0, this);
    QSplashScreen *splash = new QSplashScreen(mainWindow, QPixmap(":/images/data/splash/splash.jpg"));
    splash->show();

    mainWindow->moveToCenter();
    mainWindow->setWindowTitle("Gameka");



    /* inicializando o vboxlayout */
    layout = new QVBoxLayout(mainWindow->getMainWindowWidget());
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignTop);


    mapEditorController->init(mainWindow, mainWindow->getMainWindowWidget(), layout);


    //mainWindow->show();

    welcomeScreen = new WelcomeScreen(mainWindow);
    welcomeScreen->setMainController(this);

    splash->finish(mainWindow);
    welcomeScreen->exec();



}

void MainController::openNewProjectWindow(QString projectsDirectory, QWidget *parent) {
    newProjectWindow = new NewProjectWindow(parent, projectsDirectory, this);

    newProjectWindow->setModal(true);
    newProjectWindow->show();

    newProjectWindow->setWindowTitle("Novo Projeto");



}

void MainController::openNewProject(std::string nomeJogo, std::string nomePasta, QString projectsDirectory, int preProjectId) {
    GameData* gameData;
    gameData = GameData::getInstance();

    createGameDataInstance(preProjectId, nomeJogo, nomePasta, projectsDirectory, gameData);

    mapEditorController->initMapScene();
    //mapEditorController->initTileScene();
    mapEditorController->initMapSelectScene();
    mapEditorController->initObjectsDock();

    mainWindow->enableMainButtons();
    mainWindow->setVisible(true);
    mainWindow->setFocus();
    welcomeScreen->setVisible(false);


    changeWindowTitle();

}

void MainController::changeWindowTitle() {
    GameData* gameData;
    gameData = GameData::getInstance();

    QString nomeTela;
    nomeTela.append("Gameka - ");
    nomeTela.append(gameData->gameName->c_str());

    mainWindow->setWindowTitle(nomeTela);
}

void MainController::loadProject(std::string fileName) {
    GameData* gameData;
    gameData = GameData::getInstance();

    gameData->erase();
    DataLoader *dataLoader = new DataLoader(gameData);

    dataLoader->load(fileName);

    gameData->filePath = fileName;

    mapEditorController->initMapScene();
    //mapEditorController->initTileScene();
    mapEditorController->initMapSelectScene();
    mapEditorController->initObjectsDock();

    mainWindow->enableMainButtons();
    mainWindow->setVisible(true);
    mainWindow->setFocus();
    welcomeScreen->setVisible(false);


    changeWindowTitle();


    //QMessageBox messageBox;
    //messageBox.setText("Projeto carregado com sucesso!");
    //messageBox.exec();


}

void MainController::openConfigsTabWindow() {
    optionsController->openConfigsTabWindow(mainWindow);

}

void MainController::openConfigsTabWindow(GameObject *gameObject) {
    optionsController->openConfigsTabWindow(mainWindow, gameObject);
}

void MainController::saveProject() {
    GameData* gameData;
    gameData = GameData::getInstance();

    QMessageBox messageBox;
    messageBox.setText("Deseja realmente salvar o projeto?");
    messageBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    messageBox.setDefaultButton(QMessageBox::Cancel);

    int ret = messageBox.exec();

    if(ret == QMessageBox::Save) {
        DataWriter *dataWriter = new DataWriter(gameData);
        dataWriter->save(gameData->filePath);

        QMessageBox sucessMessageBox;
        sucessMessageBox.setText("Projeto gravado com sucesso!");
        sucessMessageBox.exec();
    }

}

void MainController::saveProjectAtExitGameka(QCloseEvent *event) {
    GameData* gameData;
    gameData = GameData::getInstance();

    QMessageBox messageBox;
    messageBox.setText("Deseja realmente salvar o projeto?");
    messageBox.setWindowTitle("Alerta!");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    messageBox.setDefaultButton(QMessageBox::Cancel);

    int ret = messageBox.exec();

    if(ret == QMessageBox::Save) {
        DataWriter *dataWriter = new DataWriter(gameData);
        dataWriter->save(gameData->filePath);

        QMessageBox sucessMessageBox;
        sucessMessageBox.setText("Projeto gravado com sucesso!");
        sucessMessageBox.exec();
    }

    if(ret == QMessageBox::Cancel) {
        event->ignore();
    }
}

void MainController::runRuntime() {
    saveProject();

    QProcess *myProcess = new QProcess();
    GameData* gameData;
    gameData = GameData::getInstance();



    printf("Runtime: %s %s\n", gameData->getProjectDirectory().append("/").append("ludo.exe").c_str(),
           gameData->getProjectDirectory().append("/").c_str());


    myProcess->setWorkingDirectory(QString(gameData->getProjectDirectory().c_str()));


    std::string dir = std::string(gameData->getProjectDirectory().append("/").append("game_linux").c_str());


#ifdef Q_WS_X11
    myProcess->start(QString(gameData->getProjectDirectory().append("/").append("game_linux").c_str()), QStringList());
#endif
#ifdef Q_WS_MACX
    myProcess->start(QString(gameData->getProjectDirectory().append("/").append("game_mac").c_str()), QStringList());

#endif
#ifdef Q_WS_WIN32
    myProcess->start(QString("\"").append(QString(gameData->getProjectDirectory().append("/").append("game_w32.exe").append("\"").c_str())), QStringList());
#endif
#ifdef Q_WS_WIN64
    myProcess->start(QString("\"").append(QString(gameData->getProjectDirectory().append("/").append("game_w32.exe").append("\"").c_str())), QStringList());
#endif

    myProcess->waitForFinished();

}

void MainController::setEditorMode(int mode) {
    mapEditorController->setEditorMode(mode);
}

void MainController::setEditorModeIconEnabled(int mode) {
    mainWindow->setEditorModeIconEnabled(mode);
}

void MainController::reloadEditorInterface() {
    mapEditorController->reloadEditorInterface();
}

void MainController::setEditorDrawMode(int mode) {
    mapEditorController->setEditorDrawMode(mode);
}

void MainController::openEasyNewGameObjectDialog() {
    optionsController->openEasyNewGameObjectDialog();
}

void MainController::openNewDialogueDialog() {
    optionsController->openNewDialogueDialog();
}


void MainController::openNewDialogueDialog(GameObjectInstance *gameObject) {
    optionsController->openNewDialogueDialog(gameObject);
}

void MainController::openNewDialogueDialog(DialogueData *dialogueData) {
    optionsController->openNewDialogueDialog(dialogueData);
}

void MainController::openNewDialogueDialog(Map *map) {
    optionsController->openNewDialogueDialog(map);
}

void MainController::openNewDialogueDialog(EventData *eventData) {
    optionsController->openNewDialogueDialog(eventData);
}

void MainController::editorUndo() {
    mapEditorController->editorUndo();
}

void MainController::editorRedo() {
    mapEditorController->editorRedo();
}

void MainController::setStatusBarText(QString text) {
    mainWindow->setStatusBarText(text);
}


void MainController::createGameDataInstance(int preProjectId, std::string gameName, std::string folderName, QString projectsDirectory, GameData *gameData) {

    gameData->erase();

    std::string *filePath;

    QDir pDir = QDir(projectsDirectory);
    if(!pDir.exists()) {
        QDir().mkpath(projectsDirectory);
    }

    if(projectsDirectory.at(projectsDirectory.size()-1) != '/') {
        projectsDirectory = projectsDirectory.append("/");
    }


    if(preProjectId == 0) {
        gameData->gameName = new std::string(gameName.c_str());
        gameData->resWidth = 640;
        gameData->resHeight = 480;



        filePath = new std::string();

        filePath->append(projectsDirectory.toStdString());
        filePath->append(folderName.c_str());

        // cria diretorio
        createDirectoryStructure(filePath);

        filePath->append("/game.gmk");

        gameData->filePath = *filePath;

        gameData->setTitleScreenFile("default_title_screen.png");
        gameData->setOptionsScreenFile("default_options_screen.png");
        gameData->setGameOverScreenFile("default_gameover_screen.png");


        DataWriter *dataWriter = new DataWriter(gameData);
        dataWriter->save(*filePath);

    } else {

        filePath = new std::string();

        filePath->append(projectsDirectory.toStdString());
        filePath->append(folderName.c_str());

        createDirectoryStructure(filePath);

        std::string destPath = std::string(*filePath);
        switch(preProjectId) {
        case 1:

            if(!QFile().copy(QString("data/pre-projects/template01.ldo"), QString(std::string(destPath.c_str()).append("/game.gmk").c_str()))) {
                printf("Falha no carregamento do template01.ldo.");
                exit(1);
            }
            break;
        case 2:
            if(!QFile().copy(QString("data/pre-projects/template02.ldo"), QString(std::string(destPath.c_str()).append("/game.gmk").c_str()))) {
                printf("Falha no carregamento do template01.ldo.");
                exit(1);
            }
            break;
        default:
            printf("Pré-projeto inválido.");
            break;
        }


        filePath->append("/game.gmk");

        gameData->filePath = *filePath;


        DataLoader *dataLoader = new DataLoader(gameData);
        dataLoader->load(*filePath);



        gameData->gameName = new std::string(gameName.c_str());

    }



}



void MainController::createSubDirectory(std::string *filePath, std::string dir) {
    std::string *subdirectory;

    subdirectory = new std::string(filePath->c_str());
    subdirectory->append(dir);

    if(!QDir(subdirectory->c_str()).exists()) {
        QDir().mkdir(subdirectory->c_str());
    }
}



void MainController::createDirectoryStructure(std::string *filePath) {

    if(!QDir(filePath->c_str()).exists()) {
        QDir().mkdir(filePath->c_str());
    }

    createSubDirectory(filePath, "/tilesets/");
    createSubDirectory(filePath, "/sfx/");
    createSubDirectory(filePath, "/musics/");
    createSubDirectory(filePath, "/objects/");
    createSubDirectory(filePath, "/images/");
    createSubDirectory(filePath, "/animations/");
    createSubDirectory(filePath, "/runtime-common/");
    createSubDirectory(filePath, "/libs/");

    /* copiando alguns arquivos essenciais */
    std::string destPath;

    destPath = std::string(filePath->c_str());

    if(!QFile().copy(QString("data/project_data/default_object_sprite.png"), QString(std::string(destPath.c_str()).append("/objects/default_object_sprite.png").c_str()))) {
        printf("Falha no carregamento do default_object_sprite.");

        exit(1);
    }

    if(!QFile().copy(QString("data/project_data/default_title_screen.png"), QString(std::string(destPath.c_str()).append("/images/default_title_screen.png").c_str()))) {
        printf("Falha no carregamento do default_title_screen.png.");
        exit(1);
    }

    if(!QFile().copy(QString("data/project_data/default_options_screen.png"), QString(std::string(destPath.c_str()).append("/images/default_options_screen.png").c_str()))) {
        printf("Falha no carregamento do default_options_screen.png.");
        exit(1);
    }

    if(!QFile().copy(QString("data/project_data/default_gameover_screen.png"), QString(std::string(destPath.c_str()).append("/images/default_gameover_screen.png").c_str()))) {
        printf("Falha no carregamento do default_gameover_screen.png.");
        exit(1);
    }

    if(!QFile().copy(QString("data/project_data/runtime-common/dialog_bar1.png"), QString(std::string(destPath.c_str()).append("/runtime-common/dialog_bar1.png").c_str()))) {
        printf("Falha no carregamento do dialog_bar1.png.");
        exit(1);
    }

    if(!QFile().copy(QString("data/project_data/runtime-common/iconsolata.ttf"), QString(std::string(destPath.c_str()).append("/runtime-common/iconsolata.ttf").c_str()))) {
        printf("Falha no carregamento do dialog_bar1.png.");
        exit(1);
    }

    if(!QFile().copy(QString("data/project_data/runtime-common/oldsansblack.ttf"), QString(std::string(destPath.c_str()).append("/runtime-common/oldsansblack.ttf").c_str()))) {
        printf("Falha no carregamento do oldsansblack.ttf .");
        exit(1);
    }



    if(QFile().exists(QString("data/project_data/runtime-common/runtime_linux"))) {
        if(!QFile().copy(QString("data/project_data/runtime-common/runtime_linux"), QString(std::string(destPath.c_str()).append("/game_linux").c_str()))) {
            printf("Falha no carregamento do runtime_linux.");
            exit(1);
        }
    }

    if(QFile().exists(QString("data/project_data/runtime-common/run_game_linux"))) {
        if(!QFile().copy(QString("data/project_data/runtime-common/run_game_linux"), QString(std::string(destPath.c_str()).append("/run_game_linux").c_str()))) {
            printf("Falha no carregamento do run_game_linux.");
            exit(1);
        }
    }

    if(QFile().exists(QString("data/project_data/runtime-common/runtime_w32.exe"))) {
        if(!QFile().copy(QString("data/project_data/runtime-common/runtime_w32.exe"), QString(std::string(destPath.c_str()).append("/game_w32.exe").c_str()))) {
            printf("Falha no carregamento do runtime_w32.exe.");
            exit(1);
        }
    }

    if(QFile().exists(QString("data/project_data/runtime-common/runtime_w64.exe"))) {
        if(!QFile().copy(QString("data/project_data/runtime-common/runtime_w64.exe"), QString(std::string(destPath.c_str()).append("/game_w64.exe").c_str()))) {
            printf("Falha no carregamento do runtime_w64.exe.");
            exit(1);
        }
    }

    if(QFile().exists(QString("data/project_data/runtime-common/runtime_mac.exe"))) {
        if(!QFile().copy(QString("data/project_data/runtime-common/runtime_mac"), QString(std::string(destPath.c_str()).append("/game_mac").c_str()))) {
            printf("Falha no carregamento do runtime_mac.");
            exit(1);
        }
    }


    copyFolder(QString("animations"), destPath);
    copyFolder(QString("images"), destPath);
    copyFolder(QString("musics"), destPath);
    copyFolder(QString("objects"), destPath);
    copyFolder(QString("sfx"), destPath);
    copyFolder(QString("tilesets"), destPath);
    copyFolder(QString("libs"), destPath);

    copyWin32dll(QString(destPath.c_str()));
}

void MainController::copyFolder(QString folder, std::string destPath) {
    QDir dir = QDir(QString("data/").append(folder).append("/"));
    if(dir.exists()) {
        QStringList files = dir.entryList();


        foreach(QString file, files) {
            if(!file.isEmpty() && file.at(0) != '.') {
                copyFileToProject(QString(folder).append("/").append(file), destPath);
            }

        }
    }

}


void MainController::copyWin32dll(QString destPath) {
    QDir dir = QDir(QString("data/windll/"));
    QStringList files = dir.entryList();


    foreach(QString file, files) {
        if(!file.isEmpty() && file.at(0) != '.') {



            if(!QFile().copy(QString("data/windll/").append(file), QString(destPath).append("/").append(file))) {
                std::cout << "Falha no carregamento do " << file.toStdString() << std::endl;
                exit(1);
            }
        }

    }
}


void MainController::copyFileToProject(QString path, std::string destPath) {
    if(!QFile().copy(QString("data/").append(path), QString(std::string(destPath.c_str()).append("/").c_str()).append(path))) {
        std::cout << "Falha no carregamento do " << path.toStdString() << std::endl;
        exit(1);
    }
}

void MainController::reopenWelcomeScreen(bool openNewProject) {

    GameData* gameData;
    gameData = GameData::getInstance();

    QMessageBox messageBox;
    messageBox.setText("Deseja salvar o projeto antes?");
    messageBox.setWindowTitle("Alerta!");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    messageBox.setDefaultButton(QMessageBox::Cancel);

    int ret = messageBox.exec();

    if(ret == QMessageBox::Save) {
        DataWriter *dataWriter = new DataWriter(gameData);
        dataWriter->save(gameData->filePath);

        QMessageBox sucessMessageBox;
        sucessMessageBox.setText("Projeto gravado com sucesso!");
        sucessMessageBox.exec();
    }

    if(ret != QMessageBox::Cancel) {
        mainWindow->setVisible(false);
        welcomeScreen->setVisible(true);
        welcomeScreen->populateProjectList();
        if(openNewProject) {
            welcomeScreen->openNewProjectWindow();
        }


    }


}

void MainController::setEditorZoom(int zoom) {
    mapEditorController->setEditorZoom(zoom);
}

void MainController::enableZoomBar() {
    mainWindow->enableZoomBar();
}

void MainController::openUpdateManagerWindow() {
    updateManagerController->openUpdateManagerWindow();
}
