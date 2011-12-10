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


#ifndef DATAWRITER_H
#define DATAWRITER_H

#include "gamedata.h"

#include "proceduredata.h"

class GameData;
class ProcedureData;

/**
 * @brief Classe da camada de persistência para salvar todos os os dados do projeto,
 * contidos em um arquivo padronizado como game.ldo.
 *
 */
class DataWriter
{
public:
    /**
     * @brief Construtor. Passa como parâmetro a instância da GameData que comporta
     * os dados do projeto.
     *
     * @param gameData
     */
    DataWriter(GameData *gameData);

    /**
     * @brief Salva em um arquivo todos os dados da instância da GameData passada pelo construtor.
     *
     * @param fileName arquivo a ser carregado.
     */
    bool save(std::string fileName);

private:


    /**
     * @brief Salva uma string no arquivo.
     *
     * @param string
     * @param fp ponteiro para o arquivo
     */
    void saveString(std::string *string, FILE *fp);

    /**
     * @brief Salva a lista de Tilesets no arquivo.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see Tileset
     */
    bool saveTilesetList(FILE *fp);

    /**
     * @brief Salva a lista de mapas no arquivo.
     *
     * @param fp ponteiro para o arquivo
     * @param list
     *
     * @see Map
     */
    bool saveMapList(FILE *fp, std::vector<Map*>* list);

    /**
     * @brief Salva a lista de objetos.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see GameObject
     */
    bool saveObjectList(FILE *fp);

    /**
     * @brief Salva a lista de objetos que rebatem BouncingBall,
     * na ordem dos objetos da lista.
     *
     * @param fp ponteiro para o arquivo
     */
    bool saveNpcObjectsToBounce(FILE *fp);

    /**
     * @brief Salva todas as habilidades dos objetos, na ordem
     * dos objetos da lista.
     *
     * @param fp ponteiro para o arquivo
     */
    bool saveObjectSkills(FILE *fp);

    /**
     * @brief Salva a lista de animações.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see AnimationData
     */
    bool saveAnimationDataList(FILE *fp);

    /**
     * @brief Salva a lista de fundos.
     *
     * @param fp ponteiro para o arquivo
     */
    bool saveBackgroundList(FILE *fp);


    /**
     * @brief Salva a lista de procedimentos.
     *
     * @param fp ponteiro para o arquivo
     * @param procedureList a lista de procedimentos a ser salva
     *
     * @see ProcedureData
     */
    bool saveProcedureList(FILE *fp, std::vector<ProcedureData*> *procedureList);

    /**
     * @brief Salva um procedimento.
     *
     * @param procedureData o procedimento a ser salvo
     * @param fp ponteiro para o arquivo
     *
     * @see ProcedureData
     */
    bool saveProcedure(ProcedureData *procedureData, FILE *fp);

    /**
     * @brief Salva todos os eventos.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see ProcedureData
     * @see EventData
     */
    bool saveAllEvents(FILE *fp);

    /**
     * @brief Salva todas as variáveis.
     *
     * @param variable
     * @param fp ponteiro para o arquivo
     */
    bool saveVariable(VariableData *variable, FILE *fp);

    /**
     * @brief Salva todas as listas de variáveis.
     *
     * @param fp ponteiro para o arquivo
     *
     * @see VariableData
     */
    bool saveAllVariableLists(FILE *fp);

    /**
     * @brief Salva todos os diálogos.
     *
     * @param dialogueData
     * @param fp ponteiro para o arquivo
     *
     * @see DialogueData
     */
    bool saveDialogueData(DialogueData *dialogueData, FILE *fp);

    /**
     * @brief Salva a lista de eventos.
     *
     * @param fp ponteiro para o arquivo
     * @param eventFunctionList
     *
     * @see EventData
     */
    bool saveEventList(FILE *fp, std::list<EventData*>* eventFunctionList);


    GameData *gameData; /**< GameData onde estão todos os dados a serem salvos. */

    static int CURRENT_VERSION; /**< Versão atual do arquivo.
                                Mudar sempre que houverem modificações na estrutura dele. */
};

#endif // DATAWRITER_H
