#include "Camera.h"
#include "../Util/CLog.h"

Camera::Camera() {
    m_w = 0;
    m_h = 0;
    m_zoom = ZOOM_DEFAULT;
    m_zoomMin = ZOOM_MIN;
    m_zoomMax = ZOOM_MAX;
    m_zoomFactor = ZOOM_FACTOR;
    m_x = 0;
    m_y = 0;
    m_viewport = new SDL_Rect();
    m_viewport->x = m_x;
    m_viewport->y = m_y;
    m_viewport->w = m_w;
    m_viewport->h = m_h;
    m_sceneW = 0;
    m_sceneH = 0;
    m_topBound    = 0;
    m_bottomBound = 0;
    m_leftBound   = 0;
    m_rightBound  = 0;
    m_bonusTop    = 0;
    m_bonusBottom = 0;
    m_bonusLeft   = 0;
    m_bonusRight  = 0;
    m_locked = false;
};

void Camera::SetWidth(float width) {
    m_w = width;
    m_viewport->w = width;
};

void Camera::SetHeight(float height) {
    m_h = height;
    m_viewport->h = height;
};

void Camera::SetSceneWidth(float sceneWidth) {
    m_sceneW = sceneWidth;
    SetBounds();
};

void Camera::SetSceneHeight(float sceneHeight) {
    m_sceneH = sceneHeight;
    SetBounds();
};

void Camera::SetBonus(float bonus) {
    SetBonus(bonus, bonus, bonus, bonus);
};

void Camera::SetBonus(float bonusLeft, float bonusRight, float bonusTop, float bonusBottom) {
    m_bonusTop    = bonusTop;
    m_bonusBottom = bonusBottom;
    m_bonusRight  = bonusRight;
    m_bonusLeft   = bonusLeft;
    SetBounds();
};

void Camera::SetLocked(bool locked) {
    m_locked = locked;
};

bool Camera::IsLocked() {
    return m_locked;
};

void Camera::SetZoom(float zoom, bool fromUser) {
    if ((m_locked && fromUser) || (m_w / zoom > m_sceneW || m_h / zoom > m_sceneH))
        return;
    if (zoom <= m_zoomMax && zoom >= m_zoomMin) {
        m_zoom = zoom;
        SetBounds();
    }
};

float Camera::GetZoom() {
    return m_zoom;
};

void Camera::StepZoom(float step, bool fromUser) {
    if (m_locked && fromUser)
        return;
    SetZoom(m_zoom + step);
};

void Camera::StepZoom(float step, float x, float y, bool fromUser) {
    if (m_locked && fromUser)
        return;
    StepZoom(step, true);
    StepZoomX(x, step);
    StepZoomY(y, step);
    UpdateViewport();
};

void Camera::Move(float dX, float dY, bool fromUser) {
    if (m_locked && fromUser)
        return;
    MoveX(dX * m_w);
    MoveY(dY * m_h);
    UpdateViewport();
};

SDL_Rect* Camera::GetViewport() {
    return m_viewport;
};

void Camera::MoveX(float x) {
    if (m_x - x < m_leftBound || m_x - x > m_rightBound)
        return;
    m_x -= x;
};

void Camera::MoveY(float y) {
    if (m_y - y < m_topBound || m_y - y > m_bottomBound)
        return;
    m_y -= y;
};

void Camera::StepZoomX(float x, float step) {
    if (m_x + m_w / m_zoom > m_sceneW + m_bonusRight) {
        m_x = m_sceneW + m_bonusRight - (m_w / m_zoom);
        m_viewport->x = m_x * -1;
        return;
    }
    MoveX(step * x * -2 * m_w);
};

void Camera::StepZoomY(float y, float step) {
    if (m_y + m_h / m_zoom > m_sceneH + m_bonusBottom) {
        m_y = m_sceneH + m_bonusBottom - (m_h / m_zoom);
        m_viewport->y = m_y;
    }
    MoveY(step * y * -2 * m_h);
};

void Camera::SetBounds() {
    m_topBound    = -m_bonusTop;
    m_leftBound   = -m_bonusLeft;
    m_bottomBound = m_sceneH + m_bonusBottom - (m_h / m_zoom);
    m_rightBound  = m_sceneW + m_bonusRight - (m_w / m_zoom);
};

void Camera::UpdateViewport() {
    m_viewport->x = m_x * -1;
    if (m_w + m_x >= m_w)
        m_viewport->w = m_w / m_zoom + m_x;
    if (m_y >= 0) //OPENGL takes down left corner
        m_viewport->y = 0;
    else
        m_viewport->y = m_y;
    if (m_h + m_y >= m_h)
        m_viewport->h = m_h / m_zoom + m_y;
};
