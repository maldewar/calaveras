#ifndef _CBOXMAKER_H_
    #define _CBOXMAKER_H_

#include <Box2D.h>
#include "../Util/CMath.h"
class CArea;
class CUnit;

#define UNIT_SENSOR_BODY       100
#define UNIT_SENSOR_FEET       101
#define UNIT_SENSOR_LEFT_HAND  102
#define UNIT_SENSOR_RIGHT_HAND 103
#define UNIT_SENSOR_HEAD       104

#define AREA_SENSOR_BODY 200

class CBoxMaker {
    private:
        static short CATEGORY_SCENE;
        static short CATEGORY_UNIT;
        static short MASK_SCENE;
        static short MASK_UNIT;

    private:
        CBoxMaker();

    public:
        static b2Body* MakeArea(CArea* area, b2World* bWorld);
        static b2Body* MakeUnit(CUnit* unit, b2World* bWorld);

};

#endif
