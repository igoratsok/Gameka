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

#include "Sphere.h"

Sphere::Sphere(Vector2 c, commtypes::real r) {
	this->c = c;
	this->r = r;

}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

bool Sphere::testMovingSphereRect(Sphere s, Vector2 f, Rect b, float *t, Vector2 *p, int *side) {
	Vector2 d;
	d.x = f.x - s.c.x;
	d.y = f.y - s.c.y;

	Rect e = b;
	e.x -= s.r;
	e.y -= s.r;
	e.w += 2*s.r;
	e.h += 2*s.r;

	if(!e.rayIntersection(s.c, f, t, p) || *t > 1.0f) {
		return false;
	}

	if(p->x == e.x) {
		*side = SIDE_LEFT;
	}

	if(p->y == e.y) {
		*side = SIDE_UP;
	}

	if(p->x == e.getMax().x) {
		*side = SIDE_RIGHT;
	}

	return true;
}


