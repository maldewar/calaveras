#ifndef __APPSTATE_H__
    #define __APPSTATE_H__
 
#include "Event.h"
#include <stack>
#include "Engine/RocketGlue.h"

/**
 * Defines all the possible states the app could have and
 * the methods and properties shared by all of them.
 */ 
class AppState : public Event {
    protected:
        Rocket::Core::ElementDocument* m_rocketDocument;
        int m_currentState;
        std::stack<int> m_stateStack;
        
    public:
        /**
         * Class constructor.
         */
        AppState();
 
    public:
        /**
         * Method to initialize and set state components.
         */
        virtual void OnActivate(SDL_Renderer* Renderer) = 0;
        /**
         * Method to destroy and unset state components.
         */
        virtual void OnDeactivate() = 0;
        /**
         * Called for processing from the main loop.
         */
        virtual void OnLoop() = 0;
        /**
         * Called to draw components from the main loop.
         */
        virtual void OnRender(SDL_Renderer* Renderer) = 0;
        /**
         * Loads the main Rocket document for this state.
         */
        void LoadDocument(const char* documentName);
        /**
         * Unloads the main Rocket document for this state.
         */
        void UnloadDocument();
        /**
         * Updates a Rocket document if it is loaded.
         */
        void UpdateDocument();
        /**
         * Renders a Rocket document if it is loaded.
         */
        void RenderDocument();
        void OnAfterEvent(SDL_Event* Event);
        void PushState(int state);
        void PopState();
        void ClearStateStack();
        virtual void Update();
        virtual void SetParams(bool dummy, ...);

    protected:
        virtual void ChangeState(const int newState, const int oldState);
        virtual void OnPushState(int state);
        virtual void OnPopState(int state);
};
 
#endif
