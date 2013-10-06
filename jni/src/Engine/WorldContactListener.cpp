#include "WorldContactListener.h"
#include "../Manager/CBoxMaker.h"
#include "../Util/CLog.h"

WorldContactListener::WorldContactListener() : b2ContactListener() {
}

void WorldContactListener::BeginContact(b2Contact* contact) {
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( (int)fixtureUserData >= UNIT_SENSOR_BODY && (int)fixtureUserData < UNIT_SENSOR_BODY + 100 ) {
        CUnit* unit = (CUnit*)contact->GetFixtureA()->GetBody()->GetUserData();
        UnitSwitch(unit, (int)fixtureUserData, true, true, contact);
        return;
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( (int)fixtureUserData >= UNIT_SENSOR_BODY && (int)fixtureUserData < UNIT_SENSOR_BODY + 100 ) {
        CUnit* unit = (CUnit*)contact->GetFixtureB()->GetBody()->GetUserData();
        UnitSwitch(unit, (int)fixtureUserData, false, true, contact);
        return;
    }
}

void WorldContactListener::EndContact(b2Contact* contact) {
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( (int)fixtureUserData >= UNIT_SENSOR_BODY && (int)fixtureUserData < UNIT_SENSOR_BODY + 100 ) {
        CUnit* unit = (CUnit*)contact->GetFixtureA()->GetBody()->GetUserData();
        UnitSwitch(unit, (int)fixtureUserData, true, false, contact);
        return;
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( (int)fixtureUserData >= UNIT_SENSOR_BODY && (int)fixtureUserData < UNIT_SENSOR_BODY + 100 ) {
        CUnit* unit = (CUnit*)contact->GetFixtureB()->GetBody()->GetUserData();
        UnitSwitch(unit, (int)fixtureUserData, false, false, contact);
        return;
    }
}

void WorldContactListener::UnitSwitch(CUnit* unit, int sensorUnit, bool isFixA, bool isBegin, b2Contact* contact) {
    void* fixtureUserData;
    int otherSensor;
    b2Fixture* otherFixture;
    if (isFixA)
        otherFixture = contact->GetFixtureB();
    else
        otherFixture = contact->GetFixtureA();
    fixtureUserData = otherFixture->GetUserData();
    otherSensor = (int)fixtureUserData;
    if ( otherSensor >= AREA_SENSOR_BODY && otherSensor < AREA_SENSOR_BODY + 100 ) {
        CArea* area = (CArea*)otherFixture->GetBody()->GetUserData();
        if (isBegin)
            BeginContact(unit, area, sensorUnit, otherSensor, 0);
        else
            EndContact(unit, area, sensorUnit, otherSensor);
        /*
        //GET EDGE ANGLE AT CONTACT
        int edgeIndex;
        b2EdgeShape edgeShape;
        if(isFixA)
            edgeIndex = contact->GetChildIndexB();
        else
            edgeIndex = contact->GetChildIndexA();
        ((b2ChainShape*)otherFixture->GetShape())->GetChildEdge(&edgeShape, edgeIndex);
        BeginContact(unit, area, sensorUnit, otherSensor, CMath::GetAbsoluteAngle(edgeShape.m_vertex1.x, edgeShape.m_vertex1.y, edgeShape.m_vertex2.x, edgeShape.m_vertex2.y));
        */
    }
}

void WorldContactListener::BeginContact(CUnit* unit, CArea* area, int sensorUnit, int sensorArea, float edgeAngle) {
    unit->BeginContact(sensorUnit, area, sensorArea);
}

void WorldContactListener::EndContact(CUnit* unit, CArea* area, int sensorUnit, int sensorArea) {
    unit->EndContact(sensorUnit, area, sensorArea);
}
