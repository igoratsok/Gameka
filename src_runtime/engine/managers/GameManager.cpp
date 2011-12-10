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

#include "GameManager.h"


GameManager::GameManager(GameData *gameData) {
	this->gameData = gameData;

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO) == -1) {
		fprintf(stderr, "SDL_Init error. Exiting..");
		exit(1);
	}

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 640);
	TTF_Init();
	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);

	screen = new Screen(gameData->resWidth, gameData->resHeight);



	SDL_WM_SetCaption(gameData->gameName->c_str(), NULL);


	fpsManager = (FPSmanager*)malloc(sizeof(FPSmanager));
	SDL_initFramerate(fpsManager);
	SDL_setFramerate(fpsManager, 60);


	stateManager = new StateManager(gameData);

	timerManager = TimerManager::getInstance();

	timer = 0;

}

GameManager::~GameManager() {

}

void GameManager::run() {
	int atimer;
	atimer = 0;

	while(!SDL_QuitRequested()) {
		timer = SDL_GetTicks();
		dt = timer - atimer;
		atimer = timer;

		screen->fillScreen();

		stateManager->updateState(dt, screen);
		stateManager->renderState(screen);

		screen->flipScreen();
		screen->blitTopScreen();

		timerManager->update(dt);

		SDL_Event event;
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				exit(0);
			}
		}

		SDL_framerateDelay(fpsManager);

	}
}
