#include "Still.h"
#include "../Util/Log.h"

Still::Still() : Elem() {
}

void Still::SetTexture(SDL_Texture* texture) {
    m_texture = texture;
}

SDL_Texture* Still::GetTexture() {
    return m_texture;
}

void Still::SetSprite(Sprite* sprite) {
    m_sprite = sprite;
}

Sprite* Still::GetSprite() {
    return m_sprite;
}

SDL_Rect* Still::GetSrcRect() {
    if (m_sprite)
        return m_sprite->GetTile(0);
    return NULL;
}

SDL_Rect* Still::GetDstRect(int centerX, int centerY) {
    if (m_sprite)
        return m_sprite->GetDstTile(0, centerX, centerY);
    return NULL;
}

void Still::OnInit() {};

void Still::OnLoop() {};
