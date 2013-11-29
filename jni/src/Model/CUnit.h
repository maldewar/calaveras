#ifndef _CUNIT_H_
    #define _CUNIT_H_

#include <Box2D.h>
#include "CElem.h"
#include "../Engine/CAnimation.h"

const int UNIT_STATE_LOOSE = 0;
const int UNIT_STATE_AFOOT = 1;

const int UNIT_SUBSTATE_FALL      = 0;
const int UNIT_SUBSTATE_ROLL      = 1;
const int UNIT_SUBSTATE_JUMP_UP   = 2;
const int UNIT_SUBSTATE_JUMP_DOWN = 3;

const int UNIT_SUBSTATE_STILL     = 0;
const int UNIT_SUBSTATE_WALK      = 1;
const int UNIT_SUBSTATE_TURN      = 2;
const int UNIT_SUBSTATE_POST_FALL = 3;
const int UNIT_SUBSTATE_PRE_JUMP  = 4;
const int UNIT_SUBSTATE_POST_JUMP = 5;
const int UNIT_SUBSTATE_STAND     = 6;

/**
 * Models an Unit to the scene.
 * The Units are the main characters in the scene.
 */
class CUnit : public CElem
{
    private:
        float m_originalLinearDamping;
        float m_originalAngularDamping;
        b2Body* m_body;
        b2Fixture* m_feet;
        CAnimation* m_animation;
        int m_substate;
        static float ANGULAR_VELOCITY_TOLERANCE;
        static float LINEAR_VELOCITY_TOLERANCE;
        static float ANGULAR_VELOCITY_HAND_TOLERANCE;
        static float ANGULAR_VELOCITY_HAND_REDUCE;

    public:
        /**
         * Class constructor.
         */
        CUnit();
        /**
         * Class constructor.
         * Binds this Unit to its parent Layer.
         * @param layer Parent Layer.
         */
        CUnit(Layer* layer);
        /**
         * Class destructor.
         */
        ~CUnit();
        void SetOriginalLinearDamping(float linearDamping);
        void SetOriginalAngularDamping(float angularDamping);
        /**
         * Sets the Box2D body for this Unit.
         */
        void SetBody();
        /**
         * Gets the Box2D body for this Unit.
         */
        b2Body* GetBody();
        /**
         * Sets the animation for the Unit state using the Animation Catalog.
         */
        void SetAnimation();
        /**
         * Sets the substate.
         * @param substate Substate value.
         */
        void SetSubstate(int substate);
        /**
         * Gets the substate.
         * @return Substate value.
         */
        int GetSubstate();
        /**
         * Gets the Animation instance for this Unit's actual state.
         * @return Animation instance for this Unit's actual state.
         */
        CAnimation* GetAnimation();
        /**
         * Initialization function for this Unit.
         */
        void OnInit();
        /**
         * Processing for each game loop.
         */
        void OnLoop();

        void BeginContact(int thisSensor, CArea* area, int areaSensor);
        void EndContact(int thisSensor, CArea* area, int areaSensor);

        void StandUp();

};
#endif
