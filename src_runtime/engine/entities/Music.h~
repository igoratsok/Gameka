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

#ifndef MUSIC_H_
#define MUSIC_H_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <string>

#include "GameData.h"

class GameData;
/**
 * @brief Classe para tocar música e som.
 *
 */
class Music
{
public:
    /**
     * @brief Construtor.
     *
     */
    Music();

    /**
     * @brief Construtor.
     *
     * @param fileName caminho para a música a ser tocada.
     * @param tipo Tipo: \n
                    - 0 (SOM): efeito sonoro;
                    - 1 (MUSICA) música;
     */
    Music(std::string *fileName, int tipo);

    /**
     * @brief
     *
     */
    virtual ~Music();

    /**
     * @brief Toca a música especificada no construtor.
     *
     * @param times número de vezes.
     */
    void play(int times);

    /**
     * @brief Pausa e resume a música.
     *
     */
    void pauseResume();

    /**
     * @brief Pára a música.
     *
     */
    void stop();

    std::string *fileName; /**< */
    Mix_Chunk *som; /**< */
    Mix_Music *music; /**< */
    bool tocando; /**< */
    int tipo; /**<  */

    static const int SOM = 0; /**< */
    static const int MUSICA = 1; /**<  */
};

#endif /* MUSIC_H_ */
