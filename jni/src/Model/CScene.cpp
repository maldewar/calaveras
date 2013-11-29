#include "CScene.h"

Vector2* CScene::m_gravity = new Vector2(0.0f, -4.81f);

CScene::CScene() {
    m_width = 0.0f;
    m_height = 0.0f;
};

void CScene::SetGravity(float x, float y) {
    m_gravity->x = x;
    m_gravity->y = y;
};

Vector2* CScene::GetGravity() {
    return m_gravity;
};

void CScene::SetVersion(std::string version) {
    m_version = version;
};

std::string CScene::GetVersion() {
    return m_version;
};

void CScene::SetName(std::string name) {
    m_name = name;
};

std::string CScene::GetName() {
    return m_name;
};

void CScene::SetWidth(float width) {
    m_width = width;
};

float CScene::GetWidth() {
    return m_width;
};

void CScene::SetHeight(float height) {
    m_height = height;
};

float CScene::GetHeight() {
    return m_height;
};

void CScene::AddFgLayer(FgLayer* fgLayer) {
    m_fgLayers.push_back(fgLayer);
};

std::vector<FgLayer*> CScene::GetFgLayers() {
    return m_fgLayers;
};

void CScene::AddWorldLayer(WorldLayer* worldLayer) {
    m_worldLayers.push_back(worldLayer);
};

std::vector<WorldLayer*> CScene::GetWorldLayers() {
    return m_worldLayers;
};

void CScene::AddBgLayer(BgLayer* bgLayer) {
    m_bgLayers.push_back(bgLayer);
};

std::vector<BgLayer*> CScene::GetBgLayers() {
    return m_bgLayers;
};

void CScene::OnInit() {
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

void CScene::OnLoop() {
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
void CScene::AddFgLayer(CFgLayer* fgLayer) {
    m_fgLayers.push_back(fgLayer);
}

std::vector<CFgLayer*> CScene::GetFgLayers() {
    return m_fgLayers;
}

void CScene::AddBgLayer(CBgLayer* bgLayer) {
    m_bgLayers.push_back(bgLayer);
}

std::vector<CBgLayer*> CScene::GetBgLayers() {
    return m_bgLayers;
}
*/
