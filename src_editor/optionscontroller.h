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


#ifndef OPTIONSCONTROLLER_H
#define OPTIONSCONTROLLER_H

#include <QFile>

#include <stdlib.h>
#include <sstream>
#include <string>

#include "maincontroller.h"
#include "eventseditorcontroller.h"
#include "configstabwindow.h"
#include "tileset.h"
#include "gameobject.h"
#include "background.h"
#include "easynewgameobjectdialog.h"
#include "map.h"
#include "eventdata.h"

#include "editorconstants.h"
#include "gameobjectinstance.h"
#include "variabledata.h"



class MainController;
class EventsEditorController;
class ConfigsTabWindow;
class TileSet;
class GameObject;
class EditorConstants;
class Background;
class EasyNewGameObjectDialog;
class Map;
class EventData;
class GameObjectInstance;
class VariableData;


/**
 * @brief Controladora de opções. Possui todas os métodos de negócio referentes a tela
 * de configurações gerais, excetuando-se a parte de eventos.
 *
 */
class OptionsController
{
public:
    /**
     * @brief Construtor.
     *
     */
    OptionsController();

    /**
     * @brief Fornece um pointeiro para a controladora principal.
     *
     * @param
     */
    void setMainController(MainController*);

    /**
     * @brief Fornece um pointeiro para a controladora do editor de eventos.
     *
     * @param eventsEditorController
     */
    void setEventsEditorController(EventsEditorController *eventsEditorController);

    /**
     * @brief Abre uma janela de configurações.
     *
     * @param parent
     */
    void openConfigsTabWindow(QWidget *parent);

    /**
     * @brief Abre uma janela de configurações aberta na aba de Objetos e com um objeto
     * específico selecionado.
     *
     * @param parent
     * @param gameObject objeto a ser selecionado.
     */
    void openConfigsTabWindow(QWidget *parent, GameObject *gameObject);


    /**
     * @brief Determina Uma tela do jogo;
     *
     * @param fileName Nome do arquivo;
     * @param option Tela do jogo: \n
                        - 0: Tela de título;
                        - 1: Tela de opções;
                        - 2: Tela de Game Over;
     */
    void setGameScreen(std::string fileName, int option);

    /**
     * @brief Importa um recurso para o projeto, colocando o arquivo em sua pasta respectiva;
     *
     * @param filePathToImport Caminho do arquivo a ser importado;
     * @param importType Tipo de importação: \n
                            - 0: Tileset;
                            - 1: Tela de título;
                            - 2: Animação;
                            - 3: Imagem estática (sprite);
                            - 4: Fundo;
                            - 5: Camada;
     */
    void importResource(std::string filePathToImport, int importType);


    /**
     * @brief Adiciona um objeto do tipo Tileset no projeto;
     *
     * @param fileName nome do arquivo. Também será o nome padrão do Tileset;
     *
     * @see TileSet
     */
    void addTileset(std::string fileName);

    /**
     * @brief Adiciona uma animação no projeto.
     *
     * @param animation O nome do arquivo da animação;
     * @param animationImportPattern O tipo pré-definido da animação: \n
                                    - 0: nenhum;
                                    - 1: ao estilo RPG Maker VX;
     * @see Animation
     */
    void addAnimation(std::string animation, int animationImportPattern);

    /**
     * @brief Adiciona um fundo no projeto;
     *
     * @param background nome do arquivo do fundo;
     */
    void addBackground(std::string background);

    /**
     * @brief Adiciona uma habilidade a um objeto;
     *
     * @param gameObject O objeto que terá a habilidade adicionada;
     * @param skillData A habilidade a ser adicionada;
     *
     * @see SkillData
     */
    void addObjectSkill(GameObject *gameObject, SkillData *skillData);

    /**
     * @brief Remove uma habilidade de um objeto;
     *
     * @param gameObject O objeto que terá a hablidade removida;
     * @param skillData A habilidade a ser removida;
     *
     * @see SkillData
     */
    void removeObjectSkill(GameObject *gameObject, SkillData *skillData);

    /**
     * @brief Determina o valor da resolução da tela do jogo de acordo com o índice,
     * da combo escolhida na tela de configurações iniciais.
     *
     * @param index índice
     */
    void determinaValorResolucaoCombo(int index);


    /**
     * @brief Adiciona um objeto no projeto;
     *
     * @param name Nome do objeto;
     * @param type Tipo do objeto;
     *
     * @see GameObject
     */
    void addObject(std::string name, int type);

    /**
     * @brief Reincia um objeto para ser um determinado tipo. Só será mantido o nome e sua
     * representação gráfica.
     *
     * @param gameObject Objeto a ser reiniciado;
     * @param newType Novo tipo do objeto;
     *
     * @see GameObject
     */
    void resetObject(GameObject *gameObject, int newType);

    /**
     * @brief Verifica se um TileSet foi utilizado.
     *
     * @param tileset Tileset a ser verificado.
     *
     * @see TileSet
     */
    bool verifyUsedTileset(TileSet *tileset);


    /**
     * @brief Obtém a lista de objetos do projeto.
     *
     * @see GameObject
     */
    std::vector<GameObject*>* getObjectList();

    /**
     * @brief Obtém a lista de Tilesets do projeto.
     *
     * @see TileSet
     */
    std::vector<TileSet*>* getTilesetList();

    /**
     * @brief Obtém a lista de mapas do projeto.
     *
     * @see Map
     */
    std::vector<Map*>* getMaplist();

    /**
     * @brief Obtém a lista de animações do projeto.
     *
     * @see AnimationData
     */
    std::vector<AnimationData*>* getAnimationDataList();

    /**
     * @brief Obtém a lista de fundos do projeto.
     *
     * @see Background
     */
    std::vector<Background*>* getBackgroundList();

    /**
     * @brief Obtém a lista de variáveis globais do projeto.
     *
     * @see VariableData
     */
    std::vector<VariableData*>* getGlobalVariableDataList();



    /**
     * @brief Abri uma janela de novo objeto simplificada.
     *
     */
    void openEasyNewGameObjectDialog();

    /**
     * @brief Abre uma janeal de novo diálogo.
     *
     */
    void openNewDialogueDialog();

    /**
     * @brief Abre uma janela de novo diálogo para um objeto específico.
     *
     * @param gameObject Objeto a que pertence o diálogo.
     */
    void openNewDialogueDialog(GameObjectInstance *gameObject);
    /**
     * @brief Abre uma janela de editar diálogo.
     *
     * @param dialogueData O diálogo a ser editado.
     */
    void openNewDialogueDialog(DialogueData *dialogueData);
    /**
     * @brief Abre uma nova janela de diálogo de um mapa.
     *
     * @param map Mapa a que pertence o diálogo.
     */
    void openNewDialogueDialog(Map *map);

    /**
     * @brief Abre uma nova janela de diálogo de um evento.
     *
     * @param event Evento a que pertence o diálogo.
     */
    void openNewDialogueDialog(EventData *event);

    /**
     * @brief Remove um objeto da lista de objetos.
     *
     * @param gameObject o objeto a ser removido.
     */
    void removeObject(GameObject *gameObject);

    /**
     * @brief Remove um tileset da lista de tilesets.
     *
     * @param tileSet o tileset a ser removido.
     */
    void removeTileset(TileSet *tileSet);

    /**
     * @brief Remove uma animação da lista de animações.
     *
     * @param animationData a animação a ser removida.
     */
    void removeAnimation(AnimationData *animationData);


    /**
     * @brief Remove um fundo da lista de fundos.
     *
     * @param bg o fundo a ser removido.
     */
    void removeBackground(Background *bg);
private:
    MainController *mainController; /**< */
    EventsEditorController *eventsEditorController; /**< Controladora de editor de eventos */

    ConfigsTabWindow *configsTabWindow; /**< A janela de configurações gerais. */
};

#endif // OPTIONSCONTROLLER_H
