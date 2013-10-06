#include "CTexture.h"

std::unordered_map<std::string, SDL_Texture*> CTexture::m_textures;

SDL_Texture* CTexture::LoadTexture(std::string file, SDL_Renderer* renderer) {
    if (m_textures.count(file) > 0)
        return m_textures[file];
    SDL_Surface* Surf_Temp = NULL;
    if ((Surf_Temp = IMG_Load(file.c_str())) == NULL) {
        return NULL;
    }
    SDL_Texture * Texture = NULL;
    if ((Texture = SDL_CreateTextureFromSurface(renderer, Surf_Temp)) == NULL) {
        SDL_FreeSurface(Surf_Temp);
        return NULL;
    }
    SDL_FreeSurface(Surf_Temp);
    m_textures[file] = Texture;
    return Texture;
}

void CTexture::LoadTextures(std::vector<std::string> files, SDL_Renderer* renderer) {
    for (auto &file : files) {
        LoadTexture(file, renderer);
    }
}

SDL_Texture* CTexture::GetTexture(std::string file) {
    if (m_textures.count(file) == 0)
        return NULL;
    return m_textures[file];
}

void CTexture::PurgeTexture(std::string file) {
    if (m_textures.find(file) != m_textures.end())
        SDL_DestroyTexture(m_textures[file]);
    m_textures.erase(file);
}

void CTexture::Flush() {
    for ( auto &it: m_textures )
        SDL_DestroyTexture(it.second);
    m_textures.erase(m_textures.begin(), m_textures.end());
}

bool CTexture::OnDraw(int X, int Y, SDL_Texture* texture, SDL_Renderer* renderer) {
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
