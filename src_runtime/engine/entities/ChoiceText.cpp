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

#include "ChoiceText.h"

ChoiceText::ChoiceText(int posicao) {
	GameData *gameData = GameData::getInstance();
	barWidth = gameData->resWidth;

	if(posicao == POS_DOWN) {
		pos.x = 10;
		pos.y = gameData->resHeight - 150 + 40;
	} else {
		pos.x = 10;
		pos.y = 40;
	}

	currentChoice = 0;
	mouseCurrentChoice = 0;
	selectorAlpha = 0;
	selectorAlphaDirection = 10;

	inputManager = InputManager::getInstance();


}

ChoiceText::~ChoiceText() {

}

void ChoiceText::addChoice(std::string string) {
	choices.push_back(string);
	texts.push_back(new Text(string, pos));
}

int ChoiceText::update(int dt) {
	selectorAlpha += selectorAlphaDirection;
	if(selectorAlpha > 255) {
		selectorAlpha = 255;
		selectorAlphaDirection = -10;
	} else if(selectorAlpha < 0) {
		selectorAlpha = 0;
		selectorAlphaDirection = 10;
	}

	if(inputManager->isKeyPressed(SDLK_DOWN)) {
		mouseCurrentChoice++;

		if(mouseCurrentChoice > (int)texts.size() - 1) {
			mouseCurrentChoice = 0;
		}

		currentChoice = mouseCurrentChoice;


	} else if(inputManager->isKeyPressed(SDLK_UP)) {
		mouseCurrentChoice--;

		if(mouseCurrentChoice < 0) {
			mouseCurrentChoice = texts.size() - 1;
		}

		currentChoice = mouseCurrentChoice;
	}

	int i = 0;
	for(std::vector<Text*>::iterator it = texts.begin(); it != texts.end(); ++it) {
		Text *currentText = *it;
		if(inputManager->isMouseInsideRectNoScrolling(Rect(currentText->rect.x, currentText->rect.y,
				currentText->rect.w, currentText->rect.h))) {
			mouseCurrentChoice = i;
			if(inputManager->isMousePressed(0)) {
				return mouseCurrentChoice;
			}
		}

		i++;

	}

	if(inputManager->isKeyPressed(SDLK_RETURN) || inputManager->isKeyPressed(SDLK_SPACE)) {
		return currentChoice;
	}


	return -1;
}

void ChoiceText::render(Screen *screen) {
	GameData *gameData = GameData::getInstance();
	float posy;
	posy = pos.y;

	int start, end;
	if(texts.size() > 2) {
		start = currentChoice - 1;
		end = currentChoice + 1;

		if(start < 0) {
			start++;
			end++;
		}

		if(end > (int)texts.size() - 1) {
			start--;
			end--;
		}
	} else if(texts.size() == 2) {
		start = 0;
		end = 1;
	} else {
		start = 0;
		end = 0;
	}



	for(std::vector<Text*>::iterator it = texts.begin() + start; it != texts.begin() + end + 1; ++it) {
		Text* text = *it;
		text->pos.y = posy;
		text->centerTextX();

		text->render(screen);

		posy += 20;
	}

	Text *currentText = texts.at(mouseCurrentChoice);

	Rect rectSelection = Rect(currentText->pos.x - 3,
			currentText->pos.y - 3,
			currentText->rect.w + 6,
			currentText->rect.h + 6);

	Sprite::drawRoundRectNoScrolling(rectSelection, 255, 255, 255, selectorAlpha, 100, screen);

	if(texts.size() > 2) {
		Vector2 posSetaRef;
		posSetaRef.x = gameData->resWidth/2;

		if(currentChoice > 1) {
			posSetaRef.y = pos.y - 3;
			Sprite::drawTriangleNoScrolling(Vector2(posSetaRef.x - 2, posSetaRef.y),
					Vector2(posSetaRef.x + 2, posSetaRef.y), Vector2(posSetaRef.x, posSetaRef.y - 2),
					255, 255, 255, selectorAlpha, screen);
		}

		if(currentChoice < (int)texts.size() - 2) {
			posSetaRef.y = pos.y + 63;
			Sprite::drawTriangleNoScrolling(Vector2(posSetaRef.x - 2, posSetaRef.y),
					Vector2(posSetaRef.x + 2, posSetaRef.y), Vector2(posSetaRef.x, posSetaRef.y + 2),
					255, 255, 255, selectorAlpha, screen);
		}
	}




}


