#include "CApp.h"
#include "Util/CTexture.h"
#include "Util/CText.h"
#include "Engine/CAnimationCatalog.h"
#include "Engine/AreaCatalog.h"

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    if((m_window = SDL_CreateWindow("Hello World!", 0, 0, 0, 0, SDL_WINDOW_SHOWN)) == NULL) {
        //TODO set window title from constant
        return false;
    }
    int w,h;
    SDL_GetWindowSize(m_window, &w, &h);
    CMath::SetFactor(w, h);
    if((m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL ) {
        return false;
    }
    CAnimationCatalog::Init(m_renderer);
    AreaCatalog::Init(m_renderer);
    m_surface = SDL_GetWindowSurface(m_window);
    if(TTF_Init() == -1) {
        return false;
    }
    if((m_texture = CTexture::LoadTexture("image.bmp",m_renderer)) == NULL) {
        return false;
    }
    CTexture::LoadTexture("calavera.png", m_renderer);
    CTexture::LoadTexture("entry.png", m_renderer);
    FPSManager::Init();
    m_text = CText::GetTextureSolid("Leela", "font/SourceSansPro-Regular.ttf", {255,255,0,255}, 22, m_renderer);
    AppStateManager::SetRenderer(m_renderer);
    AppStateManager::SetActiveAppState(APPSTATE_INTRO);
    return true;
}
