#ifndef __EVENTSLOTONCLICK__H__
    #define __EVENTSLOTONCLICK_H__
 
#include "Rocket/Core/EventListener.h"
#include "../AppStateMain.h"

class EventSlotOnClick : public Rocket::Core::EventListener {
    private:
        int m_slotIndex;
        AppStateMain* m_appState;
        
    public:
        EventSlotOnClick(AppStateMain* appStateMain, int slotIndex);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);
};
 
#endif
