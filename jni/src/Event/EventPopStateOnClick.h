#ifndef __EVENTPOPSTATEONCLICK__H__
    #define __EVENTPOPSTATEONCLICK_H__
 
#include "Rocket/Core/EventListener.h"
#include "../AppState.h"

class EventPopStateOnClick : public Rocket::Core::EventListener {
    private:
        AppState* m_appState;
        bool m_callUpdate;
        
    public:
        EventPopStateOnClick(AppState* appState, bool callUpate = false);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);
};
 
#endif
