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



#include "dataloader.h"

DataLoader::DataLoader(GameData *gameData)
    : gameData(gameData)
{
}



char* DataLoader::loadString(FILE *fp) {
    char* string;
    int tamanho;

    fread(&tamanho, 1, sizeof(int), fp);
    string = (char*) calloc(tamanho + 1, sizeof(char));

    string[tamanho] = '\0';

    fread(string, sizeof(char), tamanho, fp);

    return string;

}

bool DataLoader::load(std::string fileName) {

    FILE *fp;
    fp = fopen(fileName.c_str(), "rb");

    /* lendo o numero magico e verificando se de fato é um número mágico */
    int magic_number;
    fread(&magic_number, 1, sizeof(int), fp);

    if(magic_number != gameData->MAGIC_NUMBER) {
        return false;
    }

    fread(&gameData->version, 1, sizeof(int), fp);

    gameData->filePath = fileName;

    /* lê o nome do jogo */
    /*
    char *nome_jogo;
    int tamanho_nome_jogo;

    fread(&tamanho_nome_jogo, 1, sizeof(int), fp);
    nome_jogo = (char*) calloc(tamanho_nome_jogo + 1, sizeof(char));
    nome_jogo[tamanho_nome_jogo] = '\0';

    fread(nome_jogo, sizeof(char), tamanho_nome_jogo, fp);
    */

    char *nome_jogo;
    nome_jogo = loadString(fp);

    gameData->gameName = new std::string(nome_jogo);

    /* lê a resolução do jogo */
    fread(&gameData->resWidth, 1, sizeof(int), fp);
    fread(&gameData->resHeight, 1, sizeof(int), fp);

    fread(&gameData->deathAction, 1, sizeof(int), fp);
    fread(&gameData->gameOverAction, 1, sizeof(int), fp);
    fread(&gameData->looseLifes, 1, sizeof(bool), fp);
    fread(&gameData->totalLives, 1, sizeof(int), fp);

    loadTilesetList(fp);

    /* inicio das adicoes - 12 de março - PENDENTES NO RUNTIME -- OK*/
    loadAnimationDataList(fp);
    /* fim */

    loadObjectList(fp);
    loadNpcObjectsToBounce(fp);
    loadObjectSkills(fp);

    loadBackgroundList(fp);

    gameData->mapList = loadMapList(fp);

    loadAllVariableLists(fp);

    loadAllEvents(fp);


    /*  lendo os nomes das imagens das telas principais */
    gameData->titleScreenData.backgroundFile = std::string(loadString(fp));
    gameData->optionsScreenFile = std::string(loadString(fp));
    gameData->gameoverScreenFile = std::string(loadString(fp));

    /* lendo os nomes das musicas das telas principais */
    gameData->titleScreenMusic = std::string(loadString(fp));
    gameData->optionsScreenMusic = std::string(loadString(fp));
    gameData->gameOverScreenMusic = std::string(loadString(fp));

    /* lendo a id do mapa inicial */
    fread(&gameData->idFirstMap, 1, sizeof(int), fp);

    fclose(fp);

    return true;
}


bool DataLoader::loadTilesetList(FILE *fp) {
    int num_tilesets;

    fread(&num_tilesets, 1, sizeof(int), fp);
    gameData->tileSetList = new std::vector<TileSet*>();

    int i;
    for(i = 0; i < num_tilesets; i++) {
        TileSet *tileSet = new TileSet();

        fread(&(tileSet->id), 1, sizeof(int), fp);

        tileSet->file = std::string(loadString(fp));
        tileSet->name = std::string(loadString(fp));


        fread(&(tileSet->width), 1, sizeof(int), fp);
        fread(&(tileSet->height), 1, sizeof(int), fp);

        fread(&(tileSet->maxX), 1, sizeof(int), fp);
        fread(&(tileSet->maxY), 1, sizeof(int), fp);

        fread(&(tileSet->tileSize), 1, sizeof(int), fp);


        tileSet->collisionMatrix.resize(boost::extents[tileSet->maxX][tileSet->maxY]);
        int j, k;
        for(j = 0; j < tileSet->maxX; j++) {
            for(k = 0; k < tileSet->maxY; k++) {
                int valor;
                fread(&valor, 1, sizeof(int), fp);
                tileSet->collisionMatrix[j][k] = valor;
            }
        }

        tileSet->reloadTilesetImage();

        gameData->tileSetList->push_back(tileSet);



    }

    return true;
}

std::vector<Map*>* DataLoader::loadMapList(FILE *fp) {
    std::vector<Map*>* mapList;
    mapList = new std::vector<Map*>();

    int tamanhoMapList, i;

    fread((&tamanhoMapList), 1, sizeof(int), fp);

    for(i = 0; i < tamanhoMapList; i ++) {
        Map* map = new Map();
        int j, k, l;

        int isFolder;

        fread(&isFolder, 1, sizeof(int), fp);

        if(isFolder) {
            map->mapName = std::string(loadString(fp));

            map->filhos = loadMapList(fp);
        } else {

            fread(&(map->id), 1, sizeof(int), fp);
            map->mapName = std::string(loadString(fp));

            fread(&(map->width), 1, sizeof(int), fp);
            fread(&(map->height), 1, sizeof(int), fp);
            fread(&(map->layers), 1, sizeof(int), fp);

            int tileSetListSize;

            fread(&tileSetListSize, 1, sizeof(int), fp);

            map->tileSets = new std::vector<TileSet*>();

            for(j = 0; j < tileSetListSize; j++) {
               int id;

               fread(&id, 1, sizeof(int), fp);

               TileSet* tileSetItem = gameData->searchTilesetById(id);

               if(tileSetItem != NULL) {
                   map->tileSets->push_back(tileSetItem);
               } else {
                   printf("Erro na população dos tilesets de um mapa");
                   exit(1);
               }

             }

            /* ALTERACOES 22-FEV-2011 COMECAM AQUI */
            map->music = std::string(loadString(fp));
            map->sound = std::string(loadString(fp));

            fread(&map->loopMusic, 1, sizeof(int), fp);
            fread(&map->loopSound, 1, sizeof(int), fp);
            fread(&map->idFundo, 1, sizeof(int), fp);

            /* gravando as instancias de objetos */

            int nro_instancias;
            fread(&nro_instancias, 1, sizeof(int), fp);

            map->gameObjectInstances->clear();

            for(j = 0; j < nro_instancias; j++) {
                GameObjectInstance *gameObjectInstance = new GameObjectInstance(NULL);
                int gameObjectId;

                fread(&gameObjectInstance->id, 1, sizeof(unsigned int), fp);
                fread(&gameObjectId, 1,  sizeof(int), fp);
                gameObjectInstance->gameObject = gameData->searchGameObjectById(gameObjectId);

                if(gameObjectInstance->gameObject == NULL) {
                    std::cout << "Problema com um GameObjectInstance. Abortando..." << std::endl;
                    exit(1);
                }
                fread(&gameObjectInstance->x, 1,  sizeof(int), fp);
                fread(&gameObjectInstance->y, 1,  sizeof(int), fp);

                fread(&gameObjectInstance->nroEventos, 1,  sizeof(int), fp);
                fread(&gameObjectInstance->nroFalas, 1, sizeof(int), fp);

                fread(&gameObjectInstance->isCenter, 1, sizeof(bool), fp);
                fread(&gameObjectInstance->isMainObject, 1, sizeof(bool), fp);

                gameObjectInstance->dialogueData = loadDialogueData(fp);

                map->gameObjectInstances->push_back(gameObjectInstance);

            }


            /* ALTERACOES 22-FEV-2011 TERMINAM AQUI */

             map->map.resize(boost::extents[map->width][map->height][map->layers]);

             for(j = 0; j < map->width; j++) {
                 for(k = 0; k < map->height; k++) {
                     for(l = 0; l < map->layers; l++) {
                         fread(&(map->map[j][k][l].x), 1, sizeof(int), fp);
                         fread(&(map->map[j][k][l].y), 1, sizeof(int), fp);



                         int id;

                         fread(&id, 1, sizeof(int), fp);

                         if(id == -1) {
                            map->map[j][k][l].z = NULL;
                            map->map[j][k][l].x = -1;
                            map->map[j][k][l].y = -1;
                         } else {
                             TileSet* tileSetItem = gameData->searchTilesetById(id);

                             if(tileSetItem != NULL) {
                                 map->map[j][k][l].z = tileSetItem;
                             } else {
                                 printf("Erro na obtenção de um tileset de um tile %d\n", id);
                                 exit(1);
                             }
                         }


                     }
                 }
             }

            map->filhos = NULL;
        }

        /* lendo teleport areas */
        int nro_teleport_areas;
        nro_teleport_areas = map->teleportAreas->size();
        fread(&nro_teleport_areas, 1, sizeof(int), fp);

        map->teleportAreas = new std::vector<TeleportArea*>(nro_teleport_areas);

        for(j = 0; j < nro_teleport_areas; j++) {
            TeleportArea* teleportArea = new TeleportArea();

            fread(&teleportArea->id, 1, sizeof(int), fp);
            fread(&teleportArea->mapId, 1, sizeof(int), fp);
            fread(&teleportArea->mapPositionDetermined, 1, sizeof(bool), fp);
            fread(&teleportArea->mapPosX, 1, sizeof(int), fp);
            fread(&teleportArea->mapPosY, 1, sizeof(int), fp);
            fread(&teleportArea->x, 1, sizeof(int), fp);
            fread(&teleportArea->y, 1, sizeof(int), fp);
            fread(&teleportArea->w, 1, sizeof(int), fp);
            fread(&teleportArea->h, 1, sizeof(int), fp);
            fread(&teleportArea->showVictoryAnimation, 1, sizeof(bool), fp);

            map->teleportAreas->at(j) = teleportArea;

        }

        /* carregando o fundo */
        int idBg;
        fread(&idBg, 1, sizeof(int), fp);

        if(idBg != -1) {
            map->background = gameData->searchBackgroundById(idBg);
            if(map->background == NULL) {
                printf("Erro na obtenção de um background de id %d\n", idBg);
                exit(1);
            }
        } else {
            map->background = NULL;
        }



        map->dialogueData = loadDialogueData(fp);




         mapList->push_back(map);
    }

    return mapList;
}

bool DataLoader::loadObjectList(FILE *fp) {
    gameData->objectList->clear();

    int nro_objetos;
    fread(&nro_objetos, 1, sizeof(int), fp);
    for(int i = 0; i < nro_objetos; i++) {
        GameObject *gameObject = new GameObject();

        fread(&gameObject->id, 1, sizeof(int), fp);
        gameObject->name = std::string(loadString(fp));
        fread(&gameObject->type, 1, sizeof(int), fp);

        fread(&gameObject->isObjetoUnico, 1, sizeof(bool), fp);
        fread(&gameObject->formaGrafica, 1, sizeof(int), fp);
        fread(&gameObject->tipoMovimento, 1, sizeof(int), fp);

        gameObject->soundDamage = std::string(loadString(fp));
        gameObject->soundSpecial = std::string(loadString(fp));

        fread(&gameObject->isDraggable, 1, sizeof(bool), fp);

        fread(&gameObject->formaMovimentoMouse, 1, sizeof(int), fp);
        fread(&gameObject->vx, 1, sizeof(int), fp);
        fread(&gameObject->vy, 1, sizeof(int), fp);
        fread(&gameObject->ax, 1, sizeof(int), fp);
        fread(&gameObject->ay, 1, sizeof(int), fp);
        fread(&gameObject->dax, 1, sizeof(int), fp);
        fread(&gameObject->day, 1, sizeof(int), fp);
        fread(&gameObject->gravidade, 1, sizeof(int), fp);
        fread(&gameObject->intensidadePulo, 1, sizeof(int), fp);
        fread(&gameObject->evolucaoPorNivel, 1, sizeof(int), fp);

        /* inicio das adicoes - 12 de março - PENDENTES NO RUNTIME - OK */

        fread(&gameObject->hp, 1, sizeof(int), fp);
        fread(&gameObject->mp, 1, sizeof(int), fp);
        fread(&gameObject->atk, 1, sizeof(int), fp);
        fread(&gameObject->def, 1, sizeof(int), fp);
        fread(&gameObject->intelig, 1, sizeof(int), fp);
        fread(&gameObject->levelInicial, 1, sizeof(int), fp);
        fread(&gameObject->levelMax, 1, sizeof(int), fp);
        fread(&gameObject->velocidadeEvolucao, 1, sizeof(int), fp);
        fread(&gameObject->resolveCollision, 1, sizeof(int), fp);

        if(gameObject->type == GameObject::INIMIGO || gameObject->type == GameObject::NPC ||
           gameObject->type == GameObject::ITEM) {
            fread(&gameObject->formaMovimentacaoNpcItem, 1, sizeof(int), fp);
            fread(&gameObject->movimentaApenasDentroTela, 1, sizeof(bool), fp);
            fread(&gameObject->raioMovimentacao, 1, sizeof(int), fp);

            if(gameObject->type == GameObject::INIMIGO) {

                fread(&gameObject->derrotaEncostandoInimigo, 1, sizeof(bool), fp);
                fread(&gameObject->derrotaAtirandoItemMagiaInimigo, 1, sizeof(bool), fp);
                fread(&gameObject->derrotaAcertandoEspadaSobreInimigo, 1, sizeof(bool), fp);
                fread(&gameObject->derrotaPulandoSobreInimigo, 1, sizeof(bool), fp);
                fread(&gameObject->atacaEncostaPersonagem, 1, sizeof(bool), fp);
                fread(&gameObject->atacaEncostaPersonagemDano, 1, sizeof(int), fp);
                fread(&gameObject->atacaUsandoEspada, 1, sizeof(bool), fp);
                fread(&gameObject->espadaItemId, 1, sizeof(int), fp);
                fread(&gameObject->atacaUsandoEspadaDano, 1, sizeof(int), fp);

                fread(&gameObject->atiraItemMaginaDirecaoEstiver, 1, sizeof(bool), fp);
                fread(&gameObject->atiraItemMaginaDirecaoEstiverIdItem, 1, sizeof(int), fp);
                fread(&gameObject->atiraItemMaginaDirecaoEstiverDano, 1, sizeof(int), fp);

                fread(&gameObject->atiraItemMagiaDirecaoPersonagem, 1, sizeof(bool), fp);
                fread(&gameObject->atiraItemMagiaDirecaoPersonagemIdItem, 1, sizeof(int), fp);
                fread(&gameObject->atiraItemMagiaDirecaoPersonagemDano, 1, sizeof(int), fp);

                fread(&gameObject->tempoAtaque, 1, sizeof(float), fp);
                fread(&gameObject->magicCost, 1, sizeof(int), fp);

                fread(&gameObject->experiencePoints, 1, sizeof(int), fp);
                fread(&gameObject->defeatPoints, 1, sizeof(int), fp);

            } else if(gameObject->type == GameObject::NPC) {
                fread(&gameObject->nroFalas, 1, sizeof(int), fp);
            } else if(gameObject->type == GameObject::ITEM) {
                fread(&gameObject->concedePontos, 1, sizeof(bool), fp);
                fread(&gameObject->concedePontosValor, 1, sizeof(int), fp);
                fread(&gameObject->ganhaPerdeVida, 1, sizeof(bool), fp);
                fread(&gameObject->ganhaPerdeVidaValor, 1, sizeof(int), fp);
                fread(&gameObject->ganhaPerdeMagia, 1, sizeof(bool), fp);
                fread(&gameObject->ganhaPerdeMagiaValor, 1, sizeof(int), fp);
                fread(&gameObject->incrementaVariavel, 1, sizeof(bool), fp);
                fread(&gameObject->incrementaVariavelIdVariavel, 1, sizeof(int), fp);
                fread(&gameObject->incrementaVariavelValor, 1, sizeof(int), fp);
                fread(&gameObject->ativaEvento, 1, sizeof(bool), fp);
                fread(&gameObject->ativaEventoIdEvento, 1, sizeof(int), fp);
                fread(&gameObject->concedeHabilidade, 1, sizeof(bool), fp);
                fread(&gameObject->concedeHabilidadeIdHabilidade, 1, sizeof(int), fp);

                fread(&gameObject->comportamentoEncostarPersonagem, 1, sizeof(int), fp);
                fread(&gameObject->desapareceEncostarPersonagem, 1, sizeof(bool), fp);
                fread(&gameObject->desapareceEncostarParede, 1, sizeof(bool), fp);
            }
        }









        fread(&gameObject->possuiEventos, 1, sizeof(bool), fp);


        /* fim das adicoes - 12 de março */

        int nro_gameobject_animations;
        fread(&nro_gameobject_animations, 1, sizeof(int), fp);

        gameObject->gameObjectAnimations->clear();

        for(int j = 0; j < nro_gameobject_animations; j++) {
            GameObjectAnimation *gameObjectAnimation = new GameObjectAnimation();

            fread(&gameObjectAnimation->id, 1, sizeof(int), fp);
            fread(&gameObjectAnimation->type, 1, sizeof(int), fp);

            /* inicio das adicoes - 12 de março - PENDENTES NO RUNTIME - OK */
            fread(&gameObjectAnimation->numDirectionFactor, 1, sizeof(int), fp);

            int nro_types;
            fread(&nro_types, 1, sizeof(int), fp);

            for(int k = 0; k < nro_types; k++) {
                int valor_type;
                fread(&valor_type, 1, sizeof(int), fp);

                gameObjectAnimation->types->at(k) = valor_type;
            }


            int nro_horizontal_inverts;
            fread(&nro_horizontal_inverts, 1, sizeof(int), fp);

            for(int k = 0; k < nro_horizontal_inverts; k++) {
                bool valor_horinv;
                fread(&valor_horinv, 1, sizeof(bool), fp);
                gameObjectAnimation->horizontalInvert.at(k) = valor_horinv;
            }

            int nro_vertical_inverts;
            fread(&nro_vertical_inverts, 1, sizeof(int), fp);

            for(int k = 0; k < nro_vertical_inverts; k++) {
                bool valor_verinv;
                fread(&valor_verinv, 1, sizeof(bool), fp);
                gameObjectAnimation->verticalInvert.at(k) = valor_verinv;
            }

            int nro_adjustments;
            fread(&nro_adjustments, 1, sizeof(int), fp);

            for(int k = 0; k < nro_adjustments; k++) {
                Point point;
                fread(&point.x, 1, sizeof(int), fp);
                fread(&point.y, 1, sizeof(int), fp);

                gameObjectAnimation->adjustments.at(k) = point;
            }




            /* fim das adicoes - 12 de março */

            gameObjectAnimation->name = std::string(loadString(fp));

            int nro_sprites;
            fread(&nro_sprites, 1, sizeof(int), fp);

            for(int k = 0; k < nro_sprites; k++) {
                Sprite *sprite = new Sprite();

                fread(&sprite->id, 1, sizeof(int), fp);
                fread(&sprite->direction, 1, sizeof(int), fp);

                /* inicio das adicoes - 12 de março - PENDENTES NO RUNTIME - OK */
                fread(&sprite->activated, 1, sizeof(bool), fp);
                fread(&sprite->hascolorkey, 1, sizeof(bool), fp);
                fread(&sprite->r_colorkey, 1, sizeof(int), fp);
                fread(&sprite->g_colorkey, 1, sizeof(int), fp);
                fread(&sprite->b_colorkey, 1, sizeof(int), fp);


                /* fim das adicoes - 12 de março */

                sprite->spriteFileName = std::string(loadString(fp));

                gameObjectAnimation->sprites->at(k) = sprite;
            }

            /* inicio das adicoes - 12 de março - PENDENTES NO RUNTIME - OK */
            int nro_animations;
            fread(&nro_animations, 1, sizeof(int), fp);


            for(int k = 0; k < nro_animations; k++) {
                int animationDataId;
                fread(&animationDataId, 1, sizeof(int), fp);

                if(animationDataId != -1) {
                    gameObjectAnimation->animations->at(k) = gameData->searchAnimationDataById(animationDataId);

                    if(gameObjectAnimation->animations->at(k) == NULL) {
                        std::cout << "Problema com leitura de um animationData de um object" << std::endl;
                    }
                }

            }



            /* fim das adicoes - 12 de março */

            // TODO: fazer loop leitura de animations quando estiverem prontas

            gameObject->gameObjectAnimations->push_back(gameObjectAnimation);
        }

        gameData->objectList->push_back(gameObject);
    }



    return true;
}

bool DataLoader::loadNpcObjectsToBounce(FILE *fp) {
    for(std::vector<GameObject*>::iterator it = gameData->objectList->begin(); it != gameData->objectList->end(); ++it) {
        GameObject *gameObject = *it;

        if(gameObject->type == GameObject::PONG_BALL_OBJECT) {
            int gameObjectsToAddCount;
            fread(&gameObjectsToAddCount, 1, sizeof(int), fp);

            for(int j = 0; j < gameObjectsToAddCount; j++) {
                int idGameObjectToAdd;
                fread(&idGameObjectToAdd, 1, sizeof(int), fp);
                GameObject *gameObjectIt = gameData->searchGameObjectById(idGameObjectToAdd);

                if(gameObjectIt != NULL) {
                    gameObject->listObjectsToBounce.push_back(gameObjectIt);
                } else {
                    printf("Erro na obtenção de um objeto de id: %d\n", idGameObjectToAdd);

                }
            }
        }
    }

    return true;
}

bool DataLoader::loadObjectSkills(FILE *fp) {
    for(std::vector<GameObject*>::iterator it = gameData->objectList->begin(); it != gameData->objectList->end(); ++it) {
        GameObject *gameObject = *it;

        int nroListaHabilidades;

        fread(&nroListaHabilidades, 1, sizeof(int), fp);

        for(int j = 0; j < nroListaHabilidades; j++) {
            SkillData* skillData = new SkillData();

            fread(&skillData->id, 1, sizeof(int), fp);
            fread(&skillData->intensity, 1, sizeof(int), fp);
            fread(&skillData->magicCost, 1, sizeof(int), fp);
            fread(&skillData->level, 1, sizeof(int), fp);


            int idSkill;
            fread(&idSkill, 1, sizeof(int), fp);
            skillData->skill = gameData->searchSkillById(idSkill);
            if(skillData->skill == NULL) {
                printf("Erro na obtenção de uma skill de id: %d\n", idSkill);
                exit(1);
            }

            fread(&skillData->isMagical, 1, sizeof(int), fp);

            skillData->sound = std::string(loadString(fp));


            int idSkillData;
            fread(&idSkillData, 1, sizeof(int), fp);
            int idSkillProvider;
            fread(&idSkillProvider, 1, sizeof(int), fp);

            if(idSkillData == -1) {
                skillData->skillObject = NULL;
            } else {
                skillData->skillObject = gameData->searchGameObjectById(idSkillData);
                if(skillData->skillObject == NULL) {
                    printf("Erro na obtenção de um objeto (skillObject) de id: %d\n", idSkillData);
                    exit(1);
                }
            }


            if(idSkillProvider == -1) {
                skillData->skillProvider = NULL;
            } else {
                skillData->skillProvider = gameData->searchGameObjectById(idSkillProvider);
                if(skillData->skillProvider == NULL) {
                    printf("Erro na obtenção de um objeto (skillProvider) de id: %d\n", idSkillProvider);
                    exit(1);
                }
            }

            gameObject->listaHabilidades.push_back(skillData);



        }
    }

    return true;


}


bool DataLoader::loadAnimationDataList(FILE *fp) {
    int tamanhoLista;

    fread(&tamanhoLista, 1, sizeof(int), fp);

    for(int i = 0; i < tamanhoLista; i++) {
        AnimationData *animationData = new AnimationData();

        fread(&animationData->id, 1, sizeof(int), fp);

        animationData->fileName = std::string(loadString(fp));
        animationData->name = std::string(loadString(fp));

        fread(&animationData->colorkey_b, 1, sizeof(int), fp);
        fread(&animationData->colorkey_g, 1, sizeof(int), fp);
        fread(&animationData->colorkey_r, 1, sizeof(int), fp);

        fread(&animationData->frameLoop, 1, sizeof(int), fp);
        fread(&animationData->hasColorkey, 1, sizeof(bool), fp);
        fread(&animationData->hasLoop, 1, sizeof(bool), fp);
        int valor_horizontal_frame_number;
        fread(&valor_horizontal_frame_number, 1, sizeof(int), fp);
        animationData->setHorizontalFrameNumber(valor_horizontal_frame_number);
        fread(&animationData->horizontalSpacing, 1, sizeof(int), fp);
        fread(&animationData->order, 1, sizeof(int), fp);
        fread(&animationData->velocity, 1, sizeof(int), fp);
        int valor_vertical_frame_number;
        fread(&valor_vertical_frame_number, 1, sizeof(int), fp);
        animationData->setVerticalFrameNumber(valor_vertical_frame_number);
        fread(&animationData->verticalSpacing, 1, sizeof(int), fp);

        fread(&animationData->startX, 1, sizeof(int), fp);
        fread(&animationData->startY, 1, sizeof(int), fp);
        fread(&animationData->endX, 1, sizeof(int), fp);
        fread(&animationData->endY, 1, sizeof(int), fp);

        gameData->animationDataList->push_back(animationData);


    }

    return true;
}


bool DataLoader::loadBackgroundList(FILE *fp) {
    int tamanhoLista;

    fread(&tamanhoLista, 1, sizeof(int), fp);

    for(int i = 0; i < tamanhoLista; i++) {
        Background *bg = new Background();

        fread(&bg->id, 1, sizeof(int), fp);
        bg->name = std::string(loadString(fp));

        int tamanho_layer_list;
        fread(&tamanho_layer_list, 1, sizeof(int), fp);

        for(int j = 0; j < tamanho_layer_list; j++) {
            BgLayer *bgLayer = new BgLayer();

            bgLayer->fileName = std::string(loadString(fp));

            fread(&bgLayer->behavior, 1, sizeof(int), fp);
            fread(&bgLayer->displacementX, 1, sizeof(int), fp);
            fread(&bgLayer->displacementY, 1, sizeof(int), fp);
            fread(&bgLayer->repeatsHorizontally, 1, sizeof(int), fp);
            fread(&bgLayer->repeatsVertically, 1, sizeof(int), fp);
            fread(&bgLayer->vx, 1, sizeof(int), fp);
            fread(&bgLayer->vy, 1, sizeof(int), fp);

            bg->layerList->push_back(bgLayer);
        }

        gameData->backgroundList->push_back(bg);


    }

    return true;
}


bool DataLoader::loadAllEvents(FILE *fp) {
    gameData->procedureGlobalAlways = loadProcedure(fp);
    gameData->procedureGlobalStart = loadProcedure(fp);
    gameData->procedureGlobalEnd = loadProcedure(fp);

    gameData->procedureList = loadProcedureList(fp);


    for(std::vector<GameObject*>::iterator it = gameData->objectList->begin(); it != gameData->objectList->end(); ++it) {
        GameObject* gameObject = *it;

        gameObject->procedureGlobalAlways = loadProcedure(fp);
        gameObject->procedureGlobalStart = loadProcedure(fp);
        gameObject->procedureGlobalEnd = loadProcedure(fp);

        gameObject->procedureList = loadProcedureList(fp);
    }

    return true;
}


VariableData* DataLoader::loadVariable(FILE *fp) {
    VariableData *variable = new VariableData();

    fread(&variable->id, 1, sizeof(int), fp);
    variable->name = std::string(loadString(fp));
    fread(&variable->type, 1, sizeof(int), fp);
    fread(&variable->value, 1, sizeof(float), fp);

    return variable;
}


bool DataLoader::loadAllVariableLists(FILE *fp) {

    // lendo as variáveis globais
    int count_n_variables;
    fread(&count_n_variables, 1, sizeof(int), fp);


    for(int i = 0; i < count_n_variables; i++) {
        gameData->variableList->push_back(loadVariable(fp));
    }

    // lendos as variáveis dos objetos
    for(std::vector<GameObject*>::iterator it1 = gameData->objectList->begin(); it1 != gameData->objectList->end(); ++it1) {
        GameObject *gameObject = *it1;

        fread(&count_n_variables, 1, sizeof(int), fp);

        for(int i = 0; i < count_n_variables; i++) {
            gameObject->variableList->push_back(loadVariable(fp));
        }

    }
    return true;
}



std::vector<ProcedureData*>* DataLoader::loadProcedureList(FILE *fp) {
    int sizeProcedureList;
    std::vector<ProcedureData*>* procedureList = new std::vector<ProcedureData*>();

    fread(&sizeProcedureList, 1, sizeof(int), fp);

    for(int i = 0; i < sizeProcedureList; i++) {
        procedureList->push_back(loadProcedure(fp));
    }


    return procedureList;
}


ProcedureData* DataLoader::loadProcedure(FILE *fp) {
    ProcedureData *procedureData = new ProcedureData();

    fread(&procedureData->id, 1, sizeof(int), fp);
    procedureData->name = std::string(loadString(fp));
    fread(&procedureData->nameEditable, 1, sizeof(int), fp);

    procedureData->events = loadEventList(fp);

    return procedureData;
}

DialogueData* DataLoader::loadDialogueData(FILE *fp) {
    bool dialogueDataNotExists;
    fread(&dialogueDataNotExists, 1, sizeof(bool), fp);

    DialogueData *dialogueData;

    if(dialogueDataNotExists) {
        return NULL;
    } else {
        dialogueData = new DialogueData();

        int itemNumber;
        fread(&itemNumber, 1, sizeof(int), fp);

        for(int i = 0; i < itemNumber; i++) {
            DialogueItemData *dialogueItemData = new DialogueItemData();

            fread(&dialogueItemData->type, 1, sizeof(int), fp);
            if(dialogueItemData->type == DialogueItemData::TYPE_MESSAGE) {
                dialogueItemData->message = std::string(loadString(fp));
                dialogueItemData->associatedImage = std::string(loadString(fp));
                fread(&dialogueItemData->associatedImageAtCenter, 1, sizeof(bool), fp);
            } else {
                fread(&dialogueItemData->procedureId, 1, sizeof(bool), fp);
            }

            dialogueData->dialogueItems.push_back(dialogueItemData);
        }
    }

    return dialogueData;
}

std::list<EventData*> DataLoader::loadEventList(FILE *fp, EventData *parent) {
    int eventListSize;
    std::list<EventData*> eventListFunction;

    fread(&eventListSize, 1, sizeof(int), fp);

    for(int i = 0; i < eventListSize; i++) {
        EventData *eventData = new EventData();

        fread(&eventData->newEvent, 1, sizeof(int), fp);
        if(!eventData->newEvent) {
            fread(&eventData->type, 1, sizeof(int), fp);
            fread(&eventData->conditionType, 1, sizeof(int), fp);
            fread(&eventData->negate, 1, sizeof(bool), fp);

            fread(&eventData->opcode, 1, sizeof(int), fp);
            fread(&eventData->idAssociatedVariable, 1, sizeof(int), fp);
            fread(&eventData->idObject01, 1, sizeof(int), fp);
            fread(&eventData->instanceTypeObject01, 1, sizeof(int), fp);
            fread(&eventData->idObject02, 1, sizeof(int), fp);
            fread(&eventData->instanceTypeObject02, 1, sizeof(int), fp);
            fread(&eventData->valueType, 1, sizeof(int), fp);
            fread(&eventData->value01, 1, sizeof(int), fp);
            eventData->stringValue = std::string(loadString(fp));
            eventData->dialogueData = loadDialogueData(fp);



            eventData->subEvents = loadEventList(fp, eventData);

        }

        eventData->parent = parent;

        eventListFunction.push_back(eventData);
    }

    return eventListFunction;
}
