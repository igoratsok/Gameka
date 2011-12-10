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
#ifndef TIMERMANAGER_H_
#define TIMERMANAGER_H_

#include <stdio.h>

/**
 * @brief Gerenciador de tempo. Armazena, atualiza e permite operações com timers
 * globais de de mapa.
 * Para funcionamento adequado, o timer de mapa há de ser reinciado sempre
 * que ocorrer troca de mapa, e o método update deve ser chamado uma ver por quadro.
 *
 */
class TimerManager {
public:
        /**
         * @brief
         *
         */
        virtual ~TimerManager();

        /**
         * @brief Atualiza os timers.
         *
         * @param dt O tempo do frame.
         */
        void update(int dt);
        /**
         * @brief Reinicia o timer global.
         *
         * @param value Valor a ser reiniciado.
         */
        void resetGlobalTimer(int value);
        /**
         * @brief Reinicia o timer de mapa.
         *
         * @param value Valor a ser reiniciado.
         */
        void resetMapTimer(int value);
        /**
         * @brief Obtém timer global.
         *
         */
        unsigned long long int getGlobalTimer();
        /**
         * @brief Obtém timer do mapa.
         *
         */
        unsigned long long int getMapTimer();

        /**
         * @brief Obtém instância singleton.
         *
         */
        static TimerManager *getInstance();
private:
        /**
         * @brief
         *
         */
        TimerManager();

        static TimerManager *singleton; /**< Instância singleton. */

        unsigned long long int globalTimer; /**< Timer global. */
        unsigned long long int mapTimer; /**< Timer do mapa. */

        unsigned long long int **eventTimers; /**< Eventos de timers (ainda não usado). */

};

#endif /* GLOBALTIMER_H_ */
