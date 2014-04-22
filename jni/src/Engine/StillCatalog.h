#ifndef _STILLCATALOG_H_
    #define _STILLCATALOG_H_

#include <SDL.h>
#include <fstream>
#include <unordered_map>
#include <string>
#include "json.h"
#include "Still.h"

/**
 * Defines the values for each still in the catalog.
 */
struct StillDef {
    /**
     * Name of the Still.
     */
    std::string name;
    /**
     * Number of frames in the X axis.
     */
    int tilesX;
    /**
     * Number of frames in the Y axis.
     */
    int tilesY;
    /**
     * Width of element in meters.
     */
    float width;
    /**
     * Height of element in meters.
     */
    float height;
    /**
     * Index location fot the still frame.
     */
    int tileIndex;
    /**
     * Category for the image file.
     */
    std::string fileCategory;
    /**
     * Path to the file relative to its category.
     */
    std::string filePath;
    /**
     * Full path to the image file. FileCategory + FilePath.
     */
    std::string file;
    
};

/**
 * Catalog that provides still images for elements and their states.
 */
class StillCatalog
{
    private:
        static SDL_Renderer* m_renderer;
        static std::string m_filename;
        static std::unordered_map<std::string, StillDef> m_stillDef;
        static std::unordered_map<std::string, Sprite*> m_stillSprite;

    public:
        /**
         * Loads all the animation parameters saving those definitions
         * to provide stills.
         * @param renderer Necessary to load Textures.
         */
        static void Init(SDL_Renderer* renderer);
        /**
         * Cleans all the object used by the catalog.
         */
        static void Flush();
        /**
         * Gets an still given an element type.
         * @param type Type of element.
         */
        static Still* GetByName(std::string name);

    private:
        static void BuildCatalog(Json::Value root);
        
};
#endif
