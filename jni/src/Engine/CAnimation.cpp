#include "CAnimation.h"

CAnimation::CAnimation() {
    m_type = ANIM_TYPE_LINEAR;
    m_play = true;
    m_texture = NULL;
    m_sprite = NULL;
    m_currentFrame = 0;
    m_frameInc = 1;
    m_backwards = false;
    m_framerate = 500;
    m_maxFrames = 1;
    m_oldTime = SDL_GetTicks();
}

void CAnimation::Play() {
    m_play = true;
}

void CAnimation::Pause() {
    m_play = false;
}

void CAnimation::Reset() {
    m_play = true;
    if (m_backwards) {
        m_frameInc = -1;
        m_currentFrame = m_maxFrames - 1;
    } else {
        m_frameInc = 0;
        m_currentFrame = 0;
    }
    m_oldTime = SDL_GetTicks();
}

bool CAnimation::IsOngoing() {
    if (m_type != ANIM_TYPE_LINEAR)
        return true;
    return m_play;
}

void CAnimation::SetBackwards(bool backwards) {
    m_backwards = backwards;
    if (m_type == ANIM_TYPE_WAVE)
        m_frameInc *= -1;
    else
        if (m_backwards)
            m_frameInc = -1;
        else
            m_frameInc = 1;
}

bool CAnimation::IsBackwards() {
    return m_backwards;
}

void CAnimation::SetType(int type) {
    m_type = type;
    Reset();
}

int CAnimation::GetType() {
    return m_type;
}

bool CAnimation::OnAnimate() {
    if (!m_play)
        return false;
    if (m_oldTime + m_framerate > SDL_GetTicks())
        return false;
    m_oldTime = SDL_GetTicks();
    m_currentFrame += m_frameInc;
    if (m_type == ANIM_TYPE_LINEAR) {
        if (m_backwards)
            if (m_currentFrame == 0)
                m_play = false;
        else
            if (m_currentFrame == m_maxFrames - 1)
                m_play = false;
    } else {
        if (m_backwards) 
            if (m_currentFrame < 0)
                if (m_type == ANIM_TYPE_LOOP)
                    m_currentFrame = m_maxFrames -1;
                else if (m_maxFrames > 1) {
                    m_currentFrame = 1;
                    m_frameInc *= -1;
                }
        else
            if (m_currentFrame >= m_maxFrames )
                if (m_type == ANIM_TYPE_LOOP)
                    m_currentFrame = 0;
                else if (m_maxFrames - 2 >= 0) {
                    m_currentFrame = m_maxFrames -2;
                    m_frameInc *= -1;
                }
    }
    return true;
}

void CAnimation::SetMaxFrames(int maxFrames) {
    m_maxFrames = maxFrames;
}

int CAnimation::GetMaxFrames() {
    return m_maxFrames;
}

void CAnimation::SetFramerate(int framerate) {
    m_framerate = framerate;
}

int CAnimation::GetFramerate() {
    return m_framerate;
}

void CAnimation::SetCurrentFrame(int frame) {
    if (frame >= 0 && frame < m_maxFrames)
        m_currentFrame = frame;
}

int CAnimation::GetCurrentFrame() {
    return m_currentFrame;
}

void CAnimation::SetTexture(SDL_Texture* texture) {
    m_texture = texture;
}

SDL_Texture* CAnimation::GetTexture() {
    return m_texture;
}

void CAnimation::SetSprite(CSprite* sprite) {
    m_sprite = sprite;
}

CSprite* CAnimation::GetSprite() {
    return m_sprite;
}

SDL_Rect* CAnimation::GetSrcRect() {
    if (m_sprite)
        return m_sprite->GetTile(m_currentFrame);
    return NULL;
}

SDL_Rect* CAnimation::GetDstRect(int centerX, int centerY) {
    if (m_sprite)
        return m_sprite->GetDstTile(m_currentFrame, centerX, centerY);
    return NULL;
}
