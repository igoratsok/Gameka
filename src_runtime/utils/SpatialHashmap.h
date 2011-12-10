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

#ifndef SPATIALHASHMAP_H_
#define SPATIALHASHMAP_H_

#include <list>

#include "GameObject.h"

class GameObject;

/**
 * @brief Estrutura de Spatial Hashmap, para organizar os objetos e otimizar
 * número de testes de colisões.
 *
 */
class SpatialHashmap {
public:
        /**
         * @brief Construtor.
         *
         * @param scenewidth Largura da cena em píxeis.
         * @param sceneheight Altura da cena em píxeis.
         * @param cellsize
         */
        SpatialHashmap(int scenewidth, int sceneheight, int cellsize);
        /**
         * @brief
         *
         */
        virtual ~SpatialHashmap();

        /**
         * @brief Limpa os buckets.
         *
         */
        void clearBuckets();
        /**
         * @brief Registr um objeto.
         *
         * @param gameObject
         */
        void registerObject(GameObject *gameObject);
        /**
         * @brief Obtém ids das células próximas ao objeto.
         *
         * @param gameObject Objeto
         */
        std::list<int>* getIdsForObj(GameObject *gameObject);
        /**
         * @brief Adiciona um bucket.
         *
         * @param vector2
         * @param width
         * @param bucketAddTo
         */
        void addBucket(Vector2 vector2, float width, std::list<int>* bucketAddTo);
        /**
         * @brief Obtém os objetos próximos.
         *
         * @param gameObject Objeto
         */
        std::list<GameObject*> *getNearby(GameObject *gameObject);



        int cols, rows; /**<  */
        int size; /**<  */
        int scenewidth, sceneheight, cellsize; /**<  */
        std::vector<std::list<GameObject*> > *buckets; /**< Lista de buckets. */
};

#endif /* SPATIALHASHMAP_H_ */
