#ifndef _CMATH_H_
    #define _CMATH_H_

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#include <string>
class CMath {
    private:
        CMath();

    private:
        static float m_mToPx;
        static float m_pxToM;
        static float m_meterWidthFactor;

    public:
        static void SetFactor(int pixWidth, int pixHeight);
        static float PxToM(float value);
        static float MToPx(float value);
        static int PxToMInt(float value);
        static int MToPxInt(float value);
        static float ToCartesian(float y, float height);
        static float ToCanvas(float y, float height);
        static float ToDeg(float rad);
        static float ToRad(float deg);
        static float Random(float a, float b);
        static float GetAbsoluteAngle(float x1, float y1, float x2, float y2);
};
#endif
