#include "CApp.h"
#include "Util/CText.h"
#include "Util/CTexture.h"

void CApp::OnCleanup() {
    AppStateManager::SetActiveAppState(APPSTATE_NONE);
    CText::Flush();
    CTexture::Flush();
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
