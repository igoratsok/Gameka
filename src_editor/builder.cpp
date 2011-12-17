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


#include "builder.h"

Builder::Builder()
{
}

MainController* Builder::build()
{
    MainController* mainController;
    EventsEditorController *eventsEditorController;
    MapEditorController *mapEditorController;
    OptionsController *optionsController;
    WizardController *wizardController;
    UpdateManagerController *updateManagerController;

    mainController = new MainController();
    eventsEditorController = new EventsEditorController();
    mapEditorController = new MapEditorController();
    optionsController = new OptionsController();
    wizardController = new WizardController();
    updateManagerController = new UpdateManagerController();

    mainController->setEventsEditorController(eventsEditorController);
    mainController->setMapEditorController(mapEditorController);
    mainController->setOptionsController(optionsController);
    mainController->setWizardController(wizardController);
    mainController->setUpdateManagerController(updateManagerController);


    eventsEditorController->setMainController(mainController);
    mapEditorController->setMainController(mainController);
    optionsController->setMainController(mainController);
    wizardController->setMainController(mainController);

    optionsController->setEventsEditorController(eventsEditorController);

    return mainController;
}
