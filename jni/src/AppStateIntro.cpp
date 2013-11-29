#include "AppStateIntro.h"
#include "AppStateManager.h"
#include "Util/TextureUtil.h"
 
AppStateIntro AppStateIntro::Instance;
 
AppStateIntro::AppStateIntro() {
    m_textureLogo = NULL;
}
 
void AppStateIntro::OnActivate(SDL_Renderer* Renderer) {
    m_textureLogo = TextureUtil::LoadTexture("logo.bmp", Renderer);
    StartTime = SDL_GetTicks();
}
 
void AppStateIntro::OnDeactivate() {
    if(m_textureLogo) {
        SDL_DestroyTexture(m_textureLogo);
        m_textureLogo = NULL;
    }
}
 
void AppStateIntro::OnLoop() {
    if(StartTime + 1000 < SDL_GetTicks()) {
        AppStateManager::SetActiveAppState(APPSTATE_MAIN);
    }
}
 
void AppStateIntro::OnRender(SDL_Renderer* Renderer) {
    if(m_textureLogo) {
        TextureUtil::OnDraw(0, 0, m_textureLogo, Renderer);
    }
}
 
AppStateIntro* AppStateIntro::GetInstance() {
    return &Instance;
}
