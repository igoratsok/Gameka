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
#ifndef DIALOGUEDATA_H_
#define DIALOGUEDATA_H_

#include <list>

#include "DialogueItemData.h"

class DialogueItemData;

/**
 * @brief Entidade para guardar dados de um diálogo. Contém uma lista
 * de itens de diálogo, representados pela classe DialogueItemData.
 *
 * @see DialogueItemData
 */
class DialogueData {
public:
        /**
         * @brief Construtor.
         *
         */
	DialogueData();
	virtual ~DialogueData();

    std::list<DialogueItemData*> dialogueItems; /**< A lista de itens de diálogo. */


    /**
     * @brief Cria um DialogueData com um texto.
     *
     * @param text O texto do DialogueData.
     */
    static DialogueData* createSingleTextDialogue(std::string text);
};

#endif /* DIALOGUEDATA_H_ */
