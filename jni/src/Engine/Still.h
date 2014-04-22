#ifndef _STILL_H_
    #define _STILL_H_

#include <Box2D.h>
#include "../Model/Elem.h"
#include "Sprite.h"

/**
 * Models an Exit to the scene.
 * This element takes Unit instances in to score them to the scene.
 */
class Still : public Elem
{
    private:
        SDL_Texture* m_texture;
        Sprite* m_sprite;

    public:
        Still();
        void SetSprite(Sprite* sprite);
        Sprite* GetSprite();
        void SetTexture(SDL_Texture* texture);
        SDL_Texture* GetTexture();
        SDL_Rect* GetSrcRect();
        SDL_Rect* GetDstRect(int centerX, int centerY);
        void OnInit();
        void OnLoop();

};
#endif
