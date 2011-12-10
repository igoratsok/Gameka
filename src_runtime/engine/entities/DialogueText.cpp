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

#include "DialogueText.h"

DialogueText::DialogueText(DialogueData *dialogueData, int posicao, int dt, bool utf8) :
	dialogueData(dialogueData), posicao(posicao) {
	GameData *gameData = GameData::getInstance();

	currentIt = dialogueData->dialogueItems.begin();
	text1 = NULL;
	text2 = NULL;
	text3 = NULL;
	textImage = NULL;
	this->utf8 = utf8;

	if(posicao == POS_DOWN) {
		pos.x = 10;
		pos.y = gameData->resHeight - 150 + 40;
	} else {
		pos.x = 10;
		pos.y = 40;
	}

	processCurrentIt(dt);

	inputManager = InputManager::getInstance();

	dialogBar = new DialogBar(posicao);

	interpreter = new Interpreter();
}

DialogueText::~DialogueText() {
	if(text1 != NULL) {
		delete text1;
		text1 = NULL;
	}

	if(text2 != NULL) {
		delete text2;
		text2 = NULL;
	}

	if(text3 != NULL) {
		delete text3;
		text3 = NULL;
	}

	delete textImage;
	delete interpreter;
}


void DialogueText::processCurrentIt(int dt) {
	if(currentIt != dialogueData->dialogueItems.end()) {
		DialogueItemData *dialogueItemData = *currentIt;

		if(dialogueItemData->type == DialogueItemData::TYPE_MESSAGE) {
			createTexts(dialogueItemData->message);

			if(!dialogueItemData->associatedImage.empty()) {
				if(textImage != NULL) {
					delete textImage;
				}

				textImage = new Sprite(&std::string("images/").append(dialogueItemData->associatedImage), new Vector2(0,0));
				textImage->setScrollable(false);
				if(dialogueItemData->associatedImageAtCenter) {
					textImage->moveToScreenCenter();
				}
			} else {
				textImage = NULL;
			}

		} else {
			GameData *gameData = GameData::getInstance();

			if(dialogueItemData->procedureId > 0) {
				ProcedureData *procedureData = gameData->getProcedureById(dialogueItemData->procedureId);
				interpreter->executeProcedure(procedureData, dt);
			}

			currentIt++;
		}
	}
}

int DialogueText::update(int dt) {
	if(currentIt == dialogueData->dialogueItems.end()) {
		return 1;
	}

	if(inputManager->isKeyPressed(SDLK_z) || inputManager->isKeyPressed(SDLK_RETURN) || inputManager->isKeyPressed(SDLK_SPACE)) {
		currentIt++;

		processCurrentIt(dt);
	}


	return -1;
}

void DialogueText::render(Screen *screen) {

	if(textImage != NULL) {
		textImage->render(screen);
	}

	dialogBar->render(screen);

	if(text1 != NULL) {
		text1->render(screen);
	}

	if(text2 != NULL) {
		text2->render(screen);
	}

	if(text3 != NULL) {
		text3->render(screen);
	}



}

void DialogueText::createTexts(std::string string) {
	int nextIndex = N_CHAR_COLUMN;

	if(text1 != NULL) {
		delete text1;
		text1 = NULL;
	}

	if(text2 != NULL) {
		delete text2;
		text2 = NULL;
	}

	if(text3 != NULL) {
		delete text3;
		text3 = NULL;
	}

	for(int i = 0; i < string.size(); i++) {
		if(string.at(i) == '\n') {
			string.at(i) = ' ';
		}
	}


	int nextIndexCut;

	if(nextIndex >= (int) string.size()) {
		text1 = new Text(string, pos, utf8);
		std::cout << string << std::endl;
		return;
	} else {
		nextIndexCut = nextIndex;
		while(nextIndexCut > 0 && string.at(nextIndexCut) != ' ' && string.at(nextIndexCut) != '\n') {
			nextIndexCut--;
		}

		if(nextIndexCut != 0) {
			nextIndex = nextIndexCut;
		}

		text1 = new Text(string.substr(0, nextIndex), pos, utf8);


	}

	int nextIndexAnt = nextIndex;

	nextIndex = nextIndex +  N_CHAR_COLUMN;

	if(nextIndex >= (int) string.size()) {
		text2 = new Text(string.substr(nextIndexAnt, string.size()), Vector2(pos.x, pos.y + 20), utf8);
		return;
	} else {
		nextIndexCut = nextIndex;
		nextIndexCut = nextIndex;
		while(nextIndexCut > nextIndexAnt && string.at(nextIndexCut) != ' ' && string.at(nextIndexCut) != '\n') {
			nextIndexCut--;
		}

		if(nextIndexCut != nextIndexAnt) {
			nextIndex = nextIndexCut;
		}

		text2 = new Text(string.substr(nextIndexAnt + 1, nextIndex - nextIndexAnt - 1), Vector2(pos.x, pos.y + 20), utf8);



	}

	nextIndexAnt = nextIndex;
	nextIndex += N_CHAR_COLUMN;

	if(nextIndex >= (int) string.size()) {
		text3 = new Text(string.substr(nextIndexAnt, string.size()), Vector2(pos.x, pos.y + 40), false);
		std::cout << nextIndexAnt << " " << string.substr(nextIndexAnt, string.size()) << std::endl;
		return;
	} else {
		int nextIndexCut = nextIndex;
		while(nextIndexCut > nextIndexAnt && string.at(nextIndexCut) != ' ' && string.at(nextIndexCut) != '\n') {
			nextIndexCut--;
		}

		if(nextIndexCut != nextIndexAnt) {
			nextIndex = nextIndexCut;
		}

		text3 = new Text(string.substr(nextIndexAnt + 1, nextIndex - nextIndexAnt - 1), Vector2(pos.x, pos.y + 40), utf8);

		nextIndex += N_CHAR_COLUMN;
	}




}

