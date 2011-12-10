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

#include "DamageDisplay.h"

DamageDisplay::DamageDisplay(int damage, Vector2 position, int type) {
	std::stringstream ss;

	switch(type) {
	case TYPE_DAMAGE:
		ss.str("");
		ss << damage;

		if(damage >= 0) {
			damageText = new Text(ss.str(), position, 0, 255, 0);
		} else {
			damageText = new Text(ss.str(), position, 255, 0, 0);
		}

		damageText->setScroll(true);

		tempo = 0;
		break;
	case TYPE_LEVELUP:
		ss.str("");
		ss << damage;
		ss << " Level Up!!";

		damageText = new Text(ss.str(), position, 0, 0, 255);

		damageText->setScroll(true);

		tempo = 0;
		break;
	}


}

DamageDisplay::~DamageDisplay() {
	delete damageText;
}

int DamageDisplay::update(int dt) {
	damageText->pos.y -= dt/10.0f;

	tempo += dt;

	if(tempo > 400) {
		return -1;
	}

	return 0;
}

void DamageDisplay::render(Screen *screen) {
	damageText->render(screen);
}
