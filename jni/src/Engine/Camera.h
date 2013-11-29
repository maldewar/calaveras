#ifndef _CAMERA_H_
    #define _CAMERA_H_
#include <SDL.h>
#include "../Util/CMath.h"
#include "../Util/CLog.h"

const float ZOOM_DEFAULT = 1.0f;
const float ZOOM_MAX = 1.2f;
const float ZOOM_MIN = 0.8f;
const float ZOOM_FACTOR = 1.5f;

class Camera {
    private:
        float m_zoom, m_zoomMin, m_zoomMax, m_zoomFactor;
        float m_x, m_y;
        float m_w, m_h;
        float m_sceneW, m_sceneH;
        float m_topBound, m_bottomBound, m_leftBound, m_rightBound;
        float m_bonusTop, m_bonusBottom, m_bonusLeft, m_bonusRight;
        bool m_locked;
        SDL_Rect* m_viewport;

    private:
        void MoveX(float x);
        void MoveY(float y);
        void StepZoomX(float x, float step);
        void StepZoomY(float y, float step);
        void SetBounds();
        void UpdateViewport();
        
    public:
        Camera();
        ~Camera();
        void SetWidth(float width);
        void SetHeight(float height);
        void SetSceneWidth(float sceneWidth);
        void SetSceneHeight(float sceneHeight);
        void SetBonus(float bonus);
        void SetBonus(float bonusLeft, float bonusRight, float bonusTop, float bonusBottom);
        void SetLocked(bool locked);
        bool IsLocked();
        void SetZoom(float zoom, bool fromUser = true);
        float GetZoom();
        void StepZoom(float step, bool fromUser = true);
        void StepZoom(float step, float x, float y, bool fromUser = true);
        void Move(float dX, float dY, bool fromUser = true);
        SDL_Rect* GetViewport();

};

#endif
