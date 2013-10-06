#include "CScene.h"

CScene::CScene() {
    m_width = 0.0f;
    m_height = 0.0f;
    m_gravity.x = 0.0f;
    m_gravity.y = 9.81f;
    m_layer = NULL;
}

void CScene::SetVersion(std::string version) {
    m_version = version;
}

std::string CScene::GetVersion() {
    return m_version;
}

void CScene::SetName(std::string name) {
    m_name = name;
}

std::string CScene::GetName() {
    return m_name;
}

void CScene::SetWidth(float width) {
    m_width = width;
}

float CScene::GetWidth() {
    return m_width;
}

void CScene::SetHeight(float height) {
    m_height = height;
}

float CScene::GetHeight() {
    return m_height;
}

void CScene::AddWorldLayer(CWorldLayer* worldLayer) {
    m_worldLayers.push_back(worldLayer);
    m_layer = worldLayer;
}

std::vector<CWorldLayer*> CScene::GetWorldLayers() {
    return m_worldLayers;
}

void CScene::OnInit() {
    for(auto &worldLayer : m_worldLayers) {
        worldLayer->OnInit();
    }
}

void CScene::OnLoop() {
    for(auto &worldLayer : m_worldLayers) {
        worldLayer->OnLoop();
    }
}

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
