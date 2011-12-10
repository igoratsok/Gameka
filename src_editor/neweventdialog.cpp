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



#include "neweventdialog.h"
#include "ui_neweventdialog.h"

NewEventDialog::NewEventDialog(EventsEditorController *eventsEditorController, EventData *eventData, GameObject *gameObject, int type, int conditionType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEventDialog),
    eventsEditorController(eventsEditorController),
    eventData(eventData),
    gameObject(gameObject),
    type(type),
    conditionType(conditionType)
{
    ui->setupUi(this);

    if(type == EventData::TYPE_ACTION) {
        ui->labelCondAction->setText(QString::fromUtf8("Ação:"));
    }

    populaListaObjects();
    freeAttributeData();
}

NewEventDialog::~NewEventDialog()
{
    delete ui;


}

void NewEventDialog::preencheCampos() {
    if(!eventData->newEvent) {
        // TODO: rotina de preencher campos

    }
}

void NewEventDialog::freeAttributeData() {
    for(int i = 0; i < ui->comboBoxAttrib->count(); i++) {
        EventAttributeData *eventAttributeData = (EventAttributeData*) ui->comboBoxAttrib->itemData(i, Qt::UserRole).value<void*>();

        if(eventAttributeData->id == EventComboDataProvider::ATT_VARIABLES) {
            delete eventAttributeData;
        }
    }
}

void NewEventDialog::populaListaObjects() {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::vector<GameObject*>* objectList;

    objectList = eventsEditorController->getObjectList();

    ui->listWidgetObject1->clear();
    ui->listWidgetObject2->clear();


    QListWidgetItem *specialNewItem;

    specialNewItem = new QListWidgetItem();
    specialNewItem->setText(QString::fromUtf8("Especiais: "));
    specialNewItem->setData(Qt::UserRole, QVariant::fromValue((void*) NULL));

    ui->listWidgetObject1->addItem(specialNewItem);

//    specialNewItem = new QListWidgetItem();
//    specialNewItem->setText(QString::fromUtf8("Especiais:"));
//    specialNewItem->setData(Qt::UserRole, QVariant::fromValue((void*) NULL));

//    ui->listWidgetObject2->addItem(specialNewItem);

    std::list<GameObject *> specialGameObjects = eventsEditorController->getSpecialGameObjects(type);

    foreach(GameObject *specialGameObject, specialGameObjects) {
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString(specialGameObject->name.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) new std::pair<int, GameObject*>(std::make_pair(-1, specialGameObject))));
        newItem->setIcon(QIcon(QPixmap::fromImage(specialGameObject->getIconImage())));

        ui->listWidgetObject1->addItem(newItem);

//        newItem = new QListWidgetItem();
//        newItem->setText(QString(specialGameObject->name.c_str()));
//        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) new std::pair<int, GameObject*>(std::make_pair(-1, specialGameObject))));
//        newItem->setIcon(QIcon(QPixmap::fromImage(specialGameObject->getIconImage())));

//        ui->listWidgetObject2->addItem(newItem);
    }



    specialNewItem = new QListWidgetItem();
    specialNewItem->setText(QString::fromUtf8("Objetos de classe:"));
    specialNewItem->setData(Qt::UserRole, QVariant::fromValue((void*) NULL));

    ui->listWidgetObject1->addItem(specialNewItem);

    specialNewItem = new QListWidgetItem();
    specialNewItem->setText(QString::fromUtf8("Objetos de classe:"));
    specialNewItem->setData(Qt::UserRole, QVariant::fromValue((void*) NULL));

    ui->listWidgetObject2->addItem(specialNewItem);



    for(std::vector<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        GameObject *gameObject;
        gameObject = *it;


        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString(gameObject->name.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) new std::pair<int, GameObject*>(std::make_pair(-1, gameObject))));
        newItem->setIcon(QIcon(QPixmap::fromImage(gameObject->getIconImage())));

        ui->listWidgetObject1->addItem(newItem);

        newItem = new QListWidgetItem();
        newItem->setText(QString(gameObject->name.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) new std::pair<int, GameObject*>(std::make_pair(-1, gameObject))));
        newItem->setIcon(QIcon(QPixmap::fromImage(gameObject->getIconImage())));

        ui->listWidgetObject2->addItem(newItem);

    }


    std::vector<GameObject*> contextObjects = eventsEditorController->getContextObjects(eventData);


    if(!contextObjects.empty() || gameObject != NULL) {
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString::fromUtf8("Objetos de instância:"));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) NULL));

        ui->listWidgetObject1->addItem(newItem);

        newItem = new QListWidgetItem();
        newItem->setText(QString::fromUtf8("Objetos de instância:"));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) NULL));

        ui->listWidgetObject2->addItem(newItem);
    }

    if(gameObject != NULL) {
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString("Este objeto"));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) new std::pair<int, GameObject*>(std::make_pair(0, gameObject))));
        newItem->setIcon(QIcon(QPixmap::fromImage(gameObject->getIconImage())));

        ui->listWidgetObject1->addItem(newItem);

        newItem = new QListWidgetItem();
        newItem->setText(QString("Este objeto"));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) new std::pair<int, GameObject*>(std::make_pair(0, gameObject))));
        newItem->setIcon(QIcon(QPixmap::fromImage(gameObject->getIconImage())));

        ui->listWidgetObject2->addItem(newItem);


    }

    std::stringstream ss;

    int i = 1;
    int contextObjectsSize = contextObjects.size();
    foreach(GameObject* contextObject, contextObjects) {
        int ajusteIndice;
        if(i%2) {
            ajusteIndice = 0;
        } else {
            ajusteIndice = 2;
        }

        if(contextObject != NULL) {
            ss.str("");
            ss << QString::fromUtf8("Inst. de Contexto ").toStdString() <<  contextObjectsSize - i + ajusteIndice << " (" << i << " )";

            QListWidgetItem *newItem = new QListWidgetItem();
            newItem->setText(QString(ss.str().c_str()));
            newItem->setData(Qt::UserRole, QVariant::fromValue((void*) new std::pair<int, GameObject*>(std::make_pair(i, contextObject))));
            newItem->setIcon(QIcon(QPixmap::fromImage(contextObject->getIconImage())));

            ui->listWidgetObject1->addItem(newItem);


            ss.str("");
            ss << QString::fromUtf8("Inst. de Contexto ").toStdString() << contextObjectsSize - i + ajusteIndice << " (" << i << " )";

            newItem = new QListWidgetItem();
            newItem->setText(QString(ss.str().c_str()));
            newItem->setData(Qt::UserRole, QVariant::fromValue((void*) new std::pair<int, GameObject*>(std::make_pair(i, contextObject))));
            newItem->setIcon(QIcon(QPixmap::fromImage(contextObject->getIconImage())));

            ui->listWidgetObject2->addItem(newItem);


        }

        i++;



    }


    ui->listWidgetObject1->setCurrentRow(1);
    ui->listWidgetObject2->setCurrentRow(1);
}

void NewEventDialog::populaComboAtributos() {
    freeAttributeData();
    ui->comboBoxAttrib->clear();


    if(ui->listWidgetObject1->currentItem() != NULL) {
        std::pair<int, GameObject*> *objectPair = (std::pair<int, GameObject*> *) ui->listWidgetObject1->currentItem()->data(Qt::UserRole).value<void*>();
        GameObject *gameObject = objectPair->second;

        if(gameObject != NULL) {
            std::list<EventAttributeData*> listAttributes = eventsEditorController->getComboAttributes(gameObject, type);

            if(!listAttributes.empty()) {
                for(std::list<EventAttributeData*>::iterator it = listAttributes.begin(); it != listAttributes.end(); ++it) {
                    EventAttributeData* eventAttributeData = *it;

                    ui->comboBoxAttrib->addItem(QString(eventAttributeData->name.c_str()), QVariant::fromValue((void*) eventAttributeData));
                }

                ui->groupBoxRel->setVisible(true);
            } else {
                 ui->groupBoxRel->setVisible(false);
            }


        } else {
            ui->groupBoxRel->setVisible(false);
        }

    } else {
        ui->groupBoxRel->setVisible(false);
    }


}

void NewEventDialog::populaComboConditions() {
    ui->comboBoxCondit->clear();

    EventAttributeData *eventAttributeData = (EventAttributeData*)
            ui->comboBoxAttrib->itemData(ui->comboBoxAttrib->currentIndex(), Qt::UserRole).value<void*>();

    if(eventAttributeData != NULL) {

        for(std::list<int>::iterator it = eventAttributeData->conditions->begin(); it != eventAttributeData->conditions->end(); ++it) {
            int index = *it;

            ui->comboBoxCondit->addItem(eventsEditorController->getComboConditionString(index), QVariant::fromValue(index));
        }
    }
}

void NewEventDialog::populaComboActions() {
    ui->comboBoxCondit->clear();

    EventAttributeData *eventAttributeData = (EventAttributeData*)
            ui->comboBoxAttrib->itemData(ui->comboBoxAttrib->currentIndex(), Qt::UserRole).value<void*>();

    if(eventAttributeData != NULL) {

        for(std::list<int>::iterator it = eventAttributeData->actions->begin(); it != eventAttributeData->actions->end(); ++it) {
            int index = *it;

            ui->comboBoxCondit->addItem(eventsEditorController->getComboActionString(index), QVariant::fromValue(index));
        }
    }
}

void NewEventDialog::habilitaGroupValues() {

    EventAttributeData *eventAttributeData = (EventAttributeData*)
            ui->comboBoxAttrib->itemData(ui->comboBoxAttrib->currentIndex(), Qt::UserRole).value<void*>();

    if(eventAttributeData != NULL) {
        ui->groupBoxVal->setVisible(true);

        ui->checkBoxVariable->setVisible(eventAttributeData->showVariableValueCombo);
        ui->comboBoxVariable->setVisible(eventAttributeData->showVariableValueCombo);

        ui->checkBoxNumber->setVisible(eventAttributeData->showVariableValueCombo);
        ui->spinBoxNumber->setVisible(eventAttributeData->showVariableValueCombo);

        ui->checkBoxFieldObject02->setVisible(eventAttributeData->showObjectFieldCombo);
        ui->comboBoxFieldObject2->setVisible(eventAttributeData->showObjectFieldCombo);

        ui->groupBoxObj2->setVisible(eventAttributeData->showObject02);

        if(eventAttributeData->showObject02) {
            ui->groupBoxObj2->setVisible(true);
            populaComboAtributosObject02();
        }

        populaComboVariables();



        switch(eventAttributeData->specialComboType) {
        case 0:
            ui->checkBoxSpecial->setVisible(false);
            ui->comboBoxSpecial->setVisible(false);
            break;

        default:
            ui->checkBoxSpecial->setVisible(true);
            ui->comboBoxSpecial->setVisible(true);
            populaComboSpecial(eventAttributeData->specialComboType);
            break;
        }

        ui->dialDirection->setVisible(eventAttributeData->showDirectionInput);

        int currentOperation = ui->comboBoxCondit->itemData(ui->comboBoxCondit->currentIndex(), Qt::UserRole).value<int>();

        if(type == EventData::TYPE_ACTION) {
            if(eventsEditorController->isNoValueAction(currentOperation)) {
                ui->groupBoxVal->setVisible(false);
            } else {
                ui->groupBoxVal->setVisible(eventAttributeData->showValueGroup());
            }


        } else {
            if(eventsEditorController->isNoValueCondition(currentOperation)) {
                ui->groupBoxVal->setVisible(false);
            } else {
                ui->groupBoxVal->setVisible(eventAttributeData->showValueGroup());
            }
        }
    }




}

void NewEventDialog::populaComboVariables() {

    ui->comboBoxVariable->clear();

    foreach(VariableData *variableData, *eventsEditorController->getGlobalVariableDataList()) {
        std::stringstream ss;
        ss << "(Global)" << variableData->name;
        ui->comboBoxVariable->addItem(QString(ss.str().c_str()), QVariant(variableData->id));
    }

    if(gameObject != NULL) {
        foreach(VariableData *variableData, *gameObject->variableList) {
            ui->comboBoxVariable->addItem(QString(variableData->name.c_str()), QVariant(-variableData->id));
        }


    }
}

void NewEventDialog::populaComboSpecial(int type) {
    ui->comboBoxSpecial->clear();





    std::list<SpecialComboValueData*> specialList = eventsEditorController->getSpecialComboValueList(type, this->gameObject);

    foreach(SpecialComboValueData *special, specialList) {
        ui->comboBoxSpecial->addItem(QString(special->string.c_str()), QVariant::fromValue((void*) special));
    }
}

void NewEventDialog::populaComboAtributosObject02() {
    ui->comboBoxFieldObject2->clear();


    if(ui->listWidgetObject2->currentItem() != NULL) {
        std::pair<int, GameObject*> *objectPair = (std::pair<int, GameObject*> *) ui->listWidgetObject2->currentItem()->data(Qt::UserRole).value<void*>();
        GameObject *gameObject = objectPair->second;

        if(gameObject != NULL) {
            std::list<EventAttributeData*> listAttributes = eventsEditorController->getComboAttributes(gameObject, type);

            if(!listAttributes.empty()) {
                for(std::list<EventAttributeData*>::iterator it = listAttributes.begin(); it != listAttributes.end(); ++it) {
                    EventAttributeData* eventAttributeData = *it;

                    ui->comboBoxFieldObject2->addItem(QString(eventAttributeData->name.c_str()), QVariant::fromValue((void*) eventAttributeData));

                }

            }


        }

    }
}




void NewEventDialog::on_listWidgetObject2_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{


    if(current->data(Qt::UserRole).value<void*>() == NULL) {
        ui->listWidgetObject2->setCurrentItem(previous);
        ui->listWidgetObject2->setItemSelected(previous, true);
        ui->listWidgetObject2->setItemSelected(current, false);
    } else {
        populaComboAtributosObject02();
        populaComboVariables();
    }
}


void NewEventDialog::on_listWidgetObject1_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(current->data(Qt::UserRole).value<void*>() == NULL) {
        ui->listWidgetObject1->setCurrentItem(previous);
        ui->listWidgetObject1->setItemSelected(previous, true);
        ui->listWidgetObject1->setItemSelected(current, false);
    } else {
        populaComboAtributos();
        if(type == EventData::TYPE_CONDITION) {
            populaComboConditions();
        } else {
            populaComboActions();
        }
    }




}

void NewEventDialog::on_comboBoxAttrib_currentIndexChanged(int index)
{
    if(type == EventData::TYPE_CONDITION) {
        populaComboConditions();
    } else {
        populaComboActions();
    }
}


void NewEventDialog::on_comboBoxCondit_currentIndexChanged(int index)
{
    habilitaGroupValues();
}



void NewEventDialog::on_checkBoxNumber_toggled(bool checked)
{
    if(checked) {
        ui->checkBoxVariable->setChecked(false);
        ui->checkBoxFieldObject02->setChecked(false);
    }

}

void NewEventDialog::on_checkBoxVariable_toggled(bool checked)
{
    if(checked) {
        ui->checkBoxNumber->setChecked(false);
        ui->checkBoxFieldObject02->setChecked(false);
    }
}

void NewEventDialog::on_checkBoxFieldObject02_toggled(bool checked)
{
    if(checked) {
        ui->checkBoxNumber->setChecked(false);
        ui->checkBoxVariable->setChecked(false);
    }
}



void NewEventDialog::on_buttonBox_2_accepted()
{
    EventAttributeData *attributeData = ((EventAttributeData*) ui->comboBoxAttrib->itemData(ui->comboBoxAttrib->currentIndex(),
                                                        Qt::UserRole).value<void*>());

    int currentOperation = ui->comboBoxCondit->itemData(ui->comboBoxCondit->currentIndex(), Qt::UserRole).value<int>();
    bool isNoAction = false;

    if(type == EventData::TYPE_ACTION) {
        isNoAction = eventsEditorController->isNoValueAction(currentOperation);
    } else {
        isNoAction = eventsEditorController->isNoValueCondition(currentOperation);
    }


    if(!isNoAction && !attributeData->isObjectType() && !attributeData->isNothingType() && !ui->checkBoxFieldObject02->isChecked() &&
            !ui->checkBoxNumber->isChecked() &&
            !ui->checkBoxSpecial->isChecked() &&
            !ui->checkBoxVariable->isChecked()) {
        MessageBoxes::showMessageBox(QString::fromUtf8("Ao menos uma das caixas de valores deve ser marcada."));
        return;
    }

    eventData->newEvent = false;
    eventData->type = type;
    eventData->conditionType = conditionType;

    std::pair<int, GameObject*> *objectPair01 = (std::pair<int, GameObject*> *) ui->listWidgetObject1->currentItem()->data(Qt::UserRole).value<void*>();
    GameObject *gameObject01 = objectPair01->second;
    eventData->idObject01 = gameObject01->id;
    eventData->instanceTypeObject01 = objectPair01->first;
    eventData->opcode = ui->comboBoxCondit->itemData(ui->comboBoxCondit->currentIndex(), Qt::UserRole).value<int>();
    eventData->idAssociatedVariable = ((EventAttributeData*) ui->comboBoxAttrib->itemData(ui->comboBoxAttrib->currentIndex(),
                                                                                          Qt::UserRole).value<void*>())->id;

    std::pair<int, GameObject*> *objectPair02 = (std::pair<int, GameObject*> *) ui->listWidgetObject2->currentItem()->data(Qt::UserRole).value<void*>();
    GameObject *gameObject02 = objectPair02->second;




    // determina inicialmente o valueType como TYPE_OBJECT2, que é o caso de não
    // entrar em nenhum dos ifs a seguir
    eventData->valueType = EventData::VALUE_TYPE_OBJECT2;

//    if(attributeData->isObjectType() || ui->checkBoxFieldObject02->isChecked()) {
//        eventData->idObject02 = gameObject02->id;
//        eventData->instanceTypeObject02 = objectPair02->first;
//    } else {
//        eventData->idObject02 = -1;
//    }


    if(attributeData->isObjectType()) {
        eventData->idObject02 = gameObject02->id;
        eventData->instanceTypeObject02 = objectPair02->first;
    } else if(attributeData->showObject02 && ui->checkBoxFieldObject02->isChecked()) {
        eventData->idObject02 = gameObject02->id;
        eventData->instanceTypeObject02 = objectPair02->first;
    } else {
        eventData->idObject02 = -1;
    }



    if(ui->checkBoxNumber->isChecked()) {
         eventData->value01 = ui->spinBoxNumber->value();
         eventData->valueType = EventData::VALUE_TYPE_NUMBER;

    }

    if(ui->checkBoxVariable->isChecked()) {
        eventData->value01 = ui->comboBoxVariable->itemData(ui->comboBoxVariable->currentIndex(), Qt::UserRole).toInt();
        eventData->valueType = EventData::VALUE_TYPE_VARIABLE;
    }

    if(ui->checkBoxFieldObject02->isChecked()) {
        eventData->value01 = ((EventAttributeData*)ui->comboBoxFieldObject2->itemData(ui->comboBoxFieldObject2->currentIndex(), Qt::UserRole).value<void*>())->id;
        eventData->valueType = EventData::VALUE_TYPE_OBJECT_ATTRIBUTE;
    }

    if(ui->checkBoxSpecial->isChecked()) {


        SpecialComboValueData *specialComboValuedata = (SpecialComboValueData*)
                ui->comboBoxSpecial->itemData(ui->comboBoxSpecial->currentIndex(), Qt::UserRole).value<void*>();


        EventAttributeData *eventAttributeData = (EventAttributeData*)
                ui->comboBoxAttrib->itemData(ui->comboBoxAttrib->currentIndex(), Qt::UserRole).value<void*>();


        switch(eventAttributeData->specialComboType) {
        case EventAttributeData::COMBO_TYPE_KEY:
            eventData->value01 = specialComboValuedata->code;
            break;
        case EventAttributeData::COMBO_TYPE_MAP:
            eventData->value01 = specialComboValuedata->code;
            break;
        case EventAttributeData::COMBO_TYPE_MOUSE:
            eventData->value01 = specialComboValuedata->code;
            break;
        case EventAttributeData::COMBO_TYPE_MUSIC:
            eventData->stringValue = specialComboValuedata->string;
            break;
        case EventAttributeData::COMBO_TYPE_SOUND:
            eventData->stringValue = specialComboValuedata->string;
            break;
        case EventAttributeData::COMBO_TYPE_PROCEDURE:
            eventData->value01 = specialComboValuedata->code;
            break;
        }

        eventData->valueType = EventData::VALUE_TYPE_SPECIAL;
    }




    accept();

}

void NewEventDialog::on_buttonBox_2_rejected()
{
    reject();
}

void NewEventDialog::on_checkBoxNegate_toggled(bool checked)
{
    eventData->negate = checked;
}
