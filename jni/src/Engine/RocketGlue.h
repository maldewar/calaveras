#ifndef _ROCKETGLUE_H_
#define _ROCKETGLUE_H_

#include <iostream>
#include "SDL.h"
#include "SDL_config.h"
#include "SDL_image.h"
#include "I18NCatalog.h"
//#include "Python.h"

#if SDL_VIDEO_DRIVER_UIKIT || SDL_VIDEO_DRIVER_ANDROID || SDL_VIDEO_DRIVER_PANDORA || __SDL_NOGETPROCADDR__
#define SDL_PROC_CPP(ret,func,params) render_data.func=func;
#else // SDL_VIDEO_DRIVER_UIKIT || SDL_VIDEO_DRIVER_ANDROID || SDL_VIDEO_DRIVER_PANDORA || __SDL_NOGETPROCADDR__
#if __MINGW32__ || __MINGW64__
#define SDL_PROC_CPP(ret,func,params) \
    do { \
        *reinterpret_cast<void**>(&render_data.func) = SDL_GL_GetProcAddress(#func);\
        if ( ! render_data.func ) { \
            printf("Couldn't load GL function %s: %s\n", #func, SDL_GetError());fflush(stdout); \
            return; \
        } \
    } while ( 0 );
#else // __MINGW32__ || __MINGW64__
#define SDL_PROC_CPP(ret,func,params) \
    do { \
        render_data.func = (ret(*)params)SDL_GL_GetProcAddress(#func);\
        if ( ! render_data.func ) { \
            printf("Couldn't load GL function %s: %s\n", #func, SDL_GetError());fflush(stdout); \
            return; \
        } \
    } while ( 0 );
#endif // __MINGW32__ || __MINGW64__

#endif // SDL_VIDEO_DRIVER_UIKIT || SDL_VIDEO_DRIVER_ANDROID || SDL_VIDEO_DRIVER_PANDORA || __SDL_NOGETPROCADDR__



#include <Rocket/Core/RenderInterface.h>
#include <Rocket/Core/Platform.h>
#include <Rocket/Core.h>
#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/FileInterface.h>
#include <Rocket/Controls.h>

/**
 * Initialises libRocket and create a context.
 * @param renderer SDL renderer.
 * @param name Name for the context.
 * @param width Width in pixels of the renderable area.
 * @param height Height in pixels of the renderable area.
 * @returns libRocket context.
 */
Rocket::Core::Context* RocketInit(SDL_Renderer* renderer, const char* name, int width, int height);

/**
 * Frees a given libRocket context.
 * @param ctx libRocket context to release.
 */
void RocketFree(Rocket::Core::Context *ctx);

/**
 * Frees all the objects created by libRocket.
 */
void RocketShutdown();

/**
 * Translates SDL key input codes to libRocket input key codes.
 * @param sdlkey SDL key input code.
 * @returns libRocket input key code.
 */
int SDLKeyToRocketInput(SDL_Keycode sdlkey);

/**
 * Translates SDL key modifiers to libRocket key modifiers.
 * @param SDL key modifier code.
 * @returns libRocket key modifier.
 */
Rocket::Core::Input::KeyModifier RocketConvertSDLmod( Uint16 sdl );

/**
 * Translates SDL button codes to libRocket button codes.
 * @param SDL button code.
 * @returns libRocket button code.
 */
int RocketConvertSDLButton( Uint8 sdlButton );

/**
 * Binds SDL events to the libRocket context.
 * @param context libRocket context.
 * @param event SDL event to bind.
 */
void InjectRocket( Rocket::Core::Context* context, SDL_Event& event );
//PyObject* GetDocumentNamespace(Rocket::Core::ElementDocument *document);

/**
 * SDL implementation for the libRocket system interface.
 */
class RocketSDLSystemInterface : public Rocket::Core::SystemInterface
{
        public:
                /**
                 * Gets the elapsed time in microseconds this app has been running.
                 * @return Microseconds this app has been running.
                 */
                virtual float GetElapsedTime() {
                        return static_cast<float>( SDL_GetTicks() ) / 1000.0f;
                }
                virtual int TranslateString(Rocket::Core::String& translated, const Rocket::Core::String& input) {
                    translated.Clear();
                    std::string stdString(input.CString());
                    translated.Append(I18NCatalog::Replace(stdString).c_str());
                    //translated = input;
                    return 0;
                }
};

/**
 * SDL implementation for the libRocket file interface.
 */
class RocketSDLFileInterface : public Rocket::Core::FileInterface {
    public:
        /**
         * Opens a file.
         * @param path Path string to the file.
         * @returns libRocket file handler.
         */
        virtual Rocket::Core::FileHandle Open(const Rocket::Core::String& path) {
            return (Rocket::Core::FileHandle)SDL_RWFromFile(path.CString(), "r");
        }

        /**
         * Closes a file.
         * @param file File handle used to open the file.
         */
        virtual void Close(Rocket::Core::FileHandle file) {
            SDL_RWclose((SDL_RWops*)file);
        }

        /**
         * Reads the context of a file.
         * @param buffer Buffer for this file.
         * @param size Size in bytes of the buffer.
         * @param file File handler used to open the file.
         * @returns size of the file.
         */
        virtual size_t Read(void* buffer, size_t size, Rocket::Core::FileHandle file) {
            size_t value = SDL_RWread((SDL_RWops*)file, buffer, 1, size);
            return value;
        }

        virtual bool Seek(Rocket::Core::FileHandle file, long offset, int origin) {
            SDL_RWseek((SDL_RWops*)file, offset, origin);
            return true;
        }

        virtual size_t Tell(Rocket::Core::FileHandle file) {
            return SDL_RWtell((SDL_RWops*)file);
        }
};


class RocketSDLRenderInterface : public Rocket::Core::RenderInterface
{
protected:
    SDL_Renderer *renderer;
    //SDL_Window *window;

public:
        RocketSDLRenderInterface(SDL_Renderer *r);

        /// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
        virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);

        /// Called by Rocket when it wants to render application-compiled geometry.
        virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
        /// Called by Rocket when it wants to release application-compiled geometry.
        virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

        /// Called by Rocket when a texture is required by the library.
        virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
        /// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
        virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
        /// Called by Rocket when a loaded texture is no longer required.
        virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);

        virtual void Resize();

        /// Called by Rocket when it wants to render geometry that it does not wish to optimise.
    virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);
    /// Called by Rocket when it wants to enable or disable scissoring to clip content.
    virtual void EnableScissorRegion(bool enable);
    /// Called by Rocket when it wants to change the scissor region.
    virtual void SetScissorRegion(int x, int y, int width, int height);
};

#endif // _ROCKETGLUE_H_
