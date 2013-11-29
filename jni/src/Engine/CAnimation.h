#ifndef _CANIMATION_H_
    #define _CANIMATION_H_

#include <SDL.h>
#include "CSprite.h"

const int ANIM_TYPE_LINEAR = 0;
const int ANIM_TYPE_LOOP   = 1;
const int ANIM_TYPE_WAVE   = 2;

/**
 *  A test class. A more elaborate class description.
 */
class CAnimation {
    private:
        int m_type;
        int m_play;
        SDL_Texture* m_texture;
        CSprite* m_sprite;
        int m_currentFrame;
        int m_frameInc;
        int m_framerate;
        int m_maxFrames;
        bool m_backwards;
        long m_oldTime;

    public:
        CAnimation();
        void Play();
        void Pause();
        void Reset();
        bool IsOngoing();
        void SetBackwards(bool backwards);
        bool IsBackwards();
        void SetType(int type);
        int GetType();
        bool OnAnimate();
        void SetMaxFrames(int maxFrames);
        int GetMaxFrames();
        void SetFramerate(int framerate);
        int GetFramerate();
        void SetCurrentFrame(int frame);
        int GetCurrentFrame();
        void SetTexture(SDL_Texture* texture);
        SDL_Texture* GetTexture();
        void SetSprite(CSprite* sprite);
        CSprite* GetSprite();
        SDL_Rect* GetSrcRect();
        SDL_Rect* GetDstRect(int centerX, int centerY);

};

#endif
