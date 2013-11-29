#ifndef _ENTRY_H_
    #define _ENTRY_H_

#include <Box2D.h>
#include "CElem.h"
#include "../Engine/CAnimation.h"

const int ENTRY_STATE_CLOSED  = 0;
const int ENTRY_STATE_OPEN    = 1;
const int ENTRY_STATE_CLOSING = 2;
const int ENTRY_STATE_OPENING = 3;

/**
 * Models an Entry to the scene.
 * This element creates Units in the game to interact with the scene.
 */
class Entry : public CElem
{
    private:
        CAnimation* m_animation;
        int m_units;
        int m_capacity;
        bool m_open;
        int m_openTimer;
        int m_interval;
        float m_forceMinDistance;
        float m_forceMaxDistance;
        float m_forceMaxAngle;
        float m_forceMinAngularImpulse;
        float m_forceMaxAngularImpulse;
        float m_rotationOffset;
        long m_timerRef;
        

    public:
        /**
         * Class constructor.
         */
        Entry();
        /**
         * Class constructor.
         * Binds this Entry to its parent Layer.
         * @param layer Parent Layer.
         */
        Entry(Layer* layer);
        /**
         * Class destructor.
         */
        ~Entry();
        /**
         * Sets the animation for the entry state using the Animation Catalog.
         */
        void SetAnimation();
        /**
         * Gets the Animation instance for this Entry's actual state.
         * @returns Animation instance for this Entry's actual state.
         */
        CAnimation* GetAnimation();
        /**
         * Sets the amount of Unit instances this Entry will generate.
         * @param capacity Amount of Unit instances to generate.
         */
        void SetCapacity(int capacity);
        /**
         * Gets the amount of Unit instances this Entry will generate.
         * @returns Amount of Unit instances to generate.
         */
        int GetCapacity();
        /**
         * Gets the amount of Unit instances that remain to be generated.
         * @returns Amount of Unit instances that remain to be generated.
         */
        int GetUnits();
        /**
         * Opens the Entry so Unit instances can be generated.
         */
        void Open();
        /**
         * Closes the Entry stoping the the generation of Unit instances.
         */
        void Close();
        /**
         * Sets the state of the Entry as open or closed.
         * @param isOpen True if the Entry has to be open.
         */
        void SetOpen(bool isOpen);
        /**
         * If an Entry is initialised closed this sets the number
         * of milliseconds to wait before it auto-opens.
         * @param openTimer Milliseconds for this Entry to open.
         */
        void SetOpenTimer(int openTimer);
        /**
         * Sets the interval inbetween spawning Units.
         * @param interval Milliseconds between Units.
         */
        void SetInterval(int interval);
        /**
         * Gets the interval inbetween spawning Units.
         * @return Milliseconds between Units.
         */
        int GetInterval();
        void SetForceMinDistance(float distance);
        float GetForceMinDistance();
        void SetForceMaxDistance(float distance);
        float GetForceMaxDistance();
        void SetForceMinAngularImpulse(float angularImpulse);
        float GetForceMinAngularImpulse();
        void SetForceMaxAngularImpulse(float angularImpulse);
        float GetForceMaxAngularImpulse();
        /**
         * Sets the random Pi area used to eject Units.
         * @param angle Between 0 and 2 Pi.
         */
        void SetForceMaxAngle(float angle);
        /**
         * Gets the random Pi area used to eject Units.
         * @returns Value between 0 and 2 Pi.
         */
        float GetForceMaxAngle();
        /**
         * Gets the randomized vector used to eject Units.
         * @return Vector.
         */
        b2Vec2 GetRandomForce();
        void SetState(int state);
        void OnInit();
        void OnLoop();

};
#endif
