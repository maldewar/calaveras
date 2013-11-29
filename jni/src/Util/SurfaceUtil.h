#ifndef _SURFACEUTIL_H_
    #define _SURFACEUTIL_H_
 
#include <SDL.h>

class SurfaceUtil {
    public:
        static SDL_Surface* GetSurface(int width, int height);
        static void PutPixel32_nolock(SDL_Surface * surface, int x, int y, Uint32 color);
        static void PutPixel24_nolock(SDL_Surface * surface, int x, int y, Uint32 color);
        static void PutPixel16_nolock(SDL_Surface * surface, int x, int y, Uint32 color);
        static void PutPixel8_nolock(SDL_Surface * surface, int x, int y, Uint32 color);
        static void PutPixel32(SDL_Surface * surface, int x, int y, Uint32 color);
        static void PutPixel24(SDL_Surface * surface, int x, int y, Uint32 color);
        static void PutPixel16(SDL_Surface * surface, int x, int y, Uint32 color);
        static void PutPixel8(SDL_Surface * surface, int x, int y, Uint32 color);
};
#endif
