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

#include "SoundManager.h"

SoundManager* SoundManager::singleton = NULL;

SoundManager::SoundManager() {
	currentMusic = NULL;
	sounds = new std::list<Music*>();

}

SoundManager::~SoundManager() {

}

void SoundManager::playMusic(std::string path, int nloops) {
	if(currentMusic != NULL) {
		delete currentMusic;
	}

	currentMusic = new Music(&path, Music::MUSICA);
	currentMusic->play(nloops);
}

void SoundManager::pauseResumeMusic() {
	if(currentMusic != NULL) {
		currentMusic->pauseResume();
	}
}

void SoundManager::stopMusic() {
	if(currentMusic != NULL) {
		currentMusic->stop();
	}
}


bool SoundManager::isMusicPlaying() {
	if(!currentMusic) {
		return false;
	}

	return Mix_PlayingMusic();
}

void SoundManager::playSound(std::string path, int nloops) {
	Music *music = new Music(&path, Music::SOM);

	if(Mix_Playing(-1) == 2) {
		Mix_HaltChannel(-1);
	}
	music->play(nloops - 1);

	sounds->push_back(music);
}

void SoundManager::pauseResumeSounds() {
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
}

void SoundManager::stopSound() {
	Mix_HaltChannel(-1);

}

bool SoundManager::isSoundPlaying() {
	return Mix_Playing(-1);
}

SoundManager* SoundManager::getInstance() {
	if(singleton == NULL) {
		singleton = new SoundManager();
	}

	return singleton;
}
