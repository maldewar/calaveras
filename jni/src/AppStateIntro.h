#ifndef __APPSTATEINTRO_H__
    #define __APPSTATEINTRO_H__
 
#include "AppState.h"
 
class AppStateIntro : public AppState {
    private:
        static AppStateIntro Instance;
        SDL_Texture* m_textureLogo;
        int StartTime;
 
    private:
        AppStateIntro();
 
    public:
        void OnActivate(SDL_Renderer* Renderer);
        void OnDeactivate();
        void OnLoop();
        void OnRender(SDL_Renderer* Renderer);
 
    public:
        static AppStateIntro* GetInstance();
};
 
#endif
