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

#ifndef GAMEOBJECTCLASS_H_
#define GAMEOBJECTCLASS_H_

#include <string>
#include <iostream>
#include <vector>
#include <list>

#include "GameObjectAnimation.h"
#include "SkillData.h"
#include "ProcedureData.h"
#include "VariableData.h"
#include "GameObject.h"

class GameObjectAnimation;
class SkillData;
class ProcedureData;
class VariableData;
class GameObject;

/**
 * @brief Entidade para representar uma classe de objeto.
 *
 */
class GameObjectClass {
public:
	GameObjectClass();
	virtual ~GameObjectClass();

	ProcedureData *getProcedureById(int id);
	VariableData *getVariableById(int id);



	static const int EIGHT_MOVEMENT_OBJECT = 0;
	static const int CAR_MOVEMENT_OBJECT = 1;
	static const int PLATFORM_MOVEMENT_OBJECT = 2;
	static const int FIGHTING_MOVEMENT_OBJECT = 3;
	static const int PONG_BALL_OBJECT = 4;
	static const int MOUSE_MOVEMENT_OBJECT = 5;
	static const int STATIC_OBJECT = 6;
	static const int NPC = 7;
	static const int INIMIGO = 8;
	static const int ITEM = 9;


	int id; /**< Número identificador. */
	std::string name;  /**< Nome da classe do objeto. */
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

	/* lista de objetos que o BouncingBall pode colidir */
	std::list<GameObjectClass*> listObjectsToBounce;

	std::vector<bool> *arrayObjectsToBounce;

	std::list<std::pair<int, int> > levelSkills;


	bool isObjetoUnico; /**< Se é objeto único (não mais utilizado) */
	int formaGrafica; /**< Forma gráfica (não mais utilizado). */
	int tipoMovimento; /**< Tipo de movimento de NPC. */
	int formaMovimentoMouse; /**< Forma de movimento do mouse. */
	float vx, vy, ax, ay, dax, day; /**< Velocidade, aceleração e desaceleração nos eixos */
	float gravidade;
	int intensidadePulo;
	bool evolucaoPorNivel; /**< Se possui evolução pro nível. */

	bool isDraggable;

	std::vector<GameObjectAnimation*> *gameObjectAnimations;

	std::string getIconString();


	/* novos dados - atributos - pendentes de gravacao */
	int hp, mp, atk, def, intelig;
	int levelInicial, levelMax;
	int velocidadeEvolucao;
	bool resolveCollision;

	bool movimentaApenasDentroTela;

	/* para uso comum de Item, NPC e Inimigo  */
	int formaMovimentacaoNpcItem;
	int raioMovimentacao;

	/* comportamento Inimigo */

	bool derrotaEncostandoInimigo;
	bool derrotaAtirandoItemMagiaInimigo;
	bool derrotaAcertandoEspadaSobreInimigo;
	bool derrotaPulandoSobreInimigo;
	bool atacaEncostaPersonagem;
	int atacaEncostaPersonagemDano;
	bool atacaUsandoEspada;
	int espadaItemId;
	int atacaUsandoEspadaDano;

	bool atiraItemMaginaDirecaoEstiver;
	int atiraItemMaginaDirecaoEstiverIdItem;
	int atiraItemMaginaDirecaoEstiverDano;

	bool atiraItemMagiaDirecaoPersonagem;
	int atiraItemMagiaDirecaoPersonagemIdItem;
	int atiraItemMagiaDirecaoPersonagemDano;

	int experiencePoints;
	int defeatPoints;


	int magicCost;
	float tempoAtaque;

	/* apenas NPC */
	int nroFalas;

	/* dados Item */
	bool concedePontos;
	int concedePontosValor;
	bool ganhaPerdeVida;
	int ganhaPerdeVidaValor;
	bool ganhaPerdeMagia;
	int ganhaPerdeMagiaValor;
	bool incrementaVariavel;
	int incrementaVariavelIdVariavel;
	VariableData *incrementaVariavelVariable;
	int incrementaVariavelValor;
	bool ativaEvento;
	int ativaEventoIdEvento;
	ProcedureData *ativaEventoProcedure;
	bool concedeHabilidade;
	int concedeHabilidadeIdHabilidade;

	int comportamentoEncostarPersonagem;
	bool desapareceEncostarPersonagem;
	bool desapareceEncostarParede;



	/* geral */
	std::vector<SkillData*> listaHabilidades; /**<  Lista de habilidades dos objetos. */

	bool possuiEventos;  /**< Se possui eventos. */

	std::string soundDamage; /**< Arquivo de som de dano. */
	std::string soundSpecial;  /**< Arquivo de som especial. */

	ProcedureData *procedureGlobalAlways; /**< Procedimento "Sempre" */
	ProcedureData *procedureGlobalStart; /**< Procedimento "Início" */
	ProcedureData *procedureGlobalEnd; /**< Procedimento "Fim" */


	std::vector<ProcedureData*> *procedureList; /**< Lista de procedimentos. */
	std::vector<VariableData*> *variableList; /**< Lista de variáveis. */



	std::list<GameObject*> *instances; /**< Instâncias criadas dessa classe. */

	std::list<std::pair<int, GameObjectClass*> > itemSkills; /**< Habilidades que um Item pode ter. */

	int currentLevel; /**< Nível atual dos objetos nessa classe. */
	int currentExperiencePoints; /**< Pontos de experiência atual dos objetos nessa classe. */
	std::vector<bool> *obtainedItems; /**< Itens que os objetos dessa classe obtiveram. */

};

#endif /* GAMEOBJECTCLASS_H_ */
