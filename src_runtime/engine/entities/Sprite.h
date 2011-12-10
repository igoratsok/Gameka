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

#ifndef SPRITE_H_
#define SPRITE_H_

#include "SDL.h"
#include "SDL/SDL_video.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_gfxBlitFunc.h"
#include "SDL/SDL_rotozoom.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#include "Rectangle.h"
#include "Vector2.h"
#include "ScrollManager.h"
#include "Screen.h"
#include "GameObjectInstance.h"
#include "Util.h"
#include "ArrayCreator.h"

class Rect;
class Vector2;
class ScrollManager;
class Screen;
class GameObjectInstance;
class Util;

using namespace std;




/**
 * @brief Classe Sprite. Responsável por mostrar uma imagem
 * na tela (deve ser renderizado passando por parâmetro
 * a Screen do jogo).
 *
 * Também possui métodos para rotação e zoom.
 *
 */
class Sprite {
public:
        /**
         * @brief Construtor.
         *
         * @param nomeArquivo Nome do arquivo da imagem.
         * @param pos Posição.
         */
        Sprite(string *nomeArquivo, Vector2 *pos);
        /**
         * @brief Construtor.
         *
         * @param nome Arquivo Nome do arquivo da animação.
         * @param pos Posição.
         * @param nframes Número de quadros.
         * @param spacing Espaçamento dos quadros.
         */
        Sprite(string *nomeArquivo, Vector2 *pos, int nframes, int spacing);
        /**
         * @brief Construtor.
         *
         * @param gameObjectInstance Arquivo de GameObjectInstance criado pelo editor.
         * @param pos
         */
        Sprite(GameObjectInstance *gameObjectInstance, Vector2 *pos);
        /**
         * @brief
         *
         */
        virtual ~Sprite();

        /**
         * @brief Calcula o próximo quadro da animação, caso seja uma.
         *
         * @param dt
         */
        int update(Uint32 dt);

        /**
         * Renderiza o sprite na tela.
         *
         * @param screen tela na qual o sprite sera renderizado
         *
         * @return void
         */
        void render(Screen *screen);
        /**
         * @brief Renderiza pelo centro do quadro.
         *
         * @param screen
         */
        void renderCenter(Screen *screen);


        /**
         * @brief Obtém o retângulo da imagem.
         *
         */
        Rect* getRect();
        /**
         * @brief Obtém o retângulo exato para colisão.
         *
         */
        Rect* getRectExact();
        /**
         * @brief Obtém o retângulo sem considerar rotação.
         *
         */
        Rect* getRectWithoutRot();

        /**
         * @brief Determina rotação.
         *
         * @param rotAngle Ângulo em graus.
         */
        void setRot(float rotAngle);
        /**
         * @brief Determina zoom.
         *
         * @param zoom Zoom. 1 é o valor
         * padrao.
         */
        void setZoom(float zoom);
        /**
         * @brief Determina rotação e zoom.
         *
         * @param rotAngle Ângulo em graus.
         * @param zoom Zoom.  1 é o valor padrão.
         */
        void setRotoZoom(float rotAngle, float zoom);
        /**
         * @brief Verifica um pixel transparente no sprite.
         */
        bool verifyTransparentPixel(int x, int y);
        /**
         * @brief Verifica colisão por blocos com outro Sprite.
         *
         * @param sprite O outro Sprite.
         */
        bool blockCollidesWith(Sprite *sprite);
        /**
         * @brief Verifica colisão por píxel com outro Sprite.
         *
         * @param sprite O outro sprite.
         */
        bool pixelCollidesWith(Sprite *sprite);
        /**
         * @brief Mostra posição de acordo com a câmera ou não.
         *
         * @param scrollable
         */
        void setScrollable(bool scrollable);
        /**
         * @brief Se está rotacionado ou com zoom.
         *
         */
        bool isRotoZoomed();
        /**
         * @brief Determina o centro.
         *
         */
        void setCenter();

        /**
         * @brief Move para o centro da tela.
         *
         */
        void moveToScreenCenter();

        /**
         * @brief Se teve a animação repetida uma vez.
         *
         */
        bool hadAnimationLoopedOnce();
        /**
         * @brief Se é uma animação.
         *
         */
        bool isSpriteAnimation();

        /**
         * @brief Inverte a imagem.
         * Função retirada dos tutoriais do LadyFoo.
         * ( http://lazyfoo.net/SDL_tutorials/lesson31/index.php )
         *
         * @param surface
         * @param flags
         */
        SDL_Surface *flipSurface(SDL_Surface *surface, int flags);

        /**
         * @brief Determina velocidade de scrolling.
         *
         * @param velocity
         */
        void setScrollingVelocity(float velocity);
        /**
         * @brief Determina velocidade de scrolling em ambos eixos.
         *
         * @param x Velocidade no eixo x.
         * @param y Velocidade no eixo y.
         */
        void setScrollingVelocity(float x, float y);
        /**
         * @brief Determina o centro como a posição de renderização.
         *
         */
        void setRenderPositionCenter();

        /**
         * @brief Determina repetição em um eixo.
         *
         * @param loopX
         * @param loopY
         */
        void setLoop(bool loopX, bool loopY);

        /**
         * @brief Determina o número da animação em execução.
         *
         * @param animation Número da animação.
         */
        void setAnimation(int animation);
        /**
         * @brief Determina a direção da animação.
         *
         * @param direction A direção da animação.
         */
        void setDirection(int direction);
        /**
         * @brief Determina o ângulo da animação.
         *
         * @param angle
         */
        void setDirectionAngleDegrees(commtypes::real angle);

        /**
         * @brief Desenha uma linha.
         *
         * @param start Início da linha.
         * @param end Fim da linha.
         * @param r Intensidade da cor vermelha (0, 255)
         * @param g Intensidade da cor verde (0, 255)
         * @param b Intensidade da cor azul (0, 255)
         * @param a Intensidade do canal alpha, transparência (0, 255)
         * @param translation
         * @param screen Tela do jogo.
         */
        static void drawLine(Vector2 *start, Vector2 *end, int r, int g, int b, int a, int translation, Screen *screen);
        /**
         * @brief
         *
         * @param center Centro do círculo.
         * @param radius Raio.
         * @param r Intensidade da cor vermelha (0, 255)
         * @param g Intensidade da cor verde (0, 255)
         * @param b Intensidade da cor azul (0, 255)
         * @param a Intensidade do canal alpha, transparência (0, 255)
         * @param translation
         * @param screen Tela do jogo.
         */
        static int drawFilledCircle(Vector2 *center, int radius, int r, int g, int b, int a, int translation, Screen *screen);
        /**
         * @brief
         *
         * @param center Centro da elipse.
         * @param rx Raio no eixo X.
         * @param ry Raio no eixo Y
         * @param r Intensidade da cor vermelha (0, 255)
         * @param g Intensidade da cor verde (0, 255)
         * @param b Intensidade da cor azul (0, 255)
         * @param a Intensidade do canal alpha, transparência (0, 255)
         * @param translation
         * @param screen Tela do jogo.
         */
        static int drawFilledEllipse(Vector2 *center, int rx, int ry, int r, int g, int b, int a, int translation, Screen *screen);

        /**
         * @brief Desenha um retângulo sem scroll.
         *
         * @param rect Retângulo
         * @param r Intensidade da cor vermelha (0, 255)
         * @param g Intensidade da cor verde (0, 255)
         * @param b Intensidade da cor azul (0, 255)
         * @param a Intensidade do canal alpha, transparência (0, 255)
         * @param screen Tela do jogo.
         */
        static void drawRectNoScrolling(Rect rect, int r, int g, int b, int a, Screen *screen);

        /**
         * @brief Desenha um retângulo arredondado sem scroll.
         *
         * @param rect
         * @param r Intensidade da cor vermelha (0, 255)
         * @param g Intensidade da cor verde (0, 255)
         * @param b Intensidade da cor azul (0, 255)
         * @param a Intensidade do canal alpha, transparência (0, 255)
         * @param rad
         * @param screen Tela do jogo.
         */
        static int drawRoundRectNoScrolling(Rect rect, int r, int g, int b, int a, int rad, Screen *screen);
        /**
         * @brief Desenha um trigângulo sem scroll.
         *
         * @param pl Ponto da esquerda
         * @param pr Ponto da direita
         * @param pd Ponto de cima ou baixo
         * @param r Intensidade da cor vermelha (0, 255)
         * @param g Intensidade da cor verde (0, 255)
         * @param b Intensidade da cor azul (0, 255)
         * @param a Intensidade do canal alpha, transparência (0, 255)
         * @param screen Tela do jogo.
         */
        static void drawTriangleNoScrolling(Vector2 pl, Vector2 pr, Vector2 pd, int r, int g, int b, int a, Screen *screen);



        SDL_Surface *texture; /**< SDL_Surface da Sprite. */

        Vector2 *pos; /**< Posição. */
        Uint32 dt; /**< Tempo de frame. */
        float rotAngle, zoom; /**<  */
        bool scrollable; /**<  */
        bool loopX; /**< Se repete no eixo x */
        bool loopY; /**< Se repete no eixo y */
        Vector2 scrollingVelocity; /**< Velocidade do scrolling */
        Vector2 renderPosition; /**< Posição de renderização. */
        int width, height; /**<  */

        std::vector<SDL_Surface*> ***animationSurfaces; /**< Surfaces de animação. */
        AnimationData*** animationDatas; /**< Dados de animação. */

        static const int FLIP_HORIZONTAL = 0x00000001; /**< Flags para inverter os lados de uma surface. */
        static const int FLIP_VERTICAL = 0x00000010; /**< Flags para inverter os lados de uma surface. */
private:
        float rotAngleAnt, zoomAnt; /**< TODO */
        /**
         * @brief Renderiza o sprite na tela conforme um angulo e zoom.
         *
         * @param screen a tela na qual o sprite sera renderizado
         * @param rotAngle o angulo de renderizacao
         * @param zoom o zoom de renderizacao
         *
         * @return void
         */
        void render(SDL_Surface *screen, Uint32 rotAngle, Uint32 zoom);

        /**
         * @brief Cria um retangulo para o objeto rotacionado em
         * sua posicao correta, de forma a centralizar a
         * rotacao.
         *
         * @param textureRot a textura rotacionada
         *
         * @return rectRot o SDL_Rect da textura rotacionada
         */
        SDL_Rect createRectRot(SDL_Surface *textureRot);
        /**
         * @brief Cria um retangulo para o objeto rotacionado em
         * sua posicao de forma a permitir colisao entre
         * blocos.
         *
         * @param textureRot a textura rotacionada
         *
         * @return rectRot o SDL_Rect da textura rotacionada
         */
        SDL_Rect createRectRotForCollision(SDL_Surface *textureRot);
        /**
         * @brief Recalcula as surfaces com zoom e rotação.
         *
         */
        void refreshRotoZoom();

        /**
         * @brief Corta uma animação.
         *
         * @param animationSheet A surface da animação.
         * @param x Posição x de corte.
         * @param y Posição y de corte.
         * @param stepX Largura do corte.
         * @param stepY Altura do corte.
         */
        SDL_Surface *cropAnimationSheet(SDL_Surface* animationSheet, int x, int y, int stepX, int stepY);
        /**
         * @brief Preenche os nulos da animação.
         *
         * @param subStart
         * @param i
         * @param j
         */
        void fillAnimationNulls(int subStart, int i, int j);


        /**
         * @brief Obtém um pixel de uma surface.
         *
         * Função retirada dos tutoriais do LadyFoo.
         * ( http://lazyfoo.net/SDL_tutorials/lesson31/index.php )
         *
         * @param surface
         * @param x
         * @param y
         */
        Uint32 get_pixel32(SDL_Surface *surface, int x, int y );
        /**
         * @brief Coloca um pixel em uma surface.
         * Função retirada dos tutoriais do LadyFoo.
         * ( http://lazyfoo.net/SDL_tutorials/lesson31/index.php )
         *
         * @param surface
         * @param x
         * @param y
         * @param pixel
         */
        void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel );

        SDL_Rect rectangle; /**< Retângulo da sprite. */
        SDL_Surface *textureRotoZoomed; /**< Textura rotacionada e com zoom */
        ScrollManager *scrollManager; /**<  */

        int frameTime, frameTimeAcc; /**< Tempo do frame acumulado. */
        int currentAnimation, currentDirection, currentFrame; /**<  */

        bool animationLoopedOnce; /**< Se animação repetiu uma vez. */
        bool isAnimation; /**< Se é uma animação. */


        GameObjectInstance *gameObjectInstance; /**< Instância do objeto associada. */

        std::vector<GameObjectAnimation*> *gameObjectAnimations; /**< Animações. */

        static const int ESTADO_PARADO = 0; /**<  */
        static const int ESTADO_ANDANDO = 1; /**<  */
        static const int ESTADO_CORRENDO = 2; /**<  */
        static const int ESTADO_PULANDO = 3; /**<  */
        static const int ESTADO_CAINDO = 4; /**<  */
        static const int ESTADO_ATACANDO = 5; /**<  */
        static const int ESTADO_LEVANDO_DANO = 6; /**<  */
        static const int ESTADO_MORRENDO = 7; /**<  */

};

#endif /* SPRITE_H_ */
