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

#include "Music.h"

/**
 * Construtor de uma classe Music. O tipo
 * pode ser SOM ou MUSICA.
 */
Music::Music(std::string *fileName, int tipo) {
	// TODO Auto-generated constructor stub
	GameData *gameData = GameData::getInstance();

	if(gameData->arg1 == NULL) {
		if(tipo == SOM) {
			som = Mix_LoadWAV(fileName->c_str());
		} else {
			music = Mix_LoadMUS(fileName->c_str());
		}
	} else {
		if(tipo == SOM) {
			som = Mix_LoadWAV(std::string(gameData->arg1->c_str()).append(fileName->c_str()).c_str());
		} else {
			music = Mix_LoadMUS(std::string(gameData->arg1->c_str()).append(fileName->c_str()).c_str());
		}

	}

	tocando = false;
	this->tipo = tipo;

}

Music::~Music() {
	// TODO Auto-generated destructor stub

}

void Music::play(int times) {
	if(tipo == SOM) {
		Mix_PlayChannel(-1, som, times);
	} else {
		if(music) {
			Mix_PlayMusic(music, times);
		}

	}
}

void Music::pauseResume() {
	if(tipo == SOM) {
		if(Mix_Paused(0)) {
			Mix_Resume(0);
		} else if(Mix_Playing(0)) {
			Mix_Pause(0);
		}

		if(Mix_Paused(1)) {
			Mix_Resume(1);
		} else if(Mix_Playing(1)) {
			Mix_Pause(1);
		}
	} else {
		if(Mix_PausedMusic()) {
			Mix_ResumeMusic();
		} else {
			Mix_PauseMusic();
		}
	}


}

void Music::stop() {
	if(tipo == SOM) {
		Mix_HaltChannel(0);
		Mix_HaltChannel(1);
	} else {
		Mix_HaltMusic();
	}
}
