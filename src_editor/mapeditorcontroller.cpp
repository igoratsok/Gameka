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



#include "mapeditorcontroller.h"


MapEditorController::MapEditorController()
{
    iDrawTile = 0;
    jDrawTile = 0;

    editorLayer = 0;
    drawMode = 0;

    copyArray = NULL;

    undoStack = NULL;
    tilemapScene = NULL;



}

void MapEditorController::setMainController(MainController *mainController)
{
    this->mainController = mainController;
}


void MapEditorController::init(MainWindow *mainWindow, QWidget *parent, QVBoxLayout *layout)
{
    this->mainWindow = mainWindow;



    /* criando as docks */
    tilesetDock = new TilesetDock(mainWindow, this);
    mapSelectDock = new MapSelectDock(mainWindow, this);
    objectsDock = new ObjectsDock(this, mainWindow);


    mainWindow->addDockWidget(Qt::LeftDockWidgetArea, tilesetDock);
    mainWindow->addDockWidget(Qt::LeftDockWidgetArea, mapSelectDock);
    mainWindow->addDockWidget(Qt::RightDockWidgetArea, objectsDock);

    /* criando o mapView e o mapScene */
    tilemapView = new TilemapView(parent);
    layout->addWidget(tilemapView);


    tilemapView->hide();
    mapSelectDock->widget->hide();



    drawTileset = tilesetDock->getSelectedTileset();
    iDrawTile = 0;
    jDrawTile = 0;
    diDrawTile = 0;
    djDrawTile = 0;
    // TODO: inicializar apropriadamente o drawTileset

    editorMode = MODE_MAP;

    mapSceneInitializated = false;
    tileSceneInitializated = false;
    mapSelectSceneInitializated = false;
    objectsDockInitializated = false;




}

void MapEditorController::initMapScene() {
    GameData *gameData = GameData::getInstance();

    if(gameData->editingMap != NULL) {
        tilemapScene = new TilemapScene(gameData->editingMap->tileSets->at(0)->tileSize, gameData->editingMap->width, gameData->editingMap->height, gameData->editingMap->layers, this);
        tilemapView->setScene(tilemapScene);
        tilemapView->setAlignment(Qt::AlignLeft);
        tilemapView->horizontalScrollBar()->setValue(tilemapView->horizontalScrollBar()->minimum());

        tilemapView->show();
        initTileScene();

        mapSceneInitializated = true;
        mainController->enableZoomBar();
    }


    if(undoStack != NULL) {
        delete undoStack;
    }
    /* criando a undoStack pra CTRL+Z e SHIFT+CTRL+Z */
    undoStack = new QUndoStack(mainWindow);


    undoChangeTileCommand = new UndoChangeTileCommand(this);

    drawTileset = tilesetDock->getSelectedTileset();
    iDrawTile = 0;
    jDrawTile = 0;
    diDrawTile = 0;
    djDrawTile = 0;

}

void MapEditorController::turnOffMapScene() {
    tilemapView->setVisible(false);
}

void MapEditorController::initTileScene() {
    tilesetDock->initTileSetScene();
    tileSceneInitializated = true;
}

void MapEditorController::initMapSelectScene() {
    mapSelectDock->widget->show();
    mapSelectDock->populaArvore();

    Map *map;
    map = mapSelectDock->getMapaSelecionado();
    if(map != NULL) {
        selectMap(map);
    }

    mapSelectSceneInitializated = true;

}

void MapEditorController::initObjectsDock() {
    objectsDock->initDock();

    objectsDockInitializated = true;
}
void MapEditorController::reloadEditorInterface() {
    if(mapSceneInitializated) {
        initMapScene();
    }

    if(tileSceneInitializated) {
        initTileScene();
    }

    objectsDock->populaArvoreObjetos();

    /*
    if(mapSelectSceneInitializated) {
        initMapSelectScene();
    }
    */

}

void MapEditorController::editorUndo() {
    undoStack->undo();

    tilemapView->update();
    tilemapScene->update();
}

void MapEditorController::editorRedo() {
    undoStack->redo();

    tilemapView->update();
    tilemapScene->update();
}


void MapEditorController::setDrawTile(int iDrawTile, int jDrawTile, int diDrawTile, int djDrawTile) {
    this->iDrawTile = iDrawTile;
    this->jDrawTile = jDrawTile;
    this->diDrawTile = diDrawTile;
    this->djDrawTile = djDrawTile;
    this->drawTileset = tilesetDock->getSelectedTileset();

    if(tilemapScene != NULL) {
        tilemapScene->setSelectionRectangleSize(diDrawTile, djDrawTile);
    }


    if(copyArray != NULL) {
        delete copyArray;
        copyArray = NULL;
    }

}

void MapEditorController::pushUndoChangesCommand() {
    if(!undoChangeTileCommand->changes.empty()) {
        undoStack->push(undoChangeTileCommand);
        undoChangeTileCommand = new UndoChangeTileCommand(this);

    }
}

void MapEditorController::pushUndoChange(int i, int j, int layer, int beforeTileI, int beforeTileJ, TileSet *beforeTileset, int afterTileI, int afterTileJ, TileSet *afterTileset)
{
    UndoChangeTileCommandChange change;

    if(beforeTileI != afterTileI ||
            beforeTileJ != afterTileJ ||
            beforeTileset != afterTileset) {
        /* adicionando um undo change na lista de changes */
        change.i = i;
        change.j = j;
        change.beforeTileI = beforeTileI;
        change.beforeTileJ = beforeTileJ;
        change.beforeTileset = beforeTileset;
        change.afterTileI = afterTileI;
        change.afterTileJ = afterTileJ;
        change.afterTileset = afterTileset;
        change.layer = layer;

        undoChangeTileCommand->changes.push_back(change);
    }

}

void MapEditorController::changeTile(int i, int j, int tileI, int tileJ, int layer, TileSet *tileset) {
    GameData *gameData = GameData::getInstance();

    if(tilemapScene != NULL) {
        tilemapScene->changeTile(i, j, tileI, tileJ, layer, tileset);
    }

    if(i < gameData->editingMap->width &&
       j < gameData->editingMap->height && i >= 0 && j >= 0) {
        gameData->editingMap->map[i][j][layer].x = tileI;
        gameData->editingMap->map[i][j][layer].y = tileJ;
        gameData->editingMap->map[i][j][layer].z = tileset;
    }

    tilemapView->update();
    if(tilemapScene != NULL) {
        tilemapScene->update();
    }

}



void MapEditorController::changeTile(int i, int j) {
    int m, n;
    GameData *gameData = GameData::getInstance();

    switch(drawMode) {
    case DRAW_MODE_PENCIL:
        // printf("%d %d %d %d %d %d", i, j, iTile, jTile, diTile, djTile);
        for(m = 0; m <= diDrawTile; m++) {
            for(n = 0; n <= djDrawTile; n++) {
                int di = (i + m - iClick)%(diDrawTile + 1);
                int dj = (j + n - jClick)%(djDrawTile + 1);

                if(di < 0) {
                    di = diDrawTile + 1 + di;
                }

                if(dj < 0) {
                    dj = djDrawTile + 1 + dj;
                }

                if(copyArray == NULL) {
                    tilemapScene->changeTile(i + m, j + n, iDrawTile + di, jDrawTile + dj, editorLayer, drawTileset);
                    if(i + m < gameData->editingMap->width &&
                            j + n < gameData->editingMap->height && i + m >= 0 && j + n >= 0) {
                        pushUndoChange(i + m, j + n, editorLayer,
                                       gameData->editingMap->map[i + m][j + n][editorLayer].x,
                                       gameData->editingMap->map[i + m][j + n][editorLayer].y,
                                       gameData->editingMap->map[i + m][j + n][editorLayer].z,
                                       iDrawTile + di,
                                       jDrawTile + dj,
                                       drawTileset);


                        gameData->editingMap->map[i + m][j + n][editorLayer].x = iDrawTile + di;
                        gameData->editingMap->map[i + m][j + n][editorLayer].y = jDrawTile + dj;
                        gameData->editingMap->map[i + m][j + n][editorLayer].z = drawTileset;

                    }
                } else {





                    tilemapScene->changeTile(i + m, j + n, (*copyArray)[di][dj].x, (*copyArray)[di][dj].y, editorLayer, (*copyArray)[di][dj].z);
                    if(i + m < gameData->editingMap->width &&
                       j + n < gameData->editingMap->height && i + m >= 0 && j + n >= 0) {

                        pushUndoChange(i + m, j + n, editorLayer,
                                       gameData->editingMap->map[i + m][j + n][editorLayer].x,
                                       gameData->editingMap->map[i + m][j + n][editorLayer].y,
                                       gameData->editingMap->map[i + m][j + n][editorLayer].z,
                                       (*copyArray)[di][dj].x,
                                       (*copyArray)[di][dj].y,
                                       (*copyArray)[di][dj].z);

                        gameData->editingMap->map[i + m][j + n][editorLayer].x = (*copyArray)[di][dj].x;
                        gameData->editingMap->map[i + m][j + n][editorLayer].y = (*copyArray)[di][dj].y;
                        gameData->editingMap->map[i + m][j + n][editorLayer].z = (*copyArray)[di][dj].z;
                    }

                }




            }
        }
        break;
    case DRAW_MODE_ERASER:
        for(m = 0; m <= diDrawTile; m++) {
            for(n = 0; n <= djDrawTile; n++) {
                UndoChangeTileCommandChange change;



                tilemapScene->changeTile(i + m, j + n, -1, -1, editorLayer, NULL);
                if(i + m < gameData->editingMap->width &&
                   j + n < gameData->editingMap->height && i + m >= 0 && j + n >= 0) {

                    pushUndoChange(i + m, j + n, editorLayer,
                                   gameData->editingMap->map[i + m][j + n][editorLayer].x,
                                   gameData->editingMap->map[i + m][j + n][editorLayer].y,
                                   gameData->editingMap->map[i + m][j + n][editorLayer].z,
                                   -1,
                                   -1,
                                   NULL);

                    gameData->editingMap->map[i + m][j + n][editorLayer].x = -1;
                    gameData->editingMap->map[i + m][j + n][editorLayer].y = -1;
                    gameData->editingMap->map[i + m][j + n][editorLayer].z = NULL;
                }



            }
        }
        break;
    case DRAW_MODE_PAINT:
        floodFillBrute(i, j, gameData->editingMap->map[i][j][editorLayer].x, gameData->editingMap->map[i][j][editorLayer].y, gameData->editingMap->map[i][j][editorLayer].z, iDrawTile, jDrawTile, drawTileset);
        break;
    default:

        break;
    }



    tilemapView->update();
    tilemapScene->update();


}

void MapEditorController::changeTiles(int iStart, int jStart, int iEnd, int jEnd) {
    int iRealStart, jRealStart, iRealEnd, jRealEnd;
    GameData *gameData = GameData::getInstance();

    iRealStart = std::min(iStart, iEnd);
    jRealStart = std::min(jStart, jEnd);
    iRealEnd = std::max(iStart, iEnd);
    jRealEnd = std::max(jStart, jEnd);

    if(iRealStart < 0) {
        iRealStart = 0;
    }

    if(jRealStart < 0) {
        jRealStart = 0;
    }

    if(iRealEnd > gameData->editingMap->width - 1) {
        iRealEnd = gameData->editingMap->width - 1;
    }

    if(jRealEnd > gameData->editingMap->height - 1) {
        jRealEnd = gameData->editingMap->height - 1;
    }

    for(int i = iRealStart; i <= iRealEnd; i++) {
        for(int j = jRealStart; j <= jRealEnd; j++) {
            int di = (i - iClick)%(diDrawTile + 1);
            int dj = (j - jClick)%(djDrawTile + 1);

            if(di < 0) {
                di = diDrawTile + 1 + di;
            }

            if(dj < 0) {
                dj = djDrawTile + 1 + dj;
            }

            if(copyArray == NULL) {


                tilemapScene->changeTile(i, j, iDrawTile + di, jDrawTile + dj, editorLayer, drawTileset);
                if(i < gameData->editingMap->width &&
                        j < gameData->editingMap->height && i >= 0 && j >= 0) {

                    pushUndoChange(i, j, editorLayer,
                                   gameData->editingMap->map[i][j][editorLayer].x,
                                   gameData->editingMap->map[i][j][editorLayer].y,
                                   gameData->editingMap->map[i][j][editorLayer].z,
                                   iDrawTile + di,
                                   jDrawTile + dj,
                                   drawTileset);

                    gameData->editingMap->map[i][j][editorLayer].x = iDrawTile + di;
                    gameData->editingMap->map[i][j][editorLayer].y = jDrawTile + dj;
                    gameData->editingMap->map[i][j][editorLayer].z = drawTileset;
                }
            } else {



                tilemapScene->changeTile(i, j, (*copyArray)[di][dj].x, (*copyArray)[di][dj].y, editorLayer, (*copyArray)[di][dj].z);
                if(i < gameData->editingMap->width &&
                   j < gameData->editingMap->height && i >= 0 && j >= 0) {

                    pushUndoChange(i, j, editorLayer,
                                   gameData->editingMap->map[i][j][editorLayer].x,
                                   gameData->editingMap->map[i][j][editorLayer].y,
                                   gameData->editingMap->map[i][j][editorLayer].z,
                                   (*copyArray)[di][dj].x,
                                   (*copyArray)[di][dj].y,
                                   (*copyArray)[di][dj].z);

                    gameData->editingMap->map[i][j][editorLayer].x = (*copyArray)[di][dj].x;
                    gameData->editingMap->map[i][j][editorLayer].y = (*copyArray)[di][dj].y;
                    gameData->editingMap->map[i][j][editorLayer].z = (*copyArray)[di][dj].z;
                }
            }


        }
    }

    tilemapView->update();
    tilemapScene->update();
}

void MapEditorController::setCopyArray(int iStart, int jStart, int iEnd, int jEnd) {
    int iRealStart, jRealStart, iRealEnd, jRealEnd;
    GameData *gameData = GameData::getInstance();

    iRealStart = std::min(iStart, iEnd);
    jRealStart = std::min(jStart, jEnd);
    iRealEnd = std::max(iStart, iEnd);
    jRealEnd = std::max(jStart, jEnd);

    if(iRealStart < 0) {
        iRealStart = 0;
    }

    if(jRealStart < 0) {
        jRealStart = 0;
    }

    if(iRealEnd > gameData->editingMap->width - 1) {
        iRealEnd = gameData->editingMap->width - 1;
    }

    if(jRealEnd > gameData->editingMap->height - 1) {
        jRealEnd = gameData->editingMap->height - 1;
    }

    if(copyArray != NULL) {
        delete copyArray;
    }

    int copyArrayWidth = iRealEnd - iRealStart + 1;
    int copyArrayHeight = jRealEnd - jRealStart + 1;

    copyArray = new boost::multi_array<Point, 2>(boost::extents[copyArrayWidth][copyArrayHeight]);

    int i0, i1, j0, j1;
    for(i0 = iRealStart, i1 = 0; i0 <= iRealEnd; i0++, i1++) {
        for(j0 = jRealStart, j1 = 0; j0 <= jRealEnd; j0++, j1++) {
            (*copyArray)[i1][j1].x = gameData->editingMap->map[i0][j0][editorLayer].x;
            (*copyArray)[i1][j1].y = gameData->editingMap->map[i0][j0][editorLayer].y;
            (*copyArray)[i1][j1].z = gameData->editingMap->map[i0][j0][editorLayer].z;
        }
    }

    this->iDrawTile = 0;
    this->jDrawTile = 0;
    this->diDrawTile = copyArrayWidth-1;
    this->djDrawTile = copyArrayHeight-1;
    this->drawTileset = tilesetDock->getSelectedTileset();

    tilemapScene->setSelectionRectangleSize(diDrawTile, djDrawTile);

}

void MapEditorController::floodFill(int nodeI, int nodeJ, int targetI, int targetJ, int replacementI, int replacementJ) {
    std::list<Point> queue;
    GameData *gameData = GameData::getInstance();

    if(gameData->editingMap->map[nodeI][nodeJ][editorLayer].x != targetI ||
            gameData->editingMap->map[nodeI][nodeJ][editorLayer].y != targetJ) {
        return;
    }

    queue.push_back(Point(nodeI, nodeJ));

    for(std::list<Point>::iterator it = queue.begin(); it != queue.end(); ++it) {
        Point node = *it;

        if((gameData->editingMap->map[node.x][node.y][editorLayer].x == targetI &&
            gameData->editingMap->map[node.x][node.y][editorLayer].y == targetJ)) {
            Point westNodes = node;
            Point eastNodes = node;

            while(westNodes.x - 1 >= 0 && (gameData->editingMap->map[westNodes.x - 1][westNodes.y][editorLayer].x == targetI &&
                                           gameData->editingMap->map[westNodes.x - 1][westNodes.y][editorLayer].y == targetJ)) {
                westNodes.x--;
            }

            while(eastNodes.x + 1 < gameData->editingMap->width && (gameData->editingMap->map[eastNodes.x + 1][eastNodes.y][editorLayer].x == targetI &&
                                                                    gameData->editingMap->map[eastNodes.x + 1][eastNodes.y][editorLayer].y == targetJ)) {
                eastNodes.x++;
            }

            for(int i = westNodes.x; i <= eastNodes.x; i++) {
                gameData->editingMap->map[i][eastNodes.y][editorLayer].x = replacementI;
                gameData->editingMap->map[i][eastNodes.y][editorLayer].y = replacementJ;
                tilemapScene->changeTile(i, eastNodes.y, replacementI, replacementJ, editorLayer, drawTileset);


                if(eastNodes.y - 1 >= 0 && (gameData->editingMap->map[i][eastNodes.y - 1][editorLayer].x == targetI &&
                                  gameData->editingMap->map[i][eastNodes.y - 1][editorLayer].y == targetJ)) {
                    queue.push_back(Point(i, eastNodes.y - 1));
                }

                if(eastNodes.y + 1 < gameData->editingMap->height && (gameData->editingMap->map[i][eastNodes.y + 1][editorLayer].x == targetI &&
                                  gameData->editingMap->map[i][eastNodes.y + 1][editorLayer].y == targetJ)) {
                    queue.push_back(Point(i, eastNodes.y + 1));
                }


            }
        }
    }
}

void MapEditorController::floodFillBrute(int nodeI, int nodeJ, int targetI, int targetJ, TileSet *targetTileset, int replacementI, int replacementJ, TileSet *replacementTileset) {
    GameData *gameData = GameData::getInstance();

    if(targetI == replacementI && targetJ == replacementJ && targetTileset == replacementTileset) {
        return;
    }

    if(gameData->editingMap->map[nodeI][nodeJ][editorLayer].x != targetI ||
            gameData->editingMap->map[nodeI][nodeJ][editorLayer].y != targetJ ||
            gameData->editingMap->map[nodeI][nodeJ][editorLayer].z != targetTileset) {
        return;
    }

    //gameData->editingMap->map[nodeI][nodeJ][editorLayer].x = replacementI;
    //gameData->editingMap->map[nodeI][nodeJ][editorLayer].y = replacementJ;

    int di = (nodeI - iClick)%(diDrawTile + 1);
    int dj = (nodeJ - jClick)%(djDrawTile + 1);

    if(di < 0) {
        di = diDrawTile + 1 + di;
    }

    if(dj < 0) {
        dj = djDrawTile + 1 + dj;
    }

    pushUndoChange(nodeI, nodeJ, editorLayer,
                   gameData->editingMap->map[nodeI][nodeJ][editorLayer].x,
                   gameData->editingMap->map[nodeI][nodeJ][editorLayer].y,
                   gameData->editingMap->map[nodeI][nodeJ][editorLayer].z,
                   replacementI + di,
                   replacementJ + dj,
                   replacementTileset);

    gameData->editingMap->map[nodeI][nodeJ][editorLayer].x = replacementI + di;
    gameData->editingMap->map[nodeI][nodeJ][editorLayer].y = replacementJ + dj;
    gameData->editingMap->map[nodeI][nodeJ][editorLayer].z = replacementTileset;
    tilemapScene->changeTile(nodeI, nodeJ, replacementI + di, replacementJ + dj, editorLayer, replacementTileset);

    if(nodeI - 1 >= 0) {
        floodFillBrute(nodeI - 1, nodeJ, targetI, targetJ, targetTileset, replacementI, replacementJ, replacementTileset);
    }

    if(nodeI + 1 < gameData->editingMap->width) {
        floodFillBrute(nodeI + 1, nodeJ, targetI, targetJ, targetTileset, replacementI, replacementJ, replacementTileset);
    }

    if(nodeJ - 1 >= 0) {
        floodFillBrute(nodeI, nodeJ - 1, targetI, targetJ, targetTileset, replacementI, replacementJ, replacementTileset);
    }

    if(nodeJ + 1 < gameData->editingMap->height) {
        floodFillBrute(nodeI, nodeJ + 1, targetI, targetJ, targetTileset, replacementI, replacementJ, replacementTileset);
    }
}

void MapEditorController::openNewMapWindow() {
    newMapWindow = new NewMapWindow(this, NULL, mainWindow);
    newMapWindow->setWindowTitle(QApplication::tr("Novo Mapa"));
    newMapWindow->setModal(true);
    newMapWindow->setVisible(true);
}

void MapEditorController::openEditMapWindow(Map *map) {
    newMapWindow = new NewMapWindow(this, map, mainWindow);
    newMapWindow->setWindowTitle(QApplication::tr("Editar Mapa"));
    newMapWindow->setModal(true);
    newMapWindow->setVisible(true);
}

void MapEditorController::createNewMap(Map *newMap) {
    GameData *gameData = GameData::getInstance();
    Map *mapaSelecionado;

    mapaSelecionado = mapSelectDock->getMapaSelecionado();

    newMap->id = gameData->generateNewMapId();


    if((mapaSelecionado == NULL) || ((mapaSelecionado != NULL) && (mapaSelecionado->filhos == NULL))) {
        gameData->mapList->push_back(newMap);
    } else {
        mapaSelecionado->filhos->push_back(newMap);
    }

    mapSelectDock->populaArvore();

    if(newMap->filhos == NULL) {
        gameData->editingMap = newMap;
        initMapScene();
    }


}

void MapEditorController::refreshMapWidgets() {
    mapSelectDock->populaArvore();
    initMapScene();
}

void MapEditorController::createFolder() {
    GameData* gameData = GameData::getInstance();

    Map *newFolder;
    Map *mapaSelecionado;

    bool ok;

    QString text = QInputDialog::getText(mainWindow, *(new QString(QApplication::tr("Nova pasta"))),
                                         *(new QString(QApplication::tr("Nome:"))), QLineEdit::Normal,
                                            *(new QString("")), &ok);

    if(ok && !text.isEmpty()) {
        newFolder = new Map(text.toStdString(), new std::vector<Map*>());

        mapaSelecionado = mapSelectDock->getMapaSelecionado();

        if((mapaSelecionado == NULL) || ((mapaSelecionado != NULL) && (mapaSelecionado->filhos == NULL))) {
            gameData->mapList->push_back(newFolder);
        } else {
            mapaSelecionado->filhos->push_back(newFolder);
        }

        mapSelectDock->populaArvore();
    }


}

void MapEditorController::selectMap(Map *map) {
    GameData *gameData = GameData::getInstance();

    if(map == NULL) {
        turnOffMapScene();
    } else {
        // só muda se NÃO for pasta
        if(map->filhos == NULL) {
            gameData->editingMap = map;

            objectsDock->populaArvoreObjetos();
            initMapScene();
        }
    }




}

Map* MapEditorController::getSelectedMap() {
    return mapSelectDock->getMapaSelecionado();
}

GameObject* MapEditorController::getSelectedObject() {
    return objectsDock->getCurrentObject();
}

void MapEditorController::unSelectObject() {
    objectsDock->unselectObject();
}


void MapEditorController::setEditorMode(int mode) {
    editorMode = mode;
    mainController->setEditorModeIconEnabled(mode);
    if(tilemapScene != NULL) {
        tilemapScene->setEditorMode(mode);
    }

}

void MapEditorController::setEditorDrawMode(int mode) {
    drawMode = mode;
    tilemapScene->setSelectionRectangleSize(diDrawTile, djDrawTile);
}

void MapEditorController::setEditorZoom(int zoom) {
    if(tilemapScene != NULL) {
        tilemapScene->setZoom(zoom);
    }
}

void MapEditorController::setStatusBarText(QString text) {
    mainController->setStatusBarText(text);
}

int MapEditorController::setMapEditorLayer(int layer) {
    GameData *gameData = GameData::getInstance();

    if(layer <= (gameData->editingMap->layers - 1)) {
        editorLayer = layer;
        if(tilemapScene != NULL) {
            tilemapScene->setEditionLayer(layer);
        }



        return layer;
    } else {
        layer = gameData->editingMap->layers;

        if(gameData->editingMap->verifyLayerFilled(layer-1)) {
            editorLayer = layer;
            gameData->editingMap->extent(layer + 1);
            if(tilemapScene != NULL) {
                tilemapScene->setEditionLayer(layer);
            }


            return layer;
        }
    }

    return layer;
}

void MapEditorController::openConfigsTabWindow(GameObject* gameObject) {
    mainController->openConfigsTabWindow(gameObject);
}

void MapEditorController::openEasyNewGameObjectDialog() {
    mainController->openEasyNewGameObjectDialog();
}

void MapEditorController::openNewDialogueDialog() {
    mainController->openNewDialogueDialog();
}

void MapEditorController::openNewDialogueDialog(GameObjectInstance *gameObject) {
    mainController->openNewDialogueDialog(gameObject);
}

void MapEditorController::openNewDialogueDialog(DialogueData *dialogueData) {
    mainController->openNewDialogueDialog(dialogueData);
}

void MapEditorController::openNewDialogueDialog(Map *map) {
    mainController->openNewDialogueDialog(map);
}

void MapEditorController::openNewDialogueDialog(EventData *eventData) {
    mainController->openNewDialogueDialog(eventData);
}

void MapEditorController::setCurrentObjectAtCursor() {
    if(tilemapScene != NULL) {
        tilemapScene->setCurrentObjectAtCursor();
    }

}

void MapEditorController::addGameObjectInstanceToEditingMap(GameObjectInstance *gameObjectInstance) {
    GameData *gameData = GameData::getInstance();

    if(gameData->editingMap != NULL) {
        if(gameData->editingMap->gameObjectInstances->empty()) {
            gameObjectInstance->isCenter = true;
            gameObjectInstance->isMainObject = true;
        }

        gameData->editingMap->gameObjectInstances->push_back(gameObjectInstance);
    }



}


std::vector<GameObject*>* MapEditorController::getObjectList() {
    GameData *gameData = GameData::getInstance();

    return gameData->objectList;
}

std::vector<TileSet*>* MapEditorController::getTilesetList() {
    GameData *gameData = GameData::getInstance();

    return gameData->tileSetList;
}

std::vector<Map*>* MapEditorController::getMaplist() {
    GameData *gameData = GameData::getInstance();

    return gameData->mapList;
}

std::vector<AnimationData*>* MapEditorController::getAnimationDataList() {
    GameData *gameData = GameData::getInstance();

    return gameData->animationDataList;
}

std::vector<Background*>* MapEditorController::getBackgroundList() {
    GameData *gameData = GameData::getInstance();

    return gameData->backgroundList;
}
