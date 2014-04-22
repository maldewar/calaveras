#include <stdlib.h> 
#include "cmath"
#include "CMath.h"
#include "Log.h"

float CMath::m_mToPx = 100;
float CMath::m_pxToM = 1/100;
float CMath::m_cameraTargetWidthM = 3.25;
float CMath::m_maxZoomFactor = 1.3;
int CMath::m_mToPxRatio = 1;

CMath::CMath() {
};

void CMath::SetFactor(int screenWidth, int screenHeight) {
    m_mToPx = screenWidth / m_cameraTargetWidthM;
    m_pxToM = 1 / m_mToPx;
    m_mToPxRatio = round(m_mToPx * m_maxZoomFactor);
    Log::L("Width:%d Height:%d MtoPxRatio: %d", screenWidth, screenHeight, m_mToPxRatio);
};

Vector2* CMath::GetPointAt(float x, float y, float distance, float angle) {
    x += distance * cos(angle);
    y += distance * sin(angle);
    Vector2* v = new Vector2(x, y);
    return v;
};

Vector2* CMath::GetPointAt(Vector2* base, float distance, float angle) {
    return GetPointAt(base->x, base->y, distance, angle);
};

float CMath::Random(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return (a + r);
};

float CMath::GetAngleOffset(float base, float offset) {
    float angle = fmod(base + offset, M_PI * 2);
    if (angle > M_PI)
        angle -= 2 * M_PI;
    if (angle < -M_PI)
        angle += 2 * M_PI;
    return angle;
};

bool CMath::LinesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    return ((relativeCCW(x1, y1, x2, y2, x3, y3) *
        relativeCCW(x1, y1, x2, y2, x4, y4) <= 0)
        && (relativeCCW(x3, y3, x4, y4, x1, y1) *
        relativeCCW(x3, y3, x4, y4, x2, y2) <= 0));
};

int CMath::relativeCCW(float x1, float y1, float x2, float y2, float px, float py)
{
    x2 -= x1;
    y2 -= y1;
    px -= x1;
    py -= y1;
    double ccw = px * y2 - py * x2;
    if (ccw == 0.0f) {
        // The point is colinear, classify based on which side of
        // the segment the point falls on.  We can calculate a
        // relative value using the projection of px,py onto the
        // segment - a negative value indicates the point projects
        // outside of the segment in the direction of the particular
        // endpoint used as the origin for the projection.
        ccw = px * x2 + py * y2;
        if (ccw > 0.0f) {
            // Reverse the projection to be relative to the original x2,y2
            // x2 and y2 are simply negated.
            // px and py need to have (x2 - x1) or (y2 - y1) subtracted
            //    from them (based on the original values)
            // Since we really want to get a positive answer when the
            //    point is "beyond (x2,y2)", then we want to calculate
            //    the inverse anyway - thus we leave x2 & y2 negated.
            px -= x2;
            py -= y2;
            ccw = px * x2 + py * y2;
            if (ccw < 0.0f) {
                ccw = 0.0f;
            }
        }
    }
    return (ccw < 0.0f) ? -1 : ((ccw > 0.0f) ? 1 : 0);
}
