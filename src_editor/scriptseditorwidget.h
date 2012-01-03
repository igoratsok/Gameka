#ifndef SCRIPTSEDITORWIDGET_H
#define SCRIPTSEDITORWIDGET_H

#include <QWidget>

namespace Ui {
    class ScriptsEditorWidget;
}

class ScriptsEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptsEditorWidget(QWidget *parent = 0);
    ~ScriptsEditorWidget();

private:
    Ui::ScriptsEditorWidget *ui;
};

#endif // SCRIPTSEDITORWIDGET_H
