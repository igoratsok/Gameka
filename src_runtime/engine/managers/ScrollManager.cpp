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

#include "ScrollManager.h"

ScrollManager* ScrollManager::singleton = NULL;

ScrollManager::ScrollManager() {
	center = new Vector2();
	printf("center nulified");
	gameData = GameData::getInstance();
	translate.x = 0;
	translate.y = 0;
	tilemap = NULL;
}

ScrollManager::~ScrollManager() {

}

ScrollManager *ScrollManager::getInstance() {
	if(singleton == NULL) singleton = new ScrollManager();

	return singleton;
}

void ScrollManager::setCenter(Vector2 *center) {
	this->center = center;
}

void ScrollManager::removeCenter() {
	this->center = NULL;
}

void ScrollManager::setTilemap(Tilemap *tilemap) {
	this->tilemap = tilemap;

	if(this->tilemap != NULL) {
		tilemapRightBorder = (tilemap->tileWidth*tilemap->mapWidth - gameData->resWidth/2);
		tilemapDownBorder = (tilemap->tileHeight*tilemap->mapHeight - gameData->resHeight/2);
	}

}

Vector2* ScrollManager::getCenter() {
	return this->center;
}



void ScrollManager::scrollSDLRect(SDL_Rect *rect) {
	Vector2* vector1, *vector2;
	vector1 = new Vector2(rect->x, rect->y);

	vector2 = scrollVector(vector1);
	rect->x = vector2->x;
	rect->y = vector2->y;

	delete vector1;
	delete vector2;
}

Vector2* ScrollManager::scrollVector(Vector2 *vector) {
	int newX, newY;
	if(center != NULL) {
		if(vector == center) {
			if(center->x + translate.x > (gameData->resWidth/2)) {
				newX = gameData->resWidth/2 - translate.x;

				if(tilemap != NULL) {
					if(center->x + translate.x > tilemapRightBorder) {
						newX = gameData->resWidth/2 - translate.x + (center->x - tilemapRightBorder);
					}
				}


			} else {
				newX = vector->x;
			}

			if(center->y + translate.y > (gameData->resHeight/2)) {
				newY = gameData->resHeight/2 - translate.y;

				if(tilemap != NULL) {
					if(center->y + translate.y > tilemapDownBorder) {
						newY = gameData->resHeight/2 - translate.y + (center->y - tilemapDownBorder);
					}
				}

			} else {
				newY = vector->y;
			}

		} else {
			if(center->x + translate.x > (gameData->resWidth/2)) {
				newX = gameData->resWidth/2 - translate.x + (vector->x - center->x);

				if(tilemap != NULL) {
					if(center->x + translate.x > tilemapRightBorder) {
						newX = gameData->resWidth/2 - translate.x + (vector->x - tilemapRightBorder);
					}
				}

			} else {
				newX = vector->x;
			}

			if(center->y + translate.y > (gameData->resHeight/2)) {
				newY = gameData->resHeight/2 - translate.y + (vector->y - center->y);

				if(tilemap != NULL) {
					if(center->y + translate.y > tilemapDownBorder) {
						newY = gameData->resHeight/2 - translate.y + (vector->y - tilemapDownBorder);
					}
				}

			} else {
				newY = vector->y;
			}
		}
	} else {
		return new Vector2(vector->x, vector->y );
	}


	return new Vector2(newX, newY);
}

Vector2* ScrollManager::scrollMouseVector(Vector2 *vector) {
	float newX, newY;

	if(center == NULL) {
		return vector;
	}

	if(center->x + translate.x > (gameData->resWidth/2)) {
		newX = vector->x + (center->x + translate.x - gameData->resWidth/2);

		if(tilemap != NULL) {
			if(center->x + translate.x > tilemapRightBorder) {
				newX = vector->x + tilemapRightBorder - gameData->resWidth/2;
			}
		}

	} else {
		newX = vector->x;
	}

	if(center->y + translate.y > (gameData->resHeight/2)) {
		newY = vector->y + (center->y + translate.y - gameData->resHeight/2);

		if(tilemap != NULL) {
			if(center->y + translate.y > tilemapDownBorder) {
				newY = vector->y + tilemapDownBorder - gameData->resHeight/2;
			}
		}
	} else {
		newY = vector->y;
	}

	return new Vector2(newX, newY);
}

bool ScrollManager::isXScrolling() {
	if(center == NULL) return true;
	else if(center->x + translate.x > (gameData->resWidth/2)) return true;
	else return false;
}

bool ScrollManager::isYScrolling() {
	if(center == NULL) return true;
	else if(center->y + translate.y > (gameData->resHeight/2)) return true;
	else return false;
}

bool ScrollManager::isCenterNull(){
	return (center == NULL);
}
