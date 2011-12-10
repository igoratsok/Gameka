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

#include "DialogBar.h"

DialogBar::DialogBar(int posicao) {
	GameData *gameData = GameData::getInstance();
	barWidth = gameData->resWidth;

	if(posicao == POS_DOWN) {
		pos.x = 0;
		pos.y = gameData->resHeight - 150;
	} else {
		pos.x = 0;
		pos.y = 0;
	}

	dialogBarSprite = new Sprite(new std::string("runtime-common/dialog_bar1.png"), new Vector2(0, 0));
	dialogBarSprite->setScrollable(false);


}

DialogBar::~DialogBar() {
	delete dialogBarSprite;
}

void DialogBar::render(Screen *screen) {
	int i = 0;
	dialogBarSprite->pos->y = pos.y;

	for(i = 0; i < barWidth + 25; i += 24) {
		dialogBarSprite->pos->x = i;
		dialogBarSprite->render(screen);

	}
}
