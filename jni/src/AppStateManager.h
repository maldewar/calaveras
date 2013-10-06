#ifndef __CAPPSTATEMANAGER_H__
    #define __CAPPSTATEMANAGER_H__

#include "AppState.h"

enum {
    APPSTATE_NONE,
    APPSTATE_INTRO,
    APPSTATE_GAME
};

class AppStateManager {
    private:
        static AppState* m_activeAppState;
        static SDL_Renderer* m_renderer;

    public:
        static void SetRenderer(SDL_Renderer* Renderer);
        static void OnEvent(SDL_Event* Event);
        static void OnLoop();
        static void OnRender(SDL_Renderer* Renderer);

    public:
        static void SetActiveAppState(int AppStateID);
        static AppState* GetActiveAppState();
};

#endif
