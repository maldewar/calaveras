#ifndef __APPSTATEGAME_H__
    #define __APPSTATEGAME_H__
/**
 * Max zoom level allowed.
 */
const float GAME_ZOOM_MAX = 1.2f;
/**
 * Min zoom level allowed.
 */
const float GAME_ZOOM_MIN = 0.4f;
/**
 * Default zoom level when loading a scene.
 */
const float GAME_ZOOM_DEFAULT = 1.0f;
/**
 * Controls how fast the zoom is made using multitouch gesture.
 */
const float GAME_ZOOM_FACTOR = 1.0f;

#include "AppState.h"
#include "Model/Scene.h"
#include "Model/SceneExt.h"
#include "Renderer/SceneRenderer.h"
#include "Engine/Camera.h"
#include "Engine/RayCastTool.h" //TODO: rename to SelectTool
#include "Engine/RocketGlue.h"
 
class AppStateGame : public AppState {
    private:
        static AppStateGame Instance;
        Camera* m_camera;
        RayCastTool* m_selectTool;
        SceneRenderer* m_sceneRenderer;
        int m_act;
        int m_level;
        Scene* m_scene;
        SceneExt* m_sceneExt;
        Vector2* m_tmpVector;
        int m_startTime;
        bool m_pause;
        bool m_usingSelectTool;
        float m_zoom;
        SDL_Rect m_viewport;
        bool m_isZooming;
        bool m_isTracking;
        Rocket::Core::Element* m_returnBtn;
        Rocket::Core::Element* m_pauseBtn;
        Rocket::Core::Element* m_selectBtn;
        Rocket::Controls::ElementForm* m_debugForm;
        Rocket::Controls::ElementForm* m_topToolsForm;
        Rocket::Controls::ElementForm* m_bottomToolsForm;
 
    private:
        AppStateGame();

    public:
        enum {
            STATE_DEFAULT,
            STATE_PAUSE
        };
 
    public:
        void OnActivate(SDL_Renderer* Renderer);
        void OnDeactivate();
        void OnLoop();
        void OnRender(SDL_Renderer* renderer);
        void Update();
        static AppStateGame* GetInstance();
        SceneExt* GetSceneExt();
        
        //Events
        void OnFingerDown(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId);
        void OnFingerUp(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId);
        void OnFingerMove(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId);
        void OnMultiGesture(float mDTheta, float mDDist, float mX, float mY, Uint16 mFingers);

        // TOOLS RELATED FUNCTIONS
        void SetPause(bool pause);
        bool IsPaused();
        void TogglePause();
        void SetUsingSelectTool(bool usingSelectTool);
        bool IsUsingSelectTool();
        void ToggleUsingSelectTool();
        void BeginSelection(float x, float y);
        void EndSelection();
        
        void SetParams(bool dummy, ...);
};
 
#endif
