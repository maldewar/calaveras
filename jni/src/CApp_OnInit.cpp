#include "CApp.h"
#include "Util/TextureUtil.h"
#include "Util/Text.h"
#include "Manager/ConfigManager.h"
#include "Manager/TextureManager.h"
#include "Engine/ActorCatalog.h"
#include "Engine/AnimationCatalog.h"
#include "Engine/StillCatalog.h"
#include "Engine/AreaCatalog.h"
#include "Engine/BgCatalog.h"
#include "Engine/I18NCatalog.h"

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    if((m_window = SDL_CreateWindow("Hello World!", 0, 0, 0, 0, SDL_WINDOW_SHOWN)) == NULL) {
        //TODO set window title from constant
        return false;
    }
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); //Antialising stuff.
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8); //Antialising stuff.
    int w,h;
    SDL_GetWindowSize(m_window, &w, &h);
    AppStateManager::SetWindowWidth(w);
    AppStateManager::SetWindowHeight(h);
    AppStateManager::SetWindow(m_window);
    CMath::SetFactor(w, h);
    if((m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL ) {
        return false;
    }
    ConfigManager::Init();
    TextureManager::Init(m_renderer);
    ActorCatalog::Init();
    AnimationCatalog::Init(m_renderer);
    StillCatalog::Init(m_renderer);
    AreaCatalog::Init(m_renderer);
    BgCatalog::Init(m_renderer);
    I18NCatalog::AddFile("ui","ui.json");
    I18NCatalog::Init();
    m_surface = SDL_GetWindowSurface(m_window);
    if(TTF_Init() == -1) {
        return false;
    }
    FPSManager::Init();
    m_text = Text::GetTextureSolid("Leela", "font/SourceSansPro-Regular.ttf", {255,255,0,255}, 22, m_renderer);
    AppStateManager::SetRenderer(m_renderer);
    AppStateManager::SetActiveAppState(APPSTATE_INTRO);
    return true;
}
