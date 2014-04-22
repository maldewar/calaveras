#include "Unit.h"
#include "Scene.h"
#include "../Manager/BoxMaker.h"
#include "../Util/TextureUtil.h"
#include "../Engine/AnimationCatalog.h"
#include "../Util/Log.h"

float Unit::ANGULAR_VELOCITY_TOLERANCE = 3.0f;
float Unit::LINEAR_VELOCITY_TOLERANCE = 0.7f;
float Unit::GRAVITY_ANGLE_TOLERANCE = M_PI_4;
int Unit::MAX_AWARENESS_COUNT = 9;

Unit::Unit() : LayeredElem() {
    m_type  = ELEM_TYPE_UNIT;
    m_state = UNIT_STATE_LOOSE;
    m_substate = UNIT_SUBSTATE_FALL;
    m_groundContact = 0;
    m_isAfoot = false;
    m_leftOriented = false;
    m_transition = false;
    m_awarenessCount = MAX_AWARENESS_COUNT;
    m_contactForce = 0.0f;
    m_referenceX = 0.0f;
    m_referenceY = 0.0f;
    m_body  = NULL;
    m_width = 0.15f;
    m_height = 0.15f;
    m_tmpAngle = 0.0f;
    m_tmpCheck = false;
    m_originalLinearDamping = 0;
    m_originalAngularDamping = 0;
    SetAnimation();
}

Unit::Unit(Layer* layer) : Unit() {
    m_layer = layer;
};

void Unit::SetOriginalLinearDamping(float linearDamping) {
    m_originalLinearDamping = linearDamping;
};

void Unit::SetOriginalAngularDamping(float angularDamping) {
    m_originalAngularDamping = angularDamping;
};

void Unit::SetBody() {
    m_body = BoxMaker::MakeUnit(this, m_layer->GetWorld());
};

b2Body* Unit::GetBody() {
    return m_body;
};

void Unit::SetAnimation() {
    m_animation = AnimationCatalog::GetBySubstate(m_type, m_state, m_substate);
    if (m_animation) {
        m_animation->GetSprite()->SetDstWidth(CMath::MToPxInt(0.15f));
        m_animation->GetSprite()->SetDstHeight(CMath::MToPxInt(0.15f));
    }
};

Animation* Unit::GetAnimation() {
    return m_animation;
};

void Unit::SetSubstate(int substate) {
    m_substate = substate;
    if ((m_substate & 128) == 128)
        m_state = UNIT_STATE_AFOOT;
    else
        m_state = UNIT_STATE_LOOSE;
    m_transition = IsTransitionSubstate(m_substate);
    SetAnimation();
};

int Unit::GetSubstate() {
    return m_substate;
};

bool Unit::IsLeftOriented() {
    return m_leftOriented;
};

void Unit::OnInit() {
    m_referenceX = GetBody()->GetPosition().x;
    m_referenceY = GetBody()->GetPosition().y;
};

void Unit::OnLoop() {
    if (m_referenceX != GetBody()->GetPosition().x) {
        if (m_referenceX < GetBody()->GetPosition().x) {
            m_leftOriented = false;
        } else {
            m_leftOriented = true;
        }
    }
    m_referenceX = GetBody()->GetPosition().x;
    m_referenceY = GetBody()->GetPosition().y;
    VerifyState();
};

void Unit::BeginContact(int thisSensor, Area* area, int areaSensor) {
    switch (thisSensor) {
        case UNIT_BODY:
            if (areaSensor == AREA_BODY) {
                GetBody()->SetAngularDamping(area->GetAngularDamping());
                //GetBody()->SetLinearDamping(area->GetLinearDamping());
                if (m_groundContact == 0) {
                    m_contactForce = GetBody()->GetLinearVelocity().Length();
                    m_transition = false;
                    m_awarenessCount = MAX_AWARENESS_COUNT;
                }
                m_groundContact++;
            }
            break;
    }
};

void Unit::EndContact(int thisSensor, Area* area, int areaSensor) {
    switch (thisSensor) {
        case UNIT_BODY:
            if (areaSensor == AREA_BODY) {
                GetBody()->SetAngularDamping(m_originalAngularDamping);
                //GetBody()->SetLinearDamping(m_originalLinearDamping);
                m_groundContact--;
                if (m_groundContact == 0) {
                    m_transition = false;
                    m_awarenessCount = MAX_AWARENESS_COUNT;
                }
            }
            break;
    }
};



void Unit::SetAfoot() {
    GetBody()->SetTransform(GetBody()->GetPosition(), 0);
    GetBody()->SetFixedRotation(true);
    GetBody()->SetAngularVelocity(0.0f);
    GetBody()->SetAngularDamping(m_originalAngularDamping);
    GetBody()->SetLinearDamping(m_originalLinearDamping);
    m_isAfoot = true;
};

void Unit::SetLoose() {
    GetBody()->SetFixedRotation(false);
    m_isAfoot = false;
};

void Unit::VerifyState() {
    if (m_transition && m_animation->IsOngoing()) {
        m_animation->OnAnimate();
        return;
    }
    switch (m_state) {
        case UNIT_STATE_LOOSE:
            switch (m_substate) {
                case UNIT_SUBSTATE_FALL:
                    if (m_groundContact > 0) {
                        if (m_isAfoot) {
                            if (m_contactForce < LINEAR_VELOCITY_TOLERANCE) {
                                SetSubstate(UNIT_SUBSTATE_STILL);
                            } else {
                                SetSubstate(UNIT_SUBSTATE_STAND);
                            }
                        } else {
                            if (abs(GetBody()->GetAngularVelocity()) > ANGULAR_VELOCITY_TOLERANCE) {
                                SetSubstate(UNIT_SUBSTATE_ROLL);
                            }
                        }
                    }
                    break;
                case UNIT_SUBSTATE_ROLL:
                    if (m_isAfoot) {
                        SetSubstate(UNIT_SUBSTATE_STAND_SIDE);
                    } else {
                        if (m_groundContact == 0 && abs(GetBody()->GetAngularVelocity()) < ANGULAR_VELOCITY_TOLERANCE) {
                            SetSubstate(UNIT_SUBSTATE_FALL);
                        }
                    }
                    break;
                case UNIT_SUBSTATE_JUMP_UP:
                    break;
                case UNIT_SUBSTATE_JUMP_DOWN:
                    break;
            }
            if (m_groundContact > 0) {
                if ( abs(GetBody()->GetAngularVelocity()) < ANGULAR_VELOCITY_TOLERANCE && m_awarenessCount <= 0) {
                    SetAfoot();
                } else {
                    m_awarenessCount--;
                }
            }
            break;
        case UNIT_STATE_AFOOT:
            if (m_groundContact <= 0) {
                if (m_awarenessCount <= 0) {
                    SetLoose();
                    SetSubstate(UNIT_SUBSTATE_FALL);
                } else {
                    m_awarenessCount--;
                }
            }
            break;
    }
};

bool Unit::IsTransitionSubstate(int substate) {
    switch (substate) {
        case UNIT_SUBSTATE_TURN:
        case UNIT_SUBSTATE_POST_FALL:
        case UNIT_SUBSTATE_PRE_JUMP:
        case UNIT_SUBSTATE_POST_JUMP:
        case UNIT_SUBSTATE_STAND:
        case UNIT_SUBSTATE_STAND_SIDE:
            return true;
        default:
            return false;
    }
};
