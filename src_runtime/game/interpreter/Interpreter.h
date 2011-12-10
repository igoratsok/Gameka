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
#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#define PAIRLIST std::list<std::vector<GameObject*> >

#include <stack>
#include <list>
#include <algorithm>
#include <deque>

#include "GameObjectClass.h"
#include "EventData.h"
#include "ProcedureData.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "TimerManager.h"

class GameObjectClass;
class EventData;
class ProcedureData;
class GameObject;
class InputManager;
class SoundManager;
class TimerManager;


/**
 * @brief Interpretador de eventos.
 * O módulo de interpretador foi implementado na classe Interpreter,
 * contendo todo o mecanismo de interpretação de eventos e também todas as funções
 * contendo as instruções das condições e ações especificadas. Através de uma
 * instância dessa classe, é possível executar o seu método executeProcedure() passando como parâmetro um objeto da
 * classe ProcedureData para que um procedimento seja interpretado.
 *
 */
class Interpreter {
public:
	Interpreter();
	Interpreter(GameObject *thisGameObject);
	virtual ~Interpreter();

        /**
         * @brief Executa um procedimento.
         *
         * @param procedureData
         * @param dt
         */
        void executeProcedure(ProcedureData *procedureData, int dt);


	static PAIRLIST* setValue(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* addValue(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* multValue(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* divValue(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* playMusic(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* pauseResumeMusic(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* stopMusic(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* playSound(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* pauseResumeSound(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* stopSound(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* changeMap(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* resetCurrentMap(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* nextMap(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);


	static PAIRLIST* callProcedure(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* resetMapTimer(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* resetGlobalTimer(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* plataformerJump(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* bounce(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* boost(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* throwObject(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* followObject(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* unfollowObject(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* equalThan(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* differentThan(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* lessThan(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* lessOrEqualThan(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* greaterThan(EventData* eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* greaterOrEqualThan(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* collidesSimpleWith(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* collidesPixelWith(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);


	static PAIRLIST* buttonDown(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* buttonInstantPress(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* mouseDown(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* mouseInstantPress(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* isCurrentMap(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* isObjectLeftSide(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* isObjectUpSide(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* isObjectRightSide(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* isObjectDownSide(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* isSoundPlaying(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);
	static PAIRLIST* isMusicPlaying(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);


	static PAIRLIST* everySeconds(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);

	static PAIRLIST* executeDialogue(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt);


        std::stack<std::list<EventData*>::iterator> iteratorStack; /**< Stack de iterators. */
        std::stack<std::list<EventData*>*> eventStack; /**< Stack de eventos. */
        std::stack<PAIRLIST* > pairListStack; /**< Stack de lista de pares. */
        std::deque<std::vector<GameObject*> > *pairStack; /**< Lista de pares de contextos de instância. */



        GameObject *thisGameObject; /**< O objeto a que pertence o interpretador. */

        PAIRLIST *currentPairList; /**< A lista de pares atual. */

	static inline void equalThanTest(std::list<GameObject*> *values, float value,
					GameObject *gameObject, float obj1Value, EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList);
	static inline void differentThanTest(std::list<GameObject*> *values, float value,
				GameObject *gameObject, float obj1Value, EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList);
	static inline void lessThanTest(std::list<GameObject*> *values, float value,
					GameObject *gameObject, float obj1Value, EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList);
	static inline void lessOrEqualThanTest(std::list<GameObject*> *values, float value,
					GameObject *gameObject, float obj1Value, EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList);
	static inline void greaterThanTest(std::list<GameObject*> *values, float value,
					GameObject *gameObject, float obj1Value, EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList);
	static inline void greaterOrEqualThanTest(std::list<GameObject*> *values, float value,
					GameObject *gameObject, float obj1Value, EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList);


    static const int VALUE_TYPE_NUMBER = 0;
    static const int VALUE_TYPE_VARIABLE = 1;
    static const int VALUE_TYPE_OBJECT_ATTRIBUTE = 2;
    static const int VALUE_TYPE_SPECIAL = 3;
    static const int VALUE_TYPE_OBJECT2 = 4;
    static std::deque<ProcedureData*> *procedureDataStack;
};

#endif /* INTERPRETER_H_ */
