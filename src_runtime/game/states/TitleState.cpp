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

#include "TitleState.h"

TitleState::TitleState(StateManager *stateManager) {
	this->stateManager = stateManager;

}

TitleState::~TitleState() {
	// TODO Auto-generated destructor stub
}

void TitleState::load() {
	GameData *gameData = GameData::getInstance();

	if(!gameData->titleScreenFile.empty()) {
		std::string *diretorio = new std::string("images/");
		diretorio->append(gameData->titleScreenFile);

		fundo = new Sprite(diretorio, new Vector2(0, 0));
	} else {
		fundo = NULL;
	}

	dialogBar = new DialogBar(DialogBar::POS_DOWN);


	modalManager = new ModalStack();

	ChoiceText *choiceText;

	choiceText = new ChoiceText(ChoiceText::POS_DOWN);
	choiceText->addChoice("Novo jogo");
	//choiceText->addChoice("Carregar jogo");
	//choiceText->addChoice("Opções");
	//choiceText->addChoice("Créditos");
	choiceText->addChoice("Sair do jogo");

	modalManager->pushModal(choiceText);

	/* carrega musica de fundo (se houver) */
	if(!gameData->titleScreenMusic.empty()) {
		std::string *diretorioMusic = new std::string("musics/");
		diretorioMusic->append(gameData->titleScreenMusic.c_str());
		musicaFundo = new Music(diretorioMusic, Music::MUSICA);
		std::cout << diretorioMusic->c_str() << std::endl;
		delete diretorioMusic;

		musicaFundo->play(1);
	} else {
		musicaFundo = NULL;
	}



}

void TitleState::unload() {
	if(musicaFundo != NULL) {
		musicaFundo->stop();
	}

	delete fundo;
	delete dialogBar;

}

int TitleState::update(int dt) {
	if(modalManager->modalActivated()) {
		switch(modalManager->update(dt)) {
		case 0:
			stateManager->setMapState(gameData->idFirstMap);
			break;
		case 1:
			exit(0);
			break;
		}
	} else {

	}

	return 0;
}

void TitleState::render(Screen *screen) {
	if(fundo != NULL) {
		fundo->render(screen);
	}
	dialogBar->render(screen);
	modalManager->render(screen);
}
