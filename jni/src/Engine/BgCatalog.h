#ifndef _BGCATALOG_H_
    #define _BGCATALOG_H_

#include <SDL.h>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include "json.h"
#include "../Renderer/CompositeRenderer.h"

/**
 * Defines the values for a background.
 */
struct BgDef {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    int baseType;
    std::vector<Uint8> reds;
    std::vector<Uint8> greens;
    std::vector<Uint8> blues;
    std::vector<Uint8> alphas;
    std::vector<float> positions;
    float angle;
    float x;
    float y;
    int gradientType;
    std::string textureFile;
    float textureWidth;
    float textureHeight;
    bool textureRepeatX;
    bool textureRepeatY;
    float textureAlpha;
    int textureBlending;
};

/**
 * Catalog that provides background elements and their states.
 */
class BgCatalog
{
    private:
        static SDL_Renderer* m_renderer;
        static std::string m_filename;
        static std::unordered_map<int, BgDef> m_bgDef;

    public:
        /**
         * Loads all the background definitions.
         * @param renderer Necessary to load Textures.
         */
        static void Init(SDL_Renderer* renderer);
        /**
         * Cleans all the object used by the catalog.
         */
        static void Flush();
        /**
         * Fills the CompositeRenderer properties according to the catalog.
         * @param type Type of element.
         */
        static void FillRenderer(int id, CompositeRenderer* compositeRenderer);

    private:
        static void BuildCatalog(Json::Value root);
        
};
#endif
