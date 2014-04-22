#include "AppStateManager.h"

#include "AppStateIntro.h"
#include "AppStateMain.h"
#include "AppStateGame.h"
#include "AppStateCinematic.h"
#include "Util/Log.h"

AppState* AppStateManager::m_activeAppState = 0;
SDL_Renderer* AppStateManager::m_renderer = NULL;
SDL_Window* AppStateManager::m_window = NULL;
Rocket::Core::Context* AppStateManager::m_rocketContext = NULL;
int AppStateManager::m_windowWidth = 0;
int AppStateManager::m_windowHeight = 0;

void AppStateManager::OnEvent(SDL_Event* Event) {
    if(m_activeAppState) m_activeAppState->OnEvent(Event);
}

void AppStateManager::OnLoop() {
    if(m_activeAppState) m_activeAppState->OnLoop();
}

void AppStateManager::OnRender(SDL_Renderer* Renderer) {
    if(m_activeAppState) m_activeAppState->OnRender(Renderer);
}

void AppStateManager::SetActiveAppState(int appStateId, bool activate) {
    if (m_renderer) {
        if (!m_rocketContext)
            InitRocketContext();
        if(m_activeAppState) m_activeAppState->OnDeactivate();

        if(appStateId == APPSTATE_NONE)
            m_activeAppState = 0;
        if(appStateId == APPSTATE_INTRO)
            m_activeAppState = AppStateIntro::GetInstance();
        if(appStateId == APPSTATE_MAIN)
            m_activeAppState = AppStateMain::GetInstance();
        if(appStateId == APPSTATE_GAME)
            m_activeAppState = AppStateGame::GetInstance();
        if(appStateId == APPSTATE_CINEMATIC)
            m_activeAppState = AppStateCinematic::GetInstance();

        if(m_activeAppState && activate)
            m_activeAppState->OnActivate(m_renderer);
    }
}

void AppStateManager::SetActiveAppState(int appStateId) {
    SetActiveAppState(appStateId, true);
}

void AppStateManager::SetAppStateToGame(int act, int level) {
    Log::L("AppStateManager::SetAppStateToGame");
    SetActiveAppState(APPSTATE_GAME, false);
    if(m_activeAppState) {
            m_activeAppState->SetParams(true, act, level);
            m_activeAppState->OnActivate(m_renderer);
    }
}

void AppStateManager::SetAppStateToCinematic(int id) {
    SetActiveAppState(APPSTATE_CINEMATIC, false);
    if(m_activeAppState)
            m_activeAppState->OnActivate(m_renderer);
}

AppState* AppStateManager::GetActiveAppState() {
    return m_activeAppState;
}

void AppStateManager::SetRenderer(SDL_Renderer* Renderer) {
    m_renderer = Renderer;
}

void AppStateManager::SetWindow(SDL_Window* Window) {
    m_window = Window;
};

void AppStateManager::SetWindowWidth(int windowWidth) {
    m_windowWidth = windowWidth;
}

int AppStateManager::GetWindowWidth() {
    return m_windowWidth;
}

void AppStateManager::SetWindowHeight(int windowHeight) {
    m_windowHeight = windowHeight;
}

int AppStateManager::GetWindowHeight() {
    return m_windowHeight;
}

SDL_Window* AppStateManager::GetWindow() {
    return m_window;
};

Rocket::Core::Context* AppStateManager::GetRocketContext() {
    return m_rocketContext;
}

void AppStateManager::InitRocketContext() {
    Log::L("About to create rocket context with width:%d height;%d", AppStateManager::GetWindowWidth(), AppStateManager::GetWindowHeight());
    m_rocketContext = RocketInit(m_renderer, "main",
            AppStateManager::GetWindowWidth(),
            AppStateManager::GetWindowHeight());
    Rocket::Core::FontDatabase::LoadFontFace("font/SourceSansPro-Regular.ttf",
            "SansPro",
            Rocket::Core::Font::STYLE_NORMAL,
            Rocket::Core::Font::WEIGHT_BOLD);
}
