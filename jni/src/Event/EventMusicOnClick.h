#ifndef __EVENTMUSICONCLICK__H__
    #define __EVENTMUSICONCLICK_H__
 
#include "Rocket/Core/EventListener.h"
#include "../AppStateMain.h"

class EventMusicOnClick : public Rocket::Core::EventListener {
    private:
        AppStateMain* m_appState;
        
    public:
        EventMusicOnClick(AppStateMain* appStateMain);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);
};
 
#endif
