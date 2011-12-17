#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QDialog>
#include <iostream>
#include <QFileSystemModel>
#include <stdio.h>
#include <QtXml/QDomDocument>

#include "maincontroller.h"

class MainController;

namespace Ui {
    class WelcomeScreen;
}

class WelcomeScreen : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeScreen(QWidget *parent = 0);
    ~WelcomeScreen();

    void setMainController(MainController *mainController);
    void populateProjectList();

    void openNewProjectWindow();

    void closeEvent(QCloseEvent *);

private slots:
    void on_buttonNewProject_pressed();

    void on_buttonLoadProject_pressed();

    void on_toolButtonProjectDirectory_pressed();

    void on_listWidget_2_itemActivated(QListWidgetItem *item);

    void on_listWidget_2_currentTextChanged(const QString &currentText);

    void on_pushButtonUpdate_pressed();

private:
    Ui::WelcomeScreen *ui;
    MainController *mainController;
    QString currentProject;
};

#endif // WELCOMESCREEN_H

