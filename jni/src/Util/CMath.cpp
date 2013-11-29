#include <stdlib.h> 
#include "cmath"
#include "CMath.h"
#include "CLog.h"

float CMath::m_mToPx = 100;
float CMath::m_pxToM = 1/100;
float CMath::m_meterWidthFactor = 30;

CMath::CMath() {
};

void CMath::SetFactor(int pixWidth, int pixHeight) {
    m_mToPx = pixWidth*(m_meterWidthFactor/100);
    m_pxToM = 1/m_mToPx;
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
