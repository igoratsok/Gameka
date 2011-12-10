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


#ifndef BACKGROUNDLAYERDATA_H_
#define BACKGROUNDLAYERDATA_H_

#include <string>

/**
 * @brief Entidade para guardar camadas de um fundo.
 *
 */
class BackgroundLayerData {
public:
        /**
         * @brief Construtor da classe.
         *
         */
	BackgroundLayerData();
	virtual ~BackgroundLayerData();

        std::string fileName; /**< Nome do arquivo da imagem do fundo. */

        int displacementX, displacementY; /**< Deslocamento nos eixos do fundo. */
        bool repeatsHorizontally; /**< Se repete horizontalmente. */
        bool repeatsVertically; /**< Se repete verticalmente. */
        int behavior; /**< Comportamento. \n
                            - 0: Estática;
                            - 1: Flutuando;
                            - 2: Flutuando com personagem;
                            - 3: Flutuando com velocidade*/
        int vx, vy; /**< Velocidade no eixo x e y. */
};

#endif /* BACKGROUNDLAYERDATA_H_ */
