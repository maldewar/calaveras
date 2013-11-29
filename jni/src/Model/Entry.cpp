#include "Entry.h"
#include "CUnit.h"
#include "WorldLayer.h"
#include "../Manager/CBoxMaker.h"
#include "../Engine/AnimationCatalog.h"
#include "../Util/CLog.h"

Entry::Entry() : CElem() {
    m_type = ELEM_TYPE_ENTRY;
    m_state = ENTRY_STATE_CLOSED;
    m_units = 0;
    m_capacity = 0;
    m_open = false;
    m_openTimer = 5000;
    m_forceMinDistance = 0.0f;
    m_forceMaxDistance = 0.0f;
    m_forceMaxAngle = 0.0f;
    m_forceMinAngularImpulse = 0.0f;
    m_forceMaxAngularImpulse = 0.0f;
    m_timerRef = 0;
    m_rotationOffset = M_PI_2 * -1;
    SetAnimation();
}

Entry::Entry(Layer* layer) : Entry() {
    m_layer = layer;
}

void Entry::SetAnimation() {
    m_animation = AnimationCatalog::GetByType(m_type);
    if (m_animation) {
        m_animation->GetSprite()->SetDstWidth(CMath::MToPxInt(0.20f));
        m_animation->GetSprite()->SetDstHeight(CMath::MToPxInt(0.07f));
        if (m_state == ENTRY_STATE_CLOSED || m_state == ENTRY_STATE_OPENING)
            m_animation->SetCurrentFrame(m_animation->GetMaxFrames() - 1);
    }
}

CAnimation* Entry::GetAnimation() {
    return m_animation;
}

void Entry::SetCapacity(int capacity) {
    if (capacity >= 0)
        m_capacity = capacity;
}

int Entry::GetCapacity() {
    return m_capacity;
}

int Entry::GetUnits() {
    return m_units;
}

void Entry::Open() {
    if (m_state == ENTRY_STATE_CLOSED)
        SetState(ENTRY_STATE_OPENING);
    else
        SetState(ENTRY_STATE_OPEN);
}

void Entry::Close() {
    if (m_state == ENTRY_STATE_OPEN)
        SetState(ENTRY_STATE_CLOSING);
}

void Entry::SetOpen(bool isOpen) {
    if (isOpen)
        Open();
    else
        Close();
}

void Entry::SetOpenTimer(int openTimer) {
    m_openTimer = openTimer;    
}

void Entry::SetInterval(int interval) {
    if (interval >= 0) {
        m_interval = interval;
        m_units = m_capacity;
    }
}

int Entry::GetInterval() {
    return m_interval;
}

void Entry::SetForceMinDistance(float distance) {
    m_forceMinDistance = distance;
}

float Entry::GetForceMinDistance() {
    return m_forceMinDistance;
}

void Entry::SetForceMaxDistance(float distance) {
    m_forceMaxDistance = distance;
}

float Entry::GetForceMaxDistance() {
    return m_forceMaxDistance;
}

void Entry::SetForceMaxAngle(float angle) {
    m_forceMaxAngle = angle;
}

float Entry::GetForceMaxAngle() {
    return m_forceMaxAngle;
}

void Entry::SetForceMinAngularImpulse(float angularImpulse) {
    m_forceMinAngularImpulse = angularImpulse;
}

float Entry::GetForceMinAngularImpulse() {
    return m_forceMinAngularImpulse;
}

void Entry::SetForceMaxAngularImpulse(float angularImpulse) {
    m_forceMaxAngularImpulse = angularImpulse;
}

float Entry::GetForceMaxAngularImpulse() {
    return m_forceMaxAngularImpulse;
}

b2Vec2 Entry::GetRandomForce() {
    b2Vec2 force;
    float angle = m_rotation + m_rotationOffset;
    if (m_forceMaxAngle > 0 || m_forceMaxDistance > 0) {
        float randomAngle = CMath::Random(0.0f, m_forceMaxAngle);
        angle = angle - m_forceMaxAngle/2 + randomAngle;
        float randomDistance = CMath::Random(m_forceMinDistance, m_forceMaxDistance);
        force.x = cos(angle) * randomDistance;
        force.y = sin(angle) * randomDistance;
    } else {
        force.x = 0;
        force.y = 0;
    }
    return force;
}

void Entry::SetState(int state) {
    m_state = state;
    if (m_state == ENTRY_STATE_OPENING) {
        m_animation->SetBackwards(true);
        m_animation->Reset();
    } else if(m_state == ENTRY_STATE_CLOSING) {
        m_animation->SetBackwards(false);
        m_animation->Reset();
    }
}

void Entry::OnInit() {
    m_timerRef = SDL_GetTicks();
}

void Entry::OnLoop() {
    if (m_state == ENTRY_STATE_CLOSED) {
        if (m_timerRef < 0 || m_timerRef + m_openTimer > SDL_GetTicks())
            return;
        m_timerRef = -1;
        Open();
    } else if (m_state == ENTRY_STATE_OPEN) {
        if (m_units > 0) {
            if (m_timerRef + m_interval < SDL_GetTicks()) {
                m_timerRef = SDL_GetTicks();
                CUnit* unit = new CUnit(this->GetLayer());
                unit->SetX(this->GetX());
                unit->SetY(this->GetY());
                unit->SetBody();
                ((WorldLayer*)this->GetLayer())->AddUnit(unit);
                unit->GetBody()->ApplyLinearImpulse( GetRandomForce(), unit->GetBody()->GetWorldCenter() );
                float angularImpulse = CMath::Random(m_forceMinAngularImpulse, m_forceMaxAngularImpulse);
                angularImpulse = m_forceMinAngularImpulse - m_forceMaxAngularImpulse/2 + angularImpulse;
                unit->GetBody()->ApplyAngularImpulse(angularImpulse);
                m_units--;
            }
        }
    } else if (m_state == ENTRY_STATE_OPENING) {
        m_animation->OnAnimate();
        if (!m_animation->IsOngoing()) 
            Open();
    } else if (m_state == ENTRY_STATE_CLOSING) {
        m_animation->OnAnimate();
    }
}
