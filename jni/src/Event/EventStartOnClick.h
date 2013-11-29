#ifndef __EVENTSTARTONCLICK__H__
    #define __EVENTSTARTONCLICK_H__
 
#include "Rocket/Core/EventListener.h"
#include "../AppStateMain.h"

class EventStartOnClick : public Rocket::Core::EventListener {
    private:
        AppStateMain* m_appState;
        
    public:
        EventStartOnClick(AppStateMain* appStateMain);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);
};
 
#endif
