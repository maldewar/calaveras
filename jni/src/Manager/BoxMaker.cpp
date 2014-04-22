#include "../Model/Area.h"
#include "../Model/Unit.h"
#include "../Engine/AreaCatalog.h"
#include "../Engine/UserData.h"
#include "../Engine/AreaUserData.h"
#include "BoxMaker.h"

short BoxMaker::CATEGORY_SCENE = 0x0001;
short BoxMaker::CATEGORY_UNIT = 0x0002;
short BoxMaker::MASK_SCENE = -1;
short BoxMaker::MASK_UNIT = CATEGORY_SCENE;

BoxMaker::BoxMaker() {
}

b2Body* BoxMaker::MakeArea(Area* area, b2World* bWorld) {
    AreaCatalog::Set(area);
    AreaUserData* areaUserData = new AreaUserData(AREA_BODY);
    areaUserData->SetArea(area);
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0,0);
    bodyDef.angularDamping = area->GetAngularDamping();
    bodyDef.linearDamping = area->GetLinearDamping();

    b2Body* areaBody = bWorld->CreateBody(&bodyDef);
    areaBody->SetUserData(area);

    b2ChainShape bodyShape;
    b2Vec2 vs[area->GetTotalPoints()];
    int pointIndex = 0;
    for(auto &point : area->GetPoints()) {
        vs[pointIndex].Set(point->x, point->y);
        pointIndex++;
    }
    if (area->IsClosed())
        bodyShape.CreateLoop(vs, area->GetTotalPoints());
    else
        bodyShape.CreateChain(vs, area->GetTotalPoints());

    b2FixtureDef bodyFixtureDef;
    bodyFixtureDef.filter.categoryBits = CATEGORY_SCENE;
    bodyFixtureDef.filter.maskBits = MASK_SCENE;
    bodyFixtureDef.shape = &bodyShape;
    bodyFixtureDef.density = 20.0f;
    bodyFixtureDef.friction = 1.0f;
    b2Fixture* bodyFixture = areaBody->CreateFixture(&bodyFixtureDef);
    bodyFixture->SetUserData(areaUserData);
    return areaBody;
}

b2Body* BoxMaker::MakeUnit(Unit* unit, b2World* bWorld) {
    UserData* userData = new UserData(UNIT_BODY);
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(unit->GetX(),unit->GetY());
    bodyDef.angularDamping = 3.0f;
    bodyDef.linearDamping = 1.0f;
    unit->SetOriginalLinearDamping(1.0f);
    unit->SetOriginalAngularDamping(3.0f);
    //bodyDef.fixedRotation = true;

    b2Body* unitBody = bWorld->CreateBody(&bodyDef);
    unitBody->SetUserData(unit);

    b2CircleShape bodyShape;
    bodyShape.m_radius = unit->GetWidth()/2;
    /*
    b2PolygonShape bodyShape;
    int numVertices = 8;
    float angleOffset = M_PI_4 / 2;
    b2Vec2 vertices[numVertices];
    Vector2* tmpVector2 = new Vector2();
    for (int i = 0; i < numVertices; i++) {
        tmpVector2 = CMath::GetPointAt(0, 0, unit->GetWidth()/2, M_PI_4 * i + angleOffset);
        vertices[i] = b2Vec2(tmpVector2->x, tmpVector2->y);
    }
    bodyShape.Set(vertices, numVertices);
    */

    b2FixtureDef bodyFixtureDef;
    bodyFixtureDef.filter.categoryBits = CATEGORY_UNIT;
    bodyFixtureDef.filter.maskBits = MASK_UNIT;
    bodyFixtureDef.shape = &bodyShape;
    bodyFixtureDef.density = 20.0f;
    bodyFixtureDef.friction = 0.6f;
    bodyFixtureDef.restitution = 0.2f;
    b2Fixture* bodyFixture = unitBody->CreateFixture(&bodyFixtureDef);
    bodyFixture->SetUserData(userData);

    float cardinalSensorSize = 0.005;
    float sensorPosition = unit->GetWidth()/2 - cardinalSensorSize/2;

    b2PolygonShape cardinalShape;
    bodyFixtureDef.isSensor = true;
    bodyFixtureDef.shape = &cardinalShape;
    bodyFixtureDef.density = 0.0f;
    return unitBody;
}
