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



#include "eventswidget.h"
#include "ui_eventswidget.h"

EventsWidget::EventsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventsWidget)
{
    ui->setupUi(this);



}

EventsWidget::~EventsWidget()
{
    delete ui;
}

void EventsWidget::setEventsEditorController(EventsEditorController *eventsEditorController) {
    this->eventsEditorController = eventsEditorController;

    populaTudo();
}

void EventsWidget::populaTudo() {
    populaComboTarget();
    populaListaProcedures();
    populaVariableList();
    populaEventTree();
}


void EventsWidget::selectObject(int idObject) {
    for(int i = 0; i < ui->comboBoxTarget->count(); i++) {
        GameObject *gameObject = (GameObject*) ui->comboBoxTarget->itemData(i, Qt::UserRole).value<void*>();

        if(gameObject != NULL && gameObject->id == idObject) {
            ui->comboBoxTarget->setCurrentIndex(i);
            break;
        }
    }
}

void EventsWidget::populaComboTarget() {
    GameData *gameData = GameData::getInstance();

    ui->comboBoxTarget->clear();

    ui->comboBoxTarget->addItem(QIcon(":/icones_interface/data/icons/Gear.png"), QString("Global"), QVariant::fromValue((void*) NULL));

    for(std::vector<GameObject*>::iterator it = eventsEditorController->getObjectList()->begin(); it != eventsEditorController->getObjectList()->end(); ++it) {
        GameObject *gameObject = *it;

        ui->comboBoxTarget->addItem(QIcon(QPixmap::fromImage(gameObject->getIconImage())), QString(gameObject->name.c_str()),
                                    QVariant::fromValue((void*) gameObject));

    }
}

void EventsWidget::populaListaProcedures() {
    GameData *gameData = GameData::getInstance();

    ui->listWidgetProcedures->clear();

    std::vector<ProcedureData*> *procedureList = NULL;

    if(!ui->comboBoxTarget->itemData(ui->comboBoxTarget->currentIndex(), Qt::UserRole).isNull()) {
        GameObject *gameObject = (GameObject*)
            ui->comboBoxTarget->itemData(ui->comboBoxTarget->currentIndex(), Qt::UserRole).value<void*>();

        if(gameObject == NULL) {
            QListWidgetItem *itemProcedureAlways = new QListWidgetItem(QString(gameData->procedureGlobalAlways->name.c_str()));
            itemProcedureAlways->setData(Qt::UserRole, QVariant::fromValue((void*) gameData->procedureGlobalAlways));

            QListWidgetItem *itemProcedureStart = new QListWidgetItem(QString(gameData->procedureGlobalStart->name.c_str()));
            itemProcedureStart->setData(Qt::UserRole, QVariant::fromValue((void*) gameData->procedureGlobalStart));

            QListWidgetItem *itemProcedureEnd = new QListWidgetItem(QString(gameData->procedureGlobalEnd->name.c_str()));
            itemProcedureEnd->setData(Qt::UserRole, QVariant::fromValue((void*) gameData->procedureGlobalEnd));

            ui->listWidgetProcedures->addItem(itemProcedureAlways);
            ui->listWidgetProcedures->addItem(itemProcedureStart);
            ui->listWidgetProcedures->addItem(itemProcedureEnd);

            procedureList = gameData->procedureList;

        } else {
            QListWidgetItem *itemProcedureAlways = new QListWidgetItem(QString(gameObject->procedureGlobalAlways->name.c_str()));
            itemProcedureAlways->setData(Qt::UserRole, QVariant::fromValue((void*) gameObject->procedureGlobalAlways));

            QListWidgetItem *itemProcedureStart = new QListWidgetItem(QString(gameObject->procedureGlobalStart->name.c_str()));
            itemProcedureStart->setData(Qt::UserRole, QVariant::fromValue((void*) gameObject->procedureGlobalStart));

            QListWidgetItem *itemProcedureEnd = new QListWidgetItem(QString(gameObject->procedureGlobalEnd->name.c_str()));
            itemProcedureEnd->setData(Qt::UserRole, QVariant::fromValue((void*) gameObject->procedureGlobalEnd));



            ui->listWidgetProcedures->addItem(itemProcedureAlways);
            ui->listWidgetProcedures->addItem(itemProcedureStart);
            ui->listWidgetProcedures->addItem(itemProcedureEnd);

            procedureList = gameObject->procedureList;
        }
    }

    if(procedureList != NULL) {
        for(std::vector<ProcedureData*>::iterator it = procedureList->begin(); it != procedureList->end(); ++it) {
            ProcedureData* procedureData = *it;

            QListWidgetItem *procedureItem = new QListWidgetItem(QString(procedureData->name.c_str()));
            procedureItem->setData(Qt::UserRole, QVariant::fromValue((void*) procedureData));

            ui->listWidgetProcedures->addItem(procedureItem);


        }
    }

    ui->listWidgetProcedures->setCurrentRow(0);
}

void EventsWidget::populaEventTree() {
    GameData *gameData = GameData::getInstance();



    ui->treeWidgetEvents->clear();

    if(ui->listWidgetProcedures->currentItem() != NULL) {
        ProcedureData *currentProcedure =
                (ProcedureData*) ui->listWidgetProcedures->currentItem()->data(Qt::UserRole).value<void*>();

        ui->lineEditProcedureName->setText(QString(currentProcedure->name.c_str()));
        ui->lineEditProcedureName->setEnabled(currentProcedure->nameEditable);

        if(currentProcedure != NULL) {
            populaSubEventTree(NULL, &currentProcedure->events);


        }
    }




}

void EventsWidget::populaVariableList() {
    ui->listWidgetVariables->clear();

    if(!ui->comboBoxTarget->itemData(ui->comboBoxTarget->currentIndex(), Qt::UserRole).isNull()) {
        GameObject *gameObject = (GameObject*)
            ui->comboBoxTarget->itemData(ui->comboBoxTarget->currentIndex(), Qt::UserRole).value<void*>();

        std::vector<VariableData*> *variableList;

        if(gameObject != NULL) {
            variableList = gameObject->variableList;

        } else {
            GameData *gameData = GameData::getInstance();

            variableList = eventsEditorController->getGlobalVariableDataList();
        }

        for(std::vector<VariableData*>::iterator it = variableList->begin(); it != variableList->end(); ++it) {
            VariableData *variableData = *it;

            QListWidgetItem *itemVariable = new QListWidgetItem(QString(variableData->name.c_str()));
            itemVariable->setData(Qt::UserRole, QVariant::fromValue((void*) variableData));

            ui->listWidgetVariables->addItem(itemVariable);
        }

    }
}

void EventsWidget::activateNewEventItemMenu(QTreeWidgetItem *item) {
    EventData *eventData = (EventData*) item->data(0, Qt::UserRole).value<void*>();

    QMenu menu;
    QAction *newCondition = menu.addAction(QString::fromUtf8("Nova condição"));
    QAction *newAction = menu.addAction(QString::fromUtf8("Nova ação"));
    QAction *newDialogue = menu.addAction(QString::fromUtf8("Novo diálogo"));



    QAction *selectedAction = menu.exec(QCursor::pos());

    if(selectedAction == newCondition) {
        GameObject *gameObject = (GameObject*)
            ui->comboBoxTarget->itemData(ui->comboBoxTarget->currentIndex(), Qt::UserRole).value<void*>();

        eventsEditorController->openNewConditionWindow(eventData, gameObject);
        QTreeWidgetItem *currentItem = ui->treeWidgetEvents->currentItem();


        if(!eventData->newEvent) {
            setTreeWidgetItemData(currentItem, eventData);

            if(eventData->type == EventData::TYPE_CONDITION) {
                EventData *childEventData = new EventData();
                EventData *nextEventData = new EventData();

                QTreeWidgetItem *child = new QTreeWidgetItem();
                QTreeWidgetItem *next = new QTreeWidgetItem();

                setTreeWidgetItemData(child, childEventData);
                setTreeWidgetItemData(next, nextEventData);

                currentItem->addChild(child);


                eventData->addChild(childEventData);

                if(currentItem->parent() != NULL) {
                    currentItem->parent()->addChild(next);
                    eventData->parent->addChild(nextEventData);




                } else {
                    ui->treeWidgetEvents->addTopLevelItem(next);


                    ProcedureData *currentProcedure =
                            (ProcedureData*) ui->listWidgetProcedures->currentItem()->data(Qt::UserRole).value<void*>();

                    currentProcedure->events.push_back(nextEventData);
                }







            }



        }
    } else if(selectedAction == newAction) {
        GameObject *gameObject = (GameObject*)
            ui->comboBoxTarget->itemData(ui->comboBoxTarget->currentIndex(), Qt::UserRole).value<void*>();

        eventsEditorController->openNewActionWindow(eventData, gameObject);
        QTreeWidgetItem *currentItem = ui->treeWidgetEvents->currentItem();

        if(!eventData->newEvent) {
            setTreeWidgetItemData(currentItem, eventData);

            if(eventData->type == EventData::TYPE_ACTION) {
                EventData *nextEventData = new EventData();
                QTreeWidgetItem *next = new QTreeWidgetItem();

                setTreeWidgetItemData(next, nextEventData);

                if(currentItem->parent() != NULL) {
                    currentItem->parent()->addChild(next);
                    eventData->parent->addChild(nextEventData);


                } else {
                    ui->treeWidgetEvents->addTopLevelItem(next);

                    ProcedureData *currentProcedure =
                            (ProcedureData*) ui->listWidgetProcedures->currentItem()->data(Qt::UserRole).value<void*>();

                    currentProcedure->events.push_back(nextEventData);
                }

            }
        }
    } else if(selectedAction == newDialogue) {
        eventsEditorController->openNewDialogueDialog(eventData);

        QTreeWidgetItem *currentItem = ui->treeWidgetEvents->currentItem();

        if(eventData->dialogueData != NULL) {
            eventData->type = EventData::TYPE_DIALOGUE;
            eventData->newEvent = false;

            setTreeWidgetItemData(currentItem, eventData);



            EventData *nextEventData = new EventData();
            QTreeWidgetItem *next = new QTreeWidgetItem();

            setTreeWidgetItemData(next, nextEventData);

            if(currentItem->parent() != NULL) {
                currentItem->parent()->addChild(next);
                eventData->parent->addChild(nextEventData);


            } else {
                ui->treeWidgetEvents->addTopLevelItem(next);

                ProcedureData *currentProcedure =
                        (ProcedureData*) ui->listWidgetProcedures->currentItem()->data(Qt::UserRole).value<void*>();

                currentProcedure->events.push_back(nextEventData);
            }
        }
    }



}

void EventsWidget::activateCreatedEventItemMenu(QTreeWidgetItem *item) {
    EventData *eventData = (EventData*) item->data(0, Qt::UserRole).value<void*>();

    QMenu menu;

    QAction *editAction = menu.addAction(QString::fromUtf8("Editar"));
    QAction *removeAction = menu.addAction(QString::fromUtf8("Remover"));

    QAction *selectedAction = menu.exec(QCursor::pos());

    if(selectedAction == removeAction) {
        delete item;

        if(eventData->parent == NULL) {
            if(ui->listWidgetProcedures->currentItem() != NULL) {
                ProcedureData *currentProcedure =
                        (ProcedureData*) ui->listWidgetProcedures->currentItem()->data(Qt::UserRole).value<void*>();

                currentProcedure->events.remove(eventData);
            }
        } else {
            eventData->parent->subEvents.remove(eventData);
        }
    } else if(selectedAction == editAction) {
        GameObject *gameObject = (GameObject*)
            ui->comboBoxTarget->itemData(ui->comboBoxTarget->currentIndex(), Qt::UserRole).value<void*>();

        if(eventData->type == EventData::TYPE_ACTION || eventData->type == EventData::TYPE_CONDITION) {
            eventsEditorController->openEditEventWindow(eventData, gameObject);
        } else {
            eventsEditorController->openNewDialogueDialog(eventData);
        }

        setTreeWidgetItemData(item, eventData);
    }

}

void EventsWidget::setTreeWidgetItemData(QTreeWidgetItem *widgetItem, EventData *eventData) {
    GameObject *gameObject = (GameObject*)
        ui->comboBoxTarget->itemData(ui->comboBoxTarget->currentIndex(), Qt::UserRole).value<void*>();

    if(eventData->type == EventData::TYPE_ACTION || eventData->type == EventData::TYPE_CONDITION) {
        QString eventString = eventData->getEventString(eventsEditorController, gameObject);
        widgetItem->setData(0, Qt::UserRole, QVariant::fromValue((void*) eventData));
        widgetItem->setText(0, eventString);
        widgetItem->setToolTip(0, eventString);
        widgetItem->setIcon(0, eventData->getEventIcon());
        widgetItem->setIcon(1, eventData->getObject01Icon());
        widgetItem->setIcon(2, eventData->getObject02Icon());
    } else {
        QString eventString = eventData->getEventString(eventsEditorController, gameObject);
        widgetItem->setData(0, Qt::UserRole, QVariant::fromValue((void*) eventData));
        widgetItem->setText(0, eventString);
        widgetItem->setToolTip(0, eventString);
        widgetItem->setIcon(0, eventData->getEventIcon());
    }


}

void EventsWidget::populaSubEventTree(QTreeWidgetItem *parent, std::list<EventData *> *events) {
    ui->treeWidgetEvents->header()->resizeSection(0, 350);
    ui->treeWidgetEvents->header()->resizeSection(1, 32);
    ui->treeWidgetEvents->header()->resizeSection(2, 32);

    for(std::list<EventData*>::iterator it = events->begin(); it != events->end(); ++it) {
        EventData *eventData = *it;

        QTreeWidgetItem *widgetItem = new QTreeWidgetItem();
        setTreeWidgetItemData(widgetItem, eventData);






        if(parent != NULL) {
            parent->addChild(widgetItem);
        } else {
            ui->treeWidgetEvents->addTopLevelItem(widgetItem);
        }

        if(!eventData->subEvents.empty()) {
            populaSubEventTree(widgetItem, &eventData->subEvents);
        }

    }
}

void EventsWidget::on_comboBoxTarget_currentIndexChanged(int index)
{
    populaListaProcedures();
    populaVariableList();
}


void EventsWidget::on_listWidgetProcedures_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    populaEventTree();
}

void EventsWidget::on_treeWidgetEvents_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
    EventData *eventData = (EventData*) item->data(0, Qt::UserRole).value<void*>();

    if(eventData->newEvent) {
        activateNewEventItemMenu(item);
    } else {
        activateCreatedEventItemMenu(item);
    }

}

void EventsWidget::on_pushButtonNewProc_pressed()
{
    GameObject *gameObject = (GameObject*)
        ui->comboBoxTarget->itemData(ui->comboBoxTarget->currentIndex(), Qt::UserRole).value<void*>();

    ProcedureData* newProcedure;

    if(gameObject == NULL) {
        newProcedure = eventsEditorController->addProcedure();


    } else {
        newProcedure = eventsEditorController->addProcedure(gameObject);
    }

    QListWidgetItem *newProcedureItem = new QListWidgetItem(QString(newProcedure->name.c_str()));
    newProcedureItem->setData(Qt::UserRole, QVariant::fromValue((void*) newProcedure));
    ui->listWidgetProcedures->addItem(newProcedureItem);

}

void EventsWidget::on_lineEditProcedureName_textChanged(QString text)
{
    if(!text.isEmpty()) {
        if(ui->listWidgetProcedures->currentItem() != NULL) {
            ProcedureData *currentProcedure =
                    (ProcedureData*) ui->listWidgetProcedures->currentItem()->data(Qt::UserRole).value<void*>();

            if(currentProcedure != NULL){
                ui->listWidgetProcedures->currentItem()->setText(text);
                currentProcedure->name = text.toStdString();
            }
        }

    }
}

void EventsWidget::on_pushButtonNewVar_pressed()
{
    NewVariableDialog *newVariableDialog = new NewVariableDialog(NULL, this);
    newVariableDialog->setWindowTitle(QString::fromUtf8("Nova variável"));

    VariableData *variableData = newVariableDialog->exec();

    if(variableData != NULL) {
        GameObject *gameObject = (GameObject*)
            ui->comboBoxTarget->itemData(ui->comboBoxTarget->currentIndex(), Qt::UserRole).value<void*>();



        if(gameObject != NULL) {
            gameObject->addVariable(variableData);
        } else {
            GameData *gameData = GameData::getInstance();
            gameData->addVariable(variableData);
        }

        QListWidgetItem *itemVariable = new QListWidgetItem(QString(variableData->name.c_str()));
        itemVariable->setData(Qt::UserRole, QVariant::fromValue((void*) variableData));

        ui->listWidgetVariables->addItem(itemVariable);



    }
}




void EventsWidget::on_pushButtonEditVar_pressed()
{
    QListWidgetItem *currentItem = ui->listWidgetVariables->currentItem();

    if(currentItem != NULL) {
        VariableData *variableData = (VariableData*) currentItem->data(Qt::UserRole).value<void*>();

        NewVariableDialog *newVariableDialog = new NewVariableDialog(variableData, this);
        newVariableDialog->setWindowTitle(QString::fromUtf8("Editar variável"));

        variableData = newVariableDialog->exec();

        currentItem->setText(QString(variableData->name.c_str()));
    }


}
