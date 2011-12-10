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
#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <SDL/SDL.h>
#include <stdlib.h>

#include "Vector2.h"
#include "Rectangle.h"
#include "ScrollManager.h"

class Vector2;
class Rect;
class ScrollManager;


/**
 * @brief Gerenciador de input, responsável por obter input
 * do teclado e do mouse. É uma classe singleton.
 *
 */
class InputManager {
public:
        /**
         * @brief
         *
         */
        InputManager();
        /**
         * @brief
         *
         */
        virtual ~InputManager();

        /**
         * @brief Se uma tecla está pressionada.
         *
         * @param int índice da tecla (ver em arquivo SDL_keysym.h da SDL)
         */
        bool isKeyDown(int);
        /**
         * @brief Se uma tecla está solta..
         *
         * @param int índice da tecla (ver em arquivo SDL_keysym.h da SDL)
         */
        bool isKeyUp(int);
        /**
         * @brief Se uma tecla foi apertada no exato momento.
         *
         * @param int índice da tecla (ver em arquivo SDL_keysym.h da SDL)
         */
        bool isKeyPressed(int);
        /**
         * @brief Se uma tecla foi solta no exato momento.
         *
         * @param int índice da tecla (ver em arquivo SDL_keysym.h da SDL)
         */
        bool isKeyReleased(int);
        /**
         * @brief Obtém a posição do mouse com relação à tela.
         *
         */
        Vector2 getMousePosition();
        /**
         * @brief Obtém a posição do mouse col relação ao cenário.
         *
         */
        Vector2 getScenarioMousePosition();
        /**
         * @brief Se um botão do mouse está pressionado.
         *
         * @param int número do mouse: \n
                        - 1: botão esquerdo;
                        - 2: botão do meio;
                        - 3: botão direito;
                        - 4: roda do mouse para cima;
                        - 5: roda do mouse para baixo;
         */
        bool isMouseDown(int);
        /**
         * @brief Se um botão do mouse foi pressionado no exato momento.
         *
         * @param int número do mouse: \n
                        - 1: botão esquerdo;
                        - 2: botão do meio;
                        - 3: botão direito;
                        - 4: roda do mouse para cima;
                        - 5: roda do mouse para baixo;
         */
        bool isMousePressed(int);
        /**
         * @brief Se o mouse está dentro de um retângulo.
         *
         * @param rect Retângulo a ser testado.
         */
        bool isMouseInsideRectNoScrolling(Rect rect);
        /**
         * @brief Atualiza os valores dos arrays para consulta. Precisa ser chamado uma
         * vez por quadro.
         *
         * @param dt
         */
        void update(int dt);
        /**
         * @brief Obtém a direção atual do player, com base nas teclas
         * que ele pressionou.
         *
         */
        int getCurrentDirection();

        /**
         * @brief Se clica em um objeto.
         *
         * @param gameObject
         */
        bool clicksIn(GameObject *gameObject);
        /**
         * @brief Se está clicando em um objeto.
         *
         * @param gameObject
         */
        bool isClicking(GameObject *gameObject);
        /**
         * @brief Se o mouse está dentro de um objeto.
         *
         * @param gameObject
         */
        bool isMouseInside(GameObject *gameObject);


        /**
         * @brief Obtém uma instância da InputManager.
         *
         */
        static InputManager *getInstance();

        static InputManager *singletonInstance; /**< Obtém instância singleton da InputManager. */



        Uint8 *keyState; /**< Estado da tecla. */
        Uint8 *keyStateAntPress; /**< Estado da tecla pressionada no momento. */
        Uint8 *keyStateAntRelease; /**< Estado da tecla solta no momento. */
        Uint8 *mouseAntPress; /**< Estado do mouse pressionado no momento. */
private:
        int nkeys; /**< Número de teclas; */
        int currentDirection; /**< Direção atual do player. */
};

#endif /* INPUTMANAGER_H_ */
