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

#include "TimerManager.h"

TimerManager *TimerManager::singleton = NULL;

TimerManager::TimerManager() {
	globalTimer = 0;
	mapTimer = 0;
}

TimerManager::~TimerManager() {
	// TODO Auto-generated destructor stub
}

TimerManager *TimerManager::getInstance() {
	if(singleton == NULL) {
		singleton = new TimerManager();
	}

	return singleton;
}

void TimerManager::update(int dt) {
	globalTimer += dt;
	mapTimer += dt;
}

void TimerManager::resetGlobalTimer(int value) {
	this->globalTimer = value;
}

void TimerManager::resetMapTimer(int value) {
	this->mapTimer = value;
}

unsigned long long int TimerManager::getGlobalTimer() {
	return globalTimer;
}

unsigned long long int TimerManager::getMapTimer() {
	return mapTimer;
}
