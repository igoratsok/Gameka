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



#include "undochangetilecommand.h"

UndoChangeTileCommand::UndoChangeTileCommand(MapEditorController* mapEditorController,
                                             QUndoCommand *parent) :
    QUndoCommand(parent),
    mapEditorController(mapEditorController)
{
    setText("Comando..");
}

void UndoChangeTileCommand::redo() {
    foreach(UndoChangeTileCommandChange change, changes) {
        mapEditorController->changeTile(change.i, change.j,
                                        change.afterTileI,
                                        change.afterTileJ,
                                        change.layer,
                                        change.afterTileset);
    }
}

void UndoChangeTileCommand::undo() {
    foreach(UndoChangeTileCommandChange change, changes) {
        mapEditorController->changeTile(change.i, change.j,
                                        change.beforeTileI,
                                        change.beforeTileJ,
                                        change.layer,
                                        change.beforeTileset);
    }
}
