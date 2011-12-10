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



#include "imagecolorpicker.h"
#include "ui_imagecolorpicker.h"

ImageColorPicker::ImageColorPicker(QString imageFilePath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageColorPicker),
    imageFilePath(imageFilePath),
    image(QPixmap(imageFilePath)),
    imageColorPickerScene(new ImageColorPickerScene(image, this)),
    color(NULL)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(imageColorPickerScene);
    ui->graphicsViewColor->setScene(new QGraphicsScene(this));
}

ImageColorPicker::ImageColorPicker(QPixmap image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageColorPicker),
    image(image),
    imageColorPickerScene(new ImageColorPickerScene(image, this)),
    color(NULL)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(imageColorPickerScene);
    ui->graphicsViewColor->setScene(new QGraphicsScene(this));
}

ImageColorPicker::~ImageColorPicker()
{
    delete ui;
    delete imageColorPickerScene;
}

void ImageColorPicker::setColor(int r, int g, int b) {
    ui->lineEditR->setText(QString::number(r));
    ui->lineEditG->setText(QString::number(g));
    ui->lineEditB->setText(QString::number(b));
    ui->graphicsViewColor->setBackgroundBrush(QBrush(QColor(r, g, b)));

    if(color == NULL) {
        color = new QColor(r, g, b);
    } else {
        color->setRgb(r, g, b);
    }
}

QColor* ImageColorPicker::exec() {
    QDialog::exec();

    return color;
}

void ImageColorPicker::on_buttonBox_accepted()
{
    accept();
}

void ImageColorPicker::on_buttonBox_rejected()
{
    delete color;
    color = NULL;

    reject();
}
