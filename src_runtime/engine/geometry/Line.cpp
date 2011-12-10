
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

#include "Line.h"

Line::Line(Vector2 *start, Vector2 *end) {
	this->start = start;
	this->end = end;



	if(end->x - start->x == 0) {
		linhaVertical = true;

		if(end->y > start->y) {
			dir.y = 1;
		} else {
			dir.y = -1;
		}

	} else {
		linhaVertical = false;
		m = (end->y - start->y)/(end->x - start->x);
		q = start->y - m*start->x;

		if(end->x > start->x) {
			dir.x = 1;
		} else {
			dir.x = -1;
		}
	}

	passo = fabs(end->x - start->x)/fabs(end->y - start->y);
	if(passo > 1) passo = 1;

	passo = 0.5f;


}

Line::~Line() {
	// TODO Auto-generated destructor stub
}

// ATENÇÃO: a idéia é essa, mas tem que ver as "ordens" do end e start

void Line::startInterpolation() {
	pontoInterpolacao.x = floor(start->x);
	pontoInterpolacao.y = floor(start->y);
}

Vector2 Line::retrieveInterpolation() {
	Vector2 retorno;

	if(linhaVertical) {
		retorno.x = pontoInterpolacao.x;
		retorno.y = pontoInterpolacao.y;

		pontoInterpolacao.y += dir.y;
	} else {
		retorno.x = pontoInterpolacao.x;
		retorno.y = pontoInterpolacao.y;

		pontoInterpolacao.x += dir.x*passo;
		pontoInterpolacao.y = m*pontoInterpolacao.x + q;
	}



	return retorno;
}

bool Line::finished() {
	if(linhaVertical && dir.y*pontoInterpolacao.y > dir.y*end->y) {
		return true;
	} else if(dir.x*pontoInterpolacao.x > dir.x*end->x) {
		return true;
	}

	return false;

}

float Line::getY(float x) {
	return m*x + q;
}

float Line::getX(float y) {
	return (y - q)/m;
}
