#ifndef _AREACATALOG_H_
    #define _AREACATALOG_H_

#include <SDL.h>
#include <fstream>
#include <unordered_map>
#include <string>
#include "json.h"
#include "../Model/Area.h"

/**
 * Defines the values for the animation.
 */
struct AreaDef {
    /**
     * Name of the area according to its nature.
     */
    std::string name;
    /**
     * Nature unique identifier for this area.
     */
    int nature;
    /**
     * Restitution value.
     */
    float restitution;
    /**
     * Friction value.
     */
    float friction;
    /**
     * Density for the whole area.
     */
    float density;
    /**
     * Angular damping value.
     */
    float angularDamping;
    /**
     * Linear damping value.
     */
    float linearDamping;
    /**
     * Linear velocity value tolerance.
     */
    float linearTolerance;
    /**
     * Angular velocity value tolerance.
     */
    float angularTolerance;
};

class AreaCatalog
{
    private:
        static SDL_Renderer* m_renderer;
        static std::string m_filename;
        static std::unordered_map<int, AreaDef> m_areaDef;

    public:
        /**
         * Loads all the area parameters contained in the catalog..
         * @param renderer Necessary to load Textures.
         */
        static void Init(SDL_Renderer* renderer);
        /**
         * Cleans all the object used by the catalog.
         */
        static void Flush();
        /**
         * Sets the values for an area according to its nature.
         * @param area Area to set values to.
         */
        static void Set(Area* area);

    private:
        static void BuildCatalog(Json::Value root);

};
#endif
