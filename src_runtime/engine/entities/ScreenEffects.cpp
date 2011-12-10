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

#include "ScreenEffects.h"

ScreenEffects::ScreenEffects() {
	// TODO Auto-generated constructor stub

}

ScreenEffects::~ScreenEffects() {
	// TODO Auto-generated destructor stub
}

void ScreenEffects::update(int dt) {
	if(timerPisca > 0) {
		if(dt/4 < 255) {
			timerPisca -= dt/4;
		}


	}

	if(timerFadeIn > 0) {
		if(dt/4 < 255) {
			timerFadeIn -= dt/4;
		}


	}
}

void ScreenEffects::render(Screen *screen) {
	if(timerPisca > 0) {
		Sprite::drawRectNoScrolling(Rect(0, 0, 640, 480), corPiscaR, corPiscaG, corPiscaB, timerPisca, screen);
		std::cout << "Tp: " << timerPisca << std::endl;
	}

	if(timerFadeIn > 0) {
		int alpha = (256 - timerFadeIn);
		if(alpha > 255) alpha = 255;
		Sprite::drawRectNoScrolling(Rect(0, 0, 640, 480), corFadeInR, corFadeInG, corFadeInB, alpha, screen);
	}
}

void ScreenEffects::piscaTela(int r, int g, int b) {
	timerPisca = 256;
	corPiscaB = b;
	corPiscaG = g;
	corPiscaR = r;
}

void ScreenEffects::fadeIn(int r, int g, int b) {
	timerFadeIn = 256;
	corFadeInR = r;
	corFadeInG = g;
	corFadeInB = b;
}

bool ScreenEffects::terminouFadeIn() {
	return (timerFadeIn <= 0);
}

bool ScreenEffects::terminouPiscaTela() {
	return (timerPisca <= 0);
}
