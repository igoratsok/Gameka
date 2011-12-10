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

#include "StateManager.h"


StateManager* StateManager::singleton = NULL;

StateManager::StateManager(GameData *gameData) {
	currentState = NULL;
	nextState = NULL;
	this->gameData = gameData;
	screenEffects = new ScreenEffects();


	etapaTransicao = ETAPA_MOSTRANDO_ESTADO;
	screenEffects->piscaTela(0, 0, 0);

	inputManager = InputManager::getInstance();
	mapGameOverBackId = -1;

	setSplashState();
}

StateManager::~StateManager() {

}

void StateManager::setSplashState() {
	ScrollManager::getInstance()->setTilemap(NULL);

	if(currentState != NULL) {
		currentState->unload();
	}
	currentState = new TitleState(this);
	currentState->setGameData(gameData);
	currentState->load();

}

void StateManager::resetGame() {
	ScrollManager::getInstance()->setTilemap(NULL);



	nextState = new TitleState(this);
	nextState->setGameData(gameData);


	screenEffects->fadeIn(0, 0, 0);
	etapaTransicao = ETAPA_APAGANDO_ESTADO;
}

void StateManager::setMapState(int idLevel) {
	ScrollManager::getInstance()->setTilemap(NULL);



	nextState = new MapState(this);
	((MapState*)nextState)->setLevel(idLevel);
	nextState->setGameData(gameData);


	screenEffects->fadeIn(0, 0, 0);
	etapaTransicao = ETAPA_APAGANDO_ESTADO;
}

void StateManager::returnLastMap() {
	setMapState(mapGameOverBackId);
}

void StateManager::setGameOverState(int currentMapId) {
	this->mapGameOverBackId = currentMapId;

	ScrollManager::getInstance()->setTilemap(NULL);


	nextState = new GameOverState(this);
	nextState->setGameData(gameData);


	screenEffects->fadeIn(0, 0, 0);
	etapaTransicao = ETAPA_APAGANDO_ESTADO;
}


void StateManager::updateState(int dt, Screen *screen) {
	switch(etapaTransicao) {
	case ETAPA_MOSTRANDO_ESTADO:
		screenEffects->update(dt);
		if(screenEffects->terminouPiscaTela()) {
			etapaTransicao = ETAPA_RODANDO_ESTADO;
		}
		break;
	case ETAPA_APAGANDO_ESTADO:
		screenEffects->update(dt);
		if(screenEffects->terminouFadeIn()) {
			etapaTransicao = ETAPA_MOSTRANDO_ESTADO;

			if(currentState != NULL) {
				currentState->unload();
			}

			nextState->load();
			currentState = nextState;
			screenEffects->piscaTela(0, 0, 0);
		}

		break;
	case ETAPA_RODANDO_ESTADO:
		currentState->update(dt);
		screen->updateTopScreen();
		break;
	}

	inputManager->update(dt);


}

void StateManager::renderState(Screen *screen) {
	switch(etapaTransicao) {
	case ETAPA_MOSTRANDO_ESTADO:
		currentState->render(screen);
		screenEffects->render(screen);
		break;
	case ETAPA_APAGANDO_ESTADO:
		currentState->render(screen);
		screenEffects->render(screen);

		break;
	case ETAPA_RODANDO_ESTADO:
		currentState->render(screen);
		break;
	}


}
