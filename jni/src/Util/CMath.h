#ifndef _CMATH_H_
    #define _CMATH_H_

#include <string>
#include "../Model/Vector2.h"
/**
 * Constant for degrees to radians convertion.
 */
const int DEGTORAD = 0.0174532925199432957f;
/**
 * Constant for radians to degrees convertion.
 */
const int RADTODEG = 57.295779513082320876f;

class CMath {
    private:
        CMath();

    private:
        static float m_mToPx;
        static float m_pxToM;
        static float m_meterWidthFactor;

    public:
        static void SetFactor(int pixWidth, int pixHeight);
        static inline float PxToM(float value) {
            return value * m_pxToM;
        };
        static inline float MToPx(float value) {
            return value * m_mToPx;
        };
        static inline  int PxToMInt(float value) {
            return round(PxToM(value));
        };
        static inline int PxToMInt(float value, float scale) {
            return round(PxToM(value * scale));
        };
        static inline int MToPxInt(float value) {
            return round(MToPx(value));
        };
        static inline int MToPxInt(float value, float scale) {
            return round(MToPx(value * scale));
        };
        static inline float GetMToPxFactor() {
            return m_mToPx;
        };
        static inline float GetPxToMFactor() {
            return m_pxToM;
        };
        static inline float ToCartesian(float y, float height) {
            return height - y;
        };
        static inline float ToCanvas(float y, float height) {
            return (y - height) * -1;
        };
        static inline float ToDeg(float rad) {
            return rad * RADTODEG;
        };
        static inline float ToRad(float deg) {
            return deg * DEGTORAD;
        };
        static inline float GetDistance2(float x1, float y1, float x2, float y2) {
            return (pow(x1 - x2, 2) + pow(y1 - y2, 2));
        };
        static inline float GetDistance(float x1, float y1, float x2, float y2) {
            return sqrt(GetDistance2(x1, y1, x2, y2));
        };
        static Vector2* GetPointAt(float x, float y, float distance, float angle);
        static Vector2* GetPointAt(Vector2* base, float distance, float angle);
        static float Random(float a, float b);
        static inline float GetAbsoluteAngle(float x1, float y1, float x2, float y2) {
            return atan2(fabs(y2-y1), fabs(x2-x1));
        };
        static inline float GetAngle(float x1, float y1, float x2, float y2) {
            return atan2(y2 - y1, x2 - x1);
        };
        static inline float GetAngle(float xV, float yV, float xA, float yA, float xB, float yB) {
            float dVA = GetDistance(xV, yV, xA, yA);
            float dVB = GetDistance(xV, yV, xB, yB);
            float dAB = GetDistance(xA, yA, xB, yB);
            return acos((pow(dVA, 2) + pow(dVB, 2) - pow(dAB, 2))/(2 * dVA * dVB));
        };
        static inline float GetAngleOffset(float base, float offset) {
            float angle = fmod(base + offset, M_PI * 2);
            if (angle > M_PI)
                angle -= 2 * M_PI;
            return angle;
        };
        static inline float GetAbsoluteDiff(float val1, float val2) {
            return fabs(val2 - val1);
        };
        static inline float GetAbsolute(float val) {
            return fabs(val);
        };
        static inline float GetComplementAngle(float angle) {
            if (angle < 0)
                return -M_PI - angle;
            else
                return M_PI - angle;
        };
        
};
#endif
