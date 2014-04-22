#include "Scene.h"

//Vector2* Scene::m_gravity = new Vector2(2.4f, -2.4f); //SE
Vector2* Scene::m_gravity = new Vector2(0.0f, -4.81f); //S
//Vector2* Scene::m_gravity = new Vector2(-2.4f, -2.4f); //SW
//Vector2* Scene::m_gravity = new Vector2(2.4f, -2.4f); //SE
//Vector2* Scene::m_gravity = new Vector2(4.81f, 0.0f); //E
//Vector2* Scene::m_gravity = new Vector2(2.4f, 2.4f); //NE
//Vector2* Scene::m_gravity = new Vector2(0.0f, 4.81f); //N

Scene::Scene() {
    m_width = 0.0f;
    m_height = 0.0f;
};

Scene::~Scene() {
};

void Scene::SetGravity(float x, float y) {
    m_gravity->x = x;
    m_gravity->y = y;
};

Vector2* Scene::GetGravity() {
    return m_gravity;
};

void Scene::SetVersion(std::string version) {
    m_version = version;
};

std::string Scene::GetVersion() {
    return m_version;
};

void Scene::SetName(std::string name) {
    m_name = name;
};

std::string Scene::GetName() {
    return m_name;
};

void Scene::SetWidth(float width) {
    m_width = width;
};

float Scene::GetWidth() {
    return m_width;
};

void Scene::SetHeight(float height) {
    m_height = height;
};

float Scene::GetHeight() {
    return m_height;
};

void Scene::AddFgLayer(FgLayer* fgLayer) {
    m_fgLayers.push_back(fgLayer);
};

std::vector<FgLayer*> Scene::GetFgLayers() {
    return m_fgLayers;
};

void Scene::AddWorldLayer(WorldLayer* worldLayer) {
    m_worldLayers.push_back(worldLayer);
};

std::vector<WorldLayer*> Scene::GetWorldLayers() {
    return m_worldLayers;
};

void Scene::AddBgLayer(BgLayer* bgLayer) {
    m_bgLayers.push_back(bgLayer);
};

std::vector<BgLayer*> Scene::GetBgLayers() {
    return m_bgLayers;
};

void Scene::SetWorldLayer(WorldLayer* worldLayer) {
    m_worldLayer = worldLayer;
};

WorldLayer* Scene::GetWorldLayer() {
    return m_worldLayer;
};

void Scene::OnInit() {
    for(auto &fgLayer : m_fgLayers) {
        fgLayer->OnInit();
    }
    for(auto &worldLayer : m_worldLayers) {
        worldLayer->OnInit();
    }
    for(auto &bgLayer : m_bgLayers) {
        bgLayer->OnInit();
    }
};

void Scene::OnLoop() {
    for(auto &fgLayer : m_fgLayers) {
        fgLayer->OnLoop();
    }
    for(auto &worldLayer : m_worldLayers) {
        worldLayer->OnLoop();
    }
    for(auto &bgLayer : m_bgLayers) {
        bgLayer->OnLoop();
    }
};

/*
void Scene::AddFgLayer(CFgLayer* fgLayer) {
    m_fgLayers.push_back(fgLayer);
}

std::vector<CFgLayer*> Scene::GetFgLayers() {
    return m_fgLayers;
}

void Scene::AddBgLayer(CBgLayer* bgLayer) {
    m_bgLayers.push_back(bgLayer);
}

std::vector<CBgLayer*> Scene::GetBgLayers() {
    return m_bgLayers;
}
*/
