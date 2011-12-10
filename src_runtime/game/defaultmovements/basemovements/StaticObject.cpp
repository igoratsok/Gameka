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

#include "StaticObject.h"

StaticObject::StaticObject()
	: AcceleratedParticle(){
	velocity->x = 0;
	velocity->y = 0;
	acceleration->x = 0;
	acceleration->y = 0;

}

StaticObject::~StaticObject() {

}

StaticObject::StaticObject(std::string *fileName, commtypes::real x, commtypes::real y)
	: AcceleratedParticle(fileName, x, y){
	velocity->x = 0;
	velocity->y = 0;
	acceleration->x = 0;
	acceleration->y = 0;
}

StaticObject::StaticObject(GameObjectInstance *gameObjectInstance)
	: AcceleratedParticle(gameObjectInstance) {
	velocity->x = 0;
	velocity->y = 0;
	acceleration->x = 0;
	acceleration->y = 0;
}

int StaticObject::update(int dt) {
	if(AcceleratedParticle::update(dt) == -1) {
		return -1;
	}

	return 0;
}
