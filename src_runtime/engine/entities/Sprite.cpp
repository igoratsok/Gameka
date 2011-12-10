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

#include "Sprite.h"

/**
 * Construtor da classe sprite.
 *
 * @param nomeArq nome do arquivo a ser lido do sprite
 * @param x posicao x inicial do sprite
 * @param y posicao y inicial do sprite.
 *
 */
Sprite::Sprite(string *nomeArq, Vector2 *pos) {
	// lendo a textura
	SDL_Surface *texture1;
	GameData *gameData = GameData::getInstance();

	std::cout << nomeArq->c_str() << std::endl;


	texture1 = gameData->loadIMG(nomeArq->c_str());

	/*
	SDL_Rect rx = {0, 0, texture1->w, texture1->h};

	texture = SDL_CreateRGBSurface(SDL_SWSURFACE, texture1->w, texture1->h, 32,
			0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	if((int)texture1->format->BitsPerPixel == 32) {
		SDL_gfxBlitRGBA(texture1, NULL, texture, &rx);
	} else {
		SDL_BlitSurface(texture1, NULL, texture, &rx);
	}
	*/

        texture = texture1;



	//texture = NULL;
	//while(texture == NULL) {
	//	texture = SDL_DisplayFormatAlpha(texture1);
	//}
	//SDL_FreeSurface(texture1);

	animationLoopedOnce = false;

	this->pos = pos;

	// criando o rect do sprite
	rectangle.x = pos->x;
	rectangle.y = pos->y;
	rectangle.w = texture->w;
	rectangle.h = texture->h;

	width = rectangle.w;
	height = rectangle.h;


	rotAngle = 0;
	zoom = 1;
	scrollingVelocity.x = 1;
	scrollingVelocity.y = 1;

	textureRotoZoomed = NULL;
	scrollable = true;

	scrollManager = ScrollManager::getInstance();

	renderPosition.x = 0;
	renderPosition.y = 0;
	loopX = false;
	loopY = false;

	gameObjectInstance = NULL;
	gameObjectAnimations = NULL;

	isAnimation = false;
}

Sprite::Sprite(string *nomeArquivo, Vector2 *pos, int nframes, int spacing) {
	animationSurfaces = (std::vector<SDL_Surface*>***) calloc(1, sizeof(std::vector<SDL_Surface*>**));
	animationSurfaces[0] = (std::vector<SDL_Surface*>**) calloc(1, sizeof(std::vector<SDL_Surface*>));

	SDL_Surface *animationSheet;
	int stepX, stepY;
	GameData *gameData = GameData::getInstance();


	animationSheet = gameData->loadIMG(nomeArquivo->c_str());

	if(animationSheet == NULL) {
		fprintf(stderr, "Arquivo %s n encontrado. Abortando... \n", nomeArquivo->c_str());
		exit(1);
	}



	stepX = (animationSheet->w - spacing*(nframes - 1))/nframes;
	stepY = (animationSheet->h);

	int k = 0;
	for(k = 0; k < nframes; k++) {
		animationSurfaces[0][0]->at(k) = cropAnimationSheet(animationSheet, k, 0, stepX, stepY);
	}


	SDL_FreeSurface(animationSheet);
}


Sprite::Sprite(GameObjectInstance *gameObjectInstance, Vector2 *pos)
	: gameObjectInstance(gameObjectInstance) {
	GameData *gameData = GameData::getInstance();

	animationLoopedOnce = false;

	gameObjectAnimations = gameObjectInstance->gameObject->gameObjectAnimations;

	animationSurfaces = (std::vector<SDL_Surface*>***) calloc(gameObjectAnimations->size(), sizeof(std::vector<SDL_Surface*>**));
        ArrayCreator<AnimationData*> *animationDataArrayCreator = new ArrayCreator<AnimationData*>();

        animationDatas = animationDataArrayCreator->createMatrix(gameObjectAnimations->size(), 32);



	int i = 0;
	for(std::vector<GameObjectAnimation*>::iterator it = gameObjectAnimations->begin();
			it != gameObjectAnimations->end(); ++it) {
		GameObjectAnimation* gameObjectAnimation = *it;
		animationSurfaces[i] = (std::vector<SDL_Surface*>**) calloc(32, sizeof(std::vector<SDL_Surface*>));

		for(int j = 0; j < 32; j++) {

			int invertFlags = 0;
			if(gameObjectAnimation->types->at(j) != 0) {
				if(gameObjectAnimation->horizontalInvert.at(j)) {
					invertFlags = invertFlags | FLIP_HORIZONTAL;
				}

				if(gameObjectAnimation->verticalInvert.at(j)) {
					invertFlags = invertFlags | FLIP_VERTICAL;
				}
			}

			std::string spriteDir;

			switch(gameObjectAnimation->types->at(j)) {
			case GameObjectAnimation::NON_EXISTANT:
				animationSurfaces[i][j] = NULL;
				break;

			case GameObjectAnimation::STATIC:
				animationSurfaces[i][j] = new std::vector<SDL_Surface*>(1);

				spriteDir = std::string("objects/");
				spriteDir.append(gameObjectAnimation->sprites->at(j)->spriteFileName.c_str());

				if(invertFlags) {
					animationSurfaces[i][j]->at(0) = flipSurface(gameData->loadIMG(spriteDir), invertFlags);
				} else {
					animationSurfaces[i][j]->at(0) = gameData->loadIMG(spriteDir);
				}



				if(animationSurfaces[i][j]->at(0) == NULL) {
					fprintf(stderr, "Arquivo %s n encontrado. Abortando... \n", gameObjectAnimation->sprites->at(j)->spriteFileName.c_str());
					exit(1);
				}

				break;

			case GameObjectAnimation::ANIMATED:
				AnimationData* animationData = gameObjectAnimation->animations->at(j);
				SDL_Surface *animationSheet;
				int stepX, stepY;

                                animationDatas[i][j] = new AnimationData(*animationData);

				animationSheet = gameData->loadIMG(animationData->fileName.c_str());

				if(animationSheet == NULL) {
					fprintf(stderr, "Arquivo %s n encontrado. Abortando... \n", animationData->fileName.c_str());
					exit(1);
				}



				animationSurfaces[i][j] = new std::vector<SDL_Surface*>((animationData->endX - animationData->startX + 1)*
						(animationData->endY - animationData->startY + 1));



				stepX = (animationSheet->w - animationData->horizontalSpacing*(animationData->horizontalFrameNumber - 1))/animationData->horizontalFrameNumber;
				stepY = (animationSheet->h - animationData->verticalSpacing*(animationData->verticalFrameNumber - 1))/animationData->verticalFrameNumber;

				int k = 0;

				if(animationData->order == 0) {
					for(int x = animationData->startX - 1; x < animationData->endX; x++) {
						for(int y = animationData->startY - 1; y < animationData->endY; y++) {
							if(invertFlags) {
								animationSurfaces[i][j]->at(k) = flipSurface(cropAnimationSheet(animationSheet, x, y, stepX, stepY), invertFlags);
							} else {
								animationSurfaces[i][j]->at(k) = cropAnimationSheet(animationSheet, x, y, stepX, stepY);
							}


							k++;
						}
					}
				} else {
					for(int y = animationData->startY - 1; y < animationData->endY; y++) {
						for(int x = animationData->startX - 1; x < animationData->endX; x++) {
							if(invertFlags) {
								animationSurfaces[i][j]->at(k) = flipSurface(cropAnimationSheet(animationSheet, x, y, stepX, stepY), invertFlags);
							} else {
								animationSurfaces[i][j]->at(k) = cropAnimationSheet(animationSheet, x, y, stepX, stepY);
							}

							k++;
						}
					}
				}

				SDL_FreeSurface(animationSheet);


				break;
			}


		}

		// ajustando as direcoes nulas
		int start = -1;
		int subStart;



		// encontra um que não é null
		for(int j = 0; j < 32; j++) {
			if(animationSurfaces[i][j] != NULL) {
				start = j;
				subStart = j;
				break;
			}
		}

		if(start != -1) {
			int j;
			for(j = start + 1; j%32 != start; j++) {
				if(animationSurfaces[i][j%32] != NULL) {
					fillAnimationNulls(subStart, i, j);
					subStart = j;

				}
				//std::cout << "run: " << j << std::endl;

			}

			fillAnimationNulls(subStart, i, j);
		}





		i++;
	}

	texture = animationSurfaces[0][0]->at(0);
	std::cout << "Tamanho: " << sizeof(animationSurfaces[0][0])/sizeof(SDL_Surface*) << std::endl;

	this->pos = pos;

	// criando o rect do sprite
	rectangle.x = pos->x;
	rectangle.y = pos->y;
	rectangle.w = texture->w;
	rectangle.h = texture->h;

	width = rectangle.w;
	height = rectangle.h;


	rotAngle = 0;
	zoom = 1;
	scrollingVelocity.x = 1;
	scrollingVelocity.y = 1;

	textureRotoZoomed = NULL;
	scrollable = true;

	scrollManager = ScrollManager::getInstance();

	renderPosition.x = 0;
	renderPosition.y = 0;
	loopX = false;
	loopY = false;

	currentAnimation = 0;
	currentDirection = 0;
	currentFrame = 0;


	if(gameObjectAnimations->at(currentAnimation)->types->at(currentDirection) == GameObjectAnimation::ANIMATED) {
		frameTime = 100 - gameObjectAnimations->at(currentAnimation)->animations->at(currentDirection)->velocity;
	}


	frameTimeAcc = 0;

	isAnimation = true;


}

Sprite::~Sprite() {


	if(gameObjectAnimations != NULL) {
		for(int i = 0; i < (int)gameObjectAnimations->size(); i++) {
			for(int j = 0; j < 32; j++) {
				if(animationSurfaces[i][j] != NULL) {
					for(std::vector<SDL_Surface*>::iterator it = animationSurfaces[i][j]->begin(); it != animationSurfaces[i][j]->end(); ++it) {
						SDL_Surface *surface = *it;
						SDL_FreeSurface(surface);
					}

					animationSurfaces[i][j]->clear();
				}

			}
		}
	} else {
		SDL_FreeSurface(texture);
		if(textureRotoZoomed != NULL) {
			SDL_FreeSurface(textureRotoZoomed);
		}
	}



}

/**
 * Centraliza o determinado sprite como o centro da camera.
 */
void Sprite::setCenter() {
	scrollManager->setCenter(pos);
}

void Sprite::moveToScreenCenter() {
	GameData *gameData = GameData::getInstance();
	Rect *rect = getRectWithoutRot();

	pos->x = gameData->resWidth/2 - rect->w/2;
	pos->y = gameData->resHeight/2 - rect->h/2;


	delete rect;
}

bool Sprite::hadAnimationLoopedOnce() {
	return animationLoopedOnce;
}

bool Sprite::isSpriteAnimation() {
	return isAnimation;
}

/*
 * Função retirada dos tutoriais do LadyFoo.
 * ( http://lazyfoo.net/SDL_tutorials/lesson31/index.php )
 */
SDL_Surface* Sprite::flipSurface(SDL_Surface *surface, int flags) {
	//Pointer to the soon to be flipped surface
	SDL_Surface *flipped = NULL;

	//If the image is color keyed
	if( surface->flags & SDL_SRCCOLORKEY )
	{
		flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
	}
	//Otherwise
	else
	{
		flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
	}

	//If the surface must be locked
	if( SDL_MUSTLOCK( surface ) )
	{
		//Lock the surface
		SDL_LockSurface( surface );
	}

	//Go through columns
	for( int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx-- )
	{
		//Go through rows
		for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- )
		{

			//Get pixel
			Uint32 pixel = get_pixel32( surface, x, y );

			//Copy pixel
			if( ( flags & FLIP_VERTICAL ) && ( flags & FLIP_HORIZONTAL ) )
			{
				put_pixel32( flipped, rx, ry, pixel );
			}
			else if( flags & FLIP_HORIZONTAL )
			{
				put_pixel32( flipped, rx, y, pixel );
			}
			else if( flags & FLIP_VERTICAL )
			{
				put_pixel32( flipped, x, ry, pixel );
			}
		}
	}

	//Unlock surface
	if( SDL_MUSTLOCK( surface ) )
	{
		SDL_UnlockSurface( surface );
	}

	//Copy color key
	if( surface->flags & SDL_SRCCOLORKEY )
	{
		SDL_SetColorKey( flipped, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey );
	}

	//Return flipped surface
	return flipped;


}

void Sprite::render(Screen* screen) {
	if(gameObjectInstance == NULL) {
		rectangle.x = pos->x;
		rectangle.y = pos->y;
		render(screen->getTopScreen(), rotAngle, zoom);
	} else {
		texture = animationSurfaces[currentAnimation][currentDirection]->at(currentFrame%(animationSurfaces[currentAnimation][currentDirection]->size()));

		animationLoopedOnce = true;

		rectangle.x = pos->x;
		rectangle.y = pos->y;
		rectangle.w = texture->w;
		rectangle.h = texture->h;
		render(screen->getTopScreen(), rotAngle, zoom);
	}

}

void Sprite::renderCenter(Screen *screen) {
	rectangle.x = pos->x - rectangle.w/2;
	rectangle.y = pos->y - rectangle.h/2;
	render(screen->getTopScreen(), rotAngle, zoom);
}



void Sprite::render(SDL_Surface *screen, Uint32 rotAngle, Uint32 zoom) {
	/* se os valores de rotAngle == 0 e zoom == 1, entao nem se preocupar
	 * em rotacionar a imagem. Caso contrario, rotacionar.
	 */

	if(rotAngle == 0 && zoom == 1) {
		if(scrollable) {
			Vector2 *scrolledPosition;
			scrolledPosition = scrollManager->scrollVector(pos);
			rectangle.x = scrolledPosition->x*scrollingVelocity.x - renderPosition.x;
			rectangle.y = scrolledPosition->y*scrollingVelocity.y - renderPosition.y + pos->z;

			if(loopX) {
				if(rectangle.x > GameData::getInstance()->resWidth + rectangle.w) {
					rectangle.x = ((int)rectangle.x)%(GameData::getInstance()->resWidth) - rectangle.w;
				}
			}

			if(loopY) {
				if(rectangle.y > GameData::getInstance()->resHeight + rectangle.h) {
					rectangle.y = ((int)rectangle.y)%(GameData::getInstance()->resHeight) - rectangle.h;
				}
			}
			delete scrolledPosition;
		} else {
			rectangle.x = pos->x - renderPosition.x;
			rectangle.y = pos->y - renderPosition.y + pos->z;
		}



		SDL_BlitSurface(texture, NULL, screen, &rectangle);
	} else {
		SDL_Rect rectRot;

		rectRot = createRectRot(textureRotoZoomed);

		rectRot.y += pos->z;

		/* desenhar a surface rotacionada na tela */
		SDL_BlitSurface(textureRotoZoomed, NULL, screen, &rectRot);

	}



}


int Sprite::update(Uint32 dt) {
	this->dt = dt;
	int returnNumber = 0;

	if(gameObjectInstance != NULL &&
			animationSurfaces[currentAnimation][currentDirection]->size() > 1) {
		int frameJump;

		frameTimeAcc += dt;
		frameJump = frameTimeAcc/frameTime;
		frameTimeAcc = frameTimeAcc%frameTime;

		currentFrame += frameJump;

		if(currentFrame > (int) animationSurfaces[currentAnimation][currentDirection]->size()) {
			returnNumber = 1;
		}

		if(currentFrame >= (int) animationSurfaces[currentAnimation][currentDirection]->size()) {

                        if(animationDatas[currentAnimation][currentDirection]->hasLoop) {
                                currentFrame = (currentFrame + animationDatas[currentAnimation][currentDirection]->frameLoop)%animationSurfaces[currentAnimation][currentDirection]->size();
			} else {
				currentFrame = animationSurfaces[currentAnimation][currentDirection]->size() - 1;
			}


			//currentFrame = (currentFrame)%animationSurfaces[currentAnimation][currentDirection]->size();
		}

	}

	return returnNumber;

}


void Sprite::refreshRotoZoom() {
	if(rotAngle != rotAngleAnt || zoomAnt != zoom) {
		if(textureRotoZoomed != NULL) {
			SDL_FreeSurface(textureRotoZoomed);
		}
		textureRotoZoomed = rotozoomSurface(texture, rotAngle, zoom, 0);
		rotAngleAnt = rotAngle;
		zoomAnt = zoom;
	}
}

SDL_Surface* Sprite::cropAnimationSheet(SDL_Surface* animationSheet, int x, int y, int stepX, int stepY) {
	SDL_Surface *frameSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, stepX, stepY, 32,
			0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	SDL_Rect frameRectSrc = {x*stepX, y*stepY, stepX, stepY};
	SDL_Rect frameRectDst = {0, 0, stepX, stepY};

	if((int)animationSheet->format->BitsPerPixel == 32) {
		SDL_gfxBlitRGBA(animationSheet, &frameRectSrc, frameSurface, &frameRectDst);
	} else {
		SDL_BlitSurface(animationSheet, &frameRectSrc, frameSurface, &frameRectDst);
	}



	return frameSurface;
}

void Sprite::fillAnimationNulls(int subStart, int i, int j) {
	int subEnd;
	subEnd = j;
	int diff = subEnd - subStart;
	if(diff != 1) {
		if(diff == 2) {
			animationSurfaces[i][(subStart + 1)%32] = animationSurfaces[i][subStart%32];
		} else {
			for(int k = subStart + 1; k != (int)(diff/2) + 1 + subStart; k++) {
				animationSurfaces[i][k%32] = animationSurfaces[i][subStart%32];
				animationDatas[i][k%32] = animationDatas[i][subStart%32];
			}

			for(int k = (int)(diff/2) + subStart + 1; k != subEnd; k++) {
				animationSurfaces[i][k%32] = animationSurfaces[i][subEnd%32];
				animationDatas[i][k%32] = animationDatas[i][subEnd%32];
			}
		}
	}

}


void Sprite::setRot(float rotAngle) {
	this->rotAngle = rotAngle;
	refreshRotoZoom();
}


void Sprite::setZoom(float zoom) {
	this->zoom = zoom;
	refreshRotoZoom();
}


void Sprite::setRotoZoom(float rotAngle, float zoom) {
	this->rotAngle = rotAngle;
	this->zoom = zoom;
	refreshRotoZoom();
}

SDL_Rect Sprite::createRectRot(SDL_Surface *textureRot) {
	SDL_Rect rectRot;

	Vector2 *scrolledPosition;
	scrolledPosition = scrollManager->scrollVector(pos);
	rectangle.x = scrolledPosition->x;
	rectangle.y = scrolledPosition->y;

	delete scrolledPosition;
	rectRot.x = rectangle.x - (textureRot->w - texture->w)/2;
	rectRot.y = rectangle.y - (textureRot->h - texture->h)/2;
	rectRot.w = textureRot->w;
	rectRot.h = textureRot->h;


	return rectRot;
}


SDL_Rect Sprite::createRectRotForCollision(SDL_Surface *textureRot) {
	SDL_Rect rectRot;

	rectangle.x = pos->x;
	rectangle.y = pos->y;
	rectRot.x = rectangle.x;
	rectRot.y = rectangle.y;
	rectRot.w = textureRot->w - (textureRot->w - texture->w)/2;
	rectRot.h = textureRot->h - (textureRot->h - texture->h)/2;

	return rectRot;
}


bool Sprite::verifyTransparentPixel(int x, int y) {
	SDL_Surface *surfaceChosen;
	if(isRotoZoomed()) surfaceChosen = textureRotoZoomed;
	else surfaceChosen = texture;

	int bpp = surfaceChosen->format->BytesPerPixel;
	//SDL_LockSurface(texture);
	Uint8 *p = (Uint8 *)surfaceChosen->pixels + y*surfaceChosen->pitch + x*bpp;


	Uint32 pixelcolor;

	switch(bpp) {
	case(1):
			pixelcolor = *p;
			break;
	case(2):
			pixelcolor = *(Uint16 *)p;
			break;
	case(3):
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				pixelcolor = p[0] << 16 | p[1] << 8 | p[2];
			} else {
				pixelcolor = p[0] | p[1] << 8 | p[2] << 16;
			}
			break;
	case(4):
			pixelcolor = *(Uint32 *)p;
			if(*(p+3) == 0) return true;
			break;
	}


	//SDL_UnlockSurface(texture);

	return (texture->format->colorkey == pixelcolor);
}

bool Sprite::blockCollidesWith(Sprite *sprite) {
	Rect *r1, *r2;
	bool returnValue;
	r1 = getRectWithoutRot();
	r2 = sprite->getRectWithoutRot();

	returnValue = r1->intersectsWith(r2);

	delete r1;
	delete r2;

	return returnValue;
}

bool Sprite::pixelCollidesWith(Sprite *sprite) {
	int thisInicioX, thisInicioY, thatInicioX, thatInicioY, totalX, totalY;
	int i, j, decremento;
	Sprite *spriteThis, *spriteThat;
	Rect *thisRect, *thatRect;

	if(!this->blockCollidesWith(sprite)) return false;

	spriteThis = this;
	spriteThat = sprite;

	thisRect = this->getRect();
	thatRect = sprite->getRect();

	/* caso eixo x */
	if(thisRect->x < thatRect->x) {
		 thisInicioX = thatRect->x - thisRect->x;
		 thatInicioX = 0;
		 decremento = (thisRect->w + thisRect->x) - (thatRect->w + thatRect->x);
		 if(decremento < 0) decremento = 0;
		 totalX = thisRect->w - thisInicioX - decremento;
	} else {
		thisInicioX = 0;
		thatInicioX = thatRect->w - ((thatRect->w + thatRect->x) - thisRect->x);
		decremento = thatRect->w + thatRect->x  - (thisRect->w + thisRect->x);
		if(decremento < 0) decremento = 0;
		totalX = thatRect->w - thatInicioX - decremento;
	}

	/* caso eixo y */
	if(thisRect->y < thatRect->y) {
		 thisInicioY = thatRect->y - thisRect->y;
		 thatInicioY = 0;
		 decremento = (thisRect->h + thisRect->y) - (thatRect->h + thatRect->y);
		 if(decremento < 0) decremento = 0;
		 totalY = thisRect->h - thisInicioY - decremento;
	} else {
		thisInicioY = 0;
		thatInicioY = thatRect->h - ((thatRect->h + thatRect->y) - thisRect->y);
		decremento = thatRect->h + thatRect->y  - (thisRect->h + thisRect->y);
		if(decremento < 0) decremento = 0;
		totalY = thatRect->h - thatInicioY - decremento;
	}

	/* rodando o loop */
	for(i = 0; i < totalX; i++) {
		for(j =0; j < totalY; j++) {
			if(!spriteThis->verifyTransparentPixel(i + thisInicioX, j + thisInicioY) &&
					!spriteThat->verifyTransparentPixel(i + thatInicioX, j + thatInicioY)) {
				delete thisRect;
				delete thatRect;
				return true;
			}
		}
	}


	delete thisRect;
	delete thatRect;

	return false;
}

Rect* Sprite::getRect() {
	if(rotAngle == 0 && zoom == 1) {
		return new Rect(rectangle.x, rectangle.y, rectangle.w, rectangle.h);
	} else {
		SDL_Rect rectRot;

		rectRot = createRectRot(textureRotoZoomed);
		return new Rect(rectRot.x, rectRot.y, rectRot.w, rectRot.h);
	}

}

Rect* Sprite::getRectExact() {
	if(rotAngle == 0 && zoom == 1) {
			return new Rect(rectangle.x, rectangle.y, rectangle.w, rectangle.h);
	} else {
		SDL_Rect rectRot;

		rectRot = createRectRotForCollision(textureRotoZoomed);
		return new Rect(rectRot.x, rectRot.y, rectRot.w, rectRot.h);
	}
}

Rect* Sprite::getRectWithoutRot() {
	return new Rect(pos->x, pos->y, width, height);
}

bool Sprite::isRotoZoomed() {
	return !(rotAngle == 0 && zoom == 1);
}



void Sprite::drawLine(Vector2 *start, Vector2 *end, int r, int g, int b, int a, int translation, Screen *screen) {
	Vector2 *scrolledStart, *scrolledEnd;
	scrolledStart = ScrollManager::getInstance()->scrollVector(start);
	scrolledEnd = ScrollManager::getInstance()->scrollVector(end);
	lineRGBA(screen->getTopScreen(), scrolledStart->x + translation, scrolledStart->y + translation, scrolledEnd->x + translation, scrolledEnd->y + translation, r, g, b, a);

	delete scrolledStart;
	delete scrolledEnd;
}

int Sprite::drawFilledCircle(Vector2 *center, int radius, int r, int g, int b, int a, int translation, Screen *screen) {
	Vector2 *scrolledCenter;
	scrolledCenter = ScrollManager::getInstance()->scrollVector(center);

	int ret = filledCircleRGBA(screen->getTopScreen(), scrolledCenter->x + translation, scrolledCenter->y + translation, radius, r, g, b, a);


	delete scrolledCenter;

	return ret;

}

int Sprite::drawFilledEllipse(Vector2 *center, int rx, int ry, int r, int g, int b, int a, int translation, Screen *screen) {
	Vector2 *scrolledCenter;
	scrolledCenter = ScrollManager::getInstance()->scrollVector(center);

	int ret = filledEllipseRGBA(screen->getTopScreen(), scrolledCenter->x + translation, scrolledCenter->y + translation, rx, ry, r, g, b, a);


	delete scrolledCenter;

	return ret;
}

void Sprite::drawRectNoScrolling(Rect rect, int r, int g, int b, int a, Screen *screen) {
	boxRGBA(screen->getTopScreen(),
			rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, r, g, b, a);
}



void Sprite::setScrollingVelocity(float velocity) {
	this->scrollingVelocity.x = velocity;
	this->scrollingVelocity.y = velocity;
}

void Sprite::setScrollingVelocity(float x, float y) {
	this->scrollingVelocity.x = x;
	this->scrollingVelocity.y = y;
}

void Sprite::setScrollable(bool scrollable) {
	this->scrollable = scrollable;
}


void Sprite::setLoop(bool loopX, bool loopY) {
	this->loopX = loopX;
	this->loopY = loopY;
}

void Sprite::setAnimation(int animation) {

	if(animation > (int)gameObjectAnimations->size() - 1) {
		currentAnimation = 0;
	} else {
		currentAnimation = animation;
	}




	while(animationSurfaces[currentAnimation][currentDirection] == NULL) {
		switch(currentAnimation) {
		case ESTADO_ANDANDO:
			currentAnimation = ESTADO_PARADO;
			break;
		case ESTADO_CORRENDO:
			currentAnimation = ESTADO_ANDANDO;
			break;
		case ESTADO_PULANDO:
			currentAnimation = ESTADO_ANDANDO;
			break;
		case ESTADO_CAINDO:
			currentAnimation = ESTADO_PULANDO;
			break;
		case ESTADO_ATACANDO:
			currentAnimation = ESTADO_PARADO;
			break;
		default:
			currentAnimation = ESTADO_PARADO;
			break;

		}
	}

	if(gameObjectAnimations->at(currentAnimation)->types->at(currentDirection) == GameObjectAnimation::ANIMATED) {
		frameTime = 100 - gameObjectAnimations->at(currentAnimation)->animations->at(currentDirection)->velocity;
	}

}

void Sprite::setDirection(int direction) {
	if(direction > 31) {
		currentDirection = 0;
	} else {
		currentDirection = direction;
	}


	if(gameObjectAnimations->at(currentAnimation)->types->at(currentDirection) == GameObjectAnimation::ANIMATED) {
		frameTime = 100 - gameObjectAnimations->at(currentAnimation)->animations->at(currentDirection)->velocity;
	}
}

void Sprite::setDirectionAngleDegrees(commtypes::real angle) {
	int index;

	angle = (int)angle%360;
	if(angle < 0) {
		angle += 360;
	}

	index = ((float)((int)angle%360)/(359.0f))*32;


	setDirection(index);

}

void Sprite::setRenderPositionCenter() {
	renderPosition.x = rectangle.w/2;
	renderPosition.y = rectangle.h/2;
}

void Sprite::drawTriangleNoScrolling(Vector2 pl, Vector2 pr, Vector2 pd, int r, int g, int b, int a, Screen *screen) {
	trigonRGBA(screen->getTopScreen(), pl.x, pl.y, pr.x, pr.y, pd.x, pd.y, r, g, b, a);


}

/**
 * Desenhador de RectNoScrolling retirado da SDL_gfx mais nova.
 */
int Sprite::drawRoundRectNoScrolling(Rect rect, int r, int g, int b, int a, int rad, Screen *screen) {
	SDL_Surface * dst;
	Sint16 x1, y1, x2, y2;
	Uint32 color;
	int result;

	dst = screen->getTopScreen();
	x1 = rect.x;
	x2 = rect.x + rect.w;
	y1 = rect.y;
	y2 = rect.y + rect.h;

	color = ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a;

	Sint16 w, h, tmp;
	Sint16 xx1, xx2, yy1, yy2;

	/*
	* Check destination surface
	*/
	if (dst == NULL)
	{
		return -1;
	}

	/*
	* Check radius vor valid range
	*/
	if (rad < 0) {
		return -1;
	}

	/*
	* Special case - no rounding
	*/
	if (rad == 0) {
		return rectangleColor(dst, x1, y1, x2, y2, color);
	}

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return 0;
	}

	/*
	* Test for special cases of straight lines or single point
	*/
	if (x1 == x2) {
		if (y1 == y2) {
			return (pixelColor(dst, x1, y1, color));
		} else {
			return (vlineColor(dst, x1, y1, y2, color));
		}
	} else {
		if (y1 == y2) {
			return (hlineColor(dst, x1, x2, y1, color));
		}
	}

	/*
	* Swap x1, x2 if required
	*/
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	/*
	* Swap y1, y2 if required
	*/
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	/*
	* Calculate width&height
	*/
	w = x2 - x1;
	h = y2 - y1;

	/*
	* Maybe adjust radius
	*/
	if ((rad * 2) > w)
	{
		rad = w / 2;
	}
	if ((rad * 2) > h)
	{
		rad = h / 2;
	}

	/*
	* Draw corners
	*/
	result = 0;
	xx1 = x1 + rad;
	xx2 = x2 - rad;
	yy1 = y1 + rad;
	yy2 = y2 - rad;
	result |= arcColor(dst, xx1, yy1, rad, 180, 270, color);
	result |= arcColor(dst, xx2, yy1, rad, 270, 360, color);
	result |= arcColor(dst, xx1, yy2, rad,  90, 180, color);
	result |= arcColor(dst, xx2, yy2, rad,   0,  90, color);

	/*
	* Draw lines
	*/
	if (xx1 <= xx2) {
		result |= hlineColor(dst, xx1, xx2, y1, color);
		result |= hlineColor(dst, xx1, xx2, y2, color);
	}
	if (yy1 <= yy2) {
		result |= vlineColor(dst, x1, yy1, yy2, color);
		result |= vlineColor(dst, x2, yy1, yy2, color);
	}

	return 1;

}

/*
 * Função retirada dos tutoriais do LazyFoo.
 * ( http://lazyfoo.net/SDL_tutorials/lesson31/index.php )
 */
Uint32 Sprite::get_pixel32(SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}


/*
 * Função retirada dos tutoriais do LadyFoo.
 * ( http://lazyfoo.net/SDL_tutorials/lesson31/index.php )
 */
void Sprite::put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}
