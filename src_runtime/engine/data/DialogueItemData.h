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
#ifndef DIALOGUEITEMDATA_H_
#define DIALOGUEITEMDATA_H_

#include <string>

/**
 * @brief Entidade para guardar um item de diálogo. Pode ser uma mensagem
 * associada a uma imagem, ou uma chamada de procedimento. É agrupada
 * em um objeto DialogueData.
 *
 * @see DialogueData
 * @see ProcedureData
 */
class DialogueItemData {
public:
        /**
         * @brief Construtor.
         *
         */
	DialogueItemData();
	virtual ~DialogueItemData();

        int type; /**< O tipo. \n
                        - 0 (TYPE_MESSAGE): mensagem;
                        - 1 (TYPE_PROCEDURE): chamada de procedimento. */

        std::string message; /**< A mensagem, caso o tipo seja 0. */
        std::string associatedImage; /**< Caminho para a imagem associada a mensagem. */
        bool associatedImageAtCenter; /**< Se a imagem é centralizada. */
        int procedureId; /**< O identificador do procedimento, caso seja do tipo 1. \n
                              - Se o identificador for positivo, ele se refere a um procedimento global. \n
                              - Se o identificador for negativo, o seu valor positivo refere-se a um procedimento do objeto
                              ao que pertence esse DialogueData. */



        static const int TYPE_MESSAGE   = 0; /**< Tipo de mensagem, a ser usado na variável type. */
        static const int TYPE_PROCEDURE = 1; /**< Tipo de procedimento, a ser usado na variável type. */
};

#endif /* DIALOGUEITEMDATA_H_ */
