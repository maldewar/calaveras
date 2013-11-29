#include "CElem.h"

CElem::CElem() {
    m_type = ELEM_TYPE_DEFAULT;
    m_width = 0;
    m_height = 0;
    m_scale = 0;
    m_rotation = 0;
    m_layer = NULL;
}

CElem::CElem(Layer* layer) : CElem() {
    m_layer = layer;
}

void CElem::SetLayer(Layer* layer) {
    m_layer = layer;
}

Layer* CElem::GetLayer() {
    return m_layer;
}

void CElem::SetX(float x) {
    m_x = x;
}

float CElem::GetX() {
    return m_x;
}

void CElem::SetY(float y) {
    m_y = y;
}

float CElem::GetY() {
    return m_y;
}

void CElem::SetWidth(float width) {
    m_width = width;
}

float CElem::GetWidth() {
    return m_width;
}

void CElem::SetHeight(float height) {
    m_height = height;
}

float CElem::GetHeight() {
    return m_height;
}

void CElem::SetScale(float scale) {
    m_scale = scale;
}

float CElem::GetScale() {
    return m_scale;
}

void CElem::SetRotation(float rotation) {
    m_rotation = rotation;
}

float CElem::GetRotation() {
    return m_rotation;
}

int CElem::GetType() {
    return m_type;
}

void CElem::SetState(int state) {
    m_state = state;
}

int CElem::GetState() {
    return m_state;
}
