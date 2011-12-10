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


#ifndef UNDOCHANGETILECOMMAND_H
#define UNDOCHANGETILECOMMAND_H

#include <QUndoCommand>

#include "mapeditorcontroller.h"
#include "tileset.h"

class MapEditorController;
class TileSet;

/**
 * @brief Marcador de comando de desfazer/refazer mudanças no mapa. Utiliza a framework
 * de Undo da Qt.
 *
 */
class UndoChangeTileCommandChange {
public:
    int i, j; /**< TODO */
    int beforeTileI, beforeTileJ, afterTileI, afterTileJ; /**< TODO */
    int layer; /**< TODO */
    TileSet *beforeTileset, *afterTileset; /**< TODO */
};

/**
 * @brief Comando de desfazer/refazer mudanças no mapa. Utiliza a framework
 * de Undo da Qt.
 *
 */
class UndoChangeTileCommand : public QUndoCommand
{
public:
    /**
     * @brief Construtor.
     *
     * @param mapEditorController a controladora do editor de mapas.
     * @param parent
     */
    explicit UndoChangeTileCommand(MapEditorController* mapEditorController,
                                   QUndoCommand *parent = 0);

    /**
     * @brief Comando de desfazer.
     *
     */
    void undo();
    /**
     * @brief Comando de refazer.
     *
     */
    void redo();

    std::list<UndoChangeTileCommandChange> changes; /**< Lista de mudanças */

private:
    MapEditorController *mapEditorController; /**<  */


};

#endif // UNDOCHANGETILECOMMAND_H
