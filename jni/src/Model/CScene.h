#ifndef _CSCENE_H_
    #define _CSCENE_H_
#include <string>
#include <vector>
#include "FgLayer.h"
#include "WorldLayer.h"
#include "BgLayer.h"
class FgLayer;
class WorldLayer;
class BgLayer;
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
        std::vector<FgLayer*> m_fgLayers;
        std::vector<WorldLayer*> m_worldLayers;
        std::vector<BgLayer*> m_bgLayers;
        static Vector2* m_gravity;

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
         * Set the global gravity vector for the scene.
         * @param x X vector component.
         * @param y Y vector component.
         */
        static void SetGravity(float x, float y);
        /**
         * Gets the global gravity set for the scene.
         * @returns Gravity vector.
         */
        static Vector2* GetGravity();
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
         * Adds a FgLayer instance to the scene layers.
         * @param fgLayer FgLayer instance to add.
         */
        void AddFgLayer(FgLayer* fgLayer);
        /**
         * Gets all the FgLayer instances contained in this scene.
         * @return FgLayer instances in this scene.
         */
        std::vector<FgLayer*> GetFgLayers();
        /**
         * Adds a WorldLayer instance to the scene layers.
         * @param worldLayer WorldLayer instance to add.
         */
        void AddWorldLayer(WorldLayer* worldLayer);
        /**
         * Gets all the WorldLayer instances contained in this scene.
         * @return WorldLayer instances in this scene.
         */
        std::vector<WorldLayer*> GetWorldLayers();
        /**
         * Adds a BgLayer instance to the scene layers.
         * @param bgLayer BgLayer instance to add.
         */
        void AddBgLayer(BgLayer* bgLayer);
        /**
         * Gets all the BgLayer instances contained in this scene.
         * @return BgLayer instances in this scene.
         */
        std::vector<BgLayer*> GetBgLayers();
        void OnInit();
        void OnLoop();

};
#endif
