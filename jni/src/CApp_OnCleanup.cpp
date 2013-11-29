#include "CApp.h"
#include "Util/CText.h"
#include "Util/TextureUtil.h"
#include "Engine/I18NCatalog.h"

void CApp::OnCleanup() {
    I18NCatalog::Flush();
    AppStateManager::SetActiveAppState(APPSTATE_NONE);
    CText::Flush();
    TextureUtil::Flush();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
