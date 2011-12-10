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

#include "AuxiliarMath.h"

AuxiliarMath::AuxiliarMath() {
	int i;

	// inicializando a tabela SEN

	SEN = (float*) calloc(360*ROUNDS, sizeof(float));

	for(i = 0; i < 360*2; i++) {

		SEN[i] = ((((float)i/ROUNDS)/360)*2)*2*M_PI;
	}

}

AuxiliarMath::~AuxiliarMath() {
	// TODO Auto-generated destructor stub
}

float AuxiliarMath::sin(float value) {
	float tableValue;
	float returnValue;

	tableValue = (((value/ROUNDS)/2*M_PI)*360)*2;

	tableValue = tableValue - ((int)(tableValue/360))*tableValue;

	returnValue = SEN[(int)floor(tableValue)] +
			(SEN[(int)ceil(tableValue)] -
					SEN[(int)floor(tableValue)])*(-(floor(tableValue) - tableValue));

	return returnValue;
}
