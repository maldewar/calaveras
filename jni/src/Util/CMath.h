#ifndef _CMATH_H_
    #define _CMATH_H_

#include <string>
#include "../Model/Vector2.h"
#include "Log.h"
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
        static int relativeCCW(float x1, float y1, float x2, float y2, float px, float py);

    private:
        static float m_mToPx;
        static float m_pxToM;
        static float m_cameraTargetWidthM;
        static float m_maxZoomFactor;
        static int m_mToPxRatio;

    public:
        static void SetFactor(int screenWidth, int screenHeight);
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
        static inline int GetMToPxRatio() {
            return m_mToPxRatio;
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
        static inline float GetAbsoluteAngle(float angle) {
            if (angle >= 0 && angle <= M_PI_2)
                return angle;
            else if (angle > 0)
                return fabs(angle - M_PI);
            else if (angle < 0 && angle >= -M_PI_2)
                return fabs(angle);
            else
                return angle + M_PI;
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
        /**
         * Returns the results of a sum of angles normalized between -PI and PI radians.
         * @param base Base angle.
         * @param offset Offset angle.
         * @return Resulting angle.
         */
        static float GetAngleOffset(float base, float offset);
        static inline float GetAngleDistance(float angleA, float angleB) {
            return fabs(angleA - angleB);
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
        static bool LinesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
        
};
#endif
