#include "Elem.h"

Elem::Elem() : Node2D() {
    m_type       = 0;
    m_width      = 0;
    m_height     = 0;
    m_stackIndex = 0;
};

void Elem::SetWidth(float width) {
    m_width = width;
};

float Elem::GetWidth() {
    return m_width;
};

void Elem::SetHeight(float height) {
    m_height = height;
};

float Elem::GetHeight() {
    return m_height;
};

void Elem::SetStackIndex(int stackIndex) {
    m_stackIndex = stackIndex;
};

int Elem::GetStackIndex() {
    return m_stackIndex;
};

int Elem::GetType() {
    return m_type;
};

void Elem::SetState(int state) {
    m_state = state;
};

int Elem::GetState() {
    return m_state;
};

void Elem::OnInit() {};
void Elem::OnLoop() {};
