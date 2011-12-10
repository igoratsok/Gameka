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


#ifndef EVENTSWIDGET_H
#define EVENTSWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QMenu>
#include <QAction>

#include "gamedata.h"
#include "gameobject.h"
#include "eventseditorcontroller.h"
#include "newvariabledialog.h"
#include "eventdata.h"

class GameData;
class GameObject;

class EventsEditorController;
class NewVariableDialog;
class EventData;


namespace Ui {
    class EventsWidget;
}

/**
 * @brief Widget da aba de eventos.
 *
 */
class EventsWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param parent
     */
    explicit EventsWidget(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~EventsWidget();

    /**
     * @brief Fornece a controladora de editor de eventos, para comunicação com a camada de negócio.
     *
     * @param eventsEditorController Controladora do editor de eventos.
     */
    void setEventsEditorController(EventsEditorController *eventsEditorController);


    /**
     * @brief Seleciona um objeto específico.
     *
     * @param idObject
     */
    void selectObject(int idObject);

    /**
     * @brief Popula todas as combos e listas.
     *
     */
    void populaTudo();

private:
    Ui::EventsWidget *ui; /**< TODO */


    /**
     * @brief Popula combo do objeto relacionado.
     *
     */
    void populaComboTarget();
    /**
     * @brief Popula lista de procedimentos.
     *
     */
    void populaListaProcedures();
    /**
     * @brief Popula árvore de eventos.
     *
     */
    void populaEventTree();
    /**
     * @brief Popula lista de variáveis.
     *
     */
    void populaVariableList();
    /**
     * @brief Determina o eventData para um Widget, colocando seu texto e valor nele.
     *
     * @param widgetItem O item
     * @param eventData O evento
     */
    void setTreeWidgetItemData(QTreeWidgetItem *widgetItem, EventData* eventData);
    /**
     * @brief Popula uma subárvore.
     *
     * @param parent
     * @param events
     */
    void populaSubEventTree(QTreeWidgetItem *parent, std::list<EventData*> *events);


    /**
     * @brief
     *
     * @param item
     */
    void activateNewEventItemMenu(QTreeWidgetItem *item);
    /**
     * @brief
     *
     * @param item
     */
    void activateCreatedEventItemMenu(QTreeWidgetItem *item);




    EventsEditorController *eventsEditorController; /**< Controladora. */


private slots:
    /**
     * @brief
     *
     * @param item
     * @param column
     */
    void on_treeWidgetEvents_itemDoubleClicked(QTreeWidgetItem* item, int column);
    /**
     * @brief
     *
     * @param current
     * @param previous
     */
    void on_listWidgetProcedures_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    /**
     * @brief
     *
     * @param index
     */
    void on_comboBoxTarget_currentIndexChanged(int index);
    /**
     * @brief
     *
     */
    void on_pushButtonNewProc_pressed();
    /**
     * @brief
     *
     * @param QString
     */
    void on_lineEditProcedureName_textChanged(QString );
    /**
     * @brief
     *
     */
    void on_pushButtonNewVar_pressed();
    /**
     * @brief
     *
     */
    void on_pushButtonEditVar_pressed();
};

#endif // EVENTSWIDGET_H

