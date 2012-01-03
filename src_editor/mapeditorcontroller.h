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


#ifndef MAPEDITORCONTROLLER_H
#define MAPEDITORCONTROLLER_H

#include <QVBoxLayout>
#include <QScrollBar>
#include <stdio.h>
#include <stdlib.h>
#include <QInputDialog>
#include <QUndoStack>
#include <QUndoView>
#include <QApplication>

#include <list>
#include <algorithm>
#include <QList>

#include <boost/multi_array.hpp>

#include "maincontroller.h"
#include "tilesetdock.h"
#include "mapselectdock.h"
#include "mainwindow.h"
#include "tilemapview.h"
#include "tilemapscene.h"
#include "objectsdock.h"
#include "tileitem.h"
#include "newmapwindow.h"
#include "gamedata.h"
#include "map.h"
#include "tileset.h"
#include "gameobject.h"
#include "point.h"
#include "undochangetilecommand.h"



class TilesetDock;
class ObjectsDock;
class MapSelectDock;
class MainController;
class TilemapScene;
class MainWindow;
class NewMapWindow;
class GameData;
class Map;
class Tileset;
class GameObject;
class Point;
class UndoChangeTileCommand;


/**
 * @brief Controladora do editor de mapas. Realiza todas as funções da camada de negócio
 * quanto ao editor de mapas.
 *
 */
class MapEditorController
{
public:
    /**
     * @brief Construtor.
     *
     */
    MapEditorController();

    /**
     * @brief Fornece a controladora principal.
     *
     * @param
     */
    void setMainController(MainController*);

    /**
     * @brief Inicializa o editor de mapas.
     *
     * @param mainWindow
     * @param parent
     * @param layout
     */
    void init(MainWindow *mainWindow, QWidget *parent, QVBoxLayout *layout);

    /**
     * @brief Inicializa o TilemapScene.
     *
     */
    void initMapScene();

    /**
     * @brief Desliga a MapScene.
     *
     */
    void turnOffMapScene();
    /**
     * @brief Inicializa o TilesetScene.
     *
     */
    void initTileScene();
    /**
     * @brief Inicializa o MapSelectDock.
     *
     */
    void initMapSelectScene();
    /**
     * @brief Inicializa o ObjectsDock.
     *
     */
    void initObjectsDock();

    /**
     * @brief Recarrega a interface do editor.
     *
     */
    void reloadEditorInterface();

    /**
     * @brief Realiza ação de refazer do editor.
     *
     */
    void editorUndo();
    /**
     * @brief Realiza ação de desfazer do editor.
     *
     */
    void editorRedo();

    /**
     * @brief Determina o grupo de tiles a ser desenhado. É representada como um
     * retângulo (x, y, largura, altura) = (iDrawTile, jDrawTile, diDrawTile, djDrawTile).
     *
     * @param iDrawTile A coluna do primeiro tile do grupo;
     * @param jDrawTile A linha do primeiro tile do grupo;
     * @param diDrawTile O número de tiles na horizontal do grupo;
     * @param djDrawTile O número de tiles na vertical do grupo;
     */
    void setDrawTile(int iDrawTile, int jDrawTile, int diDrawTile, int djDrawTile);

    /**
     * @brief Insere na pilha de "desfazer" um comando.
     *
     */
    void pushUndoChangesCommand();

    /**
     * @brief Insere no comando uma mudança.
     *
     * @param i Coluna do tile modificado.
     * @param j Linha do tile modificado.
     * @param layer Camada do tile modificado.
     * @param beforeTileI Valor coluna anterior do tile.
     * @param beforeTileJ Valor linha anterior do tile.
     * @param beforeTileset Tileset anterior do tile.
     * @param afterTileI Valor coluna nova do tile.
     * @param afterTileJ Valor linha nova do tile.
     * @param afterTileset Tileset novo do tile.
     */
    void pushUndoChange(int i, int j, int layer, int beforeTileI, int beforeTileJ,
                        TileSet *beforeTileset, int afterTileI, int afterTileJ,
                        TileSet *afterTileset);
    /**
     * @brief Troca um Tile.
     *
     * @param i Coluna do tile;
     * @param j Linha do tile;
     * @param tileI Valor coluna do tile;
     * @param tileJ Valor linha do tile;
     * @param layer Valor da camada do tile;
     * @param tileset Tileset do Tile.
     */
    void changeTile(int i, int j, int tileI, int tileJ, int layer, TileSet *tileset);
    /**
     * @brief Muda tiles colocando, naquela posição, e de acordo com o modo de pintura, os Tiles
     * selecionados (iDrawTile, jDrawTile, diDrawtile, djDrawTile).
     *
     * @param i Coluna
     * @param j Linha
     */
    void changeTile(int i, int j);

    /**
     * @brief Muda tiles colocando, nas posições, e de acordo com o modo de pintura, os Tiles
     * selecionados (iDrawTile, jDrawTile, diDrawtile, djDrawTile).
     *
     * @param iStart Coluna inicial
     * @param jStart Linha inicial
     * @param iEnd Coluna final
     * @param jEnd Linha final
     */
    void changeTiles(int iStart, int jStart, int iEnd, int jEnd);
    /**
     * @brief Determina o valor do copyArray. É um array utilizado para copiar Tiles de um ponto
     * e colocá-los nos Tiles de seleção para serem pintados posteriormente.
     *
     * @param iStart Coluna inicial.
     * @param jStart Linha inicial.
     * @param iEnd Coluna final.
     * @param jEnd Linha final.
     */

    void setCopyArray(int iStart, int jStart, int iEnd, int jEnd);

    /**
     * @brief Preenche um espaço. A função não está funcionando muito bem.
     *
     * @param nodeI
     * @param nodeJ
     * @param targetI
     * @param targetJ
     * @param replacementI
     * @param replacementJ
     */
    void floodFill(int nodeI, int nodeJ, int targetI, int targetJ, int replacementI, int replacementJ);

    /**
     * @brief Preenche um espaço com algoritmo força bruta. É usado no modo de pintura "balde de tinta"
     *
     * @param nodeI Coluna do nó fonte;
     * @param nodeJ Linha do nó fonte;
     * @param targetI Valor i do nó fonte;
     * @param targetJ Valor j do nó fonte;
     * @param targetTileset Tileset i do nó fonte;
     * @param replacementI Substituição i do nó;
     * @param replacementJ Substituição j do nó;
     * @param replacementTileset Substituição de Tileset do nó;
     */
    void floodFillBrute(int nodeI, int nodeJ, int targetI, int targetJ, TileSet *targetTileset, int replacementI, int replacementJ, TileSet *replacementTileset);

    /**
     * @brief Abre janela de novo mapa.
     *
     */
    void openNewMapWindow();
    /**
     * @brief Abra janela de editar mapa.
     *
     * @param map Mapa a ser editado.
     */
    void openEditMapWindow(Map *map);
    /**
     * @brief Cria novo mapa.
     *
     * @param newMap Novo mapa.
     */
    void createNewMap(Map *newMap);
    /**
     * @brief Atualiza os widgets do mapa quanto a Tileset e objetos.
     *
     */
    void refreshMapWidgets();
    /**
     * @brief Cria uma pasta.
     *
     */
    void createFolder();
    /**
     * @brief Seleciona um mapa.
     *
     * @param map Mapa a ser selecionado.
     */
    void selectMap(Map *map);
    /**
     * @brief Determina o objeto no cursor (na cena do mapa).
     *
     */
    void setCurrentObjectAtCursor();

    /**
     * @brief Adiciona uma instância no mapa.
     *
     * @param gameObjectInstance Instância do objeto a ser adicionada.
     */
    void addGameObjectInstanceToEditingMap(GameObjectInstance *gameObjectInstance);


    /**
     * @brief Determina o modo do editor.
     *
     * @param mode
     */
    void setEditorMode(int mode);
    /**
     * @brief Determina o modo de pintura.
     *
     * @param mode
     */

    void setEditorDrawMode(int mode);

    /**
     * @brief Determina o zoom do editor. Função ainda em desenvolvimento.
     *
     * @param zoom
     */
    void setEditorZoom(int zoom);

    /**
     * @brief Determina a camada do editor.
     *
     * @param layer Número da camada.
     */
    int setMapEditorLayer(int layer);

    /**
     * @brief Determina o texto na status bar do programa.
     *
     * @param text
     */
    void setStatusBarText(QString text);




    /**
     * @brief Obtém a lista de objetos.
     *
     */
    std::vector<GameObject*>* getObjectList();
    /**
     * @brief Obtém a lista de Tilesets.
     *
     */
    std::vector<TileSet*>* getTilesetList();
    /**
     * @brief Obtém a lista de mapas.
     *
     */
    std::vector<Map*>* getMaplist();
    /**
     * @brief Obtém a lista de animações.
     *
     */
    std::vector<AnimationData*>* getAnimationDataList();
    /**
     * @brief Obtém a lista de fundos
     *
     */
    std::vector<Background*>* getBackgroundList();

    /**
     * @brief Abra a janela de configurações gerais.
     *
     * @param gameObject
     */
    void openConfigsTabWindow(GameObject* gameObject);
    /**
     * @brief Abre a janela de novo objeto simplificada.
     *
     */
    void openEasyNewGameObjectDialog();
    /**
     * @brief Abra a jenela de novo diálogo.
     *
     */
    void openNewDialogueDialog();
    /**
     * @brief Abra a jenela de novo diálogo.
     *
     * @param gameObject Objeto dono do Diálogo.
     */
    void openNewDialogueDialog(GameObjectInstance *gameObject);
    /**
     * @brief Abra a jenela de editar diálogo.
     *
     * @param dialogueData Diálogo a ser editado.
     */
    void openNewDialogueDialog(DialogueData *dialogueData);
    /**
     * @brief Abra a jenela de novo diálogo.
     *
     * @param map Mapa dono do diálogo.
     */
    void openNewDialogueDialog(Map *map);
    /**
     * @brief Abra a jenela de novo diálogo.
     *
     * @param eventData Evento dono do diálogo.
     */
    void openNewDialogueDialog(EventData *eventData);

    QUndoStack *undoStack; /**< Pilha de "desfazer" */
    QAction *undoAction, *redoAction; /**< Ações de "desfazer" e "refazer" */

    /**
     * @brief Obtém mapa selecionado.
     *
     */
    Map* getSelectedMap();
    /**
     * @brief Obtém objeto selecionado.
     *
     */
    GameObject* getSelectedObject();
    /**
     * @brief Desseleciona objeto.
     *
     */
    void unSelectObject();

    boost::multi_array<Point, 2> *copyArray; /**< Array de cópia de Tiles. */


    int iDrawTile; /**< A coluna do primeiro tile do grupo; */
    int jDrawTile;  /**< A linha do primeiro tile do grupo; */
    int diDrawTile;  /**< O número de tiles na horizontal do grupo; */
    int djDrawTile; /**< O número de tiles na vertical do grupo; */
    int iClick, jClick; /**< Posições do mapa clicadas. */

    TileSet *drawTileset; /**< Tileset desenhado. */
    UndoChangeTileCommand *undoChangeTileCommand; /**< TODO */

    bool mapSceneInitializated; /**< Se a cena do mapa foi inicializada. */
    bool tileSceneInitializated; /**< Se a cena do Tileset foi inicializada */
    bool mapSelectSceneInitializated; /**< Se a cena do mapa foi inicializada */
    bool objectsDockInitializated; /**< Se a dock de objetos foi inicializada. */


    int editorMode; /**< Modo de editor: Pode ser: \n
                        - 0: modo de mapa;
                        - 1: modo de objetos;
                        - 2: modo de eventos; */
    int drawMode; /**< Modo de pintura. Pode ser: \n
                        - 0: modo de pincel;
                        - 1: modo de borracha
                        - 2: Modo de balde de tinta.
                        - 3: Modo de retângulo */
    static const int MODE_MAP = 0; /**< */
    static const int MODE_OBJECT = 1; /**< */
    static const int MODE_EVENT = 3; /**<  */


    static const int DRAW_MODE_PENCIL = 0; /**<  */
    static const int DRAW_MODE_ERASER = 1; /**<  */
    static const int DRAW_MODE_PAINT =  2; /**<  */
    static const int DRAW_MODE_SQUARE = 3; /**< */
    static const int DRAW_MODE_CIRCLE = 4; /**< */
    static const int DRAW_MODE_SELECT_SQUARE = 5; /**<  */
    static const int DRAW_MODE_SELECT_CIRCLE = 6; /**<   */

private:
    MainController *mainController; /**< T*/

    MainWindow *mainWindow; /**<  */

    TilesetDock *tilesetDock; /**< */
    MapSelectDock *mapSelectDock; /**< */
    ObjectsDock *objectsDock; /**<  */

    TilemapView *tilemapView; /**<  */
    TilemapScene *tilemapScene; /**<  */

    NewMapWindow *newMapWindow; /**<  */

    int editorLayer; /**< Camada em edição. */




};

#endif // MAPEDITORCONTROLLER_H
