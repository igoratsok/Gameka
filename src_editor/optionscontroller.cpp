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



#include "optionscontroller.h"

OptionsController::OptionsController()
{
}

void OptionsController::setMainController(MainController *mainController)
{
    this->mainController = mainController;
}

void OptionsController::setEventsEditorController(EventsEditorController *eventsEditorController)
{
    this->eventsEditorController = eventsEditorController;
}

void OptionsController::setGameScreen(std::string fileName, int option) {
    GameData *gameData;
    gameData = GameData::getInstance();

    switch(option) {
    case EditorConstants::IMPORT_OPTION_TITLE_SCREEN:
        gameData->setTitleScreenFile(fileName);
        break;
    case EditorConstants::IMPORT_OPTION_OPTION_SCREEN:
        gameData->setOptionsScreenFile(fileName);
        break;
    case EditorConstants::IMPORT_OPTION_GAME_OVER_SCREEN:
        gameData->setGameOverScreenFile(fileName);
        break;
    }

    this->configsTabWindow->getDadosGeraisTab()->atualizaImagensTelas();

}

void OptionsController::openConfigsTabWindow(QWidget *parent)
{
    this->configsTabWindow = new ConfigsTabWindow(this, eventsEditorController, parent);
    this->configsTabWindow->setWindowTitle(QString::fromUtf8(QApplication::tr("Configurações").toStdString().c_str()));


    this->configsTabWindow->exec();

    mainController->reloadEditorInterface();
}

void OptionsController::openConfigsTabWindow(QWidget *parent, GameObject *gameObject) {
    this->configsTabWindow = new ConfigsTabWindow(this, eventsEditorController, parent);
    this->configsTabWindow->selectObject(gameObject);

    this->configsTabWindow->exec();

    mainController->reloadEditorInterface();
}

void OptionsController::importResource(std::string filePathToImport, int importType) {
    QFile *qFile = new QFile(filePathToImport.c_str());
    GameData *gameData;
    gameData = GameData::getInstance();

    int posicaoUltimaBarra;

    posicaoUltimaBarra = filePathToImport.find_last_of("/");

    if(posicaoUltimaBarra == -1) {
        posicaoUltimaBarra = filePathToImport.find_last_of("\\");
    }

    std::string nome_arq = filePathToImport.substr(posicaoUltimaBarra);

    std::string diretorio;

    switch(importType) {
    case ConfigsImportDialog::IMPORT_TILESETS:
        diretorio = gameData->getProjectDirectory().append("/tilesets/");
        break;
    case ConfigsImportDialog::IMPORT_TITLESCREENS:
        diretorio = gameData->getProjectDirectory().append("/images/");
        break;
    case ConfigsImportDialog::IMPORT_ANIMATIONS:
        diretorio = gameData->getProjectDirectory().append("/animations/");
        break;
    case ConfigsImportDialog::IMPORT_SPRITE:
        diretorio = gameData->getProjectDirectory().append("/objects/");
        break;
    case ConfigsImportDialog::IMPORT_BACKGROUND:
        diretorio = gameData->getProjectDirectory().append("/images/");
        break;
    case ConfigsImportDialog::IMPORT_LAYER:
        diretorio = gameData->getProjectDirectory().append("/images/");
        break;
    }



    diretorio.append(nome_arq);

    qFile->copy(QString(diretorio.c_str()));

}

void OptionsController::addTileset(std::string fileName) {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::string filePath;

    filePath.append("tilesets/");
    filePath.append(fileName.c_str());

    TileSet *tileSet;
    tileSet = new TileSet(filePath, 32);

    gameData->addTileset(tileSet);


    configsTabWindow->getTilesetTab()->populaLista();
    configsTabWindow->getTilesetTab()->selectLastTileset();


}

void OptionsController::addAnimation(std::string fileName, int animationImportPattern) {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::string filePath;
    filePath.append("animations/");
    filePath.append(fileName.c_str());

    AnimationData *animationData;
    QImage *image;

    std::stringstream ss;



    switch(animationImportPattern) {
    case 0:
        animationData = new AnimationData();
        animationData->fileName = filePath;
        animationData->name = fileName;

        gameData->addAnimation(animationData);


        break;
    case 1:
        image = new QImage(QString(gameData->getProjectDirectory().append("/").append(filePath).c_str()));
        if(image->width() > 96) {

            int k = 1;

            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 2; j++) {
                    animationData = new AnimationData();
                    animationData->fileName = filePath;
                    ss.str("");
                    ss << fileName << " (" << k << ")" << QApplication::tr(" Parado Baixo").toStdString().c_str();
                    animationData->name = ss.str();

                    animationData->setHorizontalFrameNumber(12);
                    animationData->setVerticalFrameNumber(8);
                    animationData->startX = 2 + i*3;
                    animationData->endX = 2 + i*3;
                    animationData->startY = 1 + j*4;
                    animationData->endY = 1 + j*4;

                    gameData->addAnimation(animationData);

                    animationData = new AnimationData();
                    animationData->fileName = filePath;
                    ss.str("");
                    ss << fileName << " (" << k << ")" << QApplication::tr(" Parado Esquerda").toStdString().c_str();
                    animationData->name = ss.str();

                    animationData->setHorizontalFrameNumber(12);
                    animationData->setVerticalFrameNumber(8);
                    animationData->startX = 2 + i*3;
                    animationData->endX = 2 + i*3;
                    animationData->startY = 2 + j*4;
                    animationData->endY = 2 + j*4;

                    gameData->addAnimation(animationData);

                    animationData = new AnimationData();
                    animationData->fileName = filePath;
                    ss.str("");
                    ss << fileName << " (" << k << ")" << QApplication::tr(" Parado Direita").toStdString().c_str();
                    animationData->name = ss.str();

                    animationData->setHorizontalFrameNumber(12);
                    animationData->setVerticalFrameNumber(8);
                    animationData->startX = 2 + i*3;
                    animationData->endX = 2 + i*3;
                    animationData->startY = 3 + j*4;
                    animationData->endY = 3 + j*4;

                    gameData->addAnimation(animationData);

                    animationData = new AnimationData();
                    animationData->fileName = filePath;
                    ss.str("");
                    ss << fileName << " (" << k << ")" << QApplication::tr(" Parado Cima").toStdString().c_str();
                    animationData->name = ss.str();

                    animationData->setHorizontalFrameNumber(12);
                    animationData->setVerticalFrameNumber(8);
                    animationData->startX = 2 + i*3;
                    animationData->endX = 2 + i*3;
                    animationData->startY = 4 + j*4;
                    animationData->endY = 4 + j*4;

                    gameData->addAnimation(animationData);

                    animationData = new AnimationData();
                    animationData->fileName = filePath;
                    ss.str("");
                    ss << fileName << " (" << k << ")" << QApplication::tr(" Andando Baixo").toStdString().c_str();
                    animationData->name = ss.str();

                    animationData->setHorizontalFrameNumber(12);
                    animationData->setVerticalFrameNumber(8);
                    animationData->startX = 1 + i*3;
                    animationData->endX = 3 + i*3;
                    animationData->startY = 1 + j*4;
                    animationData->endY = 1 + j*4;

                    gameData->addAnimation(animationData);

                    animationData = new AnimationData();
                    animationData->fileName = filePath;
                    ss.str("");
                    ss << fileName << " (" << k << ")" << QApplication::tr(" Andando Esquerda").toStdString().c_str();
                    animationData->name = ss.str();

                    animationData->setHorizontalFrameNumber(12);
                    animationData->setVerticalFrameNumber(8);
                    animationData->startX = 1 + i*3;
                    animationData->endX = 3 + i*3;
                    animationData->startY = 2 + j*4;
                    animationData->endY = 2 + j*4;

                    gameData->addAnimation(animationData);

                    animationData = new AnimationData();
                    animationData->fileName = filePath;
                    ss.str("");
                    ss << fileName << " (" << k << ")" << QApplication::tr(" Andando Direita").toStdString().c_str();
                    animationData->name = ss.str();

                    animationData->setHorizontalFrameNumber(12);
                    animationData->setVerticalFrameNumber(8);
                    animationData->startX = 1 + i*3;
                    animationData->endX = 3 + i*3;
                    animationData->startY = 3 + j*4;
                    animationData->endY = 3 + j*4;

                    gameData->addAnimation(animationData);

                    animationData = new AnimationData();
                    animationData->fileName = filePath;
                    ss.str("");
                    ss << fileName << " (" << k << ")" << QApplication::tr(" Andando Cima").toStdString().c_str();
                    animationData->name = ss.str();

                    animationData->setHorizontalFrameNumber(12);
                    animationData->setVerticalFrameNumber(8);
                    animationData->startX = 1 + i*3;
                    animationData->endX = 3 + i*3;
                    animationData->startY = 4 + j*4;
                    animationData->endY = 4 + j*4;

                    gameData->addAnimation(animationData);

                    animationData = new AnimationData();
                    animationData->fileName = filePath;
                    ss.str("");
                    ss << fileName << " (" << k << ")" << QApplication::tr(" Girando").toStdString().c_str();
                    animationData->name = ss.str();

                    animationData->setHorizontalFrameNumber(12);
                    animationData->setVerticalFrameNumber(8);
                    animationData->startX = 2 + i*3;
                    animationData->endX = 2 + i*3;
                    animationData->startY = 1 + j*4;
                    animationData->endY = 4 + j*4;

                    animationData->velocity = 90;

                    gameData->addAnimation(animationData);





                    k++;
                }
            }


        } else {
            animationData = new AnimationData();
            animationData->fileName = filePath;
            ss.str("");
            ss << fileName << QApplication::tr(" Parado Baixo").toStdString().c_str();
            animationData->name = ss.str();

            animationData->setHorizontalFrameNumber(3);
            animationData->setVerticalFrameNumber(4);
            animationData->startX = 2;
            animationData->endX = 2;
            animationData->startY = 1;
            animationData->endY = 1;

            gameData->addAnimation(animationData);

            animationData = new AnimationData();
            animationData->fileName = filePath;
            ss.str("");
            ss << fileName <<  QApplication::tr(" Parado Esquerda").toStdString().c_str();
            animationData->name = ss.str();

            animationData->setHorizontalFrameNumber(3);
            animationData->setVerticalFrameNumber(4);
            animationData->startX = 2;
            animationData->endX = 2;
            animationData->startY = 2;
            animationData->endY = 2;

            gameData->addAnimation(animationData);

            animationData = new AnimationData();
            animationData->fileName = filePath;
            ss.str("");
            ss << fileName << QApplication::tr(" Parado Direita").toStdString().c_str();
            animationData->name = ss.str();

            animationData->setHorizontalFrameNumber(3);
            animationData->setVerticalFrameNumber(4);
            animationData->startX = 2;
            animationData->endX = 2;
            animationData->startY = 3;
            animationData->endY = 3;

            gameData->addAnimation(animationData);

            animationData = new AnimationData();
            animationData->fileName = filePath;
            ss.str("");
            ss << fileName << QApplication::tr(" Parado Cima").toStdString().c_str();
            animationData->name = ss.str();

            animationData->setHorizontalFrameNumber(3);
            animationData->setVerticalFrameNumber(4);
            animationData->startX = 2;
            animationData->endX = 2;
            animationData->startY = 4;
            animationData->endY = 4;

            gameData->addAnimation(animationData);

            animationData = new AnimationData();
            animationData->fileName = filePath;
            ss.str("");
            ss << fileName << QApplication::tr(" Andando Baixo").toStdString().c_str();
            animationData->name = ss.str();

            animationData->setHorizontalFrameNumber(3);
            animationData->setVerticalFrameNumber(4);
            animationData->startX = 1;
            animationData->endX = 3;
            animationData->startY = 1;
            animationData->endY = 1;

            gameData->addAnimation(animationData);

            animationData = new AnimationData();
            animationData->fileName = filePath;
            ss.str("");
            ss << fileName << QApplication::tr(" Andando Esquerda").toStdString().c_str();
            animationData->name = ss.str();

            animationData->setHorizontalFrameNumber(3);
            animationData->setVerticalFrameNumber(4);
            animationData->startX = 1;
            animationData->endX = 3;
            animationData->startY = 2;
            animationData->endY = 2;

            gameData->addAnimation(animationData);

            animationData = new AnimationData();
            animationData->fileName = filePath;
            ss.str("");
            ss << fileName <<  QApplication::tr(" Andando Direita").toStdString().c_str();
            animationData->name = ss.str();

            animationData->setHorizontalFrameNumber(3);
            animationData->setVerticalFrameNumber(4);
            animationData->startX = 1;
            animationData->endX = 3;
            animationData->startY = 3;
            animationData->endY = 3;

            gameData->addAnimation(animationData);

            animationData = new AnimationData();
            animationData->fileName = filePath;
            ss.str("");
            ss << fileName << QApplication::tr(" Andando Cima").toStdString().c_str();
            animationData->name = ss.str();

            animationData->setHorizontalFrameNumber(3);
            animationData->setVerticalFrameNumber(4);
            animationData->startX = 1;
            animationData->endX = 3;
            animationData->startY = 4;
            animationData->endY = 4;

            gameData->addAnimation(animationData);

            animationData = new AnimationData();
            animationData->fileName = filePath;
            ss.str("");
            ss << fileName <<  QApplication::tr(" Girando").toStdString().c_str();
            animationData->name = ss.str();

            animationData->setHorizontalFrameNumber(3);
            animationData->setVerticalFrameNumber(4);
            animationData->startX = 2;
            animationData->endX = 2;
            animationData->startY = 1;
            animationData->endY = 4;

            animationData->velocity = 90;

            gameData->addAnimation(animationData);
        }


        break;
    default:

        break;
    }

    configsTabWindow->getAnimationsTab()->populaListaAnimation();
    configsTabWindow->getAnimationsTab()->selectLastItem();


}

void OptionsController::addBackground(std::string fileName) {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::string filePath;
    filePath.append("images/");
    filePath.append(fileName.c_str());

    Background *background = new Background();
    background->name = fileName;

    BgLayer *bgLayer = new BgLayer();
    bgLayer->fileName = filePath;

    background->layerList->push_back(bgLayer);

    gameData->addBackground(background);

    configsTabWindow->getBackgroundsTab()->populaListaBackgrounds(false);

}

void OptionsController::addObjectSkill(GameObject *gameObject, SkillData *skillData) {
    int id = 0;

    for(std::vector<SkillData*>::iterator it = gameObject->listaHabilidades.begin(); it != gameObject->listaHabilidades.end(); it++) {
        SkillData *skillDataIt = *it;

        if(skillDataIt->id > id) {
            id = skillDataIt->id;
        }

    }

    skillData->id = id + 1;

    gameObject->listaHabilidades.push_back(skillData);
}

void OptionsController::removeObjectSkill(GameObject *gameObject, SkillData *skillData) {
    gameObject->listaHabilidades.erase(std::find(gameObject->listaHabilidades.begin(), gameObject->listaHabilidades.end(), skillData));

}

void OptionsController::addObject(std::string name, int type) {
    GameData *gameData;
    gameData = GameData::getInstance();

    GameObject *gameObject;
    gameObject = new GameObject();

    gameObject->name = name;
    gameObject->type = type;

    gameData->addGameObject(gameObject);
    configsTabWindow->getObjectTab()->populaListaPersonagem();
    configsTabWindow->getObjectTab()->selectObject(gameObject);

    configsTabWindow->getEventsTab()->populaTudo();

}

void OptionsController::determinaValorResolucaoCombo(int index) {
    GameData *gameData = GameData::getInstance();

    switch(index) {
    case 0:
        gameData->resWidth = 320;
        gameData->resHeight = 240;
        break;
    case 1:
        gameData->resWidth = 640;
        gameData->resHeight = 480;
        break;
    case 2:
        gameData->resWidth = 640;
        gameData->resHeight = 400;
        break;
    case 3:
        gameData->resWidth = 800;
        gameData->resHeight = 600;
        break;
    case 4:
        gameData->resWidth = 1024;
        gameData->resHeight = 786;
        break;
    case 5:
        gameData->resWidth = 1280;
        gameData->resHeight = 800;
        break;
    }
}

void OptionsController::openEasyNewGameObjectDialog() {
    EasyNewGameObjectDialog *easyNewGameObjectDialog = new EasyNewGameObjectDialog(this);
    easyNewGameObjectDialog->setWindowTitle(QString(QApplication::tr("Criar objeto")));
    GameObject *gameObject = easyNewGameObjectDialog->exec();

    delete easyNewGameObjectDialog;

    if(gameObject != NULL) {
        GameData *gameData = GameData::getInstance();

        gameData->addGameObject(gameObject);
    }
}

void OptionsController::openNewDialogueDialog() {
    NewDialogueDialog *newDialogueDialog = new NewDialogueDialog(this);
    newDialogueDialog->setWindowTitle(QString::fromUtf8(QApplication::tr("Editar diálogos").toStdString().c_str()));

    DialogueData *dialogueData = newDialogueDialog->exec();

    delete newDialogueDialog;
}

void OptionsController::openNewDialogueDialog(DialogueData *dialogueData) {
    NewDialogueDialog *newDialogueDialog = new NewDialogueDialog(this, dialogueData);
    newDialogueDialog->setWindowTitle(QString::fromUtf8(QApplication::tr("Editar diálogos").toStdString().c_str()));

    dialogueData = newDialogueDialog->exec();

    delete newDialogueDialog;
}

void OptionsController::openNewDialogueDialog(GameObjectInstance *gameObject) {
    NewDialogueDialog *newDialogueDialog = new NewDialogueDialog(this, gameObject);
    newDialogueDialog->setWindowTitle(QString::fromUtf8(QApplication::tr("Editar diálogos").toStdString().c_str()));


    DialogueData *returnDialogueData = newDialogueDialog->exec();

    if(returnDialogueData != NULL) {
        delete gameObject->dialogueData;

        gameObject->dialogueData = returnDialogueData;
    }

    delete newDialogueDialog;
}

void OptionsController::openNewDialogueDialog(Map *map) {
    NewDialogueDialog *newDialogueDialog = new NewDialogueDialog(this, map->dialogueData);
    newDialogueDialog->setWindowTitle(QString::fromUtf8(QApplication::tr("Editar diálogos").toStdString().c_str()));


    DialogueData *returnDialogueData = newDialogueDialog->exec();

    if(returnDialogueData != NULL) {
        delete map->dialogueData;

        map->dialogueData = returnDialogueData;
    }

    delete newDialogueDialog;
}

void OptionsController::openNewDialogueDialog(EventData *eventData) {
    NewDialogueDialog *newDialogueDialog = new NewDialogueDialog(this, eventData->dialogueData);
    newDialogueDialog->setWindowTitle(QString::fromUtf8(QApplication::tr("Editar diálogos").toStdString().c_str()));


    DialogueData *returnDialogueData = newDialogueDialog->exec();

    if(returnDialogueData != NULL) {
        delete eventData->dialogueData;

        eventData->dialogueData = returnDialogueData;
    }

    delete newDialogueDialog;
}

std::vector<GameObject*>* OptionsController::getObjectList() {
    GameData *gameData = GameData::getInstance();

    return gameData->objectList;
}

std::vector<TileSet*>* OptionsController::getTilesetList() {
    GameData *gameData = GameData::getInstance();

    return gameData->tileSetList;
}

std::vector<Map*>* OptionsController::getMaplist() {
    GameData *gameData = GameData::getInstance();

    return gameData->mapList;
}

std::vector<AnimationData*>* OptionsController::getAnimationDataList() {
    GameData *gameData = GameData::getInstance();

    return gameData->animationDataList;
}

std::vector<Background*>* OptionsController::getBackgroundList() {
    GameData *gameData = GameData::getInstance();

    return gameData->backgroundList;
}

std::vector<VariableData*>* OptionsController::getGlobalVariableDataList() {
    GameData *gameData = GameData::getInstance();

    return gameData->variableList;
}

void OptionsController::resetObject(GameObject *gameObject, int newType) {
    gameObject->reset(newType);
    configsTabWindow->getObjectTab()->populaListaPersonagem();
    configsTabWindow->getEventsTab()->populaTudo();
    configsTabWindow->getObjectTab()->selectObject(gameObject);
}

bool OptionsController::verifyUsedTileset(TileSet *tileset) {
    GameData *gameData = GameData::getInstance();

    foreach(Map *map, *gameData->mapList) {
        foreach(TileSet *mapTileset, *map->tileSets) {
            if(mapTileset == tileset) {
                return true;
            }
        }
    }

    return false;

}

void OptionsController::removeObject(GameObject *gameObject) {
    GameData *gameData = GameData::getInstance();

    gameData->removeObject(gameObject);
}

void OptionsController::removeTileset(TileSet *tileSet) {
    GameData *gameData = GameData::getInstance();

    gameData->removeTileset(tileSet);
}

void OptionsController::removeAnimation(AnimationData *animationData) {
    GameData *gameData = GameData::getInstance();

    gameData->removeAnimation(animationData);
}

void OptionsController::removeBackground(Background *bg) {
    GameData *gameData = GameData::getInstance();

    gameData->removeBackground(bg);
}
