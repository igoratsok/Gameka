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



#include "configstilesetwidget.h"
#include "ui_configstilesetwidget.h"

ConfigsTilesetWidget::ConfigsTilesetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigsTilesetWidget)
{
    ui->setupUi(this);
    populaLista();

    tilesetColMapScene = NULL;

    ui->graphicsViewColorkey->setScene(new QGraphicsScene(this));
    ui->graphicsViewColorkey->setVisible(false);
}

ConfigsTilesetWidget::~ConfigsTilesetWidget()
{
    delete ui;
}

void ConfigsTilesetWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ConfigsTilesetWidget::setOptionsController(OptionsController *optionsController) {
    this->optionsController = optionsController;
}

void ConfigsTilesetWidget::on_pushButton_clicked()
{
    ConfigsImportDialog *newWindow;

    newWindow = new ConfigsImportDialog(optionsController, ConfigsImportDialog::IMPORT_TILESETS, this);
    newWindow->setWindowTitle(QString("Importar tilesets"));
    newWindow->setModal(true);
    newWindow->show();
}

void ConfigsTilesetWidget::disableAll() {
    ui->lineEdit->setDisabled(true);
    ui->spinBox->setDisabled(true);
    ui->graphicsView->setScene(new QGraphicsScene());
}

void ConfigsTilesetWidget::populaLista() {

    std::vector<TileSet*>* tileSetList;


    tileSetList = optionsController->getTilesetList();

    ui->listWidget->clear();

    for(std::vector<TileSet*>::iterator it = tileSetList->begin(); it != tileSetList->end(); ++it) {
        TileSet *iterationItem;

        iterationItem = *it;
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString(iterationItem->name.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) iterationItem));
        ui->listWidget->addItem(newItem);

    }
}

void ConfigsTilesetWidget::selectLastTileset() {
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
}

void ConfigsTilesetWidget::on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{

    if(current != 0x0) {
        TileSet *currentTileset;
        currentTileset = (TileSet*) current->data(Qt::UserRole).value<void*>();


        ui->lineEdit->setDisabled(false);
        ui->spinBox->setDisabled(false);
        ui->lineEdit->setText(current->text());
        ui->spinBox->setValue(currentTileset->tileSize);


        tilesetColMapScene = new TilesetColMapScene(currentTileset, this);
        ui->graphicsView->setScene(tilesetColMapScene);
        ui->graphicsView->setMouseTracking(true);
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        ui->graphicsView->repaint();
    }

}

void ConfigsTilesetWidget::on_lineEdit_textChanged(QString )
{
    ui->listWidget->currentItem()->setText(ui->lineEdit->text());
    TileSet *currentTileset;
    currentTileset = (TileSet*) ui->listWidget->currentItem()->data(Qt::UserRole).value<void*>();
    currentTileset->name = ui->lineEdit->text().toStdString();
}

void ConfigsTilesetWidget::on_spinBox_valueChanged(int )
{

}

void ConfigsTilesetWidget::on_pushButtonInvert_pressed()
{
    if(tilesetColMapScene != NULL) {
        tilesetColMapScene->invert();
    }
}


void ConfigsTilesetWidget::on_pushButtonAllX_pressed()
{
    if(tilesetColMapScene != NULL) {
        tilesetColMapScene->allX();
    }
}

void ConfigsTilesetWidget::on_pushButtonAllO_pressed()
{
    if(tilesetColMapScene != NULL) {
        tilesetColMapScene->allO();
    }
}

void ConfigsTilesetWidget::on_pushButtonUpdateSizeValue_pressed()
{



    TileSet *currentTileset;
    currentTileset = (TileSet*) ui->listWidget->currentItem()->data(Qt::UserRole).value<void*>();


    if(optionsController->verifyUsedTileset(currentTileset)) {
        MessageBoxes::showMessageBox(QString::fromUtf8("Não é possível mudar este valor para um Tileset que estiver sendo utilizado em um mapa."));

        return;
    }

    if(currentTileset->tileSize != ui->spinBox->value() &&
            MessageBoxes::showConfirmBox(QString::fromUtf8("Tem certeza que deseja alterar o valor? A matriz de colisão será reinicializada.").toStdString())) {
        currentTileset->tileSize = ui->spinBox->value();
        currentTileset->calculateCollisionMatrix();

        tilesetColMapScene = new TilesetColMapScene(currentTileset, this);
        ui->graphicsView->setScene(tilesetColMapScene);
        ui->graphicsView->setMouseTracking(true);
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        ui->graphicsView->repaint();
    }



}

void ConfigsTilesetWidget::on_pushButtonTransparentColor_pressed()
{
    TileSet *currentTileset;

    if(ui->listWidget->currentItem() != NULL) {
        currentTileset = (TileSet*) ui->listWidget->currentItem()->data(Qt::UserRole).value<void*>();

        if(currentTileset != NULL) {
            ImageColorPicker *imageColorPicker = new ImageColorPicker(QPixmap::fromImage(*currentTileset->tilesetImage), this);
            imageColorPicker->setWindowTitle("Escolher cor transparente");
            QColor *color = imageColorPicker->exec();

            if(color != NULL) {
                int r, g, b;

                color->getRgb(&r, &g, &b);

                ui->graphicsViewColorkey->setBackgroundBrush(QBrush(QColor(r, g, b)));
                ui->graphicsViewColorkey->setVisible(true);

                currentTileset->hasColorKey = true;
                currentTileset->colorkey_r = r;
                currentTileset->colorkey_g = g;
                currentTileset->colorkey_b = b;

                delete color;

                tilesetColMapScene = new TilesetColMapScene(currentTileset, this);
                ui->graphicsView->setScene(tilesetColMapScene);
                ui->graphicsView->setMouseTracking(true);
                ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
                ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

                ui->graphicsView->repaint();

                currentTileset->reloadTilesetImage();

            }
        }



    }




}


void ConfigsTilesetWidget::on_toolButton_pressed()
{
    TileSet *currentTileset;

    if(ui->listWidget->currentItem() != NULL) {
        currentTileset = (TileSet*) ui->listWidget->currentItem()->data(Qt::UserRole).value<void*>();
        if(currentTileset != NULL) {
            currentTileset->hasColorKey = false;
            ui->graphicsViewColorkey->setVisible(false);

            tilesetColMapScene = new TilesetColMapScene(currentTileset, this);
            ui->graphicsView->setScene(tilesetColMapScene);
            ui->graphicsView->setMouseTracking(true);
            ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

            ui->graphicsView->repaint();

            currentTileset->reloadTilesetImage();
        }

    }



}

void ConfigsTilesetWidget::on_removeTilesetButton_pressed()
{
    GameData *gameData = GameData::getInstance();
    TileSet *currentTileset;

    if(ui->listWidget->currentItem() != NULL) {
        currentTileset = (TileSet*) ui->listWidget->currentItem()->data(Qt::UserRole).value<void*>();
        if(currentTileset != NULL) {
            if(MessageBoxes::showConfirmBox(QString::fromUtf8("Deseja mesmo eliminar o Tileset?").toStdString())) {
                Map *map = gameData->verifyTilesetUsed(currentTileset->id);

                if(map != NULL) {
                    if(gameData->verifyTilesetUsedOnlyOne(currentTileset->id)) {
                        MessageBoxes::showMessageBox(QString::fromUtf8("Este Tileset é o único de um mapa e não pode ser removido."));
                        return;
                    }

                    if(MessageBoxes::showConfirmBox(QString::fromUtf8("O Tileset já é usado em um mapa. Deseja remover mesmo assim?").toStdString())) {
                        optionsController->removeTileset(currentTileset);
                        populaLista();

                        disableAll();;
                    }
                } else {
                    optionsController->removeTileset(currentTileset);
                    populaLista();

                    disableAll();
                }
            }
        }
    }
}
