#ifndef _CLAYER_H_
    #define _CLAYER_H_

#include <string>
#include <vector>
#include <Box2D.h>
#include "CArea.h"
class CArea;

/**
 * Models a layer of elements to be contained within a scene.
 */
class CLayer {
    protected:
        std::string m_id;
        float m_distance;
        std::vector<CArea*> m_areas;
        b2World* m_world;

    public:
        /**
         * Class constructor.
         */
        CLayer();
        /**
         * Class destructor.
         */
        ~CLayer();
        /**
         * Sets the identifier for this Layer.
         * @param id Layer identifier.
         */
        void SetId(std::string id);
        /**
         * Gets the identifier for this Layer.
         * @return Layer identifier.
         */
        std::string GetId();
        /**
         * Sets the distance from the upper Layer from the layers stack in the scene.
         * @param distance Distance in meters.
         */
        void SetDistance(float distance);
        /**
         * Gets the distance from the upper Layer from the layers stack in the scene.
         * @returns Distance in meters.
         */
        float GetDistance();
        /**
         * Adds an area to this Layer.
         * @param area Area instance.
         */
        void AddArea(CArea* area);
        /**
         * Sets the list of Area instances contained in this Layer.
         * @param areas List of Area instances.
         */
        void SetAreas(std::vector<CArea*> areas);
        /**
         * Gets all the Area instances contained in this Layer.
         * @returns All the Area instances contained in this Layer.
         */
        std::vector<CArea*> GetAreas();
        /**
         * Sets the Box2d world used to simulate physics.
         * @param world Box2d world.
         */
        void SetWorld(b2World* world);
        /**
         * Gets the Box2d world used to simulate physics.
         * @return Box2d world.
         */
        b2World* GetWorld();

};

#endif
