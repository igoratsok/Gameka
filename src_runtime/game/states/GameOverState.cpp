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

#include "GameOverState.h"

GameOverState::GameOverState(StateManager *stateManager) {
	this->stateManager = stateManager;

}

GameOverState::~GameOverState() {
	// TODO Auto-generated destructor stub
}


void GameOverState::load() {
	if(!gameData->titleScreenFile.empty()) {
		std::string *diretorio = new std::string("images/");
		diretorio->append(gameData->gameoverScreenFile);

		fundo = new Sprite(diretorio, new Vector2(0, 0));
		fundo->setScrollable(false);
	} else {
		fundo = NULL;
	}

	/* carrega musica de fundo (se houver) */
	if(!gameData->gameOverScreenMusic.empty()) {
		std::string *diretorioMusic = new std::string("musics/");
		diretorioMusic->append(gameData->gameOverScreenMusic.c_str());
		musicaFundo = new Music(diretorioMusic, Music::MUSICA);
		std::cout << diretorioMusic->c_str() << std::endl;
		delete diretorioMusic;

		musicaFundo->play(1);
	} else {
		musicaFundo = NULL;
	}

	inputManager = InputManager::getInstance();
	playerData = PlayerData::getInstance();


}

void GameOverState::unload() {
	delete fundo;
}

int GameOverState::update(int dt) {
	if(inputManager->isKeyPressed(SDLK_z) || inputManager->isKeyPressed(SDLK_RETURN)) {
		playerData->resetLives();

		if(gameData->gameOverAction == GameData::DEATH_ACTION_RESET_GAME) {
			stateManager->resetGame();
		} else if(gameData->gameOverAction == GameData::DEATH_ACTION_RESET_MAP) {
			stateManager->returnLastMap();
		} else {
			exit(0);
		}
	}

	return 0;
}

void GameOverState::render(Screen *screen) {
	fundo->render(screen);
}
