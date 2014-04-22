#include "TextureUtil.h"
#include "SurfaceUtil.h"
#include "Log.h"

std::unordered_map<std::string, SDL_Texture*> TextureUtil::m_textures;

SDL_Texture* TextureUtil::LoadTexture(std::string file, SDL_Renderer* renderer) {
    if (m_textures.count(file) > 0)
        return m_textures[file];
    SDL_Texture* texture;
    if ((texture = IMG_LoadTexture(renderer, file.c_str())) == NULL) {
        return NULL;
    }
    m_textures[file] = texture;
    return texture;
}

SDL_Texture* TextureUtil::LoadTexture(std::string file, int width, int height, SDL_Renderer* renderer) {
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(file.c_str());
    if (surface) {
        SDL_Rect dstRect;
        dstRect.x = 0;
        dstRect.y = 0;
        dstRect.w = width;
        dstRect.h = height;
        SDL_Surface* dstSurface = SurfaceUtil::GetSurface(width, height);
        int result = SDL_BlitScaled(surface, NULL, dstSurface, &dstRect);
        texture = SDL_CreateTextureFromSurface(renderer, dstSurface);
        SDL_FreeSurface(surface);
        SDL_FreeSurface(dstSurface);
    }
    return texture;
}

void TextureUtil::LoadTextures(std::vector<std::string> files, SDL_Renderer* renderer) {
    for (auto &file : files) {
        LoadTexture(file, renderer);
    }
}

SDL_Texture* TextureUtil::GetTexture(std::string file) {
    if (m_textures.count(file) == 0)
        return NULL;
    return m_textures[file];
}

void TextureUtil::PurgeTexture(std::string file) {
    if (m_textures.find(file) != m_textures.end())
        SDL_DestroyTexture(m_textures[file]);
    m_textures.erase(file);
}

void TextureUtil::Flush() {
    for ( auto &it: m_textures )
        SDL_DestroyTexture(it.second);
    m_textures.erase(m_textures.begin(), m_textures.end());
}

bool TextureUtil::OnDraw(int X, int Y, SDL_Texture* texture, SDL_Renderer* renderer) {
    if(texture == NULL) {
        return false;
    }
    SDL_Rect pos;
    pos.x = X;
    pos.y = Y;
    SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(renderer, texture, NULL, &pos);
    return true;
}
