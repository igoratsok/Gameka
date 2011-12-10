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

#include "Vector2.h"

Vector2::Vector2()
	: x(0), y(0), z(0) {


}

Vector2::Vector2(commtypes::real x, commtypes::real y)
	: x(x), y(y), z(0) {

}

Vector2::Vector2(commtypes::real x, commtypes::real y,  commtypes::real z)
	: x(x), y(y), z(z) {

}

Vector2::~Vector2() {

}

commtypes::real Vector2::magnitude() {
	return real_sqrt(x*x + y*y);
}


void Vector2::addScaledVector(const Vector2 *vector, commtypes::real scale) {
	// limitando em 40 para corrigir um bug de colisão

	if(fabs(vector->x*scale) > 40) {
		if(vector->x*scale > 0) {
			x += 40;
		} else {
			x -= 40;
		}

	} else {
		x += vector->x*scale;
	}

	if(fabs(vector->y*scale) > 40) {
		if(vector->y*scale > 0) {
			y += 40;
		} else {
			y -= 40;
		}
	} else {
		y += vector->y*scale;
	}

	if(fabs(vector->z*scale) > 40) {
		if(vector->z*scale > 0) {
			z += 40;
		} else {
			z -= 40;
		}
	} else {
		z += vector->z*scale;
	}


}

Vector2 Vector2::getDirecao() {
	Vector2 dir = Vector2();

	if(x == 0) {
		dir.x = 0;
	} else {
		dir.x = fabs(x)/x;
	}

	if(y == 0) {
		dir.y = 0;
	} else {
		dir.y = fabs(y)/y;
	}



	return dir;
}

void Vector2::limitVector(const Vector2 *vector) {
	if(x > fabs(vector->x)) {
		x = fabs(vector->x);
	} else if(x < -fabs(vector->x)) {
		x = -fabs(vector->x);
	}

	if(y > fabs(vector->y)) {
		y = fabs(vector->y);
	} else if(y < -fabs(vector->y)) {
		y = -fabs(vector->y);
	}

}

commtypes::real Vector2::getAxisByNo(int no) {
        switch(no) {
        case 0:
                return x;
        case 1:
                return y;
        case 2:
                return z;
        default:
                return x;
        }
}

void Vector2::setAxisByNo(int no, commtypes::real value) {
        switch(no) {
        case 0:
                x = value;
                break;
        case 1:
                y = value;
                break;
        case 2:
                z = value;
                break;
        default:
                x = value;
        }
}
