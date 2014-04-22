#ifndef _TEXTUREMANAGER_H_
    #define _TEXTUREMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <unordered_map>

class TextureManager {
  public:
    static void Init(SDL_Renderer* renderer);
    static SDL_Texture* RequestTexture(std::string& path);
    static void ReleaseTexture(std::string& path);
    static SDL_Renderer* GetRenderer();
    static bool GetInfo(std::string path, int& width, int& height);

  private:
    static SDL_Renderer* m_renderer;
    static std::unordered_map<std::string, SDL_Texture*> m_textures;
    static std::unordered_map<std::string, int> m_usages;
};

#endif
