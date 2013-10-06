#include "CLayer.h"

CLayer::CLayer() {
    m_distance = 0;
    m_world = new b2World(b2Vec2(0.0f, -4.81f));
}

void CLayer::SetId(std::string id) {
    m_id = id;
}

std::string CLayer::GetId() {
    return m_id;
}

void CLayer::SetDistance(float distance) {
    m_distance = distance;
}

float CLayer::GetDistance() {
    return m_distance;
}

void CLayer::AddArea(CArea* area) {
    m_areas.push_back(area);
}

void CLayer::SetAreas(std::vector<CArea*> areas) {
    m_areas = areas;
}

std::vector<CArea*> CLayer::GetAreas() {
    return m_areas;
}

void CLayer::SetWorld(b2World* world) {
    m_world = world;
}

b2World* CLayer::GetWorld() {
    return m_world;
}

