#ifndef _COMPOSITERENDERER_H_
    #define _COMPOSITERENDERER_H_
#include <SDL.h>
#include <Box2D.h>
#include <string>
#include <vector>
#include "../Engine/Gradient.h"
#include "../Util/CMath.h"

class CompositeRenderer {
    private:
        int m_width;
        int m_height;
        SDL_Texture* m_texture;
        SDL_Texture* m_baseTexture;
        std::string m_textureFile;
        bool m_textureRepeatX;
        bool m_textureRepeatY;
        Uint8 m_textureAlpha;
        Uint8 m_textureBlending;
        SDL_Renderer* m_renderer;
        Uint8 m_baseType;
        Uint8 m_red;
        Uint8 m_green;
        Uint8 m_blue;
        Uint8 m_alpha;
        Gradient* m_gradient;
        int m_textureWidthPx;
        int m_textureHeightPx;
        float m_textureWidthM;
        float m_textureHeightM;

    protected:
        float m_maxZoom;

    public:
        enum {
            /**
             * Plain color kind of base.
             */
            BASE_TYPE_PLAIN,
            /**
             * Gradient kind of base.
             */
            BASE_TYPE_GRADIENT
        };

    public:
        /**
         * Class constructor.
         */
        CompositeRenderer(int width, int height);
        /**
         * Class destructor.
         */
        ~CompositeRenderer();
        /**
         * Activates the composite creating the textures used by it.
         * @param renderer Renderer to create textures.
         */
        void Activate(SDL_Renderer* renderer);
        /**
         * Deactivates this renderer and its components.
         */
        void Deactivate();
        /**
         * Returns a composite texture according to this object parameters.
         * @returns Texture of the composite.
         */
        SDL_Texture* GetTexture();
        /**
         * Renders the composite.
         */
        void Render();
        /**
         * Sets the kind base layer used to composite a layer.
         * @param baseType Type of base layer.
         */
        void SetBaseType(Uint8 baseType);
        /**
         * Sets the red component for the base color of the layer.
         * @param red Red component of the color.
         */
        void SetRed(Uint8 red);
        /**
         * Sets the green component for the base color of the layer.
         * @param green Green component of the color.
         */
        void SetGreen(Uint8 green);
        /**
         * Sets the blue component for the base color of the layer.
         * @param blue Blue component of the color.
         */
        void SetBlue(Uint8 blue);
        /**
         * Sets the alpha component for the base color of the layer.
         * @param alpha Alpha component of the color.
         */
        void SetAlpha(Uint8 alpha);
        /**
         * Gets the gradient set for the composite.
         * @returns Gradient object.
         */
        Gradient* GetGradient();
        /**
         * Sets the texture file path.
         * @param file Texture file path.
         */
        void SetTextureFile(std::string file);
        /**
         * Sets the texture width dimension in meters.
         * If set to 0 the original image dimension is taken.
         * @param width Width in meters.
         */
        void SetTextureWidth(float with);
        /**
         * Sets the texture height dimension in meters.
         * If set to 0 the original image dimension is taken.
         * @param height Height in meters.
         */
        void SetTextureHeight(float height);
        /**
         * Indicates if the texture should repeat on the X axis.
         * @param repeat True to repeat the texture.
         */
        void SetTextureRepeatX(bool repeat);
        /**
         * Indicates if the texture should repeat on the Y axis.
         * @param repeat True to repeat the texture.
         */
        void SetTextureRepeatY(bool repeat);
        /**
         * Sets the alpha value for blending the texture if set.
         * @param alpha Alpha value for the texture.
         */
        void SetTextureAlpha(Uint8 alpha);
        /**
         * Sets the blending mode for the texture if set.
         * @param blending Blending mode for the texture.
         */
        void SetTextureBlending(Uint8 blending);

    protected:
        void RenderBase();
        void RenderTexture();
};
#endif
