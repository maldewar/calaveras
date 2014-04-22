#ifndef _UNIT_H_
    #define _UNIT_H_

#include <Box2D.h>
#include "LayeredElem.h"
#include "../Engine/Animation.h"

const int UNIT_STATE_LOOSE = 0;
const int UNIT_STATE_AFOOT = 1;

const int UNIT_SUBSTATE_FALL      = 0;
const int UNIT_SUBSTATE_ROLL      = 1;
const int UNIT_SUBSTATE_JUMP_UP   = 2;
const int UNIT_SUBSTATE_JUMP_DOWN = 3;

const int UNIT_SUBSTATE_STILL      = 128;
const int UNIT_SUBSTATE_STILL_SIDE = 129;
const int UNIT_SUBSTATE_WALK       = 130;
const int UNIT_SUBSTATE_TURN       = 131;
const int UNIT_SUBSTATE_POST_FALL  = 132;
const int UNIT_SUBSTATE_PRE_JUMP   = 133;
const int UNIT_SUBSTATE_POST_JUMP  = 134;
const int UNIT_SUBSTATE_STAND      = 135;
const int UNIT_SUBSTATE_STAND_SIDE = 136;

/**
 * Models an Unit to the scene.
 * The Units are the main characters in the scene.
 */
class Unit : public LayeredElem
{
    private:
        float m_originalLinearDamping;
        float m_originalAngularDamping;
        b2Body* m_body;
        b2Fixture* m_feet;
        Animation* m_animation;
        int m_substate;
        bool m_isAfoot;
        int m_groundContact;
        bool m_leftOriented;
        bool m_transition;
        int m_awarenessCount;
        float m_contactForce;
        float32 m_referenceX;
        float32 m_referenceY;
        float m_tmpAngle;
        bool m_tmpCheck;
        static float ANGULAR_VELOCITY_TOLERANCE;
        static float LINEAR_VELOCITY_TOLERANCE;
        static float GRAVITY_ANGLE_TOLERANCE;
        static int MAX_AWARENESS_COUNT;

    public:
        /**
         * Class constructor.
         */
        Unit();
        /**
         * Class constructor.
         * Binds this Unit to its parent Layer.
         * @param layer Parent Layer.
         */
        Unit(Layer* layer);
        /**
         * Class destructor.
         */
        ~Unit();
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
        bool IsLeftOriented();
        /**
         * Gets the Animation instance for this Unit's actual state.
         * @return Animation instance for this Unit's actual state.
         */
        Animation* GetAnimation();
        /**
         * Initialization function for this Unit.
         */
        void OnInit();
        /**
         * Processing for each game loop.
         */
        void OnLoop();

        void BeginContact(int thisSensor, Area* area, int areaSensor);
        void EndContact(int thisSensor, Area* area, int areaSensor);

        void SetAfoot();
        void SetLoose();
        void VerifyState();
        bool IsTransitionSubstate(int substate);

};
#endif
