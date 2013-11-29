#ifndef __EVENTSOUNDONCLICK__H__
    #define __EVENTSOUNDONCLICK_H__
 
#include "Rocket/Core/EventListener.h"
#include "../AppStateMain.h"

class EventSoundOnClick : public Rocket::Core::EventListener {
    private:
        AppStateMain* m_appState;
        
    public:
        EventSoundOnClick(AppStateMain* appStateMain);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);
};
 
#endif
