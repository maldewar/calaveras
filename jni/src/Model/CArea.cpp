#include "CArea.h"

CArea::CArea() {
    m_isClosed = false;
    m_totalPoints = 0;
    m_material = 0;
    m_nature = 0;
    m_linearDamping = 0;
    m_angularDamping = 0;
    m_body = NULL;
    m_layer = NULL;
}

CArea::CArea(CLayer* layer) : CArea() {
    m_layer = layer;
}

void CArea::SetLayer(CLayer* layer) {
    m_layer = layer;
}

CLayer* CArea::GetLayer() {
    return m_layer;
}

void CArea::SetBody() {
    m_body = CBoxMaker::MakeArea(this, m_layer->GetWorld());
}

b2Body* CArea::GetBody() {
    return m_body;
}

void CArea::AddPoint(float x, float y) {
    m_points.push_back({x, y});
    m_totalPoints++;
}

void CArea::AddPoint(Vector2 vector) {
    m_points.push_back(vector);
    m_totalPoints++;
}

std::vector<Vector2> CArea::GetPoints() {
    return m_points;
}

int CArea::GetTotalPoints() {
    return m_totalPoints;
}

void CArea::SetClosed(bool closed) {
    m_isClosed = closed;
}

bool CArea::IsClosed() {
    return m_isClosed;
}

void CArea::SetMaterial(int material) {
    m_material = material;
}

int CArea::GetMaterial() {
    return m_material;
}

void CArea::SetNature(int nature) {
    m_nature = nature;
}

int CArea::GetNature() {
    return m_nature;
}

void CArea::SetLinearDamping(float linearDamping) {
    m_linearDamping = linearDamping;
}

float CArea::GetLinearDamping() {
    return m_linearDamping;
}

void CArea::SetAngularDamping(float angularDamping) {
    m_angularDamping = angularDamping;
}

float CArea::GetAngularDamping() {
    return m_angularDamping;
}
