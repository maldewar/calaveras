#ifndef _ANIMATION_H_
    #define _ANIMATION_H_

#include <SDL.h>
#include "Sprite.h"

const int ANIM_TYPE_LINEAR = 0;
const int ANIM_TYPE_LOOP   = 1;
const int ANIM_TYPE_WAVE   = 2;

/**
 *  A test class. A more elaborate class description.
 */
class Animation {
    private:
        int m_type;
        int m_play;
        SDL_Texture* m_texture;
        Sprite* m_sprite;
        int m_currentFrame;
        int m_frameInc;
        int m_framerate;
        int m_maxFrames;
        bool m_backwards;
        long m_oldTime;

    public:
        Animation();
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
        void SetSprite(Sprite* sprite);
        Sprite* GetSprite();
        SDL_Rect* GetSrcRect();
        SDL_Rect* GetDstRect(int centerX, int centerY);

};

#endif
