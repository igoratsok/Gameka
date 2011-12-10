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

#include "PlayerData.h"

PlayerData *PlayerData::singleton = NULL;

PlayerData::PlayerData() {
	GameData *gameData = GameData::getInstance();
	player = NULL;

	pointsText = new Text("Pontos: ", "runtime-common/oldsansblack.ttf", Vector2(10, 10));
	hpText = new Text("Vida: ", "runtime-common/oldsansblack.ttf",  Vector2(10, 30));
	mpText = new Text("Magia: ", "runtime-common/oldsansblack.ttf",  Vector2(10, 50));

	if(gameData->looseLifes) {
		livesText = new Text("Vidas: ", "runtime-common/oldsansblack.ttf",  Vector2(gameData->resWidth - 85, 10));
		lives = gameData->totalLives;
	} else {
		livesText = NULL;
	}

	teleportPosition = NULL;


}

PlayerData::~PlayerData() {
	// TODO Auto-generated destructor stub
}

PlayerData* PlayerData::getInstance() {
	if(singleton == NULL) {
		singleton = new PlayerData();
	}



	return singleton;
}

void PlayerData::setPlayer(GameObject *player) {
	if(this->player == NULL) {
		points = 0;
	}

	if(this->player != player) {
		hp = player->gameObjectInstance->gameObject->hp;
		mp = player->gameObjectInstance->gameObject->mp;
	}

	this->player = player;

	std::stringstream ss;
	ss.str("");
	ss << "Pontos: " << points;
	pointsText->setText(ss.str());

	ss.str("");
	ss << "Vida: " << hp << "/" << player->gameObjectInstance->gameObject->hp;
	hpText->setText(ss.str());

	ss.str("");
	ss << "Magia: " << mp << "/" << player->gameObjectInstance->gameObject->mp;
	mpText->setText(ss.str());

	if(livesText != NULL) {
		ss.str("");
		ss << "Vidas: " << lives;
		livesText->setText(ss.str());
	}


}

void PlayerData::setCurrentMap(Tilemap *map) {
	this->currentMap = map;
}

Tilemap* PlayerData::getCurrentMap() {
	return currentMap;
}

void PlayerData::addPoints(int points) {
	this->points += points;

	std::stringstream ss;
	ss.str("");
	ss << "Pontos: " << this->points;
	pointsText->setText(ss.str());
}

void PlayerData::addHp(int hp) {
	this->hp += hp;
	if(this->hp > player->gameObjectInstance->gameObject->hp) {
		this->hp = player->gameObjectInstance->gameObject->hp;
	}

	player->hp = this->hp;

	std::stringstream ss;
	ss.str("");
	ss << "Vida: " << this->hp << "/" << player->gameObjectInstance->gameObject->hp;
	hpText->setText(ss.str());
}

void PlayerData::addMp(int mp) {
	this->mp += mp;
	if(this->mp > player->gameObjectInstance->gameObject->mp) {
		this->mp = player->gameObjectInstance->gameObject->mp;
	}

	player->mp = this->mp;

	std::stringstream ss;
	ss.str("");
	ss << "Magia: " << this->mp << "/" << player->gameObjectInstance->gameObject->mp;
	mpText->setText(ss.str());
}

void PlayerData::addDamage(GameObject *damager, int extraDamage) {
	player->addDamage(damager, extraDamage);

	this->hp = player->hp;

	std::stringstream ss;
	ss.str("");
	ss << "Magia: " << this->mp << "/" << player->gameObjectInstance->gameObject->mp;
	mpText->setText(ss.str());
}

void PlayerData::resetLives() {
	GameData *gameData = GameData::getInstance();
	this->lives = gameData->totalLives;


	if(livesText != NULL) {
		std::stringstream ss;
		ss.str("");
		ss << "Vidas: " << lives;
		livesText->setText(ss.str());
	}
}

void PlayerData::resetHp() {
	GameData *gameData = GameData::getInstance();

	if(player != NULL) {
		this->hp = player->gameObjectInstance->gameObject->hp;
	}

}

void PlayerData::addLives(int lives) {
	this->lives += lives;


	if(livesText != NULL) {
		std::stringstream ss;
		ss.str("");
		ss << "Vidas: " << lives;
		livesText->setText(ss.str());
	}
}

bool PlayerData::isDead() {
	return (hp <= 0);
}

int PlayerData::getHp() {
	return hp;
}

int PlayerData::getMp() {
	return mp;
}

int PlayerData::getPoints() {
	return points;
}

int PlayerData::getLives() {
	return lives;
}

void PlayerData::setTeleportPosition(Vector2 teleportPosition) {
	if(this->teleportPosition != NULL) {
		delete this->teleportPosition;
		this->teleportPosition = NULL;
	}

	this->teleportPosition = new Vector2(teleportPosition);
}

Vector2* PlayerData::getTeleportPosition() {
	return teleportPosition;
}

void PlayerData::freeTeleportPosition() {
	delete teleportPosition;
	teleportPosition = NULL;
}

void PlayerData::renderHud(Screen *screen) {
	pointsText->render(screen);
	hpText->render(screen);
	mpText->render(screen);

	if(livesText != NULL) {
		livesText->render(screen);
	}
}

GameObject* PlayerData::getPlayer() {
	return player;
}
