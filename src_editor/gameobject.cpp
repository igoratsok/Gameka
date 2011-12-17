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



#include "gameobject.h"



GameObject::GameObject()
{
    GameData *gameData = GameData::getInstance();

    initVariables();



    /* inicializando forma sprite default */
    gameObjectAnimations = new std::vector<GameObjectAnimation*>();

    /* inicializando a lista de procedures */
    procedureList = new std::vector<ProcedureData*>();

    /* inicializando a lista de variáveis */
    variableList = new std::vector<VariableData*>();

    GameObjectAnimation *gameObjectAnimation = new GameObjectAnimation();
    gameObjectAnimation->id = 0;
    gameObjectAnimation->name = std::string("Parado");
    gameObjectAnimation->type = GameObjectAnimation::STATIC;



    Sprite *sprite = new Sprite();
    sprite->spriteFileName = std::string("default_object_sprite.png");
    sprite->direction = 0;
    sprite->id = 0;


    gameObjectAnimation->sprites->at(0) = sprite;
    gameObjectAnimation->types->at(0) = 1;
    gameObjectAnimations->push_back(gameObjectAnimation);

    gameObjectAnimation = new GameObjectAnimation();
    gameObjectAnimation->id = 1;
    gameObjectAnimation->name = std::string("Andando");
    gameObjectAnimation->type = GameObjectAnimation::STATIC;
    gameObjectAnimations->push_back(gameObjectAnimation);

    gameObjectAnimation = new GameObjectAnimation();
    gameObjectAnimation->id = 2;
    gameObjectAnimation->name = std::string("Correndo");
    gameObjectAnimation->type = GameObjectAnimation::STATIC;
    gameObjectAnimations->push_back(gameObjectAnimation);


    gameObjectAnimation = new GameObjectAnimation();
    gameObjectAnimation->id = 3;
    gameObjectAnimation->name = std::string("Pulando");
    gameObjectAnimation->type = GameObjectAnimation::STATIC;
    gameObjectAnimations->push_back(gameObjectAnimation);

    gameObjectAnimation = new GameObjectAnimation();
    gameObjectAnimation->id = 4;
    gameObjectAnimation->name = std::string("Caindo");
    gameObjectAnimation->type = GameObjectAnimation::STATIC;
    gameObjectAnimations->push_back(gameObjectAnimation);

    gameObjectAnimation = new GameObjectAnimation();
    gameObjectAnimation->id = 5;
    gameObjectAnimation->name = std::string("Atacando");
    gameObjectAnimation->type = GameObjectAnimation::STATIC;
    gameObjectAnimations->push_back(gameObjectAnimation);

    gameObjectAnimation = new GameObjectAnimation();
    gameObjectAnimation->id = 6;
    gameObjectAnimation->name = std::string("Levando dano");
    gameObjectAnimation->type = GameObjectAnimation::STATIC;
    gameObjectAnimations->push_back(gameObjectAnimation);

    gameObjectAnimation = new GameObjectAnimation();
    gameObjectAnimation->id = 7;
    gameObjectAnimation->name = std::string("Morrendo");
    gameObjectAnimation->type = GameObjectAnimation::STATIC;
    gameObjectAnimations->push_back(gameObjectAnimation);




    procedureGlobalAlways = new ProcedureData();
    procedureGlobalAlways->name = QString::fromUtf8("Sempre").toStdString();
    procedureGlobalAlways->nameEditable = false;
    procedureGlobalStart = new ProcedureData();
    procedureGlobalStart->name = QString::fromUtf8("Criação do objeto").toStdString();
    procedureGlobalStart->nameEditable = false;
    procedureGlobalEnd = new ProcedureData();
    procedureGlobalEnd->name = QString::fromUtf8("Destrução do objeto").toStdString();
    procedureGlobalEnd->nameEditable = false;



}

void GameObject::initVariables() {

    formaGrafica = 0;
    tipoMovimento = 0;
    evolucaoPorNivel = 0;
    isDraggable = false;

    this->gravidade = 10;
    this->vx = 15;
    this->vy = 15;
    this->ax = 10;
    this->ay = 10;
    this->dax = 10;
    this->day = 10;
    this->intensidadePulo = 20;

    this->tipoMovimento = 1;


    hp = 5;
    mp = 5;
    atk= 1;
    def = 0;
    intelig = 1;
    evolucaoPorNivel = false;
    levelInicial = 1;
    levelMax = 99;
    velocidadeEvolucao = 50;
    resolveCollision = true;

    formaMovimentacaoNpcItem = 0;
    raioMovimentacao = 80;

    concedePontos = false;
    concedePontosValor = 0;
    ganhaPerdeVida = false;
    ganhaPerdeVidaValor = 0;
    ganhaPerdeMagia = false;
    ganhaPerdeMagiaValor = 0;
    incrementaVariavel = false;
    incrementaVariavelIdVariavel = 0;
    incrementaVariavelValor = 0;
    ativaEvento = false;
    ativaEventoIdEvento = 0;
    concedeHabilidade = false;
    concedeHabilidadeIdHabilidade = 0;

    comportamentoEncostarPersonagem = 0;
    desapareceEncostarPersonagem = false;
    desapareceEncostarParede = false;

    derrotaEncostandoInimigo = false;
    derrotaAtirandoItemMagiaInimigo = false;
    derrotaAcertandoEspadaSobreInimigo = false;
    derrotaPulandoSobreInimigo = false;
    atacaEncostaPersonagem = false;
    atacaEncostaPersonagemDano = 0;
    atacaUsandoEspada = false;
    espadaItemId = 0;
    atacaUsandoEspadaDano = false;

    atiraItemMaginaDirecaoEstiver = false;
    atiraItemMaginaDirecaoEstiverIdItem = 0;
    atiraItemMaginaDirecaoEstiverDano = 0;

    atiraItemMagiaDirecaoPersonagem = false;
    atiraItemMagiaDirecaoPersonagemIdItem = 0;
    atiraItemMagiaDirecaoPersonagemDano = 0;

    nroFalas = 0;

    movimentaApenasDentroTela = false;

    experiencePoints = 0;
    defeatPoints = 0;

}

GameObject::GameObject(int specialId) {
    this->type = SPECIAL;
    this->id = specialId;
}

void GameObject::reset(int newType) {
    int idBefore = id;

    initVariables();

    id = idBefore;

    this->type = newType;

    foreach(ProcedureData *procedureData, *procedureList) {
        procedureData->events.clear();
    }

    listaHabilidades.clear();


}

std::string GameObject::getIconString() {
    GameData *gameData = GameData::getInstance();
    return gameData->getProjectDirectory().append("/objects/").append(gameObjectAnimations->at(0)->sprites->at(0)->spriteFileName);
}

QImage GameObject::getIconImage() {
    GameData *gameData = GameData::getInstance();

    if(specialIconPath.empty()) {
        GameObjectAnimation* animationParado = gameObjectAnimations->at(0);
        Sprite *sprite = NULL;
        AnimationData *animationData = NULL;

        int valor = 0;
        int i = 0;
        for(std::vector<int>::iterator it = animationParado->types->begin(); it != animationParado->types->end(); it++) {
            valor = *it;

            if(valor == 1) {
                sprite = animationParado->sprites->at(i);
                break;
            } else if (valor == 2) {
                animationData = animationParado->animations->at(i);
                break;
            }

            i++;

        }

        std::string directory;
        QImage image;

        switch(valor) {
        case 1:

            directory = gameData->getProjectDirectory().append("/objects/").append(sprite->spriteFileName);
            image = QImage(QString(directory.c_str()));
            return image;


            break;
        case 2:
            return animationData->getIconImage();

            break;
        }
    } else {
        return QImage(QString(specialIconPath.c_str()));
    }




    return QImage();
}


int GameObject::generateNewProcedureId() {
    int id = 0;
    int procedureId;
    ProcedureData *procedureItem;

    if(!procedureList->empty()) {
        for(std::vector<ProcedureData*>::iterator it = procedureList->begin(); it != procedureList->end(); ++it) {
            procedureItem = *it;
            procedureId = procedureItem->id;
            if(procedureId > id) id = procedureId;
        }
    }

    return (id + 1);
}

void GameObject::addProcedure(ProcedureData *procedureData) {
    procedureData->id = generateNewProcedureId();

    std::stringstream ss;
    ss << "Procedimento " << procedureData->id;

    procedureData->name = ss.str();

    procedureList->push_back(procedureData);
}

void GameObject::addVariable(VariableData *variableData) {
    variableData->id = generateNewVariableId();

    variableList->push_back(variableData);
}

int GameObject::generateNewVariableId() {
    int id = 0;
    int bgId;
    VariableData *variableItem;

    if(!variableList->empty()) {
        for(std::vector<VariableData*>::iterator it = variableList->begin(); it != variableList->end(); ++it) {
            variableItem = *it;
            bgId = variableItem->id;
            if(bgId > id) id = bgId;
        }
    }

    return (id + 1);
}

ProcedureData* GameObject::getProcedureById(int id) {
    for(std::vector<ProcedureData*>::iterator it = procedureList->begin(); it != procedureList->end(); ++it) {
        ProcedureData *procedureData = *it;

        if(procedureData->id == id) {
            return procedureData;
        }
    }

    return NULL;
}

VariableData* GameObject::getVariableById(int id) {
    for(std::vector<VariableData*>::iterator it = variableList->begin(); it != variableList->end(); ++it) {
        VariableData *variableData = *it;

        if(variableData->id == id) {
            return variableData;
        }
    }

    return NULL;
}

bool GameObject::verifyIfOnlyOneAnimation() {
    int animationCount = 0;
    foreach(GameObjectAnimation *goa, *gameObjectAnimations) {
        for(int i = 0; i < 32; i++) {
            if(goa->types->at(i) == GameObjectAnimation::STATIC && goa->sprites->at(i) != NULL) {
                return false;
            }
            if(goa->types->at(i) == GameObjectAnimation::ANIMATED && goa->animations->at(i) != NULL) {
                animationCount++;
                if(animationCount == 2) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool GameObject::verifyIfOnlyOneAnimationStopped() {
    int animationCount = 0;
    GameObjectAnimation *goa = gameObjectAnimations->at(0);

    for(int i = 0; i < 32; i++) {
        if(goa->types->at(i) == GameObjectAnimation::STATIC && goa->sprites->at(i) != NULL) {
            return false;
        }
        if(goa->types->at(i) == GameObjectAnimation::ANIMATED && goa->animations->at(i) != NULL) {
            animationCount++;
            if(animationCount == 2) {
                return false;
            }
        }


    }
    return true;

}
