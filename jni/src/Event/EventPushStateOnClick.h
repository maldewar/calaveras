#ifndef __EVENTPUSHSTATEONCLICK__H__
    #define __EVENTPUSHSTATEONCLICK_H__
 
#include "Rocket/Core/EventListener.h"
#include "../AppState.h"

class EventPushStateOnClick : public Rocket::Core::EventListener {
    private:
        AppState* m_appState;
        int m_state;
        bool m_callUpdate;
        
    public:
        EventPushStateOnClick(AppState* appState, int state, bool callUpdate = false);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);
};
 
#endif
