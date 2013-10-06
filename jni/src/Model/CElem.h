#ifndef _CELEM_H_
    #define _CELEM_H_

#define ELEM_TYPE_DEFAULT 0
#define ELEM_TYPE_UNIT    1
#define ELEM_TYPE_ENTRY   2

#include "CLayer.h"
class CLayer;

/**
 * Models any element contained in a Layer.
 */
class CElem {
    protected:
        int m_type;
        int m_state;
        float m_x;
        float m_y;
        float m_width;
        float m_height;
        float m_scale;
        float m_rotation;
        CLayer* m_layer;

    public:
        /**
         * Class constructor.
         */
        CElem();
        /**
         * Class constructor.
         * Binds this Element to its parent Layer.
         * @param layer Parent layer.
         */
        CElem(CLayer* layer);
        /**
         * Class destructor.
         */
        void SetLayer(CLayer* layer);
        /**
         * Gets the parent Layer of this Element.
         * @return Parent Layer.
         */
        CLayer* GetLayer();
        /**
         * Sets the X cartesian coordinate in meters for the Element.
         * @param x X coordinate in meters.
         */
        void SetX(float x);
        /**
         * Gets the X cartesian coordinate in meters for the Element.
         * @returns X coordinate in meters.
         */
        float GetX();
        /**
         * Sets the Y cartesian coordinate in meters for the Element.
         * @param y Y coordinate in meters.
         */
        void SetY(float y);
        /**
         * Gets the Y cartesian coordinate in meters for the Element.
         * @returns Y coordinate in meters.
         */
        float GetY();
        /**
         * Sets the width of this element in meters.
         * @param width Width of the element in meters.
         */
        void SetWidth(float width);
        /**
         * Gets the width of this element in meters.
         * @returns Width of the element in meters.
         */
        float GetWidth();
        /**
         * Sets the height of this element in meters.
         * @param height Height of the element in meters.
         */
        void SetHeight(float height);
        /**
         * Gets the height of this element in meters.
         * @returns Height of the element in meters.
         */
        float GetHeight();
        /**
         * Sets the scale of this Element.
         * @param scale Scale of this Element.
         */
        void SetScale(float scale);
        /**
         * Gets the scale of this Element.
         * @returns Scale of this Element.
         */
        float GetScale();
        /**
         * Sets the initial rotation for this Element.
         * @param rotation Rotation in radians.
         */
        void SetRotation(float rotation);
        /**
         * Gets the initial rotation for this Element.
         * @returns Rotation in radians.
         */
        float GetRotation();
        /**
         * Gets the type of Element.
         * @return Type of Element.
         */
        int GetType();
        /**
         * Sets the state of the Element.
         * @param state State of the Element.
         */
        void SetState(int state);
        /**
         * Gets the state of the Element.
         * @returns State of the Element.
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
