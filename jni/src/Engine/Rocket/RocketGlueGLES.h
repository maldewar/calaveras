#ifndef _ROCKETGLUEGLES_H_
#define _ROCKETGLUEGLES_H_

#include "../RocketGlue.h"

#if !SDL_RENDER_DISABLED && SDL_VIDEO_RENDER_OGL_ES
#include "SDL_opengles.h"

typedef struct
{
 /* OpenGL functions */
#define SDL_PROC(ret,func,params) ret (APIENTRY *func) params;
#define ROCKET_OPENGLES
#include "RocketGLFuncs.h"
#undef SDL_PROC
#undef ROCKET_OPENGLES

} RenderDataGLES;

class RocketSDLRenderInterfaceOpenGLES : public RocketSDLRenderInterface
{
protected:
    RenderDataGLES render_data;

public:
        RocketSDLRenderInterfaceOpenGLES(SDL_Renderer *r, SDL_Window *w);

        /// Called by Rocket when it wants to render geometry that it does not wish to optimise.
        virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);
        /// Called by Rocket when it wants to enable or disable scissoring to clip content.
        virtual void EnableScissorRegion(bool enable);
        /// Called by Rocket when it wants to change the scissor region.
        virtual void SetScissorRegion(int x, int y, int width, int height);
};

#endif // !SDL_RENDER_DISABLED && SDL_VIDEO_RENDER_OGL_ES

#endif // _ROCKETGLUEGLES_H_
