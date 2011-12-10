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


#ifndef DATALOADER_H
#define DATALOADER_H

#include "gamedata.h"
#include "proceduredata.h"


class GameData;
class ProcedureData;

/**
 * @brief Classe da camada de persistência para carregar todos os os dados do projeto,
 * contidos em um arquivo padronizado como game.ldo.
 *
 */
class DataLoader
{
public:
    /**
     * @brief Construtor. Passa como parâmetro a instância da GameData que irá
     * comportar os dados do projeto.
     *
     * @param gameData
     */
    DataLoader(GameData *gameData);

    /**
     * @brief Carrega na instância da GameData passada pelo construtor todos os dados
     * do arquivo.
     *
     * @param fileName arquivo a ser carregado.
     */
    bool load(std::string fileName);

private:

    /**
     * @brief Carrega uma string do arquivo.
     *
     * @param fp ponteiro para o arquivo
     */
    char* loadString(FILE *fp);

    /**
     * @brief Carrega a lista de Tilesets.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see TileSet
     */
    bool loadTilesetList(FILE *fp);

    /**
     * @brief Carrega a lista de mapas.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see Map
     */
    std::vector<Map*>* loadMapList(FILE *fp);

    /**
     * @brief Carrega a lista de classes de objetos.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see GameObject
     */
    bool loadObjectList(FILE *fp);

    /**
     * @brief Carrega as listas de objetos que rebatem BouncingBalls.
     * Essa lista é carregada percorrendo-se novamente a lista de objetos
     * e carregando suas listas de objetos que rebatem BouncingBalls.
     * O motivo para tal é que, só agora, temos todas as isntâncias de objetos
     * carregadas e podemos ligar os ponteiros adequadamente.
     *
     * @param fp ponteiro para o arquivo
     *
     */
    bool loadNpcObjectsToBounce(FILE *fp);

    /**
     * @brief Carrega as habilidades dos objetos. Para isso, percorre novamente
     * a lista de objetos e preenche com suas habilidades, na ordem.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see SkillData
     */
    bool loadObjectSkills(FILE *fp);

    /**
     * @brief Carrega a lista de animações do projeto.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see AnimationData
     */
    bool loadAnimationDataList(FILE *fp);

    /**
     * @brief Carrega a lista de fundos do projeto.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see Background
     * @see BgLayer
     */
    bool loadBackgroundList(FILE *fp);

    /**
     * @brief Carrega a lista de procedimentos do projeto.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see ProcedureData
     */
    std::vector<ProcedureData*>* loadProcedureList(FILE *fp);

    /**
     * @brief Carrega um procedimento.
     *
     * @param fp ponteiro para o arquivo
     *
     * @return ProcedureData o procedimento carregado.
     *
     * @see ProcedureData
     */
    ProcedureData *loadProcedure(FILE *fp);

    /**
     * @brief Carrega todos os eventos dos objetos. Percorre a lista de objetos
     * novamente e vai preenchendo em ordem.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see ProcedureData
     * @see EventData
     */
    bool loadAllEvents(FILE *fp);

    /**
     * @brief Carrega uma variável.
     *
     * @param fp ponteiro para o arquivo
     *
     * @return VariableData a variável carregada
     *
     * @see VariableData
     */
    VariableData* loadVariable(FILE *fp);

    /**
     * @brief Carrega todas as listas de variáveis.
     *
     * @param fp ponteiro para o arquivo
     */
    bool loadAllVariableLists(FILE *fp);

    /**
     * @brief Carrega um diálogo.
     *
     * @param fp ponteiro para o arquivo
     *
     * @return DialogueData o diálogo carregado.
     */
    DialogueData *loadDialogueData(FILE *fp);

    /**
     * @brief Carrega a lista de eventos.
     *
     * @param fp ponteiro para o arquivo
     * @param parent
     *
     * @return std::list<EventData*> a lista de eventos lida.
     */
    std::list<EventData*> loadEventList(FILE *fp, EventData *parent = 0);

    GameData *gameData; /**< A instância da GameData onde serão armazenados todos os dados lidos. */
};

#endif // DATALOADER_H
