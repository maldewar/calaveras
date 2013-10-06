#ifndef __CAPPSTATE_H__
    #define __CAPPSTATE_H__
 
#include "CEvent.h"
 
class AppState : public CEvent {
    public:
        AppState();
 
    public:
        virtual void OnActivate(SDL_Renderer* Renderer) = 0;
        virtual void OnDeactivate() = 0;
        virtual void OnLoop() = 0;
        virtual void OnRender(SDL_Renderer* Renderer) = 0;
};
 
#endif
