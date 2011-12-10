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

#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(BackgroundLayerData *bgLayerData, GameObject *mainGameObject)
	: bgLayerData(bgLayerData), mainGameObject(mainGameObject) {
	GameData *gameData = GameData::getInstance();

        surface = gameData->loadIMG(bgLayerData->fileName);
        rect.w = surface->w;
	rect.h = surface->h;
	rect.x = 0;
	rect.y = 0;

	preRect.x = 0;
	preRect.y = 0;

	pos = Vector2(0, 0);
	posWithoutDisplacement = Vector2(0, 0);


	v = Vector2((float)bgLayerData->vx/18.0f, (float)bgLayerData->vy/18.0f);

	scrollManager = ScrollManager::getInstance();

	update(0);

}

BackgroundLayer::~BackgroundLayer() {
	SDL_FreeSurface(surface);
}

void BackgroundLayer::update(int dt) {
	Vector2 *scrolledVector;

	switch(bgLayerData->behavior) {
	case STATIC:
		pos.x = posWithoutDisplacement.x;
		pos.y = posWithoutDisplacement.y;

		scrolledVector = scrollManager->scrollVector(&pos);
		pos.x = scrolledVector->x;
		pos.y = scrolledVector->y;


		delete scrolledVector;
		break;
	case FLOATING:

		pos.x = ((int)(posWithoutDisplacement.x + bgLayerData->displacementX))%surface->w;
		pos.y = ((int)(posWithoutDisplacement.y + bgLayerData->displacementY))%surface->h;

		break;
	case FLOATING_RELATIVE_TO_CHARACTER_POSITION:
		if(mainGameObject != NULL) {
			if(bgLayerData->vx != 0) {
				posWithoutDisplacement.x = -mainGameObject->position->x/(30.0f/((float)bgLayerData->vx/3.0f));
			}

			if(bgLayerData->vy != 0) {
				posWithoutDisplacement.y = -mainGameObject->position->y/(30.0f/((float)bgLayerData->vy/3.0f));
			}


		}

		pos.x = ((int)(posWithoutDisplacement.x + bgLayerData->displacementX))%surface->w;
		pos.y = ((int)(posWithoutDisplacement.y + bgLayerData->displacementY))%surface->h;

		break;
	case FLOATING_VELOCITY:
		posWithoutDisplacement.addScaledVector(&v, dt);
		posWithoutDisplacement.x = ((int)posWithoutDisplacement.x)%surface->w;
		posWithoutDisplacement.y = ((int)posWithoutDisplacement.y)%surface->h;

		pos.x = ((int)(posWithoutDisplacement.x + bgLayerData->displacementX))%surface->w;
		pos.y = ((int)(posWithoutDisplacement.y + bgLayerData->displacementY))%surface->h;
		break;
	}




}

void BackgroundLayer::render(Screen *screen) {
	preRect.x = pos.x;
	preRect.y = pos.y;

	rect.x = preRect.x;
	rect.y = preRect.y;

	SDL_BlitSurface(surface, NULL, screen->getTopScreen(), &rect);

	if(bgLayerData->repeatsHorizontally) {
		renderLeftRepetitions(screen);
		renderRightRepetitions(screen);
	}



	preRect.x = pos.x;
	preRect.y = pos.y;

	rect.x = preRect.x;
	rect.y = preRect.y;

	if(bgLayerData->repeatsVertically) {
		renderUpRepetitions(screen);
		renderDownRepetitions(screen);
	}

}

void BackgroundLayer::renderLeftRepetitions(Screen *screen) {
	int nro_repeticoes = (int)(pos.x/surface->w) + 1;

	for(int i = 0; i < nro_repeticoes; i++) {
		preRect.x = pos.x - (i+1)*surface->w;
		preRect.y = pos.y;

		rect.x = preRect.x;
		rect.y = preRect.y;

		SDL_BlitSurface(surface, NULL, screen->getTopScreen(), &rect);

		if(bgLayerData->repeatsVertically) {
			renderUpRepetitions(screen);
			renderDownRepetitions(screen);
		}
	}
}

void BackgroundLayer::renderRightRepetitions(Screen *screen) {
	int nro_repeticoes = (int)((screen->width - (pos.x + surface->w))/surface->w) + 1;

	if(nro_repeticoes > 0) {
		for(int i = 0; i < nro_repeticoes; i++) {
			preRect.x = pos.x + (i+1)*surface->w;
			preRect.y = pos.y;

			rect.x = preRect.x;
			rect.y = preRect.y;

			SDL_BlitSurface(surface, NULL, screen->getTopScreen(), &rect);

			if(bgLayerData->repeatsVertically) {
				renderUpRepetitions(screen);
				renderDownRepetitions(screen);
			}
		}

	}
}

void BackgroundLayer::renderUpRepetitions(Screen *screen) {
	int nro_repeticoes = (int)(pos.y/surface->h) + 1;

	for(int i = 0; i < nro_repeticoes; i++) {
		preRect.y = pos.y - (i+1)*surface->h;

		rect.x = preRect.x;
		rect.y = preRect.y;

		SDL_BlitSurface(surface, NULL, screen->getTopScreen(), &rect);
	}
}

void BackgroundLayer::renderDownRepetitions(Screen *screen) {
	int nro_repeticoes = (int)((screen->height - pos.y)/surface->h) + 1;

	if(nro_repeticoes > 0) {
		for(int i = 0; i < nro_repeticoes; i++) {
			preRect.y = pos.y + (i+1)*surface->h;

			rect.x = preRect.x;
			rect.y = preRect.y;

			SDL_BlitSurface(surface, NULL, screen->getTopScreen(), &rect);
		}

	}
}
