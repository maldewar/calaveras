#ifndef _GRADIENT_H_
    #define _GRADIENT_H_
#include <SDL.h>
#include <map>
#include <vector>

class Gradient {
    private:
        std::map<float, Uint32> m_steps;
        float m_angle;
        float m_x;
        float m_y;
        int m_type;
        float m_basePosition, m_nextPosition;
        Uint32 m_colorFrom;
        Uint32 m_colorTo;
        SDL_Surface* m_refSurface;

    public:
        enum {
            /**
             * Linear gradient.
             */
            LINEAR,
            /**
             * Radial gradient.
             */
            RADIAL
        };

    public:
        /**
         * Class constructor.
         */
        Gradient();
        /**
         * Class destructor.
         */
        ~Gradient();
        /**
         * Adds a color step to the gradient.
         * @param color Color as a 32bit value.
         * @param position Value between 0 and 1 the color will take as a step in the gradient.
         * @returns True if the step is added.
         */
        bool AddStep(Uint32 color, float position);
        /**
         * Adds a color step to the gradient.
         * @param red Red component of the color to add from 0 to 255.
         * @param green Green component of the color to add from 0 to 255.
         * @param blue Blue component of the color to add from 0 to 255.
         * @param position Value between 0 and 1 the color will take as a step in the gradient.
         * @returns True if the step is added.
         */
        bool AddStep(Uint8 red, Uint8 green, Uint8 blue, float position);
        /**
         * Adds a color step to the gradient.
         * @param red Red component of the color to add from 0 to 255.
         * @param green Green component of the color to add from 0 to 255.
         * @param blue Blue component of the color to add from 0 to 255.
         * @param alpha Alpha component of the color to add from 0 to 255.
         * @param position Value between 0 and 1 the color will take as a step in the gradient.
         * @returns True if the step is added.
         */
        bool AddStep(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, float position);
        /**
         * Add color steps to the gradient.
         * @param colors Vector of colors.
         * @param positions Vector of positions.
         */
        void AddSteps(std::vector<Uint32> colors, std::vector<float> positions);
        void AddSteps(std::vector<Uint8> reds,
                    std::vector<Uint8> greens,
                    std::vector<Uint8> blues,
                    std::vector<Uint8> alphas,
                    std::vector<float> positions);
        /**
         * Sets a color value, if not set, for steps 0 and 1 in the gradient.
         * @param red Red component of the color to add from 0 to 255.
         * @param green Green component of the color to add from 0 to 255.
         * @param blue Blue component of the color to add from 0 to 255.
         * @param alpha Alpha component of the color to add from 0 to 255.
         */
        void SetBaseColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
        /**
         * Clear the color steps in the gradient.
         */
        void Clear();
        /**
         * Sets the angle of for a linear gradient.
         * @param angle Angle in radians.
         */
        void SetAngle(float angle);
        /**
         * Returns the angle for a linear gradient.
         * @returns Angle in radians.
         */
        float GetAngle();
        /**
         * Sets the X center coordinate for a radial gradient.
         * @param x X coordinate for the center from 0 to 1.
         */
        void SetX(float x);
        /**
         * Gets the X center coordinate for a radial gradient.
         * @returns X coordinate for the center from 0 to 1.
         */
        float GetX();
        /**
         * Sets the Y center coordinate for a radial gradient.
         * @param y Y coordinate for the center from 0 to 1.
         */
        void SetY(float y);
        /**
         * Gets the Y center coordinate for a radial gradient.
         * @returns Y coordinate for the center from 0 to 1.
         */
        float GetY();
        /**
         * Sets the type of gradient to linear or radial.
         * @param type Type of gradient.
         */
        void SetType(int type);
        /**
         * Gets the type of gradient been set.
         * @returns Type of gradients.
         */
        int GetType();
        /**
         * Draws a texture using the gradient params.
         * @param width Number of pixels for width.
         * @param height Number of pixels for height.
         * @param renderer Renderer used to generate the texture.
         * @returns Texture with gradient.
         */
        SDL_Texture* Draw(int width, int height, SDL_Renderer* renderer);

    private:
        SDL_Surface* GetSurface(int width, int height);
        void SetColorsAt(float position);
        Uint32 GetColorFrom(float position);
        Uint32 GetColorTo(float position);
};
#endif
