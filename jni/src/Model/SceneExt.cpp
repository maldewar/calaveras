#include "SceneExt.h"

SceneExt::SceneExt() {
    m_isSelecting = false;
    m_hasSelection = false;
    m_selectX = 0.0f;
    m_selectY = 0.0f;
    m_selectZenithX = 0.0f;
    m_selectZenithY = 0.0f;
    m_selectNadirX = 0.0f;
    m_selectNadirY = 0.0f;
    m_objectType = 0;
    m_nodeA = NULL;
    m_nodeB = NULL;
};

SceneExt::~SceneExt() {
};

void SceneExt::SetIsSelecting(bool isSelecting) {
    m_isSelecting = isSelecting;
};

bool SceneExt::IsSelecting() {
    return m_isSelecting;
};

void SceneExt::SetHasSelection(bool hasSelection) {
    m_hasSelection = hasSelection;
};

bool SceneExt::HasSelection() {
    return m_hasSelection;
};

void SceneExt::SetSelectX(float selectX) {
    m_selectX = selectX;
};

float SceneExt::GetSelectX() {
    return m_selectX;
};

void SceneExt::SetSelectY(float selectY) {
    m_selectY = selectY;
};

float SceneExt::GetSelectY() {
    return m_selectY;
};

void SceneExt::SetSelectZenithX(float selectZenithX) {
    m_selectZenithX = selectZenithX;
};

float SceneExt::GetSelectZenithX() {
    return m_selectZenithX;
};

void SceneExt::SetSelectZenithY(float selectZenithY) {
    m_selectZenithY = selectZenithY;
};

float SceneExt::GetSelectZenithY() {
    return m_selectZenithY;
};

void SceneExt::SetSelectNadirX(float selectNadirX) {
    m_selectNadirX = selectNadirX;
};

float SceneExt::GetSelectNadirX() {
    return m_selectNadirX;
};

void SceneExt::SetSelectNadirY(float selectNadirY) {
    m_selectNadirY = selectNadirY;
};

float SceneExt::GetSelectNadirY() {
    return m_selectNadirY;
};

void SceneExt::SetObjectType(int objectType) {
    m_objectType = objectType;
};

int SceneExt::GetObjectType() {
    return m_objectType;
};

void SceneExt::SetNodeA(AreaNode* nodeA) {
    m_nodeA = nodeA;
};

AreaNode* SceneExt::GetNodeA() {
    return m_nodeA;
};

void SceneExt::SetNodeB(AreaNode* nodeB) {
    m_nodeB = nodeB;
};

AreaNode* SceneExt::GetNodeB() {
    return m_nodeB;
};

void SceneExt::OnInit() {};

void SceneExt::OnLoop() {};
