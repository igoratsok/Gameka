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
#include "Rectangle.h"

Rect::Rect()
	: x(0), y(0), w(0), h(0) {

}

Rect::Rect(int x, int y, int w, int h)
	: x(x), y(y), w(w), h(h) {

}

Rect::~Rect() {

}

bool Rect::intersectsWith(Rect *rectangle) {
	bool testex, testey, testex1, testex2, testey1, testey2;

	testex1 = ((((this->x + this->w) - (rectangle->x)) > 0));
	testex2 = ((((this->x) - (rectangle->x + rectangle->w)) > 0));
	testex = testex1 != testex2;

	testey1 = ((((this->y + this->h) - (rectangle->y)) > 0));
	testey2 = ((((this->y) - (rectangle->y + rectangle->h)) > 0));
	testey = testey1 != testey2;

	return (testex && testey);
}

bool Rect::intersectsXAxisWith(Rect *rectangle) {
	bool testex, testex1, testex2;

	testex1 = ((((this->x + this->w) - (rectangle->x)) > 0));
	testex2 = ((((this->x) - (rectangle->x + rectangle->w)) > 0));
	testex = testex1 != testex2;

	return (testex);
}

bool Rect::intersectsYAxisWith(Rect *rectangle) {
	bool testey, testey1, testey2;

	testey1 = ((((this->y + this->h) - (rectangle->y)) > 0));
	testey2 = ((((this->y) - (rectangle->y + rectangle->h)) > 0));
	testey = testey1 != testey2;

	return (testey);
}

bool Rect::contains(Vector2 vector) {
	return (vector.x >= this->x && vector.x <= this->x + this->w &&
			vector.y >= this->y && vector.y <= this->y + this->h);
}

Vector2 Rect::getMin() {
	return Vector2(x, y);
}

Vector2 Rect::getMax() {
	return Vector2(x + w, y + h);
}

bool Rect::rayIntersection(Vector2 p, Vector2 f, float *tmin, Vector2 *q) {
	*tmin = 0.0f;
	float tmax = INFINITY;
	Vector2 d;
	d.x = f.x - p.x;
	d.y = f.y - p.y;

	for(int i = 0; i < 2; i++) {
		if(fabs(d.getAxisByNo(i)) < EPSILON) {
			if((p.getAxisByNo(i) < getMin().getAxisByNo(i)) || p.getAxisByNo(i) > getMax().getAxisByNo(i)) {
				return false;
			}
		} else {
			float ood = 1.0f/d.getAxisByNo(i);
			float t1 = (getMin().getAxisByNo(i) - p.getAxisByNo(i))*ood;
			float t2 = (getMax().getAxisByNo(i) - p.getAxisByNo(i))*ood;

			if(t1 > t2) {
				std::swap(t1, t2);
			}

			*tmin = std::max(*tmin, t1);
			tmax = std::min(tmax, t2);

			if(*tmin > tmax) return false;
		}
	}

	q->x = p.x + d.x * (*tmin);
	q->y = p.y + d.y * (*tmin);

	return true;
}

bool Rect::intersectMovingRectRect(Rect a, Rect b, Vector2 va, Vector2 vb,
			float *tfirst, float *tlast) {

	if(a.intersectsWith(&b)) {
		*tfirst = *tlast = 0.0f;
		return true;
	}

	Vector2 v;
	v.x = vb.x - va.x;
	v.y = vb.y - va.y;

	if(v.x == 0 && v.y == 0) {
		return false;
	}

	if(v.x == 0 && v.y != 0 && !a.intersectsXAxisWith(&b)) {
		return false;
	}

	if(v.x != 0 && v.y == 0 && !a.intersectsYAxisWith(&b)) {
		return false;
	}

	*tfirst = 0.0f;
	*tlast = 1.0f;

	for(int i = 0; i < 2; i++) {
		if(v.getAxisByNo(i) < 0.0f) {
			if(b.getMax().getAxisByNo(i) < a.getMin().getAxisByNo(i)) {
				return false;
			}

			if(a.getMax().getAxisByNo(i) < b.getMin().getAxisByNo(i)) {
				*tfirst = std::max((a.getMax().getAxisByNo(i) - b.getMin().getAxisByNo(i))/ v.getAxisByNo(i), *tfirst);
			}

			if(b.getMax().getAxisByNo(i) > a.getMin().getAxisByNo(i)) {
				*tlast = std::min((a.getMin().getAxisByNo(i) - b.getMax().getAxisByNo(i))/ v.getAxisByNo(i), *tlast);
			}
		} else if(v.getAxisByNo(i) > 0.0f) {
			if(b.getMin().getAxisByNo(i) > a.getMax().getAxisByNo(i)) {
				return false;
			}

			if(b.getMax().getAxisByNo(i) < a.getMin().getAxisByNo(i)) {
				*tfirst = std::max((a.getMin().getAxisByNo(i) - b.getMax().getAxisByNo(i))/v.getAxisByNo(i), *tfirst);
			}

			if(a.getMax().getAxisByNo(i) > b.getMin().getAxisByNo(i)) {
				*tlast = std::min((a.getMax().getAxisByNo(i) - b.getMin().getAxisByNo(i))/v.getAxisByNo(i), *tlast);
			}
		}


		if(*tfirst > *tlast) {
			return false;
		}

	}



	return true;
}

bool Rect::sweepTestRectRect(Rect a, Rect b, Vector2 va, Vector2 vb, float *tfirst, float *tlast) {
	Vector2 v;
	v.x = vb.x - va.x;
	v.y = vb.y - va.y;

	if(v.x == 0 && v.y == 0) {
			return false;
		}

	if(v.x == 0 && v.y != 0 && !a.intersectsXAxisWith(&b)) {
		return false;
	}

	if(v.x != 0 && v.y == 0 && !a.intersectsYAxisWith(&b)) {
		return false;
	}

	Vector2 u_0 = Vector2(0, 0);
	Vector2 u_1 = Vector2(1, 1);

	if(a.intersectsWith(&b)) {
		*tfirst = *tlast = 0.0f;
		return true;
	}

	for(long i = 0; i < 2; i++) {
		if(a.getMax().getAxisByNo(i) < b.getMin().getAxisByNo(i) && v.getAxisByNo(i) < 0) {
			u_0.setAxisByNo(i, (a.getMax().getAxisByNo(i) - b.getMin().getAxisByNo(i))/v.getAxisByNo(i));
		} else if(b.getMax().getAxisByNo(i) < a.getMin().getAxisByNo(i) && v.getAxisByNo(i) > 0) {
			u_0.setAxisByNo(i, (a.getMin().getAxisByNo(i) - b.getMax().getAxisByNo(i))/v.getAxisByNo(i));
		}

		if(b.getMax().getAxisByNo(i) > a.getMin().getAxisByNo(i) && v.getAxisByNo(i) < 0) {
			u_1.setAxisByNo(i, (a.getMin().getAxisByNo(i) - b.getMax().getAxisByNo(i))/v.getAxisByNo(i));
		} else if(a.getMax().getAxisByNo(i) > b.getMin().getAxisByNo(i) && v.getAxisByNo(i) > 0) {
			u_1.setAxisByNo(i, (a.getMax().getAxisByNo(i) - b.getMin().getAxisByNo(i))/v.getAxisByNo(i));
		}
	}

	*tfirst = std::max(u_0.x, u_0.y);
	*tlast = std::min(u_1.x, u_1.y);


	return *tfirst <= *tlast;
}

bool Rect::movingIntersectRect(Vector2 v, Rect rect, float *tfirst, float *tlast, int *lado, Rect *movedRectCol) {
	bool result = Rect::intersectMovingRectRect(*this, rect, v, Vector2(0, 0), tfirst, tlast);
	//bool result = Rectangle::intersectMovingRectRect(rect, *this, Vector2(0, 0), v, tfirst, tlast);

	Rect movedRect = *this;
	movedRect.x = round((float)this->x + v.x*(*tfirst));
	movedRect.y = round((float)this->y + v.y*(*tfirst));

	Rect movedRectNoRound = *this;
	movedRectNoRound.x = (float)this->x + v.x*(*tfirst);
	movedRectNoRound.y = (float)this->y + v.y*(*tfirst);

	movedRectCol->x = movedRect.x;
	movedRectCol->y = movedRect.y;
	//std::cout << "tfirst: " << *tfirst << std::endl;

	if(result) {
		std::cout << "Moved rect: " << movedRect.x << " " << movedRect.y << std::endl;
		std::cout << "Moved rect: " << movedRectNoRound.x << " " << movedRectNoRound.y << std::endl;
		std::cout << "MovedRect max: " << movedRect.getMax().x << ", " << movedRect.getMax().y << std::endl;
		std::cout << "MovedRect min: " << movedRect.getMin().x << ", " << movedRect.getMin().y << std::endl;
		std::cout << "Rect max: " << rect.getMax().x << ", " << rect.getMax().y << std::endl;
		std::cout << "Rect min: " << rect.getMin().x << ", " << rect.getMin().y << std::endl;
	}


	if(movedRect.getMax().x == rect.getMin().x) {
		*lado = SIDE_LEFT;
	} else if(movedRect.getMax().y == rect.getMin().y) {
		*lado = SIDE_UP;
	} else if(movedRect.getMin().y == rect.getMax().y) {
		*lado = SIDE_DOWN;
	} else {
		*lado = SIDE_RIGHT;
	}


	return result;


}
