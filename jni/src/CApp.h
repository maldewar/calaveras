#ifndef _CAPP_H_
    #define _CAPP_H_
 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Event.h"
#include "FPS.h"
#include "AppStateManager.h"
#include "Common/FPSManager.h"
#include "Util/File.h"
#include "Util/CMath.h"
 
class CApp : public Event {
    private:
        bool m_running;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        SDL_Surface* m_surface;
        SDL_Texture* m_text;

    public:
        CApp();
        int OnExecute();

    public:
        bool OnInit();
        void OnEvent(SDL_Event* Event);
        void OnExit();
        void OnLoop();
        void OnRender(SDL_Renderer* Renderer);
        void OnCleanup();
};
 
#endif
