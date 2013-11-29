#ifndef _CAPP_H_
    #define _CAPP_H_
 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "CEvent.h"
#include "CFPS.h"
#include "AppStateManager.h"
#include "Common/FPSManager.h"
#include "Util/CFile.h"
#include "Util/CMath.h"
 
class CApp : public CEvent {
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
