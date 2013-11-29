#ifndef __APPSTATECINEMATIC_H__
    #define __APPSTATECINEMATIC_H__
 
#include "AppState.h"
 
class AppStateCinematic : public AppState {
    private:
        static AppStateCinematic Instance;
        SDL_Texture* m_textureLogo;
        int StartTime;
 
    private:
        AppStateCinematic();
 
    public:
        void OnActivate(SDL_Renderer* Renderer);
        void OnDeactivate();
        void OnLoop();
        void OnRender(SDL_Renderer* Renderer);
 
    public:
        static AppStateCinematic* GetInstance();
};
 
#endif
