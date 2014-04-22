#ifndef _WORLDCONTACTLISTENER_H_
    #define _WORLDCONTACTLISTENER_H_
#include <Box2D.h>
#include "../Model/Unit.h"
#include "../Model/Area.h"
#include "UserData.h"

class WorldContactListener : public b2ContactListener {
    public:
        WorldContactListener();

    private:
        static UserData* m_userData;

    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);

    private:
        void UnitSwitch(Unit* unit, int sensorUnit, bool isFixA, bool isBegin, b2Contact* contact);

        void BeginContact(Unit* unit, Area* area, int sensorUnit, int sensorArea, float edgeAngle);
        void EndContact(Unit* unit, Area* area, int sensorUnit, int sensorArea);
};

#endif
