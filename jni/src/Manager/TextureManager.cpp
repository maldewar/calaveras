#include "TextureManager.h"
#include "../Util/PathUtil.h"
#include "../Util/Log.h"
#include "../Util/CMath.h"

SDL_Renderer* TextureManager::m_renderer;
std::unordered_map<std::string, SDL_Texture*> TextureManager::m_textures;
std::unordered_map<std::string, int> TextureManager::m_usages;

void TextureManager::Init(SDL_Renderer* renderer) {
  m_renderer = renderer;
};

SDL_Texture* TextureManager::RequestTexture(std::string& path) {
  if (m_textures.count(path) > 0) {
    m_usages[path]++;
    return m_textures[path];
  }
  SDL_Texture* texture;
  std::string full_path = PathUtil::GetCategoryFile("sprite",
                              path,
                              CMath::GetMToPxRatio());
  if ((texture = IMG_LoadTexture(m_renderer, full_path.c_str())) == NULL) {
   return NULL;
  }
  m_textures[path] = texture;
  m_usages[path] = 1;
  return texture;
};

void TextureManager::ReleaseTexture(std::string& path) {
  if (m_textures.count(path) > 0) {
    m_usages[path]--;
    if (m_usages[path] == 0) {
      SDL_DestroyTexture(m_textures[path]);
      m_textures.erase(path);
      m_usages.erase(path);
    }
  }
};

SDL_Renderer* TextureManager::GetRenderer() {
  return m_renderer;
};

bool TextureManager::GetInfo(std::string path, int& width, int& height) {
  if (m_textures.count(path) > 0) {
    int result = SDL_QueryTexture(m_textures[path], nullptr, nullptr, &width, &height);
    if (result == 0)
      return true;
  }
  return false;
};
