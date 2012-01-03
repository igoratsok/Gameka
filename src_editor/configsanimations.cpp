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


#include "configsanimations.h"
#include "ui_configsanimations.h"

ConfigsAnimations::ConfigsAnimations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigsAnimations)
{
    ui->setupUi(this);

    ui->lineEditName->setEnabled(false);
    ui->groupBoxDadosFrames->setEnabled(false);
    ui->groupBoxVisualizacao->setEnabled(false);
    ui->graphicsViewColorkey->setScene(new QGraphicsScene(this));

    currentAnimationData = NULL;

    animationsGraphicsScene = new AnimationGraphicsScene(ui->graphicsView);

    ativaMudancas = false;
    populaListaAnimation();
    ativaMudancas = true;


}

ConfigsAnimations::~ConfigsAnimations()
{
    delete ui;
}

void ConfigsAnimations::setOptionsController(OptionsController *optionsController) {
    this->optionsController = optionsController;
}

void ConfigsAnimations::selectLastItem() {
    ui->listWidget->setCurrentRow(ui->listWidget->count() -1);
}

void ConfigsAnimations::populaListaAnimation() {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::vector<AnimationData*> *animationDataList;


    animationDataList = optionsController->getAnimationDataList();

    ui->listWidget->clear();

    for(std::vector<AnimationData*>::iterator it = animationDataList->begin(); it != animationDataList->end(); ++it) {
        AnimationData *iterationItem;

        iterationItem = *it;
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString(iterationItem->name.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) iterationItem));
        ui->listWidget->addItem(newItem);

    }
}

void ConfigsAnimations::populaCampos() {
    ui->lineEditName->setText(QString(currentAnimationData->name.c_str()));

    ui->spinBoxFrameLoop->setValue(currentAnimationData->frameLoop);
    ui->spinBoxHorizontalFramesNumber->setValue(currentAnimationData->getHorizontalFrameNumber());
    ui->spinBoxHorizontalSpacing->setValue(currentAnimationData->horizontalSpacing);
    ui->spinBoxVerticalFrameNumber->setValue(currentAnimationData->getVerticalFrameNumber());
    ui->spinBoxVerticalSpacing->setValue(currentAnimationData->verticalSpacing);

    ui->horizontalSliderVelocity->setValue(currentAnimationData->velocity);

    ui->checkBox->setChecked(currentAnimationData->hasLoop);

    ui->comboBoxOrder->setCurrentIndex(currentAnimationData->order);


    ui->spinBoxColunaInicial->setMaximum(currentAnimationData->getHorizontalFrameNumber());
    ui->spinBoxColunaFinal->setMaximum(currentAnimationData->getHorizontalFrameNumber());
    ui->spinBoxLinhaInicial->setMaximum(currentAnimationData->getVerticalFrameNumber());
    ui->spinBoxLinhaFinal->setMaximum(currentAnimationData->getVerticalFrameNumber());


    ui->spinBoxColunaInicial->setValue(currentAnimationData->startX);
    ui->spinBoxLinhaInicial->setValue(currentAnimationData->startY);
    ui->spinBoxColunaFinal->setValue(currentAnimationData->endX);
    ui->spinBoxLinhaFinal->setValue(currentAnimationData->endY);



    if(currentAnimationData->hasColorkey) {
        ui->graphicsViewColorkey->setVisible(true);
        ui->graphicsViewColorkey->setBackgroundBrush(QBrush(QColor(currentAnimationData->colorkey_r,
                                                                   currentAnimationData->colorkey_g,
                                                                   currentAnimationData->colorkey_b)));
    } else {
        ui->graphicsViewColorkey->setVisible(false);
    }
}


void ConfigsAnimations::on_pushButtonAddAnimation_clicked()
{
    ConfigsImportDialog *configsImportDialog;
    configsImportDialog = new ConfigsImportDialog(optionsController, ConfigsImportDialog::IMPORT_ANIMATIONS,
                                                  this);

    configsImportDialog->exec();
}

void ConfigsAnimations::on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(current != NULL) {
        currentAnimationData = (AnimationData*) current->data(Qt::UserRole).value<void*>();
        ui->lineEditName->setEnabled(true);
        ui->groupBoxDadosFrames->setEnabled(true);
        ui->groupBoxVisualizacao->setEnabled(true);
        ativaMudancas = false;
        populaCampos();
        ativaMudancas = true;

        animationsGraphicsScene->addAnimationData(currentAnimationData);

        ui->graphicsView->setScene(animationsGraphicsScene);
        ui->graphicsView->setMouseTracking(true);
    }








}


void ConfigsAnimations::on_spinBoxHorizontalFramesNumber_valueChanged(int value)
{
    if(ativaMudancas) {
        currentAnimationData->setHorizontalFrameNumber(value);
        ui->spinBoxColunaInicial->setMaximum(currentAnimationData->getHorizontalFrameNumber());
        ui->spinBoxColunaFinal->setMaximum(currentAnimationData->getHorizontalFrameNumber());
        ui->spinBoxColunaFinal->setValue(value);
        animationsGraphicsScene->addAnimationData(currentAnimationData);
    }



}

void ConfigsAnimations::on_spinBoxVerticalFrameNumber_valueChanged(int value)
{
    if(ativaMudancas) {
        currentAnimationData->setVerticalFrameNumber(value);
        ui->spinBoxLinhaInicial->setMaximum(currentAnimationData->getVerticalFrameNumber());
        ui->spinBoxLinhaFinal->setMaximum(currentAnimationData->getVerticalFrameNumber());
        ui->spinBoxLinhaFinal->setValue(value);
        currentAnimationData->endY = value;
        animationsGraphicsScene->addAnimationData(currentAnimationData);
    }



}

void ConfigsAnimations::on_spinBoxHorizontalSpacing_valueChanged(int value)
{
    currentAnimationData->horizontalSpacing = value;
    animationsGraphicsScene->addAnimationData(currentAnimationData);
}

void ConfigsAnimations::on_spinBoxVerticalSpacing_valueChanged(int value)
{
    currentAnimationData->verticalSpacing = value;
    animationsGraphicsScene->addAnimationData(currentAnimationData);
}

void ConfigsAnimations::on_horizontalSliderVelocity_valueChanged(int value)
{
    currentAnimationData->velocity = value;
    animationsGraphicsScene->addAnimationData(currentAnimationData);
}

void ConfigsAnimations::on_checkBox_toggled(bool checked)
{
    currentAnimationData->hasLoop = checked;
    animationsGraphicsScene->addAnimationData(currentAnimationData);
}

void ConfigsAnimations::on_spinBoxFrameLoop_valueChanged(int value)
{
    currentAnimationData->frameLoop = value;
    animationsGraphicsScene->addAnimationData(currentAnimationData);
}

void ConfigsAnimations::on_comboBoxOrder_currentIndexChanged(int index)
{
    currentAnimationData->order = index;
    animationsGraphicsScene->addAnimationData(currentAnimationData);
}

void ConfigsAnimations::on_spinBoxColunaInicial_valueChanged(int value)
{
    if(value > currentAnimationData->getHorizontalFrameNumber()) {
        value = currentAnimationData->getHorizontalFrameNumber();
        ui->spinBoxColunaInicial->setValue(value);
    }
    currentAnimationData->startX = value;
    animationsGraphicsScene->addAnimationData(currentAnimationData);


}

void ConfigsAnimations::on_spinBoxLinhaInicial_valueChanged(int value)
{
    if(value > currentAnimationData->getVerticalFrameNumber()) {
        value = currentAnimationData->getVerticalFrameNumber();
        ui->spinBoxLinhaInicial->setValue(value);
    }
    currentAnimationData->startY = value;
    animationsGraphicsScene->addAnimationData(currentAnimationData);


}

void ConfigsAnimations::on_spinBoxColunaFinal_valueChanged(int value)
{
    if(value > currentAnimationData->getHorizontalFrameNumber()) {
        value = currentAnimationData->getHorizontalFrameNumber();
        ui->spinBoxColunaFinal->setValue(value);
    }
    currentAnimationData->endX = value;
    animationsGraphicsScene->addAnimationData(currentAnimationData);

}

void ConfigsAnimations::on_spinBoxLinhaFinal_valueChanged(int value)
{
    if(value > currentAnimationData->getVerticalFrameNumber()) {
        value = currentAnimationData->getVerticalFrameNumber();
        ui->spinBoxLinhaFinal->setValue(value);
    }
    currentAnimationData->endY = value;
    animationsGraphicsScene->addAnimationData(currentAnimationData);
}

void ConfigsAnimations::on_toolButtonColorkey_pressed()
{
    GameData *gameData = GameData::getInstance();

    if(ui->listWidget->currentItem() != NULL) {
        currentAnimationData = (AnimationData*) ui->listWidget->currentItem()->data(Qt::UserRole).value<void*>();
        std::string directory =  gameData->getProjectDirectory().append("/").append(currentAnimationData->fileName);

        QImage image = QImage(QString(directory.c_str()));

        ImageColorPicker *imageColorPicker = new ImageColorPicker(QPixmap::fromImage(image), this);
        imageColorPicker->setWindowTitle(tr("Escolha a cor transparente"));

        QColor *color = imageColorPicker->exec();

        if(color != NULL) {
            int r, g, b;
            color->getRgb(&r, &g, &b);

            ui->graphicsViewColorkey->setVisible(true);
            ui->graphicsViewColorkey->setBackgroundBrush(QBrush(*color));

            currentAnimationData->hasColorkey = true;
            currentAnimationData->colorkey_r = r;
            currentAnimationData->colorkey_g = g;
            currentAnimationData->colorkey_b = b;

            delete color;
        }

    }
}


void ConfigsAnimations::on_toolButtonColorkeyX_pressed()
{
    if(ui->listWidget->currentItem() != NULL) {
        currentAnimationData = (AnimationData*) ui->listWidget->currentItem()->data(Qt::UserRole).value<void*>();

        ui->graphicsViewColorkey->setVisible(false);
        currentAnimationData->hasColorkey = false;
    }

}

void ConfigsAnimations::on_removeButton_pressed()
{
    GameData *gameData = GameData::getInstance();

    if(ui->listWidget->currentItem() != NULL) {
        currentAnimationData = (AnimationData*) ui->listWidget->currentItem()->data(Qt::UserRole).value<void*>();

        if(currentAnimationData != NULL) {
            if(MessageBoxes::showConfirmBox(QString::fromUtf8(tr("Deseja remover uma animação?").toStdString().c_str()).toStdString())) {
                GameObject *gameObject = gameData->verifyAnimationUsed(currentAnimationData->id);
                if(gameObject != NULL) {
                    if(gameData->verifyAnimationUsedOnlyOnce(currentAnimationData->id)) {
                        MessageBoxes::showMessageBox(QString::fromUtf8(tr("Não é possível remover a Animação, pois é a única que um objeto usa.").toStdString().c_str()));
                        return;
                    }
                }

                optionsController->removeAnimation(currentAnimationData);
                populaListaAnimation();
            } else {
                return;
            }
        }

    }


}


void ConfigsAnimations::on_pushButtonChangeImage_pressed()
{
    ConfigsImportDialog *configsImportDialog;
    configsImportDialog = new ConfigsImportDialog(optionsController, ConfigsImportDialog::REIMPORT_ANIMATION,
                                                  this);

    configsImportDialog->exec();
    std::string *returnString = configsImportDialog->getReturnString();

    if(returnString != NULL) {


        currentAnimationData->fileName = std::string("animations/").append(*returnString);
        delete returnString;

        animationsGraphicsScene->addAnimationData(currentAnimationData);

        ui->graphicsView->setScene(animationsGraphicsScene);
    }
}
