#include "Node2D.h"
#include "../Util/Log.h"

Node2D::Node2D() : Node() {
    m_x        = 0;
    m_y        = 0;
    m_scale    = 0;
    m_rotation = 0;
    m_parent   = nullptr;

    x_offset = 0;
    y_offset = 0;
    rotation_offset = 0;
    scale_offset = 1;
};

void Node2D::SetX(float x) {
    m_x = x;
};

float Node2D::GetX() {
    return m_x;
};

void Node2D::SetY(float y) {
    m_y = y;
};

float Node2D::GetY() {
    return m_y;
};

void Node2D::SetScale(float scale) {
    m_scale = scale;
};

float Node2D::GetScale() {
    return m_scale;
};

void Node2D::SetRotation(float rotation) {
    m_rotation = rotation;
};

float Node2D::GetRotation() {
    return m_rotation;
};

void Node2D::SetParent(Node2D* parent) {
  m_parent = parent;
};

void Node2D::OnInit() {};

void Node2D::OnLoop() {};

void Node2D::OnRender() {};

void Node2D::OnCleanUp() {};
