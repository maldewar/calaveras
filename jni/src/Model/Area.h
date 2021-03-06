#ifndef _AREA_H_
    #define _AREA_H_

#include <vector>
#include <Box2D.h>
#include "AreaNode.h"
#include "../Manager/BoxMaker.h"
#include "../Engine/LayeredGraphic.h"
#include "Layer.h"
class AreaNode;
class Layer;
class LayeredGraphic;

/**
 * Models a surface or area contained by a surface in which object
 * in the scene may interact.
 */
class Area {
    private:
        bool m_isClosed;
        std::vector<AreaNode*> m_points;
        int m_material;
        int m_nature;
        int m_totalPoints;
        float m_linearDamping;
        float m_angularDamping;
        b2Body* m_body;
        Layer* m_layer;
        Vector2* m_center;
        LayeredGraphic* m_layeredGraphic;

    public:
        /**
         * Class constructor.
         */
        Area();
        /**
         * Class constructor.
         * Binds this Area to its parent Layer.
         * @param layer Parent layer.
         */
        Area(Layer* layer);
        /**
         * Class destructor.
         */
        ~Area();
        /**
         * Sets the parent Layer for this Area.
         * @param layer Parent layer.
         */
        void SetLayer(Layer* layer);
        /**
         * Gets the parent Layer for this Area.
         * @returns Parent layer.
         */
        Layer* GetLayer();
        /**
         * Sets the Box2D body for this Area.
         */
        void SetBody();
        /**
         * Gets the Box2D body for this Area.
         * @returns Body.
         */
        b2Body* GetBody();
        /**
         * Adds a point to the series for this Area.
         * @param x X cartesian coordinate in meters.
         * @param y Y cartesian coordinate in meters.
         */
        void AddPoint(float x, float y);
        /**
         * Adds a point taking the coordinate values from a Vector.
         * @param vector Vector with cartesian values in meters.
         */
        void AddPoint(AreaNode* vector);
        /**
         * Gets all points in an Area.
         * @returns Vector list with cartesian values in meters.
         */
        std::vector<AreaNode*> GetPoints();
        /**
         * Gets the total of points thet compose the Area.
         * @returns Total of points.
         */
        int GetTotalPoints();
        /**
         * Sets the area to connect its first point to the last, creating a loop.
         * @param closed TRUE for a closed area.
         */
        void SetClosed(bool closed);
        /**
         * Gets the state of the area in regards whether it is closed or not.
         * @returns TRUE if the area is closed.
         */
        bool IsClosed();
        /**
         * Set the material for this Area.
         * A material defines how the Area looks like.
         * @param material Material for this Area.
         */
        void SetMaterial(int material);
        /**
         * Gets the material for this Area.
         * A material defines how the Area looks like.
         * @returns Material for this Area.
         */
        int GetMaterial();
        /**
         * Set the Nature for this Area.
         * The nature of the Area defines its physical properties.
         * @param nature Nature for this Area.
         */
        void SetNature(int nature);
        /**
         * Gets the nature for this Area.
         * The nature of the Area defines its physical properties.
         * @returns Nature for this Area.
         */
        int GetNature();
        /**
         * Sets the linear damping.
         * @param linearDamping Linear damping value.
         */
        void SetLinearDamping(float linearDamping);
        /**
         * Gets the linear damping.
         * @returns Linear damping value.
         */
        float GetLinearDamping();
        /**
         * Sets the angular damping.
         * @param angularDamping Angular damping value.
         */
        void SetAngularDamping(float angularDamping);
        /**
         * Gets the angular damping.
         * @returns Angular damping value.
         */
        float GetAngularDamping();
        /**
         * Sets the layered graphics to render with this area.
         * @param layeredGraphic Layered Graphic object.
         */
        void SetLayeredGraphic(LayeredGraphic* layeredGraphic);
        /**
         * Gets the layered graphics to render with this area.
         * @return Layered Graphic object.
         */
        LayeredGraphic* GetLayeredGraphic();
        /**
         * Sets the center coordinates for this area.
         * @param x X coordinate.
         * @param y Y coordinate.
         */
        void SetCenter(float x, float y);
        /**
         * Gets the center point for this area.
         * @return Center point.
         */
        Vector2* GetCenter();

};
#endif
