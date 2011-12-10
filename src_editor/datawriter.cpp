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



#include "datawriter.h"

int DataWriter::CURRENT_VERSION = 0;

DataWriter::DataWriter(GameData *gameData)
    : gameData(gameData)
{
}


void DataWriter::saveString(std::string *str, FILE *fp) {
    int tamanho_string = str->size();
    fwrite(&tamanho_string, 1, sizeof(int), fp);
    fwrite(str->c_str(), tamanho_string, sizeof(char), fp);


}

bool DataWriter::save(std::string fileName) {
    FILE *fp;


    fp = fopen(fileName.c_str(), "wb");

    if(fp == NULL) {
        printf("erro ao salvar %s.\n", fileName.c_str());
        exit(1);
    }

    /* gravando o numero magico para indicar que é um arquivo de projeto do Ludo */
    fwrite(&gameData->MAGIC_NUMBER, 1, sizeof(int), fp);



    /* número da versão */
    fwrite(&CURRENT_VERSION, 1, sizeof(int), fp);

    /* gravando o tamanho do nome do jogo, seguido do nome propriamente dito */
    int tamanho_nome_jogo;
    tamanho_nome_jogo = gameData->gameName->size();

    fwrite(&tamanho_nome_jogo, 1, sizeof(int), fp);
    fwrite(gameData->gameName->c_str(), gameData->gameName->size(), sizeof(char), fp);

    /* gravando a resolução do jogo */
    fwrite(&gameData->resWidth, 1, sizeof(int), fp);
    fwrite(&gameData->resHeight, 1, sizeof(int), fp);

    fwrite(&gameData->deathAction, 1, sizeof(int), fp);
    fwrite(&gameData->gameOverAction, 1, sizeof(int), fp);
    fwrite(&gameData->looseLifes, 1, sizeof(bool), fp);
    fwrite(&gameData->totalLives, 1, sizeof(int), fp);

    saveTilesetList(fp);

    /* inicio das adicoes - 12 de março - PENDENTES NO RUNTIME */
    saveAnimationDataList(fp);
    /* fim */

    saveObjectList(fp);
    saveNpcObjectsToBounce(fp);
    saveObjectSkills(fp);

    saveBackgroundList(fp);

    saveMapList(fp, gameData->mapList);

    saveAllVariableLists(fp);

    saveAllEvents(fp);

    /* gravando os nomes das imagens das telas principais */
    saveString(&gameData->titleScreenData.backgroundFile, fp);
    saveString(&gameData->optionsScreenFile, fp);
    saveString(&gameData->gameoverScreenFile, fp);

    /* gravando os nomes das musicas das telas principais */
    saveString(&gameData->titleScreenMusic, fp);
    saveString(&gameData->optionsScreenMusic, fp);
    saveString(&gameData->gameOverScreenMusic, fp);

    /* gravando a id do mapa inicial */
    fwrite(&gameData->idFirstMap, 1, sizeof(int), fp);

    fclose(fp);

    return true;
}

bool DataWriter::saveTilesetList(FILE *fp) {
    int tileSetListSize;
    tileSetListSize = gameData->tileSetList->size();

    fwrite(&tileSetListSize, 1, sizeof(int), fp);

    for(std::vector<TileSet*>::iterator it = gameData->tileSetList->begin(); it != gameData->tileSetList->end(); ++it) {
        TileSet* tileset = (*it);

        fwrite(&tileset->id, 1, sizeof(int), fp);

        saveString(&tileset->file, fp);

        saveString(&tileset->name, fp);

        fwrite(&tileset->width, 1, sizeof(int), fp);
        fwrite(&tileset->height, 1, sizeof(int), fp);

        fwrite(&tileset->maxX, 1, sizeof(int), fp);
        fwrite(&tileset->maxY, 1, sizeof(int), fp);

        fwrite(&tileset->tileSize, 1, sizeof(int), fp);

        // TODO: salvar o collisionmatrix

        int i, j;
        for(i = 0; i < tileset->maxX; i++) {
            for(j = 0; j < tileset->maxY; j++) {
                fwrite(&tileset->collisionMatrix[i][j], 1, sizeof(int), fp);
            }
        }



    }
    return true;
}


bool DataWriter::saveMapList(FILE *fp, std::vector<Map*>* list) {
    int mapListSize;
    mapListSize = list->size();

    fwrite(&mapListSize, 1, sizeof(int), fp);

    for(std::vector<Map*>::iterator it = list->begin(); it != list->end(); ++it) {
        Map* map = (*it);
        int tamanho_string;

        if(map->isFolder()) {
            int continue_int = 1;

            fwrite(&continue_int, 1, sizeof(int), fp);

            tamanho_string = map->mapName.size();
            fwrite(&tamanho_string, 1, sizeof(int), fp);
            fwrite(map->mapName.c_str(), tamanho_string, sizeof(char), fp);

            saveMapList(fp, map->filhos);
        } else {
            int null_int = 0;

            fwrite(&null_int, 1, sizeof(int), fp);

            fwrite(&(map->id), 1, sizeof(int), fp);

            tamanho_string = map->mapName.size();
            fwrite(&tamanho_string, 1, sizeof(int), fp);
            fwrite(map->mapName.c_str(), tamanho_string, sizeof(char), fp);

            fwrite(&(map->width), 1, sizeof(int), fp);
            fwrite(&(map->height), 1, sizeof(int), fp);

            fwrite(&(map->layers), 1, sizeof(int), fp);

            int tilesetListSize;
            if(map->tileSets != NULL && !map->tileSets->empty()) {
                tilesetListSize =  map->tileSets->size();
            } else {
                tilesetListSize = 0;
            }


            fwrite(&(tilesetListSize), 1, sizeof(int), fp);

            for(std::vector<TileSet*>::iterator it2 = map->tileSets->begin(); it2 != map->tileSets->end(); ++it2) {
                TileSet* tileSet = (*it2);

                fwrite(&(tileSet->id), 1, sizeof(int), fp);
            }

            /* ALTERACOES 22-FEV-2011 COMECAM AQUI */
            saveString(&map->music, fp);
            saveString(&map->sound, fp);

            fwrite(&map->loopMusic, 1, sizeof(int), fp);
            fwrite(&map->loopSound, 1, sizeof(int), fp);
            fwrite(&map->idFundo, 1, sizeof(int), fp);

            /* gravando as instancias de objetos */

            int nro_instancias = map->gameObjectInstances->size();
            fwrite(&nro_instancias, 1, sizeof(int), fp);

            for(std::vector<GameObjectInstance*>::iterator it2 = map->gameObjectInstances->begin(); it2 != map->gameObjectInstances->end(); ++it2) {
                GameObjectInstance *gameObjectInstance = *it2;

                fwrite(&gameObjectInstance->id, 1, sizeof(unsigned int), fp);
                fwrite(&gameObjectInstance->gameObject->id, 1,  sizeof(int), fp);
                fwrite(&gameObjectInstance->x, 1,  sizeof(int), fp);
                fwrite(&gameObjectInstance->y, 1,  sizeof(int), fp);

                fwrite(&gameObjectInstance->nroEventos, 1, sizeof(int), fp);
                fwrite(&gameObjectInstance->nroFalas, 1, sizeof(int), fp);

                fwrite(&gameObjectInstance->isCenter, 1, sizeof(bool), fp);
                fwrite(&gameObjectInstance->isMainObject, 1, sizeof(bool), fp);

                saveDialogueData(gameObjectInstance->dialogueData, fp);

            }



            /* ALTERACOES 22-FEV-2011 TERMINAM AQUI */


            /* salvando o mapa */
            int i, j, k;
            for(i = 0; i < map->width; i++) {
                for(j = 0; j < map->height; j++) {
                    for(k = 0; k < map->layers; k++) {
                        fwrite(&(map->map[i][j][k].x), 1, sizeof(int), fp);
                        fwrite(&(map->map[i][j][k].y), 1, sizeof(int), fp);
                        TileSet *mapTileSet = map->map[i][j][k].z;

                        if(mapTileSet == NULL) {
                            int null_int = -1;
                            fwrite(&null_int, 1, sizeof(int), fp);
                        } else {
                            printf("MapTileset: %d\n", mapTileSet->id);
                            fwrite(&(mapTileSet->id), 1, sizeof(int), fp);
                        }


                    }
                }
            }


            /* salvando teleport areas */
            int nro_teleport_areas;
            nro_teleport_areas = map->teleportAreas->size();
            fwrite(&nro_teleport_areas, 1, sizeof(int), fp);

            for(std::vector<TeleportArea*>::iterator it = map->teleportAreas->begin(); it != map->teleportAreas->end(); ++it) {
                TeleportArea* teleportArea = *it;

                fwrite(&teleportArea->id, 1, sizeof(int), fp);
                fwrite(&teleportArea->mapId, 1, sizeof(int), fp);
                fwrite(&teleportArea->mapPositionDetermined, 1, sizeof(bool), fp);
                fwrite(&teleportArea->mapPosX, 1, sizeof(int), fp);
                fwrite(&teleportArea->mapPosY, 1, sizeof(int), fp);
                fwrite(&teleportArea->x, 1, sizeof(int), fp);
                fwrite(&teleportArea->y, 1, sizeof(int), fp);
                fwrite(&teleportArea->w, 1, sizeof(int), fp);
                fwrite(&teleportArea->h, 1, sizeof(int), fp);
                fwrite(&teleportArea->showVictoryAnimation, 1, sizeof(bool), fp);

            }

            /* salvando o fundo */
            if(map->background != NULL) {
                fwrite(&map->background->id, 1, sizeof(int), fp);
            } else {
                int null_int = -1;
                fwrite(&null_int, 1, sizeof(int), fp);
            }

            saveDialogueData(map->dialogueData, fp);




        }




    }

    return true;
}

bool DataWriter::saveObjectList(FILE *fp) {
    std::vector<GameObject*> *list;
    list = gameData->objectList;

    int nro_objetos = gameData->objectList->size();
    fwrite(&nro_objetos, 1, sizeof(int), fp);

    for(std::vector<GameObject*>::iterator it = list->begin(); it != list->end(); ++it) {
        GameObject* gameObject = *it;

        fwrite(&gameObject->id, 1, sizeof(int), fp);
        saveString(&gameObject->name, fp);
        fwrite(&gameObject->type, 1, sizeof(int), fp);

        fwrite(&gameObject->isObjetoUnico, 1, sizeof(bool), fp);
        fwrite(&gameObject->formaGrafica, 1, sizeof(int), fp);
        fwrite(&gameObject->tipoMovimento, 1, sizeof(int), fp);

        saveString(&gameObject->soundDamage, fp);
        saveString(&gameObject->soundSpecial, fp);

        fwrite(&gameObject->isDraggable, 1, sizeof(bool), fp);

        fwrite(&gameObject->formaMovimentoMouse, 1, sizeof(int), fp);
        fwrite(&gameObject->vx, 1, sizeof(int), fp);
        fwrite(&gameObject->vy, 1, sizeof(int), fp);
        fwrite(&gameObject->ax, 1, sizeof(int), fp);
        fwrite(&gameObject->ay, 1, sizeof(int), fp);
        fwrite(&gameObject->dax, 1, sizeof(int), fp);
        fwrite(&gameObject->day, 1, sizeof(int), fp);
        fwrite(&gameObject->gravidade, 1, sizeof(int), fp);
        fwrite(&gameObject->intensidadePulo, 1, sizeof(int), fp);
        fwrite(&gameObject->evolucaoPorNivel, 1, sizeof(int), fp);

        /* inicio das adicoes - 12 de março - PENDENTES NO RUNTIME */

        fwrite(&gameObject->hp, 1, sizeof(int), fp);
        fwrite(&gameObject->mp, 1, sizeof(int), fp);
        fwrite(&gameObject->atk, 1, sizeof(int), fp);
        fwrite(&gameObject->def, 1, sizeof(int), fp);
        fwrite(&gameObject->intelig, 1, sizeof(int), fp);
        fwrite(&gameObject->levelInicial, 1, sizeof(int), fp);
        fwrite(&gameObject->levelMax, 1, sizeof(int), fp);
        fwrite(&gameObject->velocidadeEvolucao, 1, sizeof(int), fp);
        fwrite(&gameObject->resolveCollision, 1, sizeof(int), fp);

        if(gameObject->type == GameObject::INIMIGO || gameObject->type == GameObject::NPC ||
           gameObject->type == GameObject::ITEM) {
            fwrite(&gameObject->formaMovimentacaoNpcItem, 1, sizeof(int), fp);
            fwrite(&gameObject->movimentaApenasDentroTela, 1, sizeof(bool), fp);
            fwrite(&gameObject->raioMovimentacao, 1, sizeof(int), fp);

            if(gameObject->type == GameObject::INIMIGO) {

                fwrite(&gameObject->derrotaEncostandoInimigo, 1, sizeof(bool), fp);
                fwrite(&gameObject->derrotaAtirandoItemMagiaInimigo, 1, sizeof(bool), fp);
                fwrite(&gameObject->derrotaAcertandoEspadaSobreInimigo, 1, sizeof(bool), fp);
                fwrite(&gameObject->derrotaPulandoSobreInimigo, 1, sizeof(bool), fp);
                fwrite(&gameObject->atacaEncostaPersonagem, 1, sizeof(bool), fp);
                fwrite(&gameObject->atacaEncostaPersonagemDano, 1, sizeof(int), fp);
                fwrite(&gameObject->atacaUsandoEspada, 1, sizeof(bool), fp);
                fwrite(&gameObject->espadaItemId, 1, sizeof(int), fp);
                fwrite(&gameObject->atacaUsandoEspadaDano, 1, sizeof(int), fp);

                fwrite(&gameObject->atiraItemMaginaDirecaoEstiver, 1, sizeof(bool), fp);
                fwrite(&gameObject->atiraItemMaginaDirecaoEstiverIdItem, 1, sizeof(int), fp);
                fwrite(&gameObject->atiraItemMaginaDirecaoEstiverDano, 1, sizeof(int), fp);

                fwrite(&gameObject->atiraItemMagiaDirecaoPersonagem, 1, sizeof(bool), fp);
                fwrite(&gameObject->atiraItemMagiaDirecaoPersonagemIdItem, 1, sizeof(int), fp);
                fwrite(&gameObject->atiraItemMagiaDirecaoPersonagemDano, 1, sizeof(int), fp);

                fwrite(&gameObject->tempoAtaque, 1, sizeof(float), fp);
                fwrite(&gameObject->magicCost, 1, sizeof(int), fp);

                fwrite(&gameObject->experiencePoints, 1, sizeof(int), fp);
                fwrite(&gameObject->defeatPoints, 1, sizeof(int), fp);


            } else if(gameObject->type == GameObject::NPC) {
                fwrite(&gameObject->nroFalas, 1, sizeof(int), fp);
            } else if(gameObject->type == GameObject::ITEM) {
                fwrite(&gameObject->concedePontos, 1, sizeof(bool), fp);
                fwrite(&gameObject->concedePontosValor, 1, sizeof(int), fp);
                fwrite(&gameObject->ganhaPerdeVida, 1, sizeof(bool), fp);
                fwrite(&gameObject->ganhaPerdeVidaValor, 1, sizeof(int), fp);
                fwrite(&gameObject->ganhaPerdeMagia, 1, sizeof(bool), fp);
                fwrite(&gameObject->ganhaPerdeMagiaValor, 1, sizeof(int), fp);
                fwrite(&gameObject->incrementaVariavel, 1, sizeof(bool), fp);
                fwrite(&gameObject->incrementaVariavelIdVariavel, 1, sizeof(int), fp);
                fwrite(&gameObject->incrementaVariavelValor, 1, sizeof(int), fp);
                fwrite(&gameObject->ativaEvento, 1, sizeof(bool), fp);
                fwrite(&gameObject->ativaEventoIdEvento, 1, sizeof(int), fp);
                fwrite(&gameObject->concedeHabilidade, 1, sizeof(bool), fp);
                fwrite(&gameObject->concedeHabilidadeIdHabilidade, 1, sizeof(int), fp);

                fwrite(&gameObject->comportamentoEncostarPersonagem, 1, sizeof(int), fp);
                fwrite(&gameObject->desapareceEncostarPersonagem, 1, sizeof(bool), fp);
                fwrite(&gameObject->desapareceEncostarParede, 1, sizeof(bool), fp);
            }
        }




        fwrite(&gameObject->possuiEventos, 1, sizeof(bool), fp);


        /* fim das adicoes - 12 de março */

        int nro_gameobject_animations = gameObject->gameObjectAnimations->size();
        fwrite(&nro_gameobject_animations, 1, sizeof(int), fp);

        for(std::vector<GameObjectAnimation*>::iterator it2 = gameObject->gameObjectAnimations->begin();
        it2 != gameObject->gameObjectAnimations->end(); ++it2) {
            GameObjectAnimation *gameObjectAnimation = *it2;

            fwrite(&gameObjectAnimation->id, 1, sizeof(int), fp);
            fwrite(&gameObjectAnimation->type, 1, sizeof(int), fp);

            /* inicio das adicoes - 12 de março - PENDENTES NO RUNTIME */
            fwrite(&gameObjectAnimation->numDirectionFactor, 1, sizeof(int), fp);

            int nro_types = gameObjectAnimation->types->size();
            fwrite(&nro_types, 1, sizeof(int), fp);

            for(std::vector<int>::iterator it3 = gameObjectAnimation->types->begin();
            it3 != gameObjectAnimation->types->end(); ++it3) {
                int valor_type = *it3;
                fwrite(&valor_type, 1, sizeof(int), fp);
            }

            int nro_horizontal_inverts = gameObjectAnimation->horizontalInvert.size();
            fwrite(&nro_horizontal_inverts, 1, sizeof(int), fp);

            for(std::vector<bool>::iterator it3 = gameObjectAnimation->horizontalInvert.begin();
            it3 != gameObjectAnimation->horizontalInvert.end(); ++it3) {
                bool valor_horinv = *it3;
                fwrite(&valor_horinv, 1, sizeof(bool), fp);
            }

            int nro_vertical_inverts = gameObjectAnimation->verticalInvert.size();
            fwrite(&nro_vertical_inverts, 1, sizeof(int), fp);

            for(std::vector<bool>::iterator it3 = gameObjectAnimation->verticalInvert.begin();
            it3 != gameObjectAnimation->verticalInvert.end(); ++it3) {
                bool valor_verinv = *it3;
                fwrite(&valor_verinv, 1, sizeof(bool), fp);
            }

            int nro_adjustments = gameObjectAnimation->adjustments.size();
            fwrite(&nro_adjustments, 1, sizeof(int), fp);

            for(std::vector<Point>::iterator it3 = gameObjectAnimation->adjustments.begin();
            it3 != gameObjectAnimation->adjustments.end(); ++it3) {
                Point point = *it3;
                fwrite(&point.x, 1, sizeof(int), fp);
                fwrite(&point.y, 1, sizeof(int), fp);
            }

            /* fim das adicoes - 12 de março */

            saveString(&gameObjectAnimation->name, fp);

            int nro_sprites = gameObjectAnimation->sprites->size();
            fwrite(&nro_sprites, 1, sizeof(int), fp);

            for(std::vector<Sprite*>::iterator it3 = gameObjectAnimation->sprites->begin();
            it3 != gameObjectAnimation->sprites->end(); ++it3) {
                Sprite *sprite = *it3;

                fwrite(&sprite->id, 1, sizeof(int), fp);
                fwrite(&sprite->direction, 1, sizeof(int), fp);

                /* inicio das adicoes - 12 de março - PENDENTES NO RUNTIME */
                fwrite(&sprite->activated, 1, sizeof(bool), fp);
                fwrite(&sprite->hascolorkey, 1, sizeof(bool), fp);
                fwrite(&sprite->r_colorkey, 1, sizeof(int), fp);
                fwrite(&sprite->g_colorkey, 1, sizeof(int), fp);
                fwrite(&sprite->b_colorkey, 1, sizeof(int), fp);



                /* fim das adicoes - 12 de março */
                saveString(&sprite->spriteFileName, fp);
            }

            /* inicio das adicoes - 12 de março - PENDENTES NO RUNTIME */
            int nro_animations = gameObjectAnimation->animations->size();
            fwrite(&nro_animations, 1, sizeof(int), fp);


            for(std::vector<AnimationData*>::iterator it3 = gameObjectAnimation->animations->begin();
                it3 != gameObjectAnimation->animations->end(); ++it3) {
                AnimationData* animationData = *it3;

                if(animationData == NULL) {
                    int nullInt = -1;
                    fwrite(&nullInt, 1, sizeof(int), fp);
                } else {
                    fwrite(&animationData->id, 1, sizeof(int), fp);
                }


            }
            /* fim das adicoes - 12 de março */

            // TODO: fazer loop escrita de animations quando estiverem prontas


        }




    }

    return true;
}

bool DataWriter::saveNpcObjectsToBounce(FILE *fp) {
    for(std::vector<GameObject*>::iterator it = gameData->objectList->begin(); it != gameData->objectList->end(); ++it) {
        GameObject *gameObject = *it;

        if(gameObject->type == GameObject::PONG_BALL_OBJECT) {
            int gameObjectsToAddCount = gameObject->listObjectsToBounce.size();
            fwrite(&gameObjectsToAddCount, 1, sizeof(int), fp);

            for(std::list<GameObject*>::iterator it = gameObject->listObjectsToBounce.begin(); it != gameObject->listObjectsToBounce.end(); ++it) {
                GameObject *gameObjectIt = *it;

                fwrite(&gameObjectIt->id, 1, sizeof(int), fp);
            }
        }
    }
}


bool DataWriter::saveObjectSkills(FILE *fp) {
    for(std::vector<GameObject*>::iterator it = gameData->objectList->begin(); it != gameData->objectList->end(); ++it) {
        GameObject *gameObject = *it;

        int nroListaHabilidades = gameObject->listaHabilidades.size();

        fwrite(&nroListaHabilidades, 1, sizeof(int), fp);

        for(std::vector<SkillData*>::iterator it2 = gameObject->listaHabilidades.begin(); it2 != gameObject->listaHabilidades.end(); ++it2) {
            SkillData* skillData = *it2;

            fwrite(&skillData->id, 1, sizeof(int), fp);
            fwrite(&skillData->intensity, 1, sizeof(int), fp);
            fwrite(&skillData->magicCost, 1, sizeof(int), fp);
            fwrite(&skillData->level, 1, sizeof(int), fp);
            fwrite(&skillData->skill->id, 1, sizeof(int), fp);
            fwrite(&skillData->isMagical, 1, sizeof(int), fp);

            saveString(&skillData->sound, fp);

            if(skillData->skillObject == NULL) {
                int null_int = -1;
                fwrite(&null_int, 1, sizeof(int), fp);
            } else {
                fwrite(&skillData->skillObject->id, 1, sizeof(int), fp);
            }

            if(skillData->skillProvider == NULL) {
                int null_int = -1;
                fwrite(&null_int, 1, sizeof(int), fp);
            } else {
                fwrite(&skillData->skillProvider->id, 1, sizeof(int), fp);
            }

        }




    }

    return true;
}

bool DataWriter::saveAnimationDataList(FILE *fp) {
    int tamanhoLista;

    tamanhoLista = gameData->animationDataList->size();
    fwrite(&tamanhoLista, 1, sizeof(int), fp);

    for(std::vector<AnimationData*>::iterator it = gameData->animationDataList->begin(); it != gameData->animationDataList->end(); ++it) {
        AnimationData* animationData = *it;

        fwrite(&animationData->id, 1, sizeof(int), fp);

        saveString(&animationData->fileName, fp);
        saveString(&animationData->name, fp);

        fwrite(&animationData->colorkey_b, 1, sizeof(int), fp);
        fwrite(&animationData->colorkey_g, 1, sizeof(int), fp);
        fwrite(&animationData->colorkey_r, 1, sizeof(int), fp);

        fwrite(&animationData->frameLoop, 1, sizeof(int), fp);
        fwrite(&animationData->hasColorkey, 1, sizeof(bool), fp);
        fwrite(&animationData->hasLoop, 1, sizeof(bool), fp);
        int valor = animationData->getHorizontalFrameNumber();
        fwrite(&valor, 1, sizeof(int), fp);
        fwrite(&animationData->horizontalSpacing, 1, sizeof(int), fp);
        fwrite(&animationData->order, 1, sizeof(int), fp);
        fwrite(&animationData->velocity, 1, sizeof(int), fp);
        valor = animationData->getVerticalFrameNumber();
        fwrite(&valor, 1, sizeof(int), fp);
        fwrite(&animationData->verticalSpacing, 1, sizeof(int), fp);

        fwrite(&animationData->startX, 1, sizeof(int), fp);
        fwrite(&animationData->startY, 1, sizeof(int), fp);
        fwrite(&animationData->endX, 1, sizeof(int), fp);
        fwrite(&animationData->endY, 1, sizeof(int), fp);


    }

    return true;
}



bool DataWriter::saveBackgroundList(FILE *fp) {
    int tamanhoLista = gameData->backgroundList->size();

    fwrite(&tamanhoLista, 1, sizeof(int), fp);

    for(std::vector<Background*>::iterator it = gameData->backgroundList->begin(); it != gameData->backgroundList->end(); ++it) {
        Background *bg = *it;

        fwrite(&bg->id, 1, sizeof(int), fp);
        saveString(&bg->name, fp);

        int tamanho_layer_list = bg->layerList->size();
        fwrite(&tamanho_layer_list, 1, sizeof(int), fp);

        for(std::vector<BgLayer*>::iterator it2 = bg->layerList->begin(); it2 != bg->layerList->end(); ++it2) {
            BgLayer *bgLayer = *it2;

            saveString(&bgLayer->fileName, fp);

            fwrite(&bgLayer->behavior, 1, sizeof(int), fp);
            fwrite(&bgLayer->displacementX, 1, sizeof(int), fp);
            fwrite(&bgLayer->displacementY, 1, sizeof(int), fp);
            fwrite(&bgLayer->repeatsHorizontally, 1, sizeof(int), fp);
            fwrite(&bgLayer->repeatsVertically, 1, sizeof(int), fp);
            fwrite(&bgLayer->vx, 1, sizeof(int), fp);
            fwrite(&bgLayer->vy, 1, sizeof(int), fp);
        }
    }

    return true;
}

bool DataWriter::saveAllEvents(FILE *fp) {
    // salvando a lista de eventos global
    saveProcedure(gameData->procedureGlobalAlways, fp);
    saveProcedure(gameData->procedureGlobalStart, fp);
    saveProcedure(gameData->procedureGlobalEnd, fp);

    saveProcedureList(fp, gameData->procedureList);

    // percorrendo a lista de objetos e salvando seus eventos, em sequência

    for(std::vector<GameObject*>::iterator it = gameData->objectList->begin(); it != gameData->objectList->end(); ++it) {
        GameObject* gameObject = *it;

        saveProcedure(gameObject->procedureGlobalAlways, fp);
        saveProcedure(gameObject->procedureGlobalStart, fp);
        saveProcedure(gameObject->procedureGlobalEnd, fp);

        saveProcedureList(fp, gameObject->procedureList);
    }



    return true;
}


bool DataWriter::saveVariable(VariableData *variable, FILE *fp) {
    fwrite(&variable->id, 1, sizeof(int), fp);
    saveString(&variable->name, fp  );
    fwrite(&variable->type, 1, sizeof(int), fp);
    fwrite(&variable->value, 1, sizeof(float), fp);
}


bool DataWriter::saveAllVariableLists(FILE *fp) {

    // gravando as variáveis globais
    int count_n_variables = gameData->variableList->size();
    fwrite(&count_n_variables, 1, sizeof(int), fp);

    for(std::vector<VariableData*>::iterator it = gameData->variableList->begin(); it != gameData->variableList->end(); ++it) {
        VariableData *variableData = *it;

        saveVariable(variableData, fp);
    }

    // gravando as variáveis dos objetos
    for(std::vector<GameObject*>::iterator it1 = gameData->objectList->begin(); it1 != gameData->objectList->end(); ++it1) {
        GameObject *gameObject = *it1;

        count_n_variables = gameObject->variableList->size();
        fwrite(&count_n_variables, 1, sizeof(int), fp);

        for(std::vector<VariableData*>::iterator it2 = gameObject->variableList->begin(); it2 != gameObject->variableList->end(); ++it2) {
            VariableData* variableData = *it2;

            saveVariable(variableData, fp);
        }
    }

    return true;
}



bool DataWriter::saveProcedureList(FILE *fp, std::vector<ProcedureData *> *procedureList) {
    int sizeProcedureList;
    sizeProcedureList = procedureList->size();

    fwrite(&sizeProcedureList, 1, sizeof(int), fp);

    for(std::vector<ProcedureData*>::iterator it = procedureList->begin(); it != procedureList->end(); ++it) {
        ProcedureData *procedureData = *it;

        saveProcedure(procedureData, fp);
    }


}


bool DataWriter::saveProcedure(ProcedureData *procedureData, FILE *fp) {
    fwrite(&procedureData->id, 1, sizeof(int), fp);
    saveString(&procedureData->name, fp);
    fwrite(&procedureData->nameEditable, 1, sizeof(int), fp);

    saveEventList(fp, &procedureData->events);

}

bool DataWriter::saveDialogueData(DialogueData *dialogueData, FILE *fp) {
    bool dialogueDataNotExists;

    if(dialogueData == NULL) {
        dialogueDataNotExists = true;

        fwrite(&dialogueDataNotExists, 1, sizeof(bool), fp);
    } else {
        dialogueDataNotExists = false;

        fwrite(&dialogueDataNotExists, 1, sizeof(bool), fp);

        int itemNumber = dialogueData->dialogueItems.size();

        fwrite(&itemNumber, 1, sizeof(int), fp);

        for(std::list<DialogueItemData*>::iterator it = dialogueData->dialogueItems.begin(); it != dialogueData->dialogueItems.end(); ++it) {
            DialogueItemData *dialogueItemData = *it;

            fwrite(&dialogueItemData->type, 1, sizeof(int), fp);
            if(dialogueItemData->type == DialogueItemData::TYPE_MESSAGE) {
                saveString(&dialogueItemData->message, fp);
                saveString(&dialogueItemData->associatedImage, fp);
                fwrite(&dialogueItemData->associatedImageAtCenter, 1, sizeof(bool), fp);
            } else {
                fwrite(&dialogueItemData->procedureId, 1, sizeof(bool), fp);
            }
        }
    }
}

bool DataWriter::saveEventList(FILE *fp, std::list<EventData *> *eventFunctionList) {
    int eventListSize;

    if(eventFunctionList == NULL) {
        eventListSize = 0;
        fwrite(&eventListSize, 0, sizeof(int), fp);
    } else {
        eventListSize = eventFunctionList->size();

        fwrite(&eventListSize, 1, sizeof(int), fp);

        for(std::list<EventData*>::iterator it = eventFunctionList->begin(); it != eventFunctionList->end(); ++it) {
            EventData *eventData = *it;


            fwrite(&eventData->newEvent, 1, sizeof(int), fp);
            if(!eventData->newEvent) {
                fwrite(&eventData->type, 1, sizeof(int), fp);
                fwrite(&eventData->conditionType, 1, sizeof(int), fp);
                fwrite(&eventData->negate, 1, sizeof(bool), fp);

                fwrite(&eventData->opcode, 1, sizeof(int), fp);
                fwrite(&eventData->idAssociatedVariable, 1, sizeof(int), fp);
                fwrite(&eventData->idObject01, 1, sizeof(int), fp);
                fwrite(&eventData->instanceTypeObject01, 1, sizeof(int), fp);
                fwrite(&eventData->idObject02, 1, sizeof(int), fp);
                fwrite(&eventData->instanceTypeObject02, 1, sizeof(int), fp);
                fwrite(&eventData->valueType, 1, sizeof(int), fp);
                fwrite(&eventData->value01, 1, sizeof(int), fp);
                saveString(&eventData->stringValue, fp);
                saveDialogueData(eventData->dialogueData, fp);

                saveEventList(fp, &eventData->subEvents);

            }





        }
    }



    return true;
}

