#ifndef _TEXTUREUTIL_H_
    #define _CTEXTUREUTIL_H_
 
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <vector>
#include <string>

class TextureUtil {
    private:
        static std::unordered_map<std::string, SDL_Texture*> m_textures;

    public:
        /**
         * Loads a texture given its path.
         * @param file Path to the image file.
         * @param renderer Renderer used to load the texture.
         */
        static SDL_Texture* LoadTexture(std::string file, SDL_Renderer* renderer);
        /**
         * Loads a texture given its path and scale it to a desired size.
         * @param file Path to the image file.
         * @param width Width to scale.
         * @param height Height to scale.
         * @param renderer Renderer used to load the texture.
         */
        static SDL_Texture* LoadTexture(std::string file, int width, int height, SDL_Renderer* renderer);
        /**
         * Loads a batch of textures given a list of paths to files.
         * @param files List of paths to file from which to load the textures.
         * @param renderer Renderer that will display these textures.
         */
        static void LoadTextures(std::vector<std::string> files, SDL_Renderer* renderer);
        /**
         * Gets a texture previously loaded.
         * @param file Path to the image used to load the texture.
         */
        static SDL_Texture* GetTexture(std::string file);
        /**
         * Cleans a texture from memory given the path used to load it.
         * @param file Path to the image used to load the texture.
         */
        static void PurgeTexture(std::string file);
        /**
         * Clean all the textures loaded.
         */
        static void Flush();
        /**
         * Used to draw a Texture. Deprecated.
         * @param X X screen coordinate.
         * @param Y Y screen coordinate.
         * @param texture Texture to render.
         * @param renderer Renderer that will render the texture.
         * @returns TRUE if the texture gets rendered.
         */
        static bool OnDraw(int X, int Y, SDL_Texture* texture, SDL_Renderer* renderer);
};
#endif
