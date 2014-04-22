#ifndef _LAYEREDELEM_H_
    #define _LAYEREDELEM_H_

const int ELEM_TYPE_DEFAULT = 0;
const int ELEM_TYPE_UNIT    = 1;
const int ELEM_TYPE_ENTRY   = 2;
const int ELEM_TYPE_EXIT    = 3;

#include "Elem.h"
#include "Layer.h"
class Layer;

/**
 * Models any element contained in a Layer.
 */
class LayeredElem : public Elem {
    protected:
        Layer* m_layer;

    public:
        /**
         * Class constructor.
         */
        LayeredElem();
        /**
         * Class constructor.
         * Binds this Element to its parent Layer.
         * @param layer Parent layer.
         */
        LayeredElem(Layer* layer);
        /**
         * Class destructor.
         */
        void SetLayer(Layer* layer);
        /**
         * Gets the parent Layer of this Element.
         * @return Parent Layer.
         */
        Layer* GetLayer();

};
#endif
