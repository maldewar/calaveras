#include "RendererUtil.h"

Uint8 RendererUtil::m_red   = 255;
Uint8 RendererUtil::m_green = 255;
Uint8 RendererUtil::m_blue  = 255;
Uint8 RendererUtil::m_alpha = 255;

void RendererUtil::RememberColor(SDL_Renderer* renderer) {
    SDL_GetRenderDrawColor(renderer, &m_red, &m_green, &m_blue, &m_alpha);
};

void RendererUtil::ResetColor(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, m_red, m_green, m_blue, m_alpha);
};

void RendererUtil::SetColor(SDL_Renderer* renderer, Color color) {
    SetColor(renderer, color, 255);
};

void RendererUtil::SetColor(SDL_Renderer* renderer, Color color, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, GetRed(color), GetGreen(color), GetBlue(color), alpha);
    if (alpha < 255)
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    else
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
};

Uint8 RendererUtil::GetRed(Color color) {
    switch(color) {
        case GRAY20:
            return 51;
        case GRAY40:
            return 102;
        case GRAY60:
            return 153;
        case GRAY80:
            return 204;
        case WHITE:
        case RED:
        case YELLOW:
        case ORANGE:
            return 255;
        default:
            return 0;
    }
};

Uint8 RendererUtil::GetGreen(Color color) {
    switch(color) {
        case GRAY20:
            return 51;
        case GRAY40:
            return 102;
        case GRAY60:
            return 153;
        case GRAY80:
            return 204;
        case WHITE:
        case GREEN:
        case YELLOW:
            return 255;
        case ORANGE:
            return 128;
        default:
            return 0;
    }
};

Uint8 RendererUtil::GetBlue(Color color) {
    switch(color) {
        case GRAY20:
            return 51;
        case GRAY40:
            return 102;
        case GRAY60:
            return 153;
        case GRAY80:
            return 204;
        case WHITE:
        case BLUE:
            return 255;
        default:
            return 0;
    }
};
