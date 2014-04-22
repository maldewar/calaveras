#include "LayeredElem.h"

LayeredElem::LayeredElem() : Elem() {
    m_type       = ELEM_TYPE_DEFAULT;
    m_layer      = NULL;
};

LayeredElem::LayeredElem(Layer* layer) : LayeredElem() {
    m_layer = layer;
};

void LayeredElem::SetLayer(Layer* layer) {
    m_layer = layer;
};

Layer* LayeredElem::GetLayer() {
    return m_layer;
};
