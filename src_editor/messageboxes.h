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


#ifndef MESSAGEBOXES_H
#define MESSAGEBOXES_H

#include <QMessageBox>
#include <string>

/**
 * @brief Classe com métodos estáticos para mostrar janeals de mensagem e de confirmação.
 *
 */
class MessageBoxes
{
public:
    /**
     * @brief Construtor.
     *
     */
    MessageBoxes();


    /**
     * @brief Mostra uma mensagem na tela.
     *
     * @param message String da mensagem a ser mostrada.
     */
    static void showMessageBox(std::string message);
    /**
     * @brief Mostra uma mensagem na tela, com QString.
     *
     * @param message String da mensagem a ser mostrada.
     */
    static void showMessageBox(QString message);
    /**
     * @brief Mostra uma mensagem de confirmação na tela com botões de "Sim" e "Não".
     *
     * @param message
     *
     * @return bool retorna: \n
     *              - true, se confirmou;
     *              - false, se não confirmou;
     */
    static bool showConfirmBox(std::string message);

};

#endif // MESSAGEBOXES_H
