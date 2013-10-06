#ifndef _CSCENE_H_
    #define _CSCENE_H_
#include <string>
#include <vector>
#include "CWorldLayer.h"
class CWorldLayer;
#include "Vector2.h"

/**
 * Models a level scenario.
 */
class CScene {
    private:
        std::string m_version;
        std::string m_name;
        float m_width;
        float m_height;
        Vector2 m_gravity;
        std::vector<CWorldLayer*> m_worldLayers;
        CWorldLayer* m_layer;

    public:
        /**
         * Class constructor.
         */
        CScene();
        /**
         * Class destructor.
         */
        ~CScene();
        /**
         * Sets the version of the descriptor from which the scene got loaded.
         * @param version Version of the descriptor.
         */
        void SetVersion(std::string version);
        /**
         * Gets the version of the descriptor from which the scene got loaded.
         * @return Version of the descriptor.
         */
        std::string GetVersion();
        /**
         * Sets the name of this scenario.
         * @param name Name of this scenario.
         */
        void SetName(std::string name);
        /**
         * Gets the name of this scenario.
         * @returns Name of this scenario.
         */
        std::string GetName();
        /**
         * Sets the width of the scene in meters.
         * @param width Width of the scene in meters.
         */
        void SetWidth(float width);
        /**
         * Gets the width of the scene in meters.
         * @returns Width of the scene in meters.
         */
        float GetWidth();
        /**
         * Sets the height of the scene in meters.
         * @param height Height of the scene in meters.
         */
        void SetHeight(float height);
        /**
         * Gets tne height of the scene in meters.
         * @returns Height of the scene in meters.
         */
        float GetHeight();
        /**
         * Adds a WorldLayer instance to the scene layers.
         * @param worldLayer WorldLayer instance to add.
         */
        void AddWorldLayer(CWorldLayer* worldLayer);
        /**
         * Gets all the WorldLayer instances contained in this scene.
         * @return WorldLayer instances in this scene.
         */
        std::vector<CWorldLayer*> GetWorldLayers();
        void OnInit();
        void OnLoop();

};
#endif
