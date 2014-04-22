#ifndef _RAYCASTTOOL_H_
    #define _RAYCASTTOOL_H_
#include <Box2D.h>
#include "../Model/SceneExt.h"
#include "../Model/WorldLayer.h"
#include "../Model/Vector2.h"
#include "../Model/AreaNode.h"
#include "UserData.h"
#include "AreaUserData.h"

class RayCastTool : public b2RayCastCallback {
    private:
        float m_rayLength;
        SceneExt*     m_sceneExt;
        b2Vec2*       m_start;
        Vector2*      m_startTemp;
        b2Vec2*       m_end;
        Vector2*      m_endTemp;
        AreaNode*     m_areaNodeA;
        AreaNode*     m_areaNodeB;
        UserData*     m_userData;
        AreaUserData* m_areaUserData;
        int           m_objectType;
        int           m_objectTypeFilter;
        bool          m_hasContact;

    public:
        /**
         * Class constructor.
         * @param rayLength Distance in meters to limit raycasting.
         */
        RayCastTool(float rayLength);
        /**
         * Class constructor.
         * @param rayLength Distance in meters to limit raycasting.
         * @param sceneExt Extra scene information object.
         */
        RayCastTool(float rayLength, SceneExt* sceneExt);
        /**
         * Cast a ray to the next object encounter in the world
         * given a reference point and an angle.
         * @param worldLayer World containing the objects to detect.
         * @param x X coordinate for the reference point.
         * @param y Y coordinate for the reference point.
         * @param gravityAngle Angle in radians for casting the ray.
         */
        void RayCast(WorldLayer* worldLayer, float x, float y, float gravityAngle);
        /**
         * Cast a ray to the next object encounter in the world
         * given a reference point, an angle and the distance of the ray.
         * @param worldLayer World containing the objects to detect.
         * @param x X coordinate for the reference point.
         * @param y Y coordinate for the reference point.
         * @param gravityAngle Angle in radians for casting the ray.
         * @param distance Distance in meters to cast the ray.
         */
        void RayCast(WorldLayer* worldLayer, float x, float y, float gravityAngle, float distance);
        /**
         * Callback function, called when a collition is detected.
         * @param fixture Fixture the dectection was detected against.
         * @param point Point in world coordinates where the collision ocurred.
         * @param fraction Fraction from the original raycast distance.
         * @param index In case of a chain shape, the index of the edge where the collition occurred.
         * @return Fraction of the ray distance where the collition was detected.
         */
        float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction, int32 index);
        /**
         * Returns true when there was a ray cast contact.
         * @return True if there was a ray cast contact.
         */
        bool HasContact();
        /**
         * Sets the fixture to ignore all objects except the ones matching this type.
         * param objectType Type of the object to detect.
         */
        void SetFilter(int objectType);
        /**
         * Clears any previously set filter.
         */
        void ClearFilter();
        /**
         * Gets the starting point of the ray.
         * @return Ray starting point.
         */
        Vector2* GetStart();
        /**
         * Gets the ending point of the ray.
         * @return Ray ending point.
         */
        Vector2* GetEnd();
        /**
         * Gets the type of the colliding object.
         * @return Colliding object type.
         */
        int GetObjectType();
        /**
         * If the collision was against an area this returns the initial point
         * of the edge of that area.
         * @return Edge node A.
         */
        AreaNode* GetAreaNodeA();
        /**
         * If the collision was against an area this returns the ending point
         * of the edge of that area.
         * @return Edge node B.
         */
        AreaNode* GetAreaNodeB();
};

#endif
