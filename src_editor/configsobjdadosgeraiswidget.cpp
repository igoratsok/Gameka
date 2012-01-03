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



#include "configsobjdadosgeraiswidget.h"
#include "ui_configsobjdadosgeraiswidget.h"

ConfigsObjDadosGeraisWidget::ConfigsObjDadosGeraisWidget(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigsObjDadosGeraisWidget),
    currentListItem(currentListItem)
{
    executandoTroca = false;
    this->optionsController = optionsController;
    this->gameObject = gameObject;
    ui->setupUi(this);

    ativaTrocaCombos = false;

    ui->comboFormaGrafica->setVisible(false);
    ui->labelFormaGrafica->setVisible(false);
    ui->checkBoxObjUnico->setVisible(false);

    ui->editNome->setText(QString(gameObject->name.c_str()));

    ui->comboFormaGrafica->setCurrentIndex(gameObject->formaGrafica);
    ui->checkBoxObjUnico->setChecked(gameObject->isObjetoUnico);
    ui->checkBoxDrag->setChecked(gameObject->isDraggable);

    scene = new QGraphicsScene(this);
    item =
            new QGraphicsPixmapItem(QPixmap::fromImage(gameObject->getIconImage()));

    item->setPos(0, 0);

    scene->addItem(item);

    ui->graphicsViewSprite->setScene(scene);

    ui->comboTipo->setCurrentIndex(gameObject->type);

    ativaTrocaCombos = true;


}

ConfigsObjDadosGeraisWidget::~ConfigsObjDadosGeraisWidget()
{
    delete ui;
}

void ConfigsObjDadosGeraisWidget::on_editNome_textChanged(QString text )
{
    currentListItem->setText(text);
    gameObject->name = text.toStdString();
}

void ConfigsObjDadosGeraisWidget::on_checkBoxObjUnico_toggled(bool checked)
{
    gameObject->isObjetoUnico = checked;
}

void ConfigsObjDadosGeraisWidget::on_comboFormaGrafica_currentIndexChanged(int index)
{
    gameObject->formaGrafica = index;
}

void ConfigsObjDadosGeraisWidget::on_botaoEditarFormaGrafica_clicked()
{
    ConfigsObjAnimationChooserWindow *configsObjAnimationChooserWindow =
            new ConfigsObjAnimationChooserWindow(optionsController,
                                                       gameObject,
                                                       currentListItem,
                                                       this);

    configsObjAnimationChooserWindow->setWindowTitle(tr("Graficos do objeto"));

    configsObjAnimationChooserWindow->exec();

    delete configsObjAnimationChooserWindow;

    currentListItem->setIcon(QIcon(QPixmap::fromImage(gameObject->getIconImage())));

    scene->removeItem(item);

    delete item;

    item =
            new QGraphicsPixmapItem(QPixmap::fromImage(gameObject->getIconImage()));

    item->setPos(0, 0);

    scene->addItem(item);

}

void ConfigsObjDadosGeraisWidget::on_checkBoxDrag_toggled(bool checked)
{
    gameObject->isDraggable = checked;
}

void ConfigsObjDadosGeraisWidget::on_comboTipo_currentIndexChanged(int index)
{
    if(ativaTrocaCombos && MessageBoxes::showConfirmBox(
                QString::fromUtf8(tr("Deseja realmente trocar o tipo do objeto? Todas as informações, exceto forma gráfica, serão apagadas.").toStdString().c_str()).toStdString())) {
        executandoTroca = true;
        optionsController->resetObject(gameObject, index);

    }

}
