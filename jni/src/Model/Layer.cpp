#include "Layer.h"
#include "CScene.h"

Layer::Layer() {
    m_distance = 0;
    m_world = new b2World(b2Vec2(CScene::GetGravity()->x,
                    CScene::GetGravity()->y));
};

Layer::~Layer() {
};

void Layer::SetId(std::string id) {
    m_id = id;
};

std::string Layer::GetId() {
    return m_id;
};

void Layer::SetDistance(float distance) {
    m_distance = distance;
};

float Layer::GetDistance() {
    return m_distance;
}

void Layer::AddArea(CArea* area) {
    m_areas.push_back(area);
}

void Layer::SetAreas(std::vector<CArea*> areas) {
    m_areas = areas;
}

std::vector<CArea*> Layer::GetAreas() {
    return m_areas;
}

void Layer::SetWorld(b2World* world) {
    m_world = world;
}

b2World* Layer::GetWorld() {
    return m_world;
}

