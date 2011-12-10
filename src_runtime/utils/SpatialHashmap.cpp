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

#include "SpatialHashmap.h"

SpatialHashmap::SpatialHashmap(int scenewidth, int sceneheight, int cellsize) :
	scenewidth(scenewidth), sceneheight(sceneheight), cellsize(cellsize) {
	cols = scenewidth/cellsize + 1;
	rows = sceneheight/cellsize + 1;
	size = cols*rows;

	buckets = new std::vector<std::list<GameObject*> >(cols*rows);


}

SpatialHashmap::~SpatialHashmap() {
	delete buckets;
}

void SpatialHashmap::clearBuckets() {
	buckets->clear();
	buckets->resize(size);
}

void SpatialHashmap::registerObject(GameObject *gameObject) {
	std::list<int> *cellIds = getIdsForObj(gameObject);
	for(std::list<int>::iterator it = cellIds->begin(); it != cellIds->end(); ++it) {
		int i = *it;
		if(i > 0 && i < size) {
			buckets->at(i).push_back(gameObject);
		}

	}

	delete cellIds;
}

std::list<int> *SpatialHashmap::getIdsForObj(GameObject *gameObject) {
	Rect *objRect = gameObject->sprite->getRectWithoutRot();
	std::list<int> *bucketsObjIsIn = new std::list<int>();

	Vector2 min = Vector2(*gameObject->position);
	Vector2 max = Vector2(gameObject->position->x + objRect->w,
			gameObject->position->y + objRect->h);
	delete objRect;


	addBucket(min, cols, bucketsObjIsIn);
	addBucket(Vector2(max.x, min.y), cols, bucketsObjIsIn);
	addBucket(max, cols, bucketsObjIsIn);
	addBucket(Vector2(min.x, max.y), cols, bucketsObjIsIn);

	return bucketsObjIsIn;


}

void SpatialHashmap::addBucket(Vector2 vector2, float width, std::list<int>* bucketAddTo) {
	int cellPosition = (int)(floor(vector2.x/cellsize) + floor(vector2.y/cellsize)*width);

	if(std::find(bucketAddTo->begin(), bucketAddTo->end(), cellPosition) == bucketAddTo->end()) {
		bucketAddTo->push_back(cellPosition);
	}
}

std::list<GameObject*> *SpatialHashmap::getNearby(GameObject *gameObject) {
	std::list<GameObject*> *objects = new std::list<GameObject*>();
	std::list<int> *cellIds = getIdsForObj(gameObject);

	for(std::list<int>::iterator it = cellIds->begin(); it != cellIds->end(); ++it) {
		int i = *it;
		if(i > 0 && i < size) {
			if(!buckets->at(i).empty()) {
				objects->insert(objects->begin(), buckets->at(i).begin(), buckets->at(i).end());
			}
		}


	}

	delete cellIds;

	return objects;

}
