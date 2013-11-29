#include "AppStateGame.h"
#include "AppStateManager.h"
#include "Manager/SceneLoader.h"
#include "Event/EventChangeAppState.h"
#include "Event/EventPauseGame.h"
#include "Util/CMath.h"
#include "Util/CLog.h"
 
AppStateGame AppStateGame::Instance;
 
AppStateGame::AppStateGame() : AppState() {
    m_sceneRenderer = new SceneRenderer();
    m_camera = new Camera();
    m_act = 0;
    m_level = 0;
    m_scene = NULL;
}
 
void AppStateGame::OnActivate(SDL_Renderer* Renderer) {
    m_zoom = GAME_ZOOM_DEFAULT;
    m_viewport.x = 0;
    m_viewport.y = 0;
    m_viewport.w = 0;
    m_viewport.h = 0;
    m_startTime = 0;
    m_pause = false;
    m_isZooming = false;
    CLog::Log("AppStateGame::OnActivate()");
    SceneLoader* sceneLoader = new SceneLoader();
    m_scene = sceneLoader->LoadScene(m_act, m_level);
    m_scene->OnInit();
    //delete sceneLoader;
    m_sceneRenderer->Activate(m_scene, Renderer);
    CLog::Log("New Scene Loaded width:%f, height:%f", m_scene->GetWidth(), m_scene->GetHeight());
    m_startTime = SDL_GetTicks();
    SDL_GetRendererOutputSize(Renderer, &m_viewport.w, &m_viewport.h);
    m_camera->SetWidth(m_viewport.w);
    m_camera->SetHeight(m_viewport.h);
    m_camera->SetSceneWidth(CMath::MToPx(m_scene->GetWidth()));
    m_camera->SetSceneHeight(CMath::MToPx(m_scene->GetHeight()));
    m_camera->SetBonus(0,0,200,200);
    CLog::Log("RendererOutputSize w:%d h:%d", m_viewport.w, m_viewport.h);
    LoadDocument("ui/game.html");
    if (m_rocketDocument) {
        EventChangeAppState* returnOnClick = new EventChangeAppState(APPSTATE_MAIN);
        EventPauseGame* pauseOnClick = new EventPauseGame(this);
        m_returnBtn = m_rocketDocument->GetElementById("returnBtn");
        m_pauseBtn = m_rocketDocument->GetElementById("pauseBtn");
        if (m_returnBtn)
            m_returnBtn->AddEventListener("click", returnOnClick, false);
        if (m_pauseBtn)
            m_pauseBtn->AddEventListener("click", pauseOnClick, false);
    }
}
 
void AppStateGame::OnDeactivate() {
    CLog::Log("AppStateGame::OnDeactivate()");
    m_sceneRenderer->Deactivate();
    UnloadDocument();
    //TODO: clean scene.
}
 
void AppStateGame::OnLoop() {
    if (!m_pause) {
        m_scene->OnLoop();
    }
    UpdateDocument();
}
 
void AppStateGame::OnRender(SDL_Renderer* renderer) {
    m_sceneRenderer->Render(m_camera);
    RenderDocument();
}
 
AppStateGame* AppStateGame::GetInstance() {
    return &Instance;
}

void AppStateGame::OnFingerMove(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId) {
    if (!m_isZooming) {
        m_camera->Move(mDX, mDY);
    }
    m_isZooming = false;
}

void AppStateGame::OnMultiGesture(float dTheta, float dDist, float x, float y, Uint16 fingers) {
    m_isZooming = true;
    m_camera->StepZoom(dDist, x, y);
}

void AppStateGame::Pause(bool pause) {
    m_pause = pause;
}

void AppStateGame::TogglePause() {
    if (m_pause)
        m_pause = false;
    else
        m_pause = true;
}

void AppStateGame::SetParams(bool dummy, ...) {
    CLog::Log("AppStateGame::SetParams");
    va_list params;
    va_start(params, dummy);
    m_act = va_arg(params, int);
    m_level = va_arg(params, int);
    CLog::Log("Parameters set to act:%d level:%d", m_act, m_level);
    va_end(params);
}
