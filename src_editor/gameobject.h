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


#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <QPixmap>
#include <QImage>

#include "gamedata.h"
#include "sprite.h"
#include "gameobjectanimation.h"
#include "skilldata.h"
#include "proceduredata.h"
#include "variabledata.h"
#include "dialoguedata.h"

class GameData;
class Sprite;
class GameObjectAnimation;
class SkillData;
class ProcedureData;
class VariableData;
class DialogueData;

/**
 * @brief Entidade para representar uma classe de objeto.
 *
 */
class GameObject
{
public:
    /**
     * @brief
     *
     */
    GameObject();
    /**
     * @brief Construtor.
     *
     * @param specialId Identificador especial.
     */
    GameObject(int specialId);

    /**
     * @brief Inicializa todas as variáveis com valores padrão.
     *
     */
    void initVariables();
    /**
     * @brief Reinicia o objeto em um novo tipo.
     *
     * @param newType
     */
    void reset(int newType);


    static const int EIGHT_MOVEMENT_OBJECT = 0; /**<  */
    static const int CAR_MOVEMENT_OBJECT = 1; /**<  */
    static const int PLATFORM_MOVEMENT_OBJECT = 2; /**<  */
    static const int FIGHTING_MOVEMENT_OBJECT = 3; /**<  */
    static const int PONG_BALL_OBJECT = 4; /**<  */
    static const int MOUSE_MOVEMENT_OBJECT = 5; /**<  */
    static const int STATIC_OBJECT = 6; /**<  */
    static const int NPC = 7; /**<  */
    static const int INIMIGO = 8; /**<  */
    static const int ITEM = 9; /**<  */
    static const int SPECIAL = 10; /**<  */


    int id; /**< Número identificador. */
    std::string name; /**< Nome da classe do objeto. */
    std::string specialIconPath; /**< Nome do arquivo do ícone especial (caso seja um objeto especial). */
    int type; /**< Tipo: \n
                    - 0 (EIGHT_MOVEMENT_OBJECT): Movimento em oito direções;
                    - 1 (CAR_MOVEMENT_OBJECT): Movimento de carro;
                    - 2 (PLATFORM_MOVEMENT_OBJECT): Movimento de carro;
                    - 3 (FIGHTING_MOVEMENT_OBJECT): Movemento de luta (não implementado);
                    - 4 (PONG_BALL_MOVEMENT): Movimento de bola saltitante;
                    - 5 (MOUSE_MOVEMENT_OBJECT): Movimento com o mouse;
                    - 6 (STATIC_OBJECT): Objeto estático;
                    - 7 (NPC): NPC aliado;
                    - 8 (INIMIGO): NPC inimigo;
                    - 9 (ITEM): Item;
                    - 10 (SPECIAL): Objeto especial     */


    bool isObjetoUnico; /**< Se é objeto único (não mais utilizado) */
    int formaGrafica; /**< Forma gráfica (não mais utilizado). */
    int tipoMovimento; /**< Tipo de movimento de NPC. */
    int formaMovimentoMouse; /**< Forma de movimento do mouse. */
    float vx, vy, ax, ay, dax, day; /**< Velocidade, aceleração e desaceleração nos eixos */
    float gravidade;
    int intensidadePulo;
    bool evolucaoPorNivel; /**< Se possui evolução pro nível. */

    bool isDraggable; /**<  */

    std::vector<GameObjectAnimation*> *gameObjectAnimations; /**<  */

    /**
     * @brief
     *
     */
    std::string getIconString();
    /**
     * @brief
     *
     */
    QImage getIconImage();

    /* lista de objetos que o BouncingBall pode colidir */
    std::list<GameObject*> listObjectsToBounce; /**<  */


    /* novos dados - atributos - pendentes de gravacao */
    int hp, mp, atk, def, intelig; /**<  */
    int levelInicial, levelMax; /**<  */
    int velocidadeEvolucao; /**<  */
    bool resolveCollision; /**<  */

    bool movimentaApenasDentroTela; /**<  */

    /* para uso comum de Item, NPC e Inimigo  */
    int formaMovimentacaoNpcItem; /**<  */
    int raioMovimentacao; /**<  */

    /* comportamento Inimigo */

    bool derrotaEncostandoInimigo; /**<  */
    bool derrotaAtirandoItemMagiaInimigo; /**<  */
    bool derrotaAcertandoEspadaSobreInimigo; /**<  */
    bool derrotaPulandoSobreInimigo; /**<  */
    bool atacaEncostaPersonagem; /**<  */
    int atacaEncostaPersonagemDano; /**<  */
    bool atacaUsandoEspada; /**<  */
    int espadaItemId; /**<  */
    int atacaUsandoEspadaDano; /**<  */

    bool atiraItemMaginaDirecaoEstiver; /**<  */
    int atiraItemMaginaDirecaoEstiverIdItem; /**<  */
    int atiraItemMaginaDirecaoEstiverDano; /**<  */

    bool atiraItemMagiaDirecaoPersonagem; /**<  */
    int atiraItemMagiaDirecaoPersonagemIdItem; /**<  */
    int atiraItemMagiaDirecaoPersonagemDano; /**<  */

    int experiencePoints; /**<  */
    int defeatPoints; /**<  */


    int magicCost; /**<  */
    float tempoAtaque; /**<  */

    /* apenas NPC */
    int nroFalas; /**<  */

    /* dados Item */
    bool concedePontos; /**<  */
    int concedePontosValor; /**<  */
    bool ganhaPerdeVida; /**<  */
    int ganhaPerdeVidaValor; /**<  */
    bool ganhaPerdeMagia; /**<  */
    int ganhaPerdeMagiaValor; /**<  */
    bool incrementaVariavel; /**<  */
    int incrementaVariavelIdVariavel; /**<  */
    int incrementaVariavelValor; /**<  */
    bool ativaEvento; /**<  */
    int ativaEventoIdEvento; /**<  */
    bool concedeHabilidade; /**<  */
    int concedeHabilidadeIdHabilidade; /**<  */

    int comportamentoEncostarPersonagem; /**<  */
    bool desapareceEncostarPersonagem; /**<  */
    bool desapareceEncostarParede; /**<  */



    /* geral */
    std::vector<SkillData*> listaHabilidades; /**<  Lista de habilidades dos objetos. */

    bool possuiEventos; /**< Se possui eventos. */


    std::string soundDamage; /**< Arquivo de som de dano. */
    std::string soundSpecial; /**< Arquivo de som especial. */


    ProcedureData *procedureGlobalAlways; /**< Procedimento "Sempre" */
    ProcedureData *procedureGlobalStart; /**< Procedimento "Início" */
    ProcedureData *procedureGlobalEnd; /**< Procedimento "Fim" */

    std::vector<ProcedureData*> *procedureList; /**< Lista de procedimentos. */
    std::vector<VariableData*> *variableList; /**< Lista de variáveis. */


    /**
     * @brief Adiciona um procedimento.
     *
     * @param procedureData
     */
    void addProcedure(ProcedureData *procedureData);
    /**
     * @brief Adiciona uma variável.
     *
     * @param variableData
     */
    void addVariable(VariableData *variableData);
    /**
     * @brief Obtém procedimento pelo identificador.
     *
     * @param id
     */
    ProcedureData *getProcedureById(int id);
    /**
     * @brief Obtém variável pelo identificador.
     *
     * @param id
     */
    VariableData *getVariableById(int id);


    /**
     * @brief Verifica se o objeto possui apenas uma animação.
     *
     * @return  true,   caso ele tenha apenas um AnimationData e nenhum Sprite;
     *          false,  caso contrário.
     */
    bool verifyIfOnlyOneAnimation();





private:
    /**
     * @brief Gera novo identificador para procedimento.
     *
     */
    int generateNewProcedureId();
    /**
     * @brief Gera novo identificador para variável.
     *
     */
    int generateNewVariableId();

};

#endif // GAMEOBJECT_H
