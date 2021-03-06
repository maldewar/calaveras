#ifndef _LAYER_H_
    #define _LAYER_H_

#include <string>
#include <vector>
#include <Box2D.h>
#include "Area.h"
class Area;

/**
 * Models a layer of elements to be contained within a scene.
 */
class Layer {
    protected:
        std::string m_id;
        float m_distance;
        std::vector<Area*> m_areas;
        b2World* m_world;

    public:
        /**
         * Class constructor.
         */
        Layer();
        /**
         * Class destructor.
         */
        ~Layer();
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
        void AddArea(Area* area);
        /**
         * Sets the list of Area instances contained in this Layer.
         * @param areas List of Area instances.
         */
        void SetAreas(std::vector<Area*> areas);
        /**
         * Gets all the Area instances contained in this Layer.
         * @returns All the Area instances contained in this Layer.
         */
        std::vector<Area*> GetAreas();
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
