#ifndef _CTEXT_H_
    #define _CTEXT_H_
 
#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <string>

enum {
    TEXT_SOLID,
    TEXT_SHADED,
    TEXT_BLENDED
};

class CText {
    public:
        CText();

    private:
        static std::unordered_map<std::string, TTF_Font*> m_fonts;

    private:
        static SDL_Surface* GetSurface(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size, int style, int quality);
        static SDL_Texture* GetTexture(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size, int style, SDL_Renderer* renderer, int quality);

    public:
        static SDL_Surface* GetSurfaceSolid(std::string text, std::string file, SDL_Color color, int size);
        static SDL_Surface* GetSurfaceSolid(std::string text, std::string file, SDL_Color color, int size, int style);
        static SDL_Surface* GetSurfaceShaded(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size);
        static SDL_Surface* GetSurfaceShaded(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size, int style);
        static SDL_Surface* GetSurfaceBlended(std::string text, std::string file, SDL_Color color, int size);
        static SDL_Surface* GetSurfaceBlended(std::string text, std::string file, SDL_Color color, int size, int style);
        static SDL_Texture* GetTextureSolid(std::string text, std::string file, SDL_Color color, int size, SDL_Renderer* renderer);
        static SDL_Texture* GetTextureSolid(std::string text, std::string file, SDL_Color color, int size, int style, SDL_Renderer* renderer);
        static SDL_Texture* GetTextureShaded(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size, SDL_Renderer* renderer);
        static SDL_Texture* GetTextureShaded(std::string text, std::string file, SDL_Color color, SDL_Color bgColor, int size, int style, SDL_Renderer* renderer);
        static SDL_Texture* GetTextureBlended(std::string text, std::string file, SDL_Color color, int size, SDL_Renderer* renderer);
        static SDL_Texture* GetTextureBlended(std::string text, std::string file, SDL_Color color, int size, int style, SDL_Renderer* renderer);
        static void Flush();
};
#endif
