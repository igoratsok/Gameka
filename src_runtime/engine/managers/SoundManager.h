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
#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include <vector>

#include "Music.h"
class Music;

using namespace std;


/**
 * @brief Gerenciador de som. Permite tocar músicas e sons, e alocar/desalocar
 * memória para eles.
 *
 */
class SoundManager {
public:
        /**
         * @brief
         *
         */
        virtual ~SoundManager();

        /**
         * @brief Toca uma música.
         *
         * @param path Caminho do arquivo da música;
         * @param nloops Número de repetições da música.
         */
        void playMusic(std::string path, int nloops);
        /**
         * @brief Pausa ou resume uma música.
         *
         */
        void pauseResumeMusic();
        /**
         * @brief Pára uma música.
         *
         */
        void stopMusic();
        /**
         * @brief Se tem uma música tocando.
         *
         */
        bool isMusicPlaying();

        /**
         * @brief Toca um som.
         *
         * @param path Caminho do arquivo do som.
         * @param nloops Número de repetições do som.
         */
        void playSound(std::string path, int nloops);
        /**
         * @brief Pausa ou resume os sons.
         *
         */
        void pauseResumeSounds();
        /**
         * @brief Pára os sons.
         *
         */
        void stopSound();
        /**
         * @brief Se tem um som tocando.
         *
         */
        bool isSoundPlaying();



        /**
         * @brief Obtém instância singleton
         *
         */
        static SoundManager* getInstance();

        Music *currentMusic; /**< Música atual sendo tocada. */
        std::list<Music*> *sounds; /**< Sons sendo tocados. */

private:
        /**
         * @brief
         *
         */
        SoundManager();

        static SoundManager *singleton; /**< TODO */



};

#endif /* SOUNDMANAGER_H_ */
