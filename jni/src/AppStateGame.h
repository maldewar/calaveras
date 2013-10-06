#ifndef __CAPPSTATEGAME_H__
    #define __CAPPSTATEGAME_H__

#define GAME_ZOOM_MAX 1.2
#define GAME_ZOOM_MIN 0.4
#define GAME_ZOOM_DEFAULT 1.0
#define GAME_ZOOM_FACTOR 1.0

#include "AppState.h"
#include "Model/CScene.h"
#include "Util/CLog.h"
#include "Util/CMath.h"
 
class AppStateGame : public AppState {
    private:
        static AppStateGame Instance;
        CScene* m_scene;
        int StartTime;
        float m_zoom;
        SDL_Rect m_viewport;
        bool m_isZooming;
 
    private:
        AppStateGame();
 
    public:
        void OnActivate(SDL_Renderer* Renderer);
        void OnDeactivate();
        void OnLoop();
        void OnRender(SDL_Renderer* Renderer);
 
    public:
        static AppStateGame* GetInstance();
        void OnFingerMove(float mX, float mY, float mDX, float mDY, SDL_FingerID mFingerId);
        void OnMultiGesture(float mDTheta, float mDDist, float mX, float mY, Uint16 mFingers);
};
 
#endif
