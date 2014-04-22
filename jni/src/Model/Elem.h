#ifndef _ELEM_H_
    #define _ELEM_H_

#include "Node2D.h"

/**
 * Models any element contained in a Layer.
 */
class Elem : public Node2D {
    protected:
        int m_type;
        int m_state;
        float m_width;
        float m_height;
        int m_stackIndex;

    public:
        /**
         * Class constructor.
         */
        Elem();
        /**
         * Sets the width of this element in meters.
         * @param width Width of the element in meters.
         */
        virtual void SetWidth(float width);
        /**
         * Gets the width of this element in meters.
         * @returns Width of the element in meters.
         */
        float GetWidth();
        /**
         * Sets the height of this element in meters.
         * @param height Height of the element in meters.
         */
        virtual void SetHeight(float height);
        /**
         * Gets the height of this element in meters.
         * @returns Height of the element in meters.
         */
        float GetHeight();
        /**
         * Sets the stack index for this Elem.
         * @param stackIndex Index on the stack.
         */
        void SetStackIndex(int stackIndex);
        /**
         * Gets the stack index for this Elem.
         * @return Index on the stack.
         */
        int GetStackIndex();
        /**
         * Gets the type of Elem.
         * @return Type of Elem.
         */
        int GetType();
        /**
         * Sets the state of the Elem.
         * @param state State of the Elem.
         */
        void SetState(int state);
        /**
         * Gets the state of the Elem.
         * @returns State of the Elem.
         */
        int GetState();
        /**
         * Called right before the scene starts to play.
         */
        void OnInit();
        /**
         * Called on every loop step of the application.
         */
        void OnLoop();

};
#endif
