#ifndef __CAPPSTATEMANAGER_H__
    #define __CAPPSTATEMANAGER_H__

#include "AppState.h"
#include "Engine/RocketGlue.h"

enum {
    APPSTATE_NONE,
    APPSTATE_INTRO,
    APPSTATE_MAIN,
    APPSTATE_GAME,
    APPSTATE_CINEMATIC
};

class AppStateManager {
    private:
        static AppState* m_activeAppState;
        static SDL_Renderer* m_renderer;
        static Rocket::Core::Context* m_rocketContext;
        static int m_windowWidth;
        static int m_windowHeight;

    public:
        static void SetRenderer(SDL_Renderer* Renderer);
        static void OnEvent(SDL_Event* Event);
        static void OnLoop();
        static void OnRender(SDL_Renderer* Renderer);
        static void SetWindowWidth(int windowWidth);
        static int GetWindowWidth();
        static void SetWindowHeight(int windowHeight);
        static int GetWindowHeight();
        static Rocket::Core::Context* GetRocketContext();

    public:
        static void SetActiveAppState(int appStateId);
        static void SetAppStateToGame(int act, int level);
        static void SetAppStateToCinematic(int id);
        static AppState* GetActiveAppState();

    private:
        static void InitRocketContext();
        static void SetActiveAppState(int appStateId, bool activate);
};

#endif
