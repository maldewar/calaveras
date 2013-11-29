#ifndef __EVENTCHANGEAPPSTATE__H__
    #define __EVENTCHANGEAPPSTATE_H__
 
#include "Rocket/Core/EventListener.h"

class EventChangeAppState : public Rocket::Core::EventListener {
    private:
        int m_appState;
        
    public:
        EventChangeAppState(int appState);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);
};
 
#endif
