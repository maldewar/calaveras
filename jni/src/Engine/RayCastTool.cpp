#include "RayCastTool.h"
#include "../Util/CMath.h"
#include "../Util/Log.h"

RayCastTool::RayCastTool(float rayLength) : RayCastTool(rayLength, NULL) {};

RayCastTool::RayCastTool(float rayLength, SceneExt* sceneExt) : b2RayCastCallback() {
    m_rayLength        = rayLength;
    m_sceneExt         = sceneExt;
    m_start            = new b2Vec2();
    m_startTemp        = new Vector2();
    m_end              = new b2Vec2();
    m_endTemp          = new Vector2();
    m_areaNodeA        = NULL;
    m_areaNodeB        = NULL;
    m_userData         = NULL;
    m_areaUserData     = NULL;
    m_objectType       = 0;
    m_objectTypeFilter = 0;
};

void RayCastTool::RayCast(WorldLayer* worldLayer, float x, float y, float gravityAngle) {
    RayCast(worldLayer, x, y, gravityAngle, m_rayLength);
};

void RayCastTool::RayCast(WorldLayer* worldLayer, float x, float y, float gravityAngle, float distance) {
    m_hasContact = false;
    m_start->Set(x, y);
    m_startTemp->x = x;
    m_startTemp->y = y;
    m_endTemp = CMath::GetPointAt(m_startTemp, distance, gravityAngle);
    m_end->Set(m_endTemp->x, m_endTemp->y);
    if (m_sceneExt) {
        m_sceneExt->SetSelectNadirX(m_endTemp->x);
        m_sceneExt->SetSelectNadirY(m_endTemp->y);
        m_sceneExt->SetObjectType(0);
    }
    m_objectType = 0;
    m_areaNodeA = NULL;
    m_areaNodeB = NULL;
    worldLayer->GetWorld()->RayCast(this, *m_start, *m_end);
};

float32 RayCastTool::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction, int32 index) {
    m_userData = static_cast<UserData*>( fixture->GetUserData() );
    if (m_objectTypeFilter > 0 && m_userData->type != m_objectTypeFilter || fraction < 0.00001)
        return -1;
    Log::L("FOUND CONTACT at fraction: %f", fraction);
    m_hasContact = true;
    m_objectType = m_userData->type;
    m_end->Set(point.x, point.y);
    m_endTemp->x = point.x;
    m_endTemp->y = point.y;
    if (m_sceneExt) {
        m_sceneExt->SetSelectNadirX(point.x);
        m_sceneExt->SetSelectNadirY(point.y);
        m_sceneExt->SetObjectType(m_objectType);
    }
    if (m_userData->type == AREA_BODY) {
        m_areaUserData = static_cast<AreaUserData*>( fixture->GetUserData() );
        m_areaUserData->GetSection(index, m_areaNodeA, m_areaNodeB);
        if (m_sceneExt) {
            m_sceneExt->SetNodeA(m_areaNodeA);
            m_sceneExt->SetNodeB(m_areaNodeB);
        }
    }
    return fraction;
};

bool RayCastTool::HasContact() {
    return m_hasContact;
};

void RayCastTool::SetFilter(int objectType) {
    m_objectTypeFilter = objectType;
};

void RayCastTool::ClearFilter() {
    m_objectTypeFilter = 0;
};

Vector2* RayCastTool::GetStart() {
    return m_startTemp;
};

Vector2* RayCastTool::GetEnd() {
    return m_endTemp;
};

int RayCastTool::GetObjectType() {
    return m_objectType;
};

AreaNode* RayCastTool::GetAreaNodeA() {
    return m_areaNodeA;
};

AreaNode* RayCastTool::GetAreaNodeB() {
    return m_areaNodeB;
};
