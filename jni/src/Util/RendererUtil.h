#ifndef _RENDERERUTIL_H_
    #define _RENDERERUTIL_H_

#include <SDL.h>

class RendererUtil {
    private:
        static Uint8 m_red;
        static Uint8 m_green;
        static Uint8 m_blue;
        static Uint8 m_alpha;

    public:
        enum Color{
            WHITE,
            GRAY80,
            GRAY60,
            GRAY40,
            GRAY20,
            BLACK,
            RED,
            GREEN,
            BLUE,
            YELLOW,
            ORANGE
        };

    public:
        static void RememberColor(SDL_Renderer* renderer);
        static void ResetColor(SDL_Renderer* renderer);
        static void SetColor(SDL_Renderer* renderer, Color color);
        static void SetColor(SDL_Renderer* renderer, Color color, Uint8 alpha);

    private:
        static Uint8 GetRed(Color color);
        static Uint8 GetGreen(Color color);
        static Uint8 GetBlue(Color color);
};

#endif
