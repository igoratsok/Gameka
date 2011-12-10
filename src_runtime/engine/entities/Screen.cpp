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

#include "Screen.h"

Screen::Screen(int width, int height) {
	this->width = width;
	this->height = height;
	scrollManager = ScrollManager::getInstance();
        topScreen = SDL_CreateRGBSurface(SDL_DOUBLEBUF | SDL_HWSURFACE, width, height, 24, 0, 0, 0, 0);
        screen = SDL_SetVideoMode(width, height, 24, SDL_DOUBLEBUF | SDL_HWSURFACE);
	screenPos = new Vector2();
	zoom = 1;
	topScreenRot = NULL;


}

Screen::~Screen() {
	// TODO Auto-generated destructor stub
}

SDL_Surface* Screen::getTopScreen() {
	return topScreen;
}

void Screen::fillScreen() {
	SDL_FillRect(getTopScreen(), NULL, SDL_MapRGB(getTopScreen()->format, 0, 0, 0));
}

void Screen::flipScreen() {
	SDL_Flip(getTopScreen());
}

void Screen::updateTopScreen() {

}

void Screen::blitTopScreen() {
	SDL_FillRect(screen, NULL, SDL_MapRGB(getTopScreen()->format, 0, 0, 0));
	if(zoom == 1) SDL_BlitSurface(topScreen, NULL, screen, NULL);
	else {
		SDL_BlitSurface(topScreenRot, NULL, screen, &rectRot);
	}
	SDL_Flip(screen);
}

void Screen::createRectRot() {
	Vector2 *scrolledPosition;
	if(!scrollManager->isCenterNull()) {}
	scrolledPosition = scrollManager->scrollVector(screenPos);





	rectRot.x = -(topScreenRot->w - width)/2;
	rectRot.y = -(topScreenRot->h - height)/2;
	//rectRot.x = - scrollManager->getCenter()->x*zoom -(topScreenRot->w - width)/2;
	//rectRot.y = - scrollManager->getCenter()->y*zoom -(topScreenRot->h - height)/2;
	rectRot.w = topScreenRot->w;
	rectRot.h = topScreenRot->h;
	delete scrolledPosition;

}

void Screen::setZoom(float zoom) {
	this->zoom = zoom;
	if(topScreenRot != NULL)
		SDL_FreeSurface(topScreenRot);
	topScreenRot = rotozoomSurface(topScreen, 0, zoom, 0);
	createRectRot();
}
