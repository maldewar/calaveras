#include "Exit.h"
#include "Unit.h"
#include "WorldLayer.h"
#include "../Manager/BoxMaker.h"
#include "../Engine/AnimationCatalog.h"
#include "../Util/Log.h"

Exit::Exit() : LayeredElem() {
    m_type = ELEM_TYPE_EXIT;
    m_state = EXIT_STATE_OPEN;
    m_units = 0;
    m_capacity = 0;
    m_open = false;
    m_openTimer = 5000;
    m_timerRef = 0;
    m_rotationOffset = M_PI_2 * -1;
    SetAnimation();
}

Exit::Exit(Layer* layer) : Exit() {
    m_layer = layer;
}

void Exit::SetAnimation() {
    m_animation = AnimationCatalog::GetByType(m_type);
    if (m_animation) {
        m_animation->GetSprite()->SetDstWidth(CMath::MToPxInt(0.20f));
        m_animation->GetSprite()->SetDstHeight(CMath::MToPxInt(0.07f));
        if (m_state == EXIT_STATE_CLOSED || m_state == EXIT_STATE_OPENING)
            m_animation->SetCurrentFrame(m_animation->GetMaxFrames() - 1);
    }
}

Animation* Exit::GetAnimation() {
    return m_animation;
}

void Exit::SetCapacity(int capacity) {
    if (capacity >= 0)
        m_capacity = capacity;
}

int Exit::GetCapacity() {
    return m_capacity;
}

int Exit::GetUnits() {
    return m_units;
}

void Exit::Open() {
    if (m_state == EXIT_STATE_CLOSED)
        SetState(EXIT_STATE_OPENING);
    else
        SetState(EXIT_STATE_OPEN);
}

void Exit::Close() {
    if (m_state == EXIT_STATE_OPEN)
        SetState(EXIT_STATE_CLOSING);
}

void Exit::SetOpen(bool isOpen) {
    if (isOpen)
        Open();
    else
        Close();
}

void Exit::SetOpenTimer(int openTimer) {
    m_openTimer = openTimer;    
}

void Exit::SetInterval(int interval) {
    if (interval >= 0) {
        m_interval = interval;
        m_units = m_capacity;
    }
}

int Exit::GetInterval() {
    return m_interval;
}

void Exit::SetState(int state) {
    m_state = state;
    if (m_state == EXIT_STATE_OPENING) {
        m_animation->SetBackwards(true);
        m_animation->Reset();
    } else if(m_state == EXIT_STATE_CLOSING) {
        m_animation->SetBackwards(false);
        m_animation->Reset();
    }
}

void Exit::OnInit() {
    m_timerRef = SDL_GetTicks();
}

void Exit::OnLoop() {
    if (m_state == EXIT_STATE_CLOSED) {
        if (m_timerRef < 0 || m_timerRef + m_openTimer > SDL_GetTicks())
            return;
        m_timerRef = -1;
        Open();
    } else if (m_state == EXIT_STATE_OPEN) {
        /*
        if (m_units > 0) {
            if (m_timerRef + m_interval < SDL_GetTicks()) {
                m_timerRef = SDL_GetTicks();
                Unit* unit = new Unit(this->GetLayer());
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
        */
    } else if (m_state == EXIT_STATE_OPENING) {
        m_animation->OnAnimate();
        if (!m_animation->IsOngoing()) 
            Open();
    } else if (m_state == EXIT_STATE_CLOSING) {
        m_animation->OnAnimate();
    }
}
