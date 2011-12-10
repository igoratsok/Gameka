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

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>
#include <list>

#include "CommonTypes.h"


#include "Vector2.h"
#include "Sphere.h"
#include "Sprite.h"
#include "Screen.h"
#include "Tilemap.h"
#include "Tile.h"
#include "DamageDisplay.h"
#include "PlayerData.h"
#include "DialogueText.h"
#include "InputManager.h"
#include "ModalManager.h"

#include "GameObjectInstance.h"
#include "Interpreter.h"
#include "SpatialHashmap.h"
#include "SoundManager.h"





class Vector2;
class Sphere;
class Sprite;
class Screen;
class Tilemap;
class Tile;
class DamageDisplay;
class PlayerData;
class DialogueText;
class InputManager;
class ModalStack;
class GameObjectInstance;
class Interpreter;
class SpatialHashmap;
class SoundManager;




/**
 * Objeto de jogo genérico. Possui métodos
 * de detecção de colisão por blocos, píxel, determinação de rotação
 * dentre outros. Todos objetos de jogo devem herdar dessa classe,
 * exceto Tiles.
 */
class GameObject {
public:
	GameObject();
	GameObject(commtypes::real x, commtypes::real y);
	GameObject(std::string *fileName);
	GameObject(std::string *fileName, commtypes::real x, commtypes::real y);
	GameObject(GameObjectInstance *gameObjectInstance);
	virtual ~GameObject();

	Sphere getSphere();
	Vector2 getCenter();

	bool blockCollidesWith(GameObject* gameObject);
	bool pixelCollidesWith(GameObject* gameObject);
	void setCenter();
	void setPositionByCenter(Vector2 center);
	void setSpriteRotation(commtypes::real angle);
	void setSpriteDirectionAngle(commtypes::real angle);
	void setTilemap(Tilemap* tilemap);
	void setObjectList(std::list<GameObject*> *objectList);
	void setSpatialHashmap(SpatialHashmap *spatialHashMap);
	void setModalManager(ModalStack *modalManager);
	std::list<GameObject*>* getObjectList();

	void setInvincibility(int value);
	int getInvincibility();
	bool isInvincible();

	void setNoAttackTimer(int timer);


	void addHp(int damage);
	void addMp(int damage);
	void addExp(int exp);

	float getAtk();
	float getDef();
	float getInt();

	int addDamage(GameObject *damager, int extraDamage = 1);

	virtual int update(int dt);
	void render(Screen *screen);
	void renderCenter(Screen *screen);

	bool collidesWith(GameObject *gameObject);
	bool collidesPixelWith(GameObject *gameObject);

	virtual void follow(Vector2 point, int dt);
	virtual void moveAway(Vector2 point, int dt);
	virtual void follow(Vector2 point, int dt, float velocity);
	virtual void moveAway(Vector2 point, int dt, float velocity);

	virtual void bounce(Rect rect, int dt);
	virtual void bounceEvent(int dt);

	void playSpecialSound();
	void playDamageSound();


	bool isInMapLeftSide();
	bool isInMapUpSide();
	bool isInMapRightSide();
	bool isInMapDownSide();

	Tile* testBoxCollisionTile(int dt);
	bool testBoxCollisionTileUp(int dt);
	bool testBoxCollisionTileDown(int dt);
	bool testBoxCollisionTileLeft(int dt);
	bool testBoxCollisionTileRight(int dt);

	bool testBoxCollisionTile(int dt, Vector2 position);
	bool testBoxCollisionTileUp(int dt, Vector2 position);
	bool testBoxCollisionTileDown(int dt, Vector2 position);
	bool testBoxCollisionTileLeft(int dt, Vector2 position);
	bool testBoxCollisionTileRight(int dt, Vector2 position);

	void setAttributeById(int id, float value);
	float getAttributeById(int id);

	void setVariableById(int id, float value);
	float getVariableById(int id);


	Vector2* position;
	Vector2 positionAnt;
	Tilemap* tilemap;
	Sprite *sprite;

	GameObjectInstance *gameObjectInstance;
	InputManager *inputManager;
	ModalStack *modalManager;

	SpatialHashmap *spatialHashmap;
	Interpreter *interpreter;


	commtypes::real angle;



	bool isCenter;
	bool isMainObject;
	bool autoCollision;
	bool drawShadow;

	bool enemyPhysicalAttackCapable;

	int hp, mp;
	Vector2 *velocity;
	Vector2 *lastDirection;
	Vector2 *acceleration;
	float gravity;
	float jumpIntensity;


	/* variáveis para tratamento de drag&drop */
	Vector2 dragDropDifference;
	bool isDragging;
	bool clickFirstFrame;

	/* variável para ítens mágicos, como fogo */
	bool isMagical;

	SoundManager *soundManager;

	int noAttackTimer;


    static const int ATT_POSITION_X =       0;
    static const int ATT_POSITION_Y =       1;
    static const int ATT_VELOCITY =         2;
    static const int ATT_VELOCITY_X =       3;
    static const int ATT_VELOCITY_Y =       4;
    static const int ATT_ACCELERATION =     5;
    static const int ATT_ACCELERATION_X =   6;
    static const int ATT_ACCELERATION_Y =   7;

    static const int ATT_GRAVITY =          8;
    static const int ATT_JUMP_INTENSITY =   9;
    static const int ATT_HP =               10;
    static const int ATT_MP =               11;
    static const int ATT_ATK =              12;
    static const int ATT_DEF =              13;
    static const int ATT_INT =              14;

    static const int ATT_DIRECTION =        15;
    static const int ATT_ANIMATION =        16;
    static const int ATT_ROTATION =         17;
    static const int ATT_ZOOM =             18;
    static const int ATT_INSTANCE_NUMBER =  31;
    static const int ATT_GAME_TIMER       = 35;
	static const int ATT_MAP_TIMER        = 36;

	static const int ATT_OBJECT_LEVEL                   = 37;





private:
	Sphere *boundingSphere;
	std::list<GameObject*> *objectList;
	std::list<DamageDisplay*> damageDisplayList;




	int invincibilityTimer;
	bool invincibilityVisibilityFlag;




};

#endif /* GAMEOBJECT_H_ */
