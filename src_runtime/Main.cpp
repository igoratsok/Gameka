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
#include <time.h>
#include <stdlib.h>

#include "GameManager.h"
#include "GameData.h"
#include "Line.h"
#include "Vector2.h"
#include "Rectangle.h"
#include "Sphere.h"

class Line;
class Vector2;
class Rect;
class Sphere;

#include <string>

#undef main

int main(int argc, char **argv) {
        GameData *gameData;
	gameData = GameData::getInstance();
	gameData->gameName = new string("Jogo Sample");
	gameData->resWidth = 640;
	gameData->resHeight = 480;



	Sphere sphere = Sphere(Vector2(0, 10), 2);
	Rect rect = Rect(10, 10, 10, 10);
	Vector2 finalPos = Vector2(30, 10);
	Vector2 p;
	float t;
	int side;

	if(Sphere::testMovingSphereRect(sphere, finalPos, rect, &t, &p, &side)) {
		printf("1::: %d %f: %f %f\n", side, t, p.x, p.y);
	}

	Rect rect1 = Rect(10, 10, 10, 10);
	Rect rect2 = Rect(0, 0, 2, 2);
	Vector2 v1 = Vector2(0, 0);
	Vector2 v2 = Vector2(10, 1);
	float tfirst, tlast;
	Rect recx = Rect(0, 0, 0, 0);

	if(rect2.movingIntersectRect(v2, rect1, &tfirst, &tlast, &side, &recx)) {
		printf("2::: %f %f %f, SIDE: %d\n", tfirst, tlast, rect2.x + (v2.x*tfirst), side);
	}


	Vector2 r1 = Vector2(0, 0);
	Vector2 r2 = Vector2(20, 3);

	if(rect1.rayIntersection(r1, r2, &tfirst, &p)) {
		printf("3:: %f, %f, %f", tfirst, p.x, p.y);
	}



	char *teste = (char*) calloc(1, sizeof(char));
	teste[0] = '\0';

	std::string testao = std::string(teste);

	printf("argc: %d\n", argc);

	if(argc > 1) {
		gameData->arg1 = new std::string(argv[1]);
	} else {
		gameData->arg1 = NULL;
	}

	FILE *fp;

	if(gameData->arg1 != NULL) {
		fp = fopen(std::string(gameData->arg1->c_str()).append("game.ldo").c_str(), "rb");
		std::cout << std::string(gameData->arg1->c_str()).append("game.ldo").c_str() << std::endl;
	} else {
		fp = fopen("game.ldo", "rb");
	}

	if( fp ) {
		fclose(fp);
		gameData->loadFile("game.ldo");
	} else {
		gameData->loadFile("game.gmk");
	}


	gameData->preprocessPointers();




	GameManager *gameManager;
	gameManager = new GameManager(gameData);
	gameManager->run();
}
