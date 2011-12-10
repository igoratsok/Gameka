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


#ifndef NEWEVENTAREADIALOG_H
#define NEWEVENTAREADIALOG_H

#include <QDialog>

namespace Ui {
    class NewEventAreaDialog;
}

/**
 * @brief Janela para criação de uma nova área de evento. Ainda não implementada.
 *
 */
class NewEventAreaDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit NewEventAreaDialog(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~NewEventAreaDialog();

private:
    Ui::NewEventAreaDialog *ui; /**< TODO */
};

#endif // NEWEVENTAREADIALOG_H
