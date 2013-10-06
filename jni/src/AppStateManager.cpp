#include "AppStateManager.h"

#include "AppStateIntro.h"
#include "AppStateGame.h"

AppState* AppStateManager::m_activeAppState = 0;
SDL_Renderer* AppStateManager::m_renderer = NULL;

void AppStateManager::OnEvent(SDL_Event* Event) {
    if(m_activeAppState) m_activeAppState->OnEvent(Event);
}

void AppStateManager::OnLoop() {
    if(m_activeAppState) m_activeAppState->OnLoop();
}

void AppStateManager::OnRender(SDL_Renderer* Renderer) {
    if(m_activeAppState) m_activeAppState->OnRender(Renderer);
}

void AppStateManager::SetActiveAppState(int AppStateID) {
    if (m_renderer) {
        if(m_activeAppState) m_activeAppState->OnDeactivate();
        if(AppStateID == APPSTATE_NONE)
            m_activeAppState = 0;
        if(AppStateID == APPSTATE_INTRO)
            m_activeAppState = AppStateIntro::GetInstance();
        if(AppStateID == APPSTATE_GAME)
            m_activeAppState = AppStateGame::GetInstance();
        if(m_activeAppState)
            m_activeAppState->OnActivate(m_renderer);
    }
}

AppState* AppStateManager::GetActiveAppState() {
    return m_activeAppState;
}

void AppStateManager::SetRenderer(SDL_Renderer* Renderer) {
    m_renderer = Renderer;
}
