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


#ifndef ANIMATIONDATA_H
#define ANIMATIONDATA_H

#include <string>
#include <QImage>

#include "gamedata.h"

class GameData;



/**
 * @brief Entidade para guardar todos os dados de uma "Animação"
  * contida na aba de animações.
 *
 */
class AnimationData
{
public:
    /**
     * @brief Construtor da classe.
     *
     */
    AnimationData();

    int id; /**< Número identificador da animação. */
    std::string name; /**< Nome identificador da animação. */
    std::string fileName; /**< Nome do arquivo da animação. */

    int horizontalSpacing; /**< Espaçamento horizontal entre os frames. */
    int verticalSpacing; /**< Espaçamento vertical entre os frames. */
    int order; /**< Ordem do percorrimento dos frames na animação:
                    0 para esquerda-direita primeiro; 1 para cima-baixo primeiro */
    int velocity; /**< Velocidade da animação */
    bool hasLoop; /**< Se a animação tem loop. */
    int frameLoop; /**< Para qual frame ela retorna no loop */

    bool hasColorkey; /**< Se tem colorkey. */
    int colorkey_r, colorkey_g, colorkey_b; /**< Qual o colorkey da animação. */

    bool activated; /**< Se está ativada. */

    int startX, startY, endX, endY; /**< Em que linhas e colunas a animação começa e termina */


    /**
     * @brief Determina o número de frames na horizontal.
     *
     * @param number o número de frames na horizontal.
     */
    void setHorizontalFrameNumber(int number);

    /**
     * @brief Determina o número de frames na vertical.
     *
     * @param number o número de frames na vertical
     */
    void setVerticalFrameNumber(int number);

    /**
     * @brief Obtém o número de frames na horizontal.
     *
     * @return int
     */
    int getHorizontalFrameNumber();


    /**
     * @brief Obtém o número de frames na vertical.
     *
     * @return int
     */
    int getVerticalFrameNumber();

    /**
     * @brief Obtém um ícone estático e representativo desta animação.
     * Este obtém um ícone estático e representativo da animação,
     * pegando o primeiro frame que estiver disponível.
     *
     * @return QImage o ícone representativo da imagem
     */
    QImage getIconImage();

private:
    int horizontalFrameNumber; /**< Número de quadros na horizontal. */
    int verticalFrameNumber; /**< Número de quadros na vertical. */


};

#endif // ANIMATIONDATA_H
