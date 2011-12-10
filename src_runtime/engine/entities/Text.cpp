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

#include "Text.h"

Text::Text(std::string text, Vector2 pos, bool utf8) {
	scrollManager = ScrollManager::getInstance();
	scroll = false;
	this->utf8 = utf8;
	loadText(text, "runtime-common/iconsolata.ttf", pos, 255, 255, 255);
}

Text::~Text() {
	// TODO Auto-generated destructor stub
}

Text::Text(std::string text, std::string fontFile, Vector2 pos) {
	scrollManager = ScrollManager::getInstance();
	scroll = false;
	loadText(text, fontFile, pos, 255, 255, 255);
}

Text::Text(std::string text, Vector2 pos, int r, int b, int g) {
	scrollManager = ScrollManager::getInstance();
	scroll = false;
	loadText(text, "runtime-common/iconsolata.ttf", pos, r, g, b);
}

Text::Text(std::string text, std::string fontFile, Vector2 pos, int r, int g, int b) {
	scrollManager = ScrollManager::getInstance();
	scroll = false;
	loadText(text, fontFile, pos, r, g, b);
}

void Text::loadText(std::string text, std::string fontFile, Vector2 pos, int r, int g, int b) {
	GameData *gameData = GameData::getInstance();

	if(gameData->arg1 == NULL) {
		font = TTF_OpenFont(fontFile.c_str(), 16);
	} else {
		font = TTF_OpenFont(std::string(gameData->arg1->c_str()).append(fontFile.c_str()).c_str(), 16);
	}

	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	color.r = r;
	color.g = g;
	color.b = b;


	shadowColor.r = 0;
	shadowColor.g = 0;
	shadowColor.b = 0;

	this->text = text;
	this->pos = pos;

	if(this->text.empty()) {
		this->text = std::string(" ");
	}

	if(utf8) {
		textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
		textSurfaceShadow = TTF_RenderUTF8_Blended(font, text.c_str(), shadowColor);
	} else {
		textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
		textSurfaceShadow = TTF_RenderText_Blended(font, text.c_str(), shadowColor);
	}



	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = textSurface->w;
	rect.h = textSurface->h;
}

void Text::setText(std::string text) {
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(textSurfaceShadow);

	textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
	textSurfaceShadow = TTF_RenderUTF8_Blended(font, text.c_str(), shadowColor);

	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = textSurface->w;
	rect.h = textSurface->h;
}

void Text::centerTextX() {
	GameData *gameData = GameData::getInstance();

	pos.x = gameData->resWidth/2 - rect.w/2;

}

void Text::render(Screen *screen) {
	Vector2 *scrolledPosition;

	if(scroll) {
		scrolledPosition = scrollManager->scrollVector(&pos);
	} else {
		scrolledPosition = new Vector2(pos);
	}

	for(int i = -1; i < 2; i++) {
		for(int j = -1; j < 2; j++) {
			rect.x = scrolledPosition->x + i;
			rect.y = scrolledPosition->y + j;
			SDL_BlitSurface(textSurfaceShadow, NULL, screen->getTopScreen(), &rect);
		}
	}

	rect.x = scrolledPosition->x;
	rect.y = scrolledPosition->y;


	SDL_BlitSurface(textSurface, NULL, screen->getTopScreen(), &rect);

	delete scrolledPosition;
}

void Text::setScroll(bool value) {
	this->scroll = value;
}
