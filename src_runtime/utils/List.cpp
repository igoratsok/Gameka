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

#include "List.h"



template <class T>
List<T>::List() {
	list = NULL;

}

template <class T>
List<T>::~List() {
	// TODO Auto-generated destructor stub
}

template <class T>
void List<T>::add(T *element) {
	if(list == NULL) {
		list = element;
		element->next = NULL;
	} else {
		T *p1;
		p1 = list;
		while(p1->next != NULL) {
			p1 = p1->next;
		}

		p1->next = element;
		element->next = NULL;


	}
}

template <class T>
T* List<T>::start() {
	it = list;
	return it;
}

template <class T>
T* List<T>::iterate() {
	it = it->next;
	return it;
}

template <class T>
T* List<T>::end() {
	return NULL;
}

template <class T>
T* List<T>::elementAt(int i) {
	T *element, *p1;
	int count;

	p1 = list;
	count = 0;
	for(count = 0; count < i; count++) {
		if(p1 != NULL) {
			p1 = p1->next;
		} else {
			return NULL;
		}
	}

	return p1;
}
