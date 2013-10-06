#ifndef _WORLDCONTACTLISTENER_H_
    #define _WORLDCONTACTLISTENER_H_
#include <Box2D.h>
#include "../Model/CUnit.h"
#include "../Model/CArea.h"

class WorldContactListener : public b2ContactListener {
    public:
        WorldContactListener();

    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);

    private:
        void UnitSwitch(CUnit* unit, int sensorUnit, bool isFixA, bool isBegin, b2Contact* contact);

        void BeginContact(CUnit* unit, CArea* area, int sensorUnit, int sensorArea, float edgeAngle);
        void EndContact(CUnit* unit, CArea* area, int sensorUnit, int sensorArea);
};

#endif
