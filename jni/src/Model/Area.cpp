#include "Area.h"

Area::Area() {
    m_isClosed = false;
    m_totalPoints = 0;
    m_material = 0;
    m_nature = 0;
    m_linearDamping = 0;
    m_angularDamping = 0;
    m_body = NULL;
    m_layer = NULL;
    m_layeredGraphic = NULL;
    m_center = new Vector2(0, 0);
};

Area::Area(Layer* layer) : Area() {
    m_layer = layer;
};

void Area::SetLayer(Layer* layer) {
    m_layer = layer;
};

Layer* Area::GetLayer() {
    return m_layer;
};

void Area::SetBody() {
    m_body = BoxMaker::MakeArea(this, m_layer->GetWorld());
};

b2Body* Area::GetBody() {
    return m_body;
};

void Area::AddPoint(float x, float y) {
    m_points.push_back(new AreaNode(x, y));
    m_totalPoints++;
};

void Area::AddPoint(AreaNode* vector) {
    m_points.push_back(vector);
    m_totalPoints++;
};

std::vector<AreaNode*> Area::GetPoints() {
    return m_points;
};

int Area::GetTotalPoints() {
    return m_totalPoints;
};

void Area::SetClosed(bool closed) {
    m_isClosed = closed;
};

bool Area::IsClosed() {
    return m_isClosed;
};

void Area::SetMaterial(int material) {
    m_material = material;
};

int Area::GetMaterial() {
    return m_material;
};

void Area::SetNature(int nature) {
    m_nature = nature;
};

int Area::GetNature() {
    return m_nature;
};

void Area::SetLinearDamping(float linearDamping) {
    m_linearDamping = linearDamping;
};

float Area::GetLinearDamping() {
    return m_linearDamping;
};

void Area::SetAngularDamping(float angularDamping) {
    m_angularDamping = angularDamping;
};

float Area::GetAngularDamping() {
    return m_angularDamping;
};

void Area::SetLayeredGraphic(LayeredGraphic* layeredGraphic) {
    m_layeredGraphic = layeredGraphic;
};

LayeredGraphic* Area::GetLayeredGraphic() {
    return m_layeredGraphic;
};

void Area::SetCenter(float x, float y) {
    m_center->x = x;
    m_center->y = y;
};

Vector2* Area::GetCenter() {
    return m_center;
};
