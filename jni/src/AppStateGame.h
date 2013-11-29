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
#include "Model/CScene.h"
#include "Renderer/SceneRenderer.h"
#include "Engine/Camera.h"
#include "Engine/RocketGlue.h"
 
class AppStateGame : public AppState {
    private:
        static AppStateGame Instance;
        Camera* m_camera;
        SceneRenderer* m_sceneRenderer;
        int m_act;
        int m_level;
        CScene* m_scene;
        int m_startTime;
        bool m_pause;
        float m_zoom;
        SDL_Rect m_viewport;
        bool m_isZooming;
        Rocket::Core::Element* m_returnBtn;
        Rocket::Core::Element* m_pauseBtn;
 
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
        static AppStateGame* GetInstance();
        void OnFingerMove(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId);
        void OnMultiGesture(float mDTheta, float mDDist, float mX, float mY, Uint16 mFingers);
        void Pause(bool pause);
        void TogglePause();
        void SetParams(bool dummy, ...);
};
 
#endif
