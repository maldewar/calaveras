#ifndef _BOXMAKER_H_
    #define _BOXMAKER_H_

#include <Box2D.h>
#include "../Util/CMath.h"
class Area;
class Unit;

const int UNIT_BODY = 100;
const int AREA_BODY = 200;

class BoxMaker {
    private:
        static short CATEGORY_SCENE;
        static short CATEGORY_UNIT;
        static short MASK_SCENE;
        static short MASK_UNIT;

    private:
        BoxMaker();

    public:
        static b2Body* MakeArea(Area* area, b2World* bWorld);
        static b2Body* MakeUnit(Unit* unit, b2World* bWorld);

};

#endif
