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



#include "objectsdock.h"
#include "ui_objectsdock.h"

ObjectsDock::ObjectsDock(MapEditorController *mapEditorController, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::ObjectsDock), mapEditorController(mapEditorController)
{
    ui->setupUi(this);
    this->widget()->setVisible(false);

    populaArvoreObjetos();
}

ObjectsDock::~ObjectsDock()
{
    delete ui;
}

void ObjectsDock::initDock() {
    this->widget()->setVisible(true);
}

void ObjectsDock::populaArvoreObjetos() {
    GameData *gameData = GameData::getInstance();

    std::vector<GameObject*> *objectList;

    objectList = mapEditorController->getObjectList();

    QTreeWidgetItem *itemPersonagem, *itemNPC, *itemItem, *itemEstatico;

    itemPersonagem = new QTreeWidgetItem((QTreeWidget*)0);
    itemPersonagem->setText(0, QString(tr("Personagem")));
    itemPersonagem->setData(0, Qt::UserRole, QVariant::fromValue((void*) NULL));

    itemNPC = new QTreeWidgetItem((QTreeWidget*)0);
    itemNPC->setText(0, QString(tr("NPC")));
    itemNPC->setData(0, Qt::UserRole, QVariant::fromValue((void*) NULL));

    itemItem = new QTreeWidgetItem((QTreeWidget*)0);
    itemItem->setText(0, QString(tr("Item")));
    itemItem->setData(0, Qt::UserRole, QVariant::fromValue((void*) NULL));

    itemEstatico = new QTreeWidgetItem((QTreeWidget*)0);
    itemEstatico->setText(0, QString(tr("Estatico")));
    itemEstatico->setData(0, Qt::UserRole, QVariant::fromValue((void*) NULL));

    ui->treeWidget->clear();

    if(objectList->size() > 0) {
        ui->treeWidget->addTopLevelItem(itemPersonagem);
        ui->treeWidget->addTopLevelItem(itemNPC);
        ui->treeWidget->addTopLevelItem(itemItem);
        ui->treeWidget->addTopLevelItem(itemEstatico);

        for(std::vector<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
            GameObject* gameObject = *it;

            QTreeWidgetItem *newItem = new QTreeWidgetItem((QTreeWidget*)0);
            newItem->setText(0, QString(gameObject->name.c_str()));
            newItem->setIcon(0, QIcon(QPixmap::fromImage(gameObject->getIconImage())));
            newItem->setData(0, Qt::UserRole, QVariant::fromValue((void*) gameObject));

            if(gameObject->type == GameObject::ITEM) {
                itemItem->addChild(newItem);
            } else if(gameObject->type == GameObject::NPC || gameObject->type == GameObject::INIMIGO){
                itemNPC->addChild(newItem);
            } else if(gameObject->type == GameObject::STATIC_OBJECT){
                itemEstatico->addChild(newItem);
            } else {
                itemPersonagem->addChild(newItem);
            }

        }

        ui->treeWidget->expandAll();
    }


}

GameObject* ObjectsDock::getCurrentObject() {
    if(ui->treeWidget->currentItem() != NULL) {
        return (GameObject*) ui->treeWidget->currentItem()->data(0, Qt::UserRole).value<void*>();
    } else {
        return NULL;
    }
}

void ObjectsDock::unselectObject() {
    ui->treeWidget->setCurrentItem(ui->treeWidget->topLevelItem(0));
}

void ObjectsDock::on_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    mapEditorController->setEditorMode(MapEditorController::MODE_OBJECT);
    mapEditorController->setCurrentObjectAtCursor();
}

void ObjectsDock::on_treeWidget_customContextMenuRequested(QPoint pos)
{
    if(ui->treeWidget->currentItem() != NULL) {
        QMenu menu;
        QAction *editarPropriedadesAction = menu.addAction(tr("Editar propriedades"));
        GameObject* gameObject = (GameObject*) ui->treeWidget->currentItem()->data(0, Qt::UserRole).value<void*>();


        if(gameObject != NULL) {
            QAction *selectedAction = menu.exec(QCursor::pos());

            if(selectedAction == editarPropriedadesAction) {
                mapEditorController->openConfigsTabWindow(gameObject);
            }
        }


    }

}

void ObjectsDock::on_pushButtonCreateObject_pressed()
{
    mapEditorController->openEasyNewGameObjectDialog();
    populaArvoreObjetos();

}
