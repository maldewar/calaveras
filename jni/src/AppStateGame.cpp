#include "AppStateGame.h"
#include "AppStateManager.h"
#include "Manager/SceneLoader.h"
#include "Event/EventChangeAppState.h"
#include "Event/EventSetSettings.h"
#include "Event/EventGameTools.h"
#include "Util/CMath.h"
#include "Util/Log.h"
 
AppStateGame AppStateGame::Instance;
 
AppStateGame::AppStateGame() : AppState() {
    m_sceneRenderer = new SceneRenderer();
    m_camera = new Camera();
    m_act = 0;
    m_level = 0;
    m_scene = NULL;
    m_tmpVector = new Vector2();
}
 
void AppStateGame::OnActivate(SDL_Renderer* Renderer) {
    Log::L("AppStateGame::OnActivate ACTIVATING SCENE.");
    m_zoom = GAME_ZOOM_DEFAULT;
    m_viewport.x = 0;
    m_viewport.y = 0;
    m_viewport.w = 0;
    m_viewport.h = 0;
    m_startTime = 0;
    m_pause = false;
    m_usingSelectTool = false;
    m_isZooming = false;
    m_isTracking = false;
    SceneLoader* sceneLoader = new SceneLoader();
    m_scene = sceneLoader->LoadScene(m_act, m_level);
    m_scene->OnInit();
    m_sceneExt = new SceneExt();
    m_sceneExt->OnInit();
    delete sceneLoader;
    m_sceneRenderer->Activate(m_scene, m_sceneExt, Renderer);
    Log::L("New Scene Loaded width:%f, height:%f", m_scene->GetWidth(), m_scene->GetHeight());
    m_startTime = SDL_GetTicks();
    SDL_GetRendererOutputSize(Renderer, &m_viewport.w, &m_viewport.h);

    m_camera->Reset();
    m_camera->SetWidth(m_viewport.w);
    m_camera->SetHeight(m_viewport.h);
    m_camera->SetSceneWidth(m_scene->GetWidth());
    m_camera->SetSceneHeight(m_scene->GetHeight());
    m_camera->SetBonus(0,0,200,200);

    m_selectTool = new RayCastTool(10, m_sceneExt);
    m_selectTool->SetFilter(UNIT_BODY);
    Log::L("RendererOutputSize w:%d h:%d", m_viewport.w, m_viewport.h);
    LoadDocument("ui/game.html");
    if (m_rocketDocument) {
        EventChangeAppState* returnOnClick = new EventChangeAppState(APPSTATE_MAIN);
        EventSetSettings* setSettings = new EventSetSettings(this);
        EventGameTools* gameTools = new EventGameTools(this);
        m_returnBtn = m_rocketDocument->GetElementById("returnBtn");
        m_pauseBtn = m_rocketDocument->GetElementById("pauseBtn");
        m_selectBtn = m_rocketDocument->GetElementById("selectBtn");
        m_debugForm = dynamic_cast<Rocket::Controls::ElementForm*>(m_rocketDocument->GetElementById("debugForm"));
        m_bottomToolsForm = 
            dynamic_cast<Rocket::Controls::ElementForm*>(m_rocketDocument->GetElementById("bottomToolsForm"));
        m_topToolsForm = 
            dynamic_cast<Rocket::Controls::ElementForm*>(m_rocketDocument->GetElementById("topToolsForm"));
        if (m_returnBtn)
            m_returnBtn->AddEventListener("click", returnOnClick, false);
        if (m_debugForm)
            m_debugForm->AddEventListener("submit", setSettings, false);
        if (m_topToolsForm)
            m_topToolsForm->AddEventListener("submit", gameTools, false);
        if (m_bottomToolsForm)
            m_bottomToolsForm->AddEventListener("submit", gameTools, false);
    }
}
 
void AppStateGame::OnDeactivate() {
    m_sceneRenderer->Deactivate();
    UnloadDocument();
    delete m_scene;
    delete m_sceneExt;
    //TODO: clean scene.
}
 
void AppStateGame::OnLoop() {
    if (!m_pause) {
        m_scene->OnLoop();
        if (m_usingSelectTool) {
            m_selectTool->RayCast(m_scene->GetWorldLayer(),
                        m_sceneExt->GetSelectZenithX(),
                        m_sceneExt->GetSelectZenithY(),
                        Scene::GetGravity()->Angle());
        }
    }
    UpdateDocument();
}
 
void AppStateGame::OnRender(SDL_Renderer* renderer) {
    m_sceneRenderer->Render(m_camera);
    RenderDocument();
};

void AppStateGame::Update() {
    if (m_pause)
        m_pauseBtn->SetClass("enabled", true);
    else
        m_pauseBtn->SetClass("enabled", false);
    if (m_usingSelectTool)
        m_selectBtn->SetClass("enabled", true);
    else
        m_selectBtn->SetClass("enabled", false);
    m_rocketDocument->Update();
};
 
AppStateGame* AppStateGame::GetInstance() {
    return &Instance;
};

SceneExt* AppStateGame::GetSceneExt() {
    return m_sceneExt;
};

void AppStateGame::OnFingerDown(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId) {
    if (m_usingSelectTool) {
        m_tmpVector = m_camera->GetWorldPosition(mX, mY);
        BeginSelection(m_tmpVector->x, m_tmpVector->y);
    }
};

void AppStateGame::OnFingerUp(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId) {
    m_isTracking = false;
    m_usingSelectTool = false;
    EndSelection();
    Update();
};

void AppStateGame::OnFingerMove(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId) {
    if (!m_isZooming) {
        if (!m_isTracking && !m_usingSelectTool && (CMath::GetAbsolute(mDX) > 0.004f || CMath::GetAbsolute(mDY) > 0.004f))
            m_isTracking = true;
        if (m_isTracking)
            m_camera->Move(mDX, mDY);
        if (m_usingSelectTool) {
            m_tmpVector = m_camera->GetWorldPosition(mX, mY);
            m_sceneExt->SetSelectZenithX(m_tmpVector->x);
            m_sceneExt->SetSelectZenithY(m_tmpVector->y);
        }
    }
    m_isZooming = false;
};

void AppStateGame::OnMultiGesture(float dTheta, float dDist, float x, float y, Uint16 fingers) {
    m_isZooming = true;
    m_camera->StepZoom(dDist, x, y);
};

void AppStateGame::SetPause(bool pause) {
    m_pause = pause;
};

bool AppStateGame::IsPaused() {
    return m_pause;
};

void AppStateGame::TogglePause() {
    m_pause = ! m_pause;
};

void AppStateGame::SetUsingSelectTool(bool usingSelectTool) {
    m_usingSelectTool = usingSelectTool;
    if (m_usingSelectTool)
        m_isTracking = false;
};

bool AppStateGame::IsUsingSelectTool() {
    return m_usingSelectTool;
};

void AppStateGame::ToggleUsingSelectTool() {
    if (m_usingSelectTool)
        SetUsingSelectTool(false);
    else
        SetUsingSelectTool(true);
};

void AppStateGame::SetParams(bool dummy, ...) {
    va_list params;
    va_start(params, dummy);
    m_act = va_arg(params, int);
    m_level = va_arg(params, int);
    va_end(params);
};

void AppStateGame::BeginSelection(float x, float y) {
    m_sceneExt->SetIsSelecting(true);
    m_sceneExt->SetSelectZenithX(x);
    m_sceneExt->SetSelectZenithY(y);
};

void AppStateGame::EndSelection() {
    m_sceneExt->SetIsSelecting(false);
};
