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


#include "SplashState.h"



void SplashState::load() {
	std::string *nomeSprite1;
	//= "colisor_.png";
	std::string *nomeSprite2, *nomeSprite3;
	//= "emissor01.png";
	nomeSprite1 = new std::string("emissor01.png");
	nomeSprite2 = new std::string("car.png");
	nomeSprite3 = new std::string("fundo.jpg");

	fundo = new Sprite(nomeSprite3, new Vector2(0,0));


	//map = gameData->mapList->at(0);
	map = new Tilemap(0);


	spriteTeste = new Sprite(nomeSprite1 ,new Vector2(200,100));
	rot = 20;
	spriteTeste->setRot(rot);
	spriteColisor = new Sprite(nomeSprite2, new Vector2(200, 0));
	acc = new VehicleMovement(nomeSprite2, 100, 0);

	//acc->setCenter();
	acc->setTilemap(map);

	GameData *gameData = GameData::getInstance();



	emo = new EightMovementObject(nomeSprite1, 100, 0);
	emo->setAutomaticRotation(true);
	emo->setCenter();
	emo->setTilemap(map);


	inputManager = new InputManager();
	zoom = 1;

}
void SplashState::render(Screen *screen) {
	map->render(screen);
	//spriteTeste->render(screen);
	//spriteColisor->render(screen);
	//fundo->render(screen);
	acc->render(screen);
	emo->render(screen);


	//lineRGBA(screen->getTopScreen(), 0, 0, 500, 500, 1, 1, 1, 1);

	//screen->setZoom(zoom);


}

void SplashState::unload() {

}

int SplashState::update(int dt) {
	if(rot > 360) rot = 0;
	rot += 0.1;
	//spriteTeste->setRot(rot);

	/*
	if(inputManager->isKeyDown(SDLK_LEFT)) {
		spriteColisor->pos->x--;
	}
	if(inputManager->isKeyDown(SDLK_DOWN)) {
			spriteColisor->pos->y++;
	}
	if(inputManager->isKeyDown(SDLK_UP)) {
			spriteColisor->pos->y--;
	}
	if(inputManager->isKeyDown(SDLK_RIGHT)) {
			spriteColisor->pos->x++;
	}
	if(inputManager->isKeyDown(SDLK_z)) {
		zoom += 0.05;
	}
	if(inputManager->isKeyDown(SDLK_x)) {
		zoom -= 0.05;
		if(zoom < 0.1) zoom = 0.1;
	}

	if(spriteColisor->pixelCollidesWith(spriteTeste)){

		spriteColisor->pos->x = 200;
		spriteColisor->pos->y = 0;

	}
	*/

	//acc->update(dt);
	emo->update(dt);

	printf("vx: %f \tvy: %f\n", emo->velocity->x*dt, emo->velocity->y*dt);


	return 0;
}
