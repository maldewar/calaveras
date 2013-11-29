#ifndef _EXIT_H_
    #define _EXIT_H_

#include <Box2D.h>
#include "CElem.h"
#include "../Engine/CAnimation.h"

const int EXIT_STATE_CLOSED  = 0;
const int EXIT_STATE_OPEN    = 1;
const int EXIT_STATE_CLOSING = 2;
const int EXIT_STATE_OPENING = 3;

/**
 * Models an Exit to the scene.
 * This element takes Unit instances in to score them to the scene.
 */
class Exit : public CElem
{
    private:
        CAnimation* m_animation;
        int m_units;
        int m_capacity;
        bool m_open;
        int m_openTimer;
        int m_interval;
        float m_rotationOffset;
        long m_timerRef;
        

    public:
        /**
         * Class constructor.
         */
        Exit();
        /**
         * Class constructor.
         * Binds this Exit to its parent Layer.
         * @param layer Parent Layer.
         */
        Exit(Layer* layer);
        /**
         * Class destructor.
         */
        ~Exit();
        /**
         * Sets the animation for the exit state using the Animation Catalog.
         */
        void SetAnimation();
        /**
         * Gets the Animation instance for this Exit's actual state.
         * @returns Animation instance for this Exit's actual state.
         */
        CAnimation* GetAnimation();
        /**
         * Defines how many Unit instances this Exit can take.
         * @param capacity Amount of Unit instances to take.
         */
        void SetCapacity(int capacity);
        /**
         * Gets the amount of Unit instances this Exit can take.
         * @returns Amount of Unit instances this Exit can take.
         */
        int GetCapacity();
        /**
         * Gets the amount of Unit instances this Exit has taken.
         * @returns Amount of Unit instances this Exit has taken..
         */
        int GetUnits();
        /**
         * Opens the Exit so Unit instances can get in.
         */
        void Open();
        /**
         * Closes the Exit stoping Unit instances in.
         */
        void Close();
        /**
         * Sets the state of the Exit as open or closed.
         * @param isOpen True if the Exit has to be open.
         */
        void SetOpen(bool isOpen);
        /**
         * If an Exit is initialised closed this sets the number
         * of milliseconds to wait before it auto-opens.
         * @param openTimer Milliseconds for this Entry to open.
         */
        void SetOpenTimer(int openTimer);
        void SetInterval(int interval);
        int GetInterval();
        void SetState(int state);
        void OnInit();
        void OnLoop();

};
#endif
