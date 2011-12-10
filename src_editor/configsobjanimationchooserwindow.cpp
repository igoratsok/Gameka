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



#include "configsobjanimationchooserwindow.h"
#include "ui_configsobjanimationchooserwindow.h"

ConfigsObjAnimationChooserWindow::ConfigsObjAnimationChooserWindow(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigsObjAnimationChooserWindow),
    optionsController(optionsController),
    gameObject(gameObject),
    currentListItem(currentListItem)
{
    ui->setupUi(this);

    copyGameObjectAnimation();

    populaListaEstados();
    populaListaAnimacoes();

    ui->labelDirectionNumber->setText(QString::number(ui->horizontalSliderDirectionNumber->value()*4).append(" dirs"));

    ui->groupBoxDirecao->setEnabled(false);
    ui->groupBoxSpriteAnim->setEnabled(false);
    ui->groupBoxVisu->setEnabled(false);

    currentGameObjectAnimation = NULL;

    animationGraphicsScene = new AnimationGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(animationGraphicsScene);

    ui->graphicsViewColorKey->setScene(new QGraphicsScene(this));
    ui->graphicsViewColorKey->setVisible(false);


}

ConfigsObjAnimationChooserWindow::~ConfigsObjAnimationChooserWindow()
{
    delete ui;
    delete animationGraphicsScene;
}


void ConfigsObjAnimationChooserWindow::on_horizontalSliderDirectionNumber_valueChanged(int value)
{
    ui->dial->setMaximum(pow(2, value));
    ui->labelDirectionNumber->setText(QString::number(pow(2, value)).append(" dirs"));
}

void ConfigsObjAnimationChooserWindow::populaListaEstados() {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::vector<GameObjectAnimation*> *gameObjectAnimationList;


    gameObjectAnimationList = gameObjectAnimations;

    ui->listWidgetEstados->clear();

    for(std::vector<GameObjectAnimation*>::iterator it = gameObjectAnimationList->begin(); it != gameObjectAnimationList->end(); ++it) {
        GameObjectAnimation *iterationItem;

        iterationItem = *it;
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString(iterationItem->name.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) iterationItem));
        ui->listWidgetEstados->addItem(newItem);

    }
}

void ConfigsObjAnimationChooserWindow::populaListaAnimacoes() {

    std::vector<AnimationData*> *animationDataList;


    animationDataList = optionsController->getAnimationDataList();

    ui->listWidget->clear();

    QListWidgetItem *newItem = new QListWidgetItem();
    newItem->setText("-----");
    newItem->setData(Qt::UserRole, QVariant::fromValue((void*) NULL));
    ui->listWidget->addItem(newItem);

    for(std::vector<AnimationData*>::iterator it = animationDataList->begin(); it != animationDataList->end(); ++it) {
        AnimationData *iterationItem;

        iterationItem = *it;
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString(iterationItem->name.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) iterationItem));
        newItem->setIcon(QIcon(QPixmap::fromImage(iterationItem->getIconImage())));
        ui->listWidget->addItem(newItem);

    }
}

void ConfigsObjAnimationChooserWindow::mostraAnimacaoVisualizacao() {
    if(ui->listWidget->currentItem() != NULL) {
        AnimationData *animationData = (AnimationData*) ui->listWidget->currentItem()->data(Qt::UserRole).value<void*>();

        if(animationData != NULL) {
            animationGraphicsScene->addAnimationData(animationData);
        } else {
            animationGraphicsScene->removeGraphics();
        }
    }

}

void ConfigsObjAnimationChooserWindow::mostraSpriteVisualizacao() {
    std::string diretorio = std::string("objects/");
    diretorio.append(ui->lineEditSprite->text().toStdString());

    if(!ui->lineEditSprite->text().isEmpty()) {
        animationGraphicsScene->addSpriteData(diretorio);
    } else {
        animationGraphicsScene->removeGraphics();
    }
}

void ConfigsObjAnimationChooserWindow::copyGameObjectAnimation() {
    gameObjectAnimations = new std::vector<GameObjectAnimation*>(gameObject->gameObjectAnimations->size());

    for(unsigned int i = 0; i < gameObject->gameObjectAnimations->size(); i++) {
        GameObjectAnimation *gameObjectAnimation = new GameObjectAnimation(*gameObject->gameObjectAnimations->at(i));

        gameObjectAnimation->sprites = new std::vector<Sprite*>(gameObject->gameObjectAnimations->at(i)->sprites->size());

        for(unsigned int j = 0; j < gameObject->gameObjectAnimations->at(i)->sprites->size(); j++) {
            Sprite *sprite = new Sprite(*gameObject->gameObjectAnimations->at(i)->sprites->at(j));

            gameObjectAnimation->sprites->at(j) = sprite;
        }

        gameObjectAnimation->animations = new std::vector<AnimationData*>(gameObject->gameObjectAnimations->at(i)->animations->size());

        for(unsigned int j = 0; j < gameObject->gameObjectAnimations->at(i)->animations->size(); j++) {
            gameObjectAnimation->animations->at(j) = gameObject->gameObjectAnimations->at(i)->animations->at(j);
        }

        gameObjectAnimation->types = new std::vector<int>(gameObject->gameObjectAnimations->at(i)->types->size());

        for(unsigned int j = 0; j < gameObject->gameObjectAnimations->at(i)->types->size(); j++) {
            gameObjectAnimation->types->at(j) = gameObject->gameObjectAnimations->at(i)->types->at(j);
        }

        gameObjectAnimations->at(i) = gameObjectAnimation;



    }

}

void ConfigsObjAnimationChooserWindow::preencheCamposCurrentDirection() {
    int direction = getDialConvertedValue();
    int type;
    Sprite *currentSprite = currentGameObjectAnimation->sprites->at(direction);
    AnimationData *currentAnimationData = currentGameObjectAnimation->animations->at(direction);

    type = currentGameObjectAnimation->types->at(direction);
    ui->tabWidgetSpriteAnim->setCurrentIndex(type);

    if(currentSprite != NULL) {
         ui->lineEditSprite->setText(QString(currentSprite->spriteFileName.c_str()));
         if(currentSprite->hascolorkey) {
             ui->graphicsViewColorKey->setVisible(true);
             ui->graphicsViewColorKey->setBackgroundBrush(QBrush(QColor(currentSprite->r_colorkey,
                                                                        currentSprite->g_colorkey,
                                                                        currentSprite->b_colorkey)));
         } else {
             ui->graphicsViewColorKey->setVisible(false);
         }
    } else {
        ui->graphicsViewColorKey->setVisible(false);
    }



    ui->checkBoxInvertHorizontal->setChecked(currentGameObjectAnimation->horizontalInvert.at(direction));
    ui->checkBoxInvertHorizontal2->setChecked(currentGameObjectAnimation->horizontalInvert.at(direction));
    ui->checkBoxInvertVertical->setChecked(currentGameObjectAnimation->verticalInvert.at(direction));
    ui->checkBoxInvertVertically2->setChecked(currentGameObjectAnimation->verticalInvert.at(direction));

    if(currentAnimationData == NULL) {
        ui->listWidget->setCurrentItem(ui->listWidget->itemAt(0, 0));
    } else {
        for(int i = 1; i < ui->listWidget->count(); i++) {
            AnimationData *animationData = (AnimationData*) ui->listWidget->item(i)->data(Qt::UserRole).value<void*>();
            if(animationData->id == currentAnimationData->id) {
                ui->listWidget->setCurrentItem(ui->listWidget->item(i));

            }
        }
    }

    animationGraphicsScene->setAdjustPoint(currentGameObjectAnimation->adjustments.at(direction).x,
                                           currentGameObjectAnimation->adjustments.at(direction).y);

    ui->spinBoxAdjustX->setValue(currentGameObjectAnimation->adjustments.at(direction).x);
    ui->spinBoxAdjustX2->setValue(currentGameObjectAnimation->adjustments.at(direction).x);
    ui->spinBoxAdjustY->setValue(currentGameObjectAnimation->adjustments.at(direction).y);
    ui->spinBoxAdjustY2->setValue(currentGameObjectAnimation->adjustments.at(direction).y);

}

int ConfigsObjAnimationChooserWindow::getDialConvertedValue() {
    int value = ui->dial->value();

    return (int)(value*(pow(2, 5 - ui->horizontalSliderDirectionNumber->value())) + 8)%32;
}

void ConfigsObjAnimationChooserWindow::on_dial_valueChanged(int value)
{
    ui->spinBoxDirectionValue->setValue(getDialConvertedValue());
    preencheCamposCurrentDirection();

    atualizaVisualizacao();
}

void ConfigsObjAnimationChooserWindow::on_listWidgetEstados_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    currentGameObjectAnimation = (GameObjectAnimation*) current->data(Qt::UserRole).value<void*>();

    if(currentGameObjectAnimation != NULL) {
        ui->groupBoxDirecao->setEnabled(true);
        ui->groupBoxSpriteAnim->setEnabled(true);
        ui->groupBoxVisu->setEnabled(true);
        preencheCamposCurrentDirection();

        atualizaVisualizacao();
    }




}

void ConfigsObjAnimationChooserWindow::on_tabWidgetSpriteAnim_currentChanged(int index)
{
    currentGameObjectAnimation->types->at(getDialConvertedValue()) = index;

    atualizaVisualizacao();


}

void ConfigsObjAnimationChooserWindow::atualizaVisualizacao() {
    int index = ui->tabWidgetSpriteAnim->currentIndex();

    switch(index) {
    case 0:
        animationGraphicsScene->removeGraphics();
        break;
    case 1:
        mostraSpriteVisualizacao();
        break;
    case 2:
        mostraAnimacaoVisualizacao();
        break;
    default:

        break;
    }
}


void ConfigsObjAnimationChooserWindow::on_checkBoxInvertHorizontal_toggled(bool checked)
{
    currentGameObjectAnimation->horizontalInvert.at(getDialConvertedValue()) = checked;
    ui->checkBoxInvertHorizontal2->setChecked(checked);
}

void ConfigsObjAnimationChooserWindow::on_checkBoxInvertVertical_toggled(bool checked)
{
    currentGameObjectAnimation->verticalInvert.at(getDialConvertedValue()) = checked;
    ui->checkBoxInvertVertically2->setChecked(checked);
}

void ConfigsObjAnimationChooserWindow::on_checkBoxInvertHorizontal2_toggled(bool checked)
{
    currentGameObjectAnimation->horizontalInvert.at(getDialConvertedValue()) = checked;
    ui->checkBoxInvertHorizontal->setChecked(checked);
}

void ConfigsObjAnimationChooserWindow::on_checkBoxInvertVertically2_toggled(bool checked)
{
    currentGameObjectAnimation->verticalInvert.at(getDialConvertedValue()) = checked;
    ui->checkBoxInvertVertical->setChecked(checked);
}

void ConfigsObjAnimationChooserWindow::on_pushButtonSpriteChooser_pressed()
{
    ConfigsImportDialog *configsImportDialog = new ConfigsImportDialog(optionsController, ConfigsImportDialog::IMPORT_SPRITE, this);

    configsImportDialog->exec();

    std::string *stringReturn = configsImportDialog->getReturnString();

    delete configsImportDialog;

    if(stringReturn != NULL) {
        ui->lineEditSprite->setText(QString(stringReturn->c_str()));

        currentGameObjectAnimation->sprites->at(getDialConvertedValue())->spriteFileName = std::string(stringReturn->c_str());

        delete stringReturn;

        atualizaVisualizacao();
    }


}

void ConfigsObjAnimationChooserWindow::on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    currentGameObjectAnimation->animations->at(getDialConvertedValue()) = (AnimationData*) current->data(Qt::UserRole).value<void*>();

    atualizaVisualizacao();
}

bool ConfigsObjAnimationChooserWindow::verificaSeParadoTemAnimacao() {
    GameObjectAnimation *testGameObjectAnimation = gameObjectAnimations->at(0);

    int i = 0;
    for(std::vector<int>::iterator it = testGameObjectAnimation->types->begin(); it != testGameObjectAnimation->types->end(); ++it) {
        int valor = *it;

        if(valor != 0) {

            if(valor == 1) {
                Sprite *testSprite;
                testSprite = testGameObjectAnimation->sprites->at(i);

                if(!testSprite->spriteFileName.empty()) {
                    return true;
                }
            } else {
                AnimationData *testAnimationData;
                testAnimationData = testGameObjectAnimation->animations->at(i);

                if(testAnimationData != NULL) {
                    return true;
                }
            }



        }

        i++;
    }

    return false;
}

void ConfigsObjAnimationChooserWindow::limpaDadosAntigos() {
    for(std::vector<GameObjectAnimation*>::iterator it = gameObject->gameObjectAnimations->begin(); it != gameObject->gameObjectAnimations->end(); ++it) {
        GameObjectAnimation *testGameObjectAnimation = *it;

        int i = 0;
        for(std::vector<int>::iterator it2 = testGameObjectAnimation->types->begin(); it2 != testGameObjectAnimation->types->end(); ++it2) {
            int value = *it2;

            switch(value) {
            case 1:
                delete testGameObjectAnimation->sprites->at(i);
                break;
            case 2:
                testGameObjectAnimation->animations->at(i) = NULL;
                break;
            default:

                break;
            }

            i++;
        }

        delete testGameObjectAnimation->types;
        delete testGameObjectAnimation->sprites;
        delete testGameObjectAnimation->animations;


        delete testGameObjectAnimation;
    }

    delete gameObject->gameObjectAnimations;
    gameObject->gameObjectAnimations = NULL;
}

void ConfigsObjAnimationChooserWindow::corrigeDadosArmazenamento() {

    for(std::vector<GameObjectAnimation*>::iterator it = gameObjectAnimations->begin(); it != gameObjectAnimations->end(); ++it) {
        GameObjectAnimation *testGameObjectAnimation = *it;

        int i = 0;
        for(std::vector<int>::iterator it2 = testGameObjectAnimation->types->begin(); it2 != testGameObjectAnimation->types->end(); ++it2) {
            int value = *it2;

            switch(value) {
            case 1:
                testGameObjectAnimation->animations->at(i) = NULL;
                break;
            case 2:
                delete testGameObjectAnimation->sprites->at(i);
                testGameObjectAnimation->sprites->at(i) = new Sprite();
                break;
            default:

                break;
            }

            i++;
        }

    }



}

void ConfigsObjAnimationChooserWindow::on_buttonBox_accepted()
{
    // validando o novo gameObjectAnimations
    if(verificaSeParadoTemAnimacao()) {
        corrigeDadosArmazenamento();
        limpaDadosAntigos();
        gameObject->gameObjectAnimations = gameObjectAnimations;
    } else {
        MessageBoxes::showMessageBox(QString::fromUtf8("É necessário ter ao menos uma representação gráfica em \"Parado\""));
    }



}

void ConfigsObjAnimationChooserWindow::on_spinBoxAdjustX_valueChanged(int value)
{
    currentGameObjectAnimation->adjustments.at(getDialConvertedValue()).x = value;
    ui->spinBoxAdjustX2->setValue(value);
    animationGraphicsScene->setAdjustPoint(ui->spinBoxAdjustX->value(), ui->spinBoxAdjustY->value());
}

void ConfigsObjAnimationChooserWindow::on_spinBoxAdjustY_valueChanged(int value)
{
    currentGameObjectAnimation->adjustments.at(getDialConvertedValue()).y = value;
    ui->spinBoxAdjustY2->setValue(value);
    animationGraphicsScene->setAdjustPoint(ui->spinBoxAdjustX->value(), ui->spinBoxAdjustY->value());
}

void ConfigsObjAnimationChooserWindow::on_spinBoxAdjustX2_valueChanged(int value)
{
    currentGameObjectAnimation->adjustments.at(getDialConvertedValue()).x = value;
    ui->spinBoxAdjustX->setValue(value);
    animationGraphicsScene->setAdjustPoint(ui->spinBoxAdjustX->value(), ui->spinBoxAdjustY->value());
}

void ConfigsObjAnimationChooserWindow::on_spinBoxAdjustY2_valueChanged(int value)
{
    currentGameObjectAnimation->adjustments.at(getDialConvertedValue()).y = value;
    ui->spinBoxAdjustY->setValue(value);
    animationGraphicsScene->setAdjustPoint(ui->spinBoxAdjustX->value(), ui->spinBoxAdjustY->value());
}

void ConfigsObjAnimationChooserWindow::on_toolButtonColorkey_pressed()
{
    if(!ui->lineEditSprite->text().isEmpty()) {
        GameData *gameData = GameData::getInstance();

        std::string diretorio = std::string("objects/");
        diretorio.append(ui->lineEditSprite->text().toStdString());

        QString caminho = QString(gameData->getProjectDirectory().append("/").append(diretorio).c_str());

        ImageColorPicker *imageColorPicker = new ImageColorPicker(caminho);

        QColor *color = imageColorPicker->exec();

        if(color != NULL) {
            int r, g, b;
            color->getRgb(&r, &g, &b);

            ui->graphicsViewColorKey->setBackgroundBrush(QBrush(*color));
            ui->graphicsViewColorKey->setVisible(true);

            currentGameObjectAnimation->sprites->at(getDialConvertedValue())->hascolorkey = true;
            currentGameObjectAnimation->sprites->at(getDialConvertedValue())->r_colorkey = r;
            currentGameObjectAnimation->sprites->at(getDialConvertedValue())->b_colorkey = b;
            currentGameObjectAnimation->sprites->at(getDialConvertedValue())->g_colorkey = g;



            delete color;
        }


        delete imageColorPicker;

    }
}

void ConfigsObjAnimationChooserWindow::on_toolButton_pressed()
{
    currentGameObjectAnimation->sprites->at(getDialConvertedValue())->hascolorkey = false;
    ui->graphicsViewColorKey->setVisible(false);

}

