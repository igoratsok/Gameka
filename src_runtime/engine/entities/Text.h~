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
#ifndef TEXT_H_
#define TEXT_H_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Vector2.h"
#include "Screen.h"
#include "GameData.h"
#include "ScrollManager.h"

class Vector2;
class Screen;
class GameData;
class ScrollManager;

/**
 * @brief Abstração para mostrar texto na tela.
 *
 */
class Text {
public:
        /**
         * @brief Construtor.
         *
         * @param text O texto a ser mostrado.
         * @param pos Posição do texto.
         * @param utf8 Se o texto é em codificação UTF8.
         */
        Text(std::string text, Vector2 pos, bool utf8 = true);
        /**
         * @brief Construtor.
         *
         * @param text O texto a ser mostrado.
         * @param fontFile O nome do arquivo da fonte do texto.
         * @param pos Posição do texto.
         */
        Text(std::string text, std::string fontFile, Vector2 pos);
        /**
         * @brief Construtor
         *
         * @param text O texto a ser mostrado.
         * @param pos Posição do texto.
         * @param r Intensidade da cor vermelha do texto (0 a 255).
         * @param g Intensidade da cor verde do texto (0 a 255).
         * @param b Intensidade da cor azul do texto (0 a 255).
         */
        Text(std::string text, Vector2 pos, int r, int b, int g);
        /**
         * @brief Construtor
         *
         * @param text O texto a ser mostrado.
         * @param fontFile O nome do arquivo da fonte do texto.
         * @param pos Posição do texto.
         * @param r Intensidade da cor vermelha do texto (0 a 255).
         * @param g Intensidade da cor verde do texto (0 a 255).
         * @param b Intensidade da cor azul do texto (0 a 255).
         */
        Text(std::string text, std::string fontFile, Vector2 pos, int r, int g, int b);
        /**
         * @brief
         *
         */
        virtual ~Text();

        /**
         * @brief Construtor
         *
         * @param text O texto a ser mostrado.
         * @param fontFile O nome do arquivo da fonte do texto.
         * @param pos Posição do texto.
         * @param r Intensidade da cor vermelha do texto (0 a 255).
         * @param g Intensidade da cor verde do texto (0 a 255).
         * @param b Intensidade da cor azul do texto (0 a 255).
         */
        void loadText(std::string text, std::string fontFile, Vector2 pos, int r, int g, int b);

        /**
         * @brief Troca o texto.
         *
         * @param text
         */
        void setText(std::string text);
        /**
         * @brief Determina se anda com a câmera ou não.
         *
         * @param value Valor: \n
                        - true: anda com a câmera;
                        - false: não anda com a câmera.
         */
        void setScroll(bool value);



        TTF_Font *font; /**< Fonte carregada. */
        std::string text; /**< O texto. */
        char *fontFile; /**< Nome do arquivo da fonte. */
        SDL_Surface *textSurface; /**< A Surface do texto. */
        SDL_Surface *textSurfaceShadow; /**< A Surface da sombra do texto. */
        SDL_Color color; /**< A cor do texto. */
        SDL_Color shadowColor; /**< A cor da sombra do texto. */
        SDL_Rect rect; /**< O retângulo da surface do texto. */
        Vector2 pos; /**< A posição do texto. */
        int psize; /**< O tamanho do texto. */
        bool utf8; /**< Se o texto é em codificação UTF8. */




        /**
         * @brief Centraliza texto no eixo X.
         *
         */
        void centerTextX();


        /**
         * @brief Renderiza o texto.
         *
         * @param screen
         */
        void render(Screen *screen);

private:
        ScrollManager *scrollManager; /**<  */
        bool scroll; /**< Se anda com a câmera. */

};

#endif /* TEXT_H_ */
