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
#ifndef SPLASHSTATE_H_
#define SPLASHSTATE_H_

#include <stdio.h>
#include <string>
#include <list>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "State.h"

#include "StateManager.h"
#include "Sprite.h"
#include "Screen.h"
#include "Tilemap.h"
#include "InputManager.h"
#include "EightMovementObject.h"
#include "VehicleMovement.h"
#include "GameData.h"

class StateManager;
class Sprite;
class Screen;
class Tilemap;
class InputManager;
class EightMovementObject;
class VehicleMovement;
class GameData;



using namespace std;

class SplashState : public State {
public:

	void load();
	void unload();
	int update(int dt);
	void render(Screen *screen);

	float rot;
	float zoom;

	Sprite *spriteTeste, *spriteColisor, *fundo;
	InputManager *inputManager;
	Tilemap *map;
	VehicleMovement *acc;
	EightMovementObject *emo;

};

#endif /* SPLASHSTATE_H_ */
