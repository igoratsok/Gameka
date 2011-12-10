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

#include "ObjectFactory.h"

ObjectFactory::ObjectFactory() {


}

ObjectFactory::~ObjectFactory() {
	// TODO Auto-generated destructor stub
}

EightMovementObject* ObjectFactory::mountEightMovement(GameObjectInstance *gameObjectInstance) {
	EightMovementObject *eightMovement;
	eightMovement = new EightMovementObject(gameObjectInstance);



	return eightMovement;
}

PlatformerMovement* ObjectFactory::mountPlatformerMovement(GameObjectInstance *gameObjectInstance) {
	PlatformerMovement *platformerMovement;
	platformerMovement = new PlatformerMovement(gameObjectInstance);



	return platformerMovement;
}

VehicleMovement* ObjectFactory::mountVehicleMovement(GameObjectInstance *gameObjectInstance) {
	VehicleMovement *vehicleMovement;
	vehicleMovement = new VehicleMovement(gameObjectInstance);



	return vehicleMovement;
}

StaticObject* ObjectFactory::mountStaticObject(GameObjectInstance *gameObjectInstance) {
	StaticObject *staticObject;
	staticObject = new StaticObject(gameObjectInstance);



	return staticObject;
}

BouncingBall* ObjectFactory::mountBouncingBallObject(GameObjectInstance *gameObjectInstance) {
	BouncingBall *bouncingBallObject;
	bouncingBallObject = new BouncingBall(gameObjectInstance);


	return bouncingBallObject;
}

MouseFollowMovement* ObjectFactory::mountMouseFollowMovementObject(GameObjectInstance *gameObjectInstance) {
	MouseFollowMovement* mouseFollowMovement;
	mouseFollowMovement = new MouseFollowMovement(gameObjectInstance);




	return mouseFollowMovement;
}

ItemMovementObject* ObjectFactory::mountItemMovementObject(GameObjectInstance *gameObjectInstance) {
	ItemMovementObject* itemMovementObject;
	itemMovementObject = new ItemMovementObject(gameObjectInstance);




	return itemMovementObject;
}

NpcMovementObject* ObjectFactory::mountNpcMovementObject(GameObjectInstance *gameObjectInstance) {
	NpcMovementObject* npcMovementObject;
	npcMovementObject = new NpcMovementObject(gameObjectInstance);



	return npcMovementObject;
}

EnemyMovementObject* ObjectFactory::mountEnemyMovementObject(GameObjectInstance *gameObjectInstance) {
	EnemyMovementObject* enemyMovementObject;
	enemyMovementObject = new EnemyMovementObject(gameObjectInstance);



	return enemyMovementObject;
}
