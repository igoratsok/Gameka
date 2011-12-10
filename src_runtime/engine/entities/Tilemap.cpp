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

#include "Tilemap.h"

Tilemap::Tilemap(int mapId) {
	int i, j;
	gameData = GameData::getInstance();
	scrollManager = ScrollManager::getInstance();

	tileset = new Tileset();

	tileset->file = "tile_example.png";

	tilesetSurface = gameData->loadIMG("tile_example.png");
	tileWidth = 32;
	tileHeight = 32;

	renderRect.w = tileWidth;
	renderRect.h = tileHeight;

	nx = tilesetSurface->w/tileWidth;
	ny = tilesetSurface->h/tileHeight;

	mapWidth = 30;
	mapHeight = 30;
	mapLayers = 1;



	for(i = 0; i < mapWidth; i++) {
		for(j = 0; j < mapHeight; j++) {
			if(!((i > 15 && i < 20) && (j > 15 && j < 20))) {
				map[i][j][0] = new Tile(0, 2, tileHeight, tileWidth);
				map[i][j][0]->setCollisionType(Tile::COLLISION_PASS);
				map[i][j][0]->tileset = tileset;
			} else {
				map[i][j][0] = new Tile(1, 0, tileHeight, tileWidth);
				map[i][j][0]->setCollisionType(Tile::COLLISION_BLOCK);
				map[i][j][0]->tileset = tileset;
			}
		}
	}





}

Tilemap::~Tilemap() {
	// TODO Auto-generated destructor stub
}

Tilemap::Tilemap() {
	gameData = GameData::getInstance();
	scrollManager = ScrollManager::getInstance();
}

void Tilemap::render(Screen* screen) {
	int i, j, z, startX, startY, endX, endY;



	if(scrollManager->isXScrolling()) {
		startX = scrollManager->getCenter()->x - gameData->resWidth - tileWidth;
		endX = scrollManager->getCenter()->x +  scrollManager->translate.x + gameData->resWidth/2 + tileWidth;
	} else {
		startX = scrollManager->getCenter()->x - gameData->resWidth - tileWidth;
		endX = scrollManager->getCenter()->x +  scrollManager->translate.x + gameData->resWidth + tileWidth;
	}

	if(scrollManager->isYScrolling()) {
		startY = scrollManager->getCenter()->y - gameData->resHeight - tileHeight;
		endY = scrollManager->getCenter()->y +  scrollManager->translate.y + gameData->resHeight/2 + tileHeight;
	} else {
		startY = scrollManager->getCenter()->y - gameData->resHeight - tileHeight;
		endY = scrollManager->getCenter()->y +  scrollManager->translate.y + gameData->resHeight + tileHeight;
	}






	startX /= tileWidth;
	startY /= tileHeight;



	if(startX > mapWidth - gameData->resWidth/tileWidth) {
		startX = mapWidth - gameData->resWidth/tileWidth;
	}

	if(startY > mapHeight - gameData->resHeight/tileHeight) {
		startY = mapHeight - gameData->resHeight/tileHeight;
	}



	if(scrollManager->getCenter()->x < 0) {
		endX = mapWidth;
	} else {
		endX /= tileWidth;
	}

	if(scrollManager->getCenter()->y < 0) {
		endY = mapHeight;
	} else {
		endY /= tileHeight;
	}


	if(endX > mapWidth) endX = mapWidth;
	if(endY > mapHeight) endY = mapHeight;
	if(startX < 0) startX = 0;
	if(startY < 0) startY = 0;


	for(i = startX; i < endX; i++) {
		for(j = startY; j < endY; j++) {
			for(z = 0; z < mapLayers; z++) {


				renderRect.x = i*tileWidth;
				renderRect.y = j*tileHeight;




				scrollManager->scrollSDLRect(&renderRect);

				Tile* tile = (map[i][j][z]);

				if(tile != NULL) {
					if(tile->rectangleTileMap.x == -1 || tile->rectangleTileMap.y != -1) {
						SDL_BlitSurface(tile->getTilesetSurface(), &(tile->rectangleTileMap),
								screen->getTopScreen(), &renderRect);
					}

				}
			}
		}
	}
}

Tile* Tilemap::getTilesetByIndex(int j, int i, int z) {
	if(i >= 0 && i < mapWidth && j >= 0 && j < mapHeight) {
		return map[i][j][z];
	} else {
		return NULL;
	}

}

Tile* Tilemap::getTilesetByPosition(commtypes::real x, commtypes::real y, commtypes::real z) {
	int indexX, indexY;

	indexX = (int)(x/tileWidth);
	indexY = (int)(y/tileHeight);

	return getTilesetByIndex(indexY, indexX, z);
}

Tile* Tilemap::isTilesetColisionBlockByPosition(const int type, commtypes::real x, commtypes::real y) {
	for(int z = 0; z < mapLayers; z++) {
		Tile *tile = getTilesetByPosition(x, y, z);

		if(tile != NULL && tile->collisionType == type) {
			return tile;
		}
	}

	return NULL;
}
