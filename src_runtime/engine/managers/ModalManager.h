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
#ifndef MODALMANAGER_H_
#define MODALMANAGER_H_

#include <stack>

#include "Modal.h"
#include "Screen.h"

class Modal;
class Screen;

/**
 * @brief Pilha de estados modais. Serve para colocar na tela
 * estados que bloqueiam o estado atual até que sejam terminados,
 * como diálogos e escolhas de texto.
 *
 * @see Modal
 *
 */
class ModalStack {
public:
        /**
         * @brief Construtor.
         *
         */
        ModalStack();
        /**
         * @brief
         *
         */
        virtual ~ModalStack();


        /**
         * @brief Se existem elementos na pilha.
         *
         */
        bool modalActivated();
        /**
         * @brief Coloca um Modal na pilha.
         *
         * @param modal
         */
        void pushModal(Modal *modal);
        /**
         * @brief Retira um modal da pilha.
         *
         */
        void popModal();

        /**
         * @brief Atualiza o estado do modal no topo da pilha e retorna
         * a resposta do método update dele.
         *
         * @param dt
         */
        int update(int dt);
        /**
         * @brief Renderiza o estado do modal no topo da pilha.
         *
         * @param screen
         */
        void render(Screen *screen);

        std::stack<Modal*> modalStack; /**< A pilha de modais. */

};

#endif /* MODALMANAGER_H_ */
