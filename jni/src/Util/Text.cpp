#include "Text.h"

std::unordered_map<std::string, TTF_Font*> Text::m_fonts;

Text::Text() {
}

SDL_Surface* Text::GetSurface(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size, int style, int quality) {
    TTF_Font* font = NULL;
    if (m_fonts.count(file) == 0) {
        if((font = TTF_OpenFont(file.c_str(), size)) == NULL) {
            return NULL;
        }
        m_fonts[file] = font;
    } else {
        font = m_fonts[file];
    }
    SDL_Surface* surfTemp = NULL;
    switch(quality) {
        case TEXT_SHADED:
            surfTemp = TTF_RenderText_Shaded(font, text.c_str(), color, bgColor);
            break;
        case TEXT_BLENDED:
            surfTemp = TTF_RenderText_Blended(font, text.c_str(), color);
            break;
        default:
            surfTemp = TTF_RenderText_Solid(font, text.c_str(), color);
    }
    return surfTemp;
}

SDL_Texture* Text::GetTexture(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size, int style, SDL_Renderer* renderer, int quality) {
    SDL_Surface* surfTemp = GetSurface(text, file, color, bgColor, size, style, quality);
    SDL_Texture* texture = NULL;
    if ((texture = SDL_CreateTextureFromSurface(renderer, surfTemp)) == NULL) {
        SDL_FreeSurface(surfTemp);
        return NULL;
    }
    SDL_FreeSurface(surfTemp);
    return texture;
}

SDL_Surface* Text::GetSurfaceSolid(std::string text, std::string file, SDL_Color color, int size) {
    return GetSurface(text, file, color, color, size, 0, TEXT_SOLID);
}

SDL_Surface* Text::GetSurfaceSolid(std::string text, std::string file, SDL_Color color, int size, int style) {
    return GetSurface(text, file, color, color, size, style, TEXT_SOLID);
}

SDL_Surface* Text::GetSurfaceShaded(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size) {
    return GetSurface(text, file, color, bgColor, size, 0, TEXT_SHADED);
}

SDL_Surface* Text::GetSurfaceShaded(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size, int style) {
    return GetSurface(text, file, color, bgColor, size, style, TEXT_SHADED);
}

SDL_Surface* Text::GetSurfaceBlended(std::string text, std::string file, SDL_Color color, int size) {
    return GetSurface(text, file, color, color, size, 0, TEXT_BLENDED);
}

SDL_Surface* Text::GetSurfaceBlended(std::string text, std::string file, SDL_Color color, int size, int style) {
    return GetSurface(text, file, color, color, size, style, TEXT_BLENDED);
}

SDL_Texture* Text::GetTextureSolid(std::string text, std::string file, SDL_Color color, int size, SDL_Renderer* renderer) {
    return GetTexture(text, file, color, color, size, 0, renderer, TEXT_SOLID);
}

SDL_Texture* Text::GetTextureSolid(std::string text, std::string file, SDL_Color color, int size, int style, SDL_Renderer* renderer) {
    return GetTexture(text, file, color, color, size, style, renderer, TEXT_SOLID);
}

SDL_Texture* Text::GetTextureShaded(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size, SDL_Renderer* renderer) {
    return GetTexture(text, file, color, bgColor, size, 0, renderer, TEXT_SHADED);
}

SDL_Texture* Text::GetTextureShaded(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size, int style, SDL_Renderer* renderer) {
    return GetTexture(text, file, color, bgColor, size, style, renderer, TEXT_SHADED);
}

SDL_Texture* Text::GetTextureBlended(std::string text, std::string file, SDL_Color color, int size, SDL_Renderer* renderer) {
    return GetTexture(text, file, color, color, size, 0, renderer, TEXT_BLENDED);
}

SDL_Texture* Text::GetTextureBlended(std::string text, std::string file, SDL_Color color, int size, int style, SDL_Renderer* renderer) {
    return GetTexture(text, file, color, color, size, style, renderer, TEXT_BLENDED);
}

void Text::Flush() {
    for(auto i = m_fonts.begin(); i != m_fonts.end(); ++i) {
        TTF_CloseFont(i->second); 
        i->second = NULL;
    }
    m_fonts.clear();
}
