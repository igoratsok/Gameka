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

#include "InputManager.h"

InputManager* InputManager::singletonInstance = NULL;


InputManager::InputManager() {
	int i;
	/* obtendo o keyState */
	keyState = SDL_GetKeyState(NULL);
	nkeys = 322;

	keyStateAntPress = (Uint8*) calloc(nkeys+1, sizeof(Uint8));
	keyStateAntRelease = (Uint8*) calloc(nkeys+1, sizeof(Uint8));


	for(i = 0; i < nkeys; i++) {
		keyStateAntPress[i] = false;
	}

	for(i = 0; i < nkeys; i++) {
		keyStateAntRelease[i] = false;
	}

	mouseAntPress = (Uint8*) calloc(3, sizeof(Uint8));
	for(i = 0; i < 3; i++) {
		mouseAntPress[i] = false;
	}

	mouseAntPress[0] = false;

	currentDirection = 0;

}

InputManager::~InputManager() {
	// TODO Auto-generated destructor stub
}


bool InputManager::isKeyDown(int key) {
	return keyState[key];
}

bool InputManager::isKeyUp(int key) {
	return !keyState[key];
}

bool InputManager::isKeyPressed(int key) {
	if(keyState[key] && !keyStateAntPress[key]) {
		return true;
	}


	return false;
}

bool InputManager::isKeyReleased(int key) {
	if(!keyState[key] && keyStateAntRelease[key]) {
		keyStateAntRelease[key] = keyState[key];
		return true;
	}

	return false;
}

InputManager* InputManager::getInstance() {
	if(singletonInstance == NULL) {
		singletonInstance = new InputManager();
	}
	return singletonInstance;
}

Vector2 InputManager::getMousePosition() {
	Vector2 mousePosition;
	int x, y;
	SDL_GetMouseState(&x, &y);
	mousePosition.x = x;
	mousePosition.y = y;

	return mousePosition;
}

Vector2 InputManager::getScenarioMousePosition() {
	Vector2 mousePosition = getMousePosition();
	Vector2 *scrolledMousePosition;
	scrolledMousePosition = ScrollManager::getInstance()->scrollMouseVector(&mousePosition);

	Vector2 functionReturn = *scrolledMousePosition;
	delete scrolledMousePosition;

	return functionReturn;

}

bool InputManager::isMouseDown(int botao) {
	return SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(botao);
}

bool InputManager::isMousePressed(int botao) {

	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(botao) && (mouseAntPress[botao] == false)) {
		mouseAntPress[botao] = SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(botao);
		return true;
	}




	return false;
}

bool InputManager::isMouseInsideRectNoScrolling(Rect rect) {
	Vector2 mousePos = getMousePosition();
	if(mousePos.x > rect.x && mousePos.x < rect.x + rect.w &&
			mousePos.y > rect.y && mousePos.y < rect.y + rect.h) {
		return true;
	} else {
		return false;
	}
}

void InputManager::update(int dt) {
	if(keyState[SDLK_RIGHT] || keyState[SDLK_UP] || keyState[SDLK_LEFT] || keyState[SDLK_DOWN]) {
		if(keyState[SDLK_RIGHT]) {
			if(keyState[SDLK_UP]) {
				currentDirection = 45;
			} else if(keyState[SDLK_DOWN]) {
				currentDirection = 315;
			} else {
				currentDirection = 0;
			}
		} else if(keyState[SDLK_UP]) {
			if(keyState[SDLK_LEFT]) {
				currentDirection = 135;
			} else if(keyState[SDLK_RIGHT]) {
				currentDirection = 45;
			} else {
				currentDirection = 90;
			}
		} else if(keyState[SDLK_LEFT]) {
			if(keyState[SDLK_UP]) {
				currentDirection = 135;
			} else if(keyState[SDLK_DOWN]) {
				currentDirection = 225;
			} else {
				currentDirection = 180;
			}
		} else if(keyState[SDLK_DOWN]) {
			if(keyState[SDLK_LEFT]) {
				currentDirection = 225;
			} else if(keyState[SDLK_RIGHT]) {
				currentDirection = 315;
			} else {
				currentDirection = 270;
			}
		}
	}



	for(int i = 0; i < nkeys; i++) {
		keyStateAntPress[i] = keyState[i];
		keyStateAntRelease[i] = keyState[i];
	}

	for(int i = 0; i < 3; i++) {
		mouseAntPress[i] = SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(i);
	}



}

int InputManager::getCurrentDirection() {
	return currentDirection;
}

bool InputManager::clicksIn(GameObject *gameObject) {
	if(isMousePressed(1)) {
		return isMouseInside(gameObject);
	} else {
		return false;
	}
}

bool InputManager::isClicking(GameObject *gameObject) {
	if(isMouseDown(1)) {
		return isMouseInside(gameObject);
	} else {
		return false;
	}
}

bool InputManager::isMouseInside(GameObject *gameObject) {
	Vector2 mousePosition = getScenarioMousePosition();

	Rect *gameObjectRect = gameObject->sprite->getRectWithoutRot();

	if(mousePosition.x < gameObject->position->x) {
		delete gameObjectRect;
		return false;
	}

	if(mousePosition.x > gameObject->position->x + gameObjectRect->w) {
		delete gameObjectRect;
		return false;
	}

	if(mousePosition.y < gameObject->position->y) {
		delete gameObjectRect;
		return false;
	}

	if(mousePosition.y > gameObject->position->y + gameObjectRect->h) {
		delete gameObjectRect;
		return false;
	}


	delete gameObjectRect;
	return true;
}
