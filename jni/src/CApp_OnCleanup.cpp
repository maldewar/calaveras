#include "CApp.h"
#include "Util/Text.h"
#include "Util/TextureUtil.h"
#include "Engine/I18NCatalog.h"

void CApp::OnCleanup() {
    I18NCatalog::Flush();
    AppStateManager::SetActiveAppState(APPSTATE_NONE);
    Text::Flush();
    TextureUtil::Flush();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
