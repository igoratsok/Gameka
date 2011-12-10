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

#include "ModalManager.h"

ModalStack::ModalStack() {
	// TODO Auto-generated constructor stub

}

ModalStack::~ModalStack() {
	// TODO Auto-generated destructor stub
}

bool ModalStack::modalActivated() {
	return !modalStack.empty();
}

void ModalStack::pushModal(Modal *modal) {
	modalStack.push(modal);
}

void ModalStack::popModal() {
	modalStack.pop();
}

int ModalStack::update(int dt) {
	if(!modalStack.empty()) {
		Modal *modal = modalStack.top();
		return modal->update(dt);
	} else {
		modalStack.pop();
		return 0;
	}

}

void ModalStack::render(Screen *screen) {
	std::stack<Modal*> aux;

	while(!modalStack.empty()) {
		modalStack.top()->render(screen);
		aux.push(modalStack.top());
		modalStack.pop();
	}

	while(!aux.empty()) {
		modalStack.push(aux.top());
		aux.pop();
	}
}
