#include "WorldContactListener.h"
#include "../Manager/BoxMaker.h"
#include "../Engine/UserData.h"
#include "../Engine/AreaUserData.h"
#include "../Util/Log.h"

UserData* WorldContactListener::m_userData = NULL;

WorldContactListener::WorldContactListener() : b2ContactListener() {
}

void WorldContactListener::BeginContact(b2Contact* contact) {
    m_userData = static_cast<UserData*>( contact->GetFixtureA()->GetUserData() );
    if ( m_userData->type >= UNIT_BODY && m_userData->type < UNIT_BODY + 100 ) {
        Unit* unit = (Unit*)contact->GetFixtureA()->GetBody()->GetUserData();
        UnitSwitch(unit, m_userData->type, true, true, contact);
        return;
    }

    m_userData = static_cast<UserData*>( contact->GetFixtureB()->GetUserData() );
    if ( m_userData->type >= UNIT_BODY && m_userData->type < UNIT_BODY + 100 ) {
        Unit* unit = (Unit*)contact->GetFixtureB()->GetBody()->GetUserData();
        UnitSwitch(unit, m_userData->type, false, true, contact);
        return;
    }
}

void WorldContactListener::EndContact(b2Contact* contact) {
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    m_userData = static_cast<UserData*>( contact->GetFixtureA()->GetUserData() );
    if ( m_userData->type >= UNIT_BODY && m_userData->type < UNIT_BODY + 100 ) {
        Unit* unit = (Unit*)contact->GetFixtureA()->GetBody()->GetUserData();
        UnitSwitch(unit, (int)fixtureUserData, true, false, contact);
        return;
    }
    m_userData = static_cast<UserData*>( contact->GetFixtureB()->GetUserData() );
    if ( m_userData->type >= UNIT_BODY && m_userData->type < UNIT_BODY + 100 ) {
        Unit* unit = (Unit*)contact->GetFixtureB()->GetBody()->GetUserData();
        UnitSwitch(unit, (int)fixtureUserData, false, false, contact);
        return;
    }
}

void WorldContactListener::UnitSwitch(Unit* unit, int sensorUnit, bool isFixA, bool isBegin, b2Contact* contact) {
    void* fixtureUserData;
    int otherSensor;
    b2Fixture* otherFixture;
    if (isFixA)
        otherFixture = contact->GetFixtureB();
    else
        otherFixture = contact->GetFixtureA();
    fixtureUserData = otherFixture->GetUserData();
    otherSensor = ((UserData*)fixtureUserData)->type;
    if ( otherSensor >= AREA_BODY && otherSensor < AREA_BODY + 100 ) {
        Area* area = (Area*)otherFixture->GetBody()->GetUserData();
        if (isBegin)
            BeginContact(unit, area, sensorUnit, otherSensor, 0);
        else
            EndContact(unit, area, sensorUnit, otherSensor);
    }
}

void WorldContactListener::BeginContact(Unit* unit, Area* area, int sensorUnit, int sensorArea, float edgeAngle) {
    unit->BeginContact(sensorUnit, area, sensorArea);
}

void WorldContactListener::EndContact(Unit* unit, Area* area, int sensorUnit, int sensorArea) {
    unit->EndContact(sensorUnit, area, sensorArea);
}
