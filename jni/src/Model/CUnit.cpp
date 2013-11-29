#include "CUnit.h"
#include "../Manager/CBoxMaker.h"
#include "../Util/TextureUtil.h"
#include "../Engine/AnimationCatalog.h"
#include "../Util/CLog.h"

float CUnit::ANGULAR_VELOCITY_TOLERANCE = 6.0f;
float CUnit::LINEAR_VELOCITY_TOLERANCE = 0.5f;
float CUnit::ANGULAR_VELOCITY_HAND_TOLERANCE = 8.0f;
float CUnit::ANGULAR_VELOCITY_HAND_REDUCE = 0.007f;

CUnit::CUnit() : CElem() {
    m_type  = ELEM_TYPE_UNIT;
    m_state = UNIT_STATE_LOOSE;
    m_substate = UNIT_SUBSTATE_FALL;
    m_body  = NULL;
    m_width = 0.15f;
    m_height = 0.15f;
    m_originalLinearDamping = 0;
    m_originalAngularDamping = 0;
    SetAnimation();
}

CUnit::CUnit(Layer* layer) : CUnit() {
    m_layer = layer;
}

void CUnit::SetOriginalLinearDamping(float linearDamping) {
    m_originalLinearDamping = linearDamping;
}

void CUnit::SetOriginalAngularDamping(float angularDamping) {
    m_originalAngularDamping = angularDamping;
}

void CUnit::SetBody() {
    m_body = CBoxMaker::MakeUnit(this, m_layer->GetWorld());
}

b2Body* CUnit::GetBody() {
    return m_body;
}

void CUnit::SetAnimation() {
    m_animation = AnimationCatalog::GetByType(m_type);
    if (m_animation) {
        m_animation->GetSprite()->SetDstWidth(CMath::MToPxInt(0.15f));
        m_animation->GetSprite()->SetDstHeight(CMath::MToPxInt(0.15f));
    }
}

CAnimation* CUnit::GetAnimation() {
    return m_animation;
}

void CUnit::SetSubstate(int substate) {
    m_substate = substate;
}

int CUnit::GetSubstate() {
    return m_substate;
}

void CUnit::OnInit() {
}

void CUnit::OnLoop() {
    //Decision making, commands and environment awareness.
}

void CUnit::BeginContact(int thisSensor, CArea* area, int areaSensor) {
    switch (thisSensor) {
        case UNIT_SENSOR_BODY:
            if (areaSensor == AREA_SENSOR_BODY) {
                //CLog::Log("Starting contact.");
                GetBody()->SetAngularDamping(area->GetAngularDamping());
                GetBody()->SetLinearDamping(area->GetLinearDamping());
            }
            break;
        case UNIT_SENSOR_FEET:
        case UNIT_SENSOR_LEFT_HAND:
        case UNIT_SENSOR_RIGHT_HAND:
        case UNIT_SENSOR_HEAD:
            StandUp();
            break;
    }
}

void CUnit::EndContact(int thisSensor, CArea* area, int areaSensor) {
    switch (thisSensor) {
        case UNIT_SENSOR_BODY:
            if (areaSensor == AREA_SENSOR_BODY) {
                //CLog::Log("End contact.");
                GetBody()->SetAngularDamping(m_originalAngularDamping);
                GetBody()->SetLinearDamping(m_originalLinearDamping);
            }
            break;
    }
}



void CUnit::StandUp() {
    if (abs(this->GetBody()->GetAngularVelocity()) < ANGULAR_VELOCITY_TOLERANCE
        && abs(this->GetBody()->GetLinearVelocity().x) < LINEAR_VELOCITY_TOLERANCE
        && abs(this->GetBody()->GetLinearVelocity().y) < LINEAR_VELOCITY_TOLERANCE) {
        this->GetBody()->SetFixedRotation(true);
        this->GetBody()->SetAngularVelocity(0.0f);
        GetBody()->SetAngularDamping(m_originalAngularDamping);
        GetBody()->SetLinearDamping(m_originalLinearDamping);
        //CLog::Log("Fixed at linear velocity of %f m/s",this->GetBody()->GetLinearVelocity().x);
    }
}
