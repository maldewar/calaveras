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

float CMath::PxToM(float value) {
    return value * m_pxToM;
};

float CMath::MToPx(float value) {
    return value * m_mToPx;
}

int CMath::PxToMInt(float value) {
    return (int)PxToM(value);
}

int CMath::MToPxInt(float value) {
    return (int)MToPx(value);
}

float CMath::ToCartesian(float y, float height) {
    return height - y;
}

float CMath::ToCanvas(float y, float height) {
    return (y - height) * -1;
};

float CMath::ToDeg(float rad) {
    return rad * RADTODEG;
};

float CMath::ToRad(float deg) {
    return deg * DEGTORAD;
};

float CMath::Random(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return (a + r);
};

float CMath::GetAbsoluteAngle(float x1, float y1, float x2, float y2) {
    return atan2(fabs(y2-y1), fabs(x2-x1));
};
