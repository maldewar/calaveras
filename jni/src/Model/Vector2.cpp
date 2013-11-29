#include "Vector2.h"
#include "cmath"

Vector2::Vector2() {
    x = 0;
    y = 0;
};

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
};

float Vector2::Dist(Vector2* v) {
    return sqrt(Dist2(v));
};

float Vector2::Dist2(Vector2* v) {
    float xD = v->x - this->x;
    float yD = v->y - this->y;
    return xD * xD + yD * yD;
};

float Vector2::Angle() {
    return atan2(y, x);
};
