#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
    AppStateManager::OnEvent(Event);
}

void CApp::OnExit() {
    m_running = false;
}
