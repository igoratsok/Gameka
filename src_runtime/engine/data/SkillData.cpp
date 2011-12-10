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

#include "SkillData.h"

std::vector<DialogueData*> *SkillData::skillMessages = NULL;

SkillData::SkillData() {
	// TODO Auto-generated constructor stub

}

SkillData::~SkillData() {
	// TODO Auto-generated destructor stub
}

void SkillData::playSound() {
	SoundManager *soundManager = SoundManager::getInstance();

	if(!sound.empty()) {
		std::string diretorioSound = std::string("sfx/");
		diretorioSound.append(sound.c_str());
		soundManager->playSound(diretorioSound, 1);
	}
}

std::vector<DialogueData*> *SkillData::getSkillMessages() {
	if(skillMessages == NULL) {
		skillMessages = new std::vector<DialogueData*>();

		skillMessages->push_back(DialogueData::createSingleTextDialogue(
				"Você ganhou a habilidade de atirar objeto! Use a tecla x."));

		skillMessages->push_back(DialogueData::createSingleTextDialogue(
				"Você ganhou a habilidade de atirar objeto com o mouse! Clique na posição desejada."));

		skillMessages->push_back(DialogueData::createSingleTextDialogue(
				"Você ganhou a habilidade de usar espada! Use a tecla x."));

		skillMessages->push_back(DialogueData::createSingleTextDialogue(
				"Você ganhou a habilidade de pular! Use a tecla z."));

		skillMessages->push_back(DialogueData::createSingleTextDialogue(
				"Você ganhou a habilidade de pulo duplo! Enquanto estiver pulando, pressione a tecla z."));

		skillMessages->push_back(DialogueData::createSingleTextDialogue(
				"Você ganhou a habilidade de correr! Use a tecla a."));

		skillMessages->push_back(DialogueData::createSingleTextDialogue(
				"Você ganhou a habilidade de quicar paredes! Pule em uma parede e aperte z."));

		skillMessages->push_back(DialogueData::createSingleTextDialogue(
				"Você ganhou a habilidade de planar! Enquanto estiver no ar, aperte a tecla c."));

		skillMessages->push_back(DialogueData::createSingleTextDialogue(
				"Você ganhou a habilidade de voar! Use a tecla s."));

	}

	return skillMessages;
}
