#include "AppStateCinematic.h"
#include "AppStateManager.h"
#include "Util/TextureUtil.h"
 
AppStateCinematic AppStateCinematic::Instance;
 
AppStateCinematic::AppStateCinematic() {
    m_textureLogo = NULL;
}
 
void AppStateCinematic::OnActivate(SDL_Renderer* Renderer) {
    m_textureLogo = TextureUtil::LoadTexture("logo.bmp", Renderer);
    StartTime = SDL_GetTicks();
}
 
void AppStateCinematic::OnDeactivate() {
    if(m_textureLogo) {
        SDL_DestroyTexture(m_textureLogo);
        m_textureLogo = NULL;
    }
}
 
void AppStateCinematic::OnLoop() {
}
 
void AppStateCinematic::OnRender(SDL_Renderer* Renderer) {
    if(m_textureLogo) {
        TextureUtil::OnDraw(0, 0, m_textureLogo, Renderer);
    }
}
 
AppStateCinematic* AppStateCinematic::GetInstance() {
    return &Instance;
}
