#ifndef _ANIMATIONCATALOG_H_
    #define _ANIMATIONCATALOG_H_

#include <SDL.h>
#include <fstream>
#include <unordered_map>
#include <string>
#include "json.h"
#include "Animation.h"

/**
 * Defines the values for the animation.
 */
struct AnimationDef {
    /**
     * Primary index based on the type of element.
     */
    int elemType;
    /**
     * Secondary index based on the state of the element.
     */
    int elemState;
    /**
     * Terciary index based on the substate of the element.
     */
    int elemSubstate;
    /**
     * Type of animation, linear, loop or wave.
     */
    int animType;
    /**
     * Defines the direction for the animation from the last to the first frame.
     */
    bool isBackwards;
    /**
     * Sets the starting frame for the animation.
     */
    int currentFrame;
    /**
     * Total numbers of frames.
     */
    int maxFrames;
    /**
     * Number of milliseconds to wait in between frame transitions.
     */
    int framerate;
    /**
     * Number of frames in the X axis.
     */
    int tilesX;
    /**
     * Number of frames in the Y axis.
     */
    int tilesY;
    /**
     * Width in meters for each frame.
     */
    float tileWidth;
    /**
     * Height in meters for each frame.
     */
    float tileHeight;
    /**
     * Offset in the X axis in pixels to locate the frames.
     */
    int offsetX;
    /**
     * Offset in the Y axis in pixels to locate the frames.
     */
    int offsetY;
    /**
     * Category for the image file.
     */
    std::string fileCategory;
    /**
     * Path relative to the category folder to the image file.
     */
    std::string filePath;
    /**
     * Path to the image file.
     */
    std::string file;
    
};

/**
 * Catalog that provides animation for elements and their states.
 */
class AnimationCatalog
{
    private:
        static SDL_Renderer* m_renderer;
        static std::string m_filename;
        static std::unordered_map<int, AnimationDef> m_animDef;
        static std::unordered_map<int, Sprite*> m_animSprite;

    public:
        /**
         * Loads all the animation parameters saving those definitions
         * to provide animations.
         * @param renderer Necessary to load Textures.
         */
        static void Init(SDL_Renderer* renderer);
        /**
         * Cleans all the object used by the catalog.
         */
        static void Flush();
        /**
         * Gets an animation given an element type.
         * @param type Type of element.
         */
        static Animation* GetByType(int type);
        /**
         * Gets an animation given an element type and its state.
         * @param type Type of element.
         * @param state State of the element.
         */
        static Animation* GetByState(int type, int state);
        /**
         * Gets an animation given an element type, its state and substate.
         * @param type Type of element.
         * @param state State of the element.
         * @param substate Substate of the element.
         */
        static Animation* GetBySubstate(int type, int state, int substate);

    private:
        static void BuildCatalog(Json::Value root);
        static Animation* GetAnimation(int type, int state, int substate);
        
};
#endif
