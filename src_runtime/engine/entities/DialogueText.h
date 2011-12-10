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

#ifndef DIALOGUETEXT_H_
#define DIALOGUETEXT_H_

#include <stdlib.h>

#include "DialogueData.h"
#include "Screen.h"
#include "Vector2.h"
#include "Modal.h"
#include "InputManager.h"
#include "DialogBar.h"

#include "../../game/interpreter/Interpreter.h"

class DialogueData;
class Screen;
class Vector2;
class InputManager;
class DialogBar;
class Interpreter;

/**
 * @brief Contexto modal de diálogos. Mostra uma série de mensagens com imagens associadas ou não;
 * ou realiza chamadas de procedimentos.
 *
 */
class DialogueText : public Modal {
public:
        /**
         * @brief Construtor.
         *
         * @param dialogueData O DialogueData associado.s
         * @param posicao Posição: \n
                            - 0: embaixo;
                            - 1: em cima.
         * @param dt Tempo do frame.
         * @param utf8 Se o texto é UTF8.
         */
        DialogueText(DialogueData *dialogueData, int posicao, int dt = 30, bool utf8 = false);
        /**
         * @brief
         *
         */
        virtual ~DialogueText();

        /**
         * @brief Processa iterator atual.
         *
         * @param dt
         */
        void processCurrentIt(int dt);
        /**
         * @brief Cria os textos.
         *
         * @param string
         *
         * @see Text
         */
        void createTexts(std::string string);

        /**
         * @brief Verifica se um botão foi pressionado para passar para a próxima mensagem.
         *
         * @param dt
         */
        int update(int dt);
        /**
         * @brief Renderiza.
         *
         * @param screen
         */
        void render(Screen *screen);

        DialogueData *dialogueData; /**< O DialogueData. */
        int posicao; /**< Posição: \n
                            - 0: embaixo;
                            - 1: em cima. */

        Vector2 pos; /**<  Posição real. */
        bool utf8; /**< Se é UTF8 */

        std::list<DialogueItemData*>::iterator currentIt; /**< Iterador dos itens. */

        Text *text1;  /**< Primeira linha de texto.  */
        Text *text2;  /**< Segunda linha de texto. */
        Text *text3; /**<  Terceira linha de texto. */

        InputManager *inputManager; /**<  */
        DialogBar *dialogBar; /**< */
        Interpreter *interpreter; /**< */

        Sprite *textImage; /**<  */

        static const int POS_DOWN = 0; /**<  */
        static const int POS_UP = 1; /**< */

        static const int N_CHAR_COLUMN = 75; /**<  */
};

#endif /* DIALOGUETEXT_H_ */
