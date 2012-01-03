#include "scriptseditorwidget.h"
#include "ui_scriptseditorwidget.h"

ScriptsEditorWidget::ScriptsEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScriptsEditorWidget)
{
    ui->setupUi(this);
}

ScriptsEditorWidget::~ScriptsEditorWidget()
{
    delete ui;
}
