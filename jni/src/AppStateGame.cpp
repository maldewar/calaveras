#include "AppStateGame.h"
#include "AppStateManager.h"
#include "Manager/CSceneLoader.h"
#include "Renderer/CSceneRenderer.h"
 
AppStateGame AppStateGame::Instance;
 
AppStateGame::AppStateGame() {
    m_scene = NULL;
    m_zoom = GAME_ZOOM_DEFAULT;
    m_viewport.x = 0;
    m_viewport.y = 0;
    m_viewport.w = 0;
    m_viewport.h = 0;
    StartTime = 0;

    m_isZooming = false;
}
 
void AppStateGame::OnActivate(SDL_Renderer* Renderer) {
    CSceneLoader* sceneLoader = new CSceneLoader(1,1);
    m_scene = sceneLoader->LoadScene();
    m_scene->OnInit();
    //delete sceneLoader;
    CLog::Log("Scene width:%f, height:%f", m_scene->GetWidth(), m_scene->GetHeight());
    StartTime = SDL_GetTicks();
    SDL_GetRendererOutputSize(Renderer, &m_viewport.w, &m_viewport.h);
    CLog::Log("Viewport width:%d, height:%d, x:%d, y:%d", m_viewport.w, m_viewport.h, m_viewport.x, m_viewport.y);
}
 
void AppStateGame::OnDeactivate() {
}
 
void AppStateGame::OnLoop() {
    /*if(StartTime + 5000 < SDL_GetTicks()) {
        AppStateManager::SetActiveAppState(APPSTATE_NONE);
    }*/
    m_scene->OnLoop();
}
 
void AppStateGame::OnRender(SDL_Renderer* Renderer) {
    //SDL_RenderSetLogicalSize(m_renderer, 640, 480);
    SDL_RenderSetViewport(Renderer, &m_viewport);
    SDL_RenderSetScale(Renderer, m_zoom, m_zoom);
    if (m_scene) {
        CSceneRenderer::Render(m_scene, Renderer);
    }
    SDL_RenderSetScale(Renderer, 1.0f, 1.0f);
    SDL_RenderSetViewport(Renderer, NULL);
}
 
AppStateGame* AppStateGame::GetInstance() {
    return &Instance;
}

void AppStateGame::OnFingerMove(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId) {
    if (!m_isZooming) {
        const float x = m_viewport.x + mDX * m_viewport.w;
        const float y = m_viewport.y + mDY * m_viewport.h * -1;
        if ((x * -1 + m_viewport.w)/m_zoom <= CMath::MToPx(m_scene->GetWidth()) && x <= 0) {
            m_viewport.x = x;
        }
        if ((y + m_viewport.h)/m_zoom <= CMath::MToPx(m_scene->GetHeight()) && y >= 0)  {
            m_viewport.y = y;
        }
    }
    m_isZooming = false;
}

void AppStateGame::OnMultiGesture(float mDTheta, float mDDist, float mX, float mY, Uint16 mFingers) {
    m_isZooming = true;
    const float zoom = m_zoom + mDDist * GAME_ZOOM_FACTOR;
    const float zoomX = m_viewport.w/zoom;
    const float zoomY = m_viewport.h/zoom;
    if (zoom < GAME_ZOOM_MAX 
        && zoom > GAME_ZOOM_MIN 
        && zoomX < CMath::MToPx(m_scene->GetWidth()) 
        && zoomY < CMath::MToPx(m_scene->GetHeight())) {
        const int xDir = (mX>0.5?1:-1);
        const int yDir = (mY<0.5?1:-1);
        const float x = m_viewport.x + ((zoomX - m_viewport.w/m_zoom) * (mX) * 2 * xDir);
        const float y = m_viewport.y + ((zoomY - m_viewport.h/m_zoom) * (mY) * 2 * yDir);
        //const float x = m_viewport.x + m_viewport.x * (m_zoom/zoom * mX * xDir);
        //const float y = m_viewport.y + m_viewport.y * (m_zoom/zoom * mY * yDir);
        //CLog::Log(" x offset:%f", ((zoomX - m_viewport.w/m_zoom) * (1-mX) * xDir));
        if (x >= 0)
            m_viewport.x = 0;
        else
            if ((x * -1 + m_viewport.w)/zoom <= CMath::MToPx(m_scene->GetWidth()))
                m_viewport.x = x;
            else
                m_viewport.x = m_viewport.x + zoomX - m_viewport.w/m_zoom;
        if (y <= 0)
            m_viewport.y = 0;
        else 
            if ((y + m_viewport.h)/zoom < CMath::MToPx(m_scene->GetHeight()))
                m_viewport.y = y;
            else
                m_viewport.y = CMath::MToPx(m_scene->GetHeight()) - m_viewport.h/m_zoom;

        m_zoom = zoom;
    }
}
