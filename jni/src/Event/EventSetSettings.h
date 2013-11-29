#ifndef __EVENTPUSHSTATEONCLICK__H__
    #define __EVENTPUSHSTATEONCLICK_H__
 
#include "Rocket/Core/EventListener.h"
#include "../AppState.h"

class EventSetSettings : public Rocket::Core::EventListener {
    private:
        AppState* m_appState;
        bool m_callPopState;
        bool m_callUpdate;
        
    public:
        EventSetSettings(AppState* appState);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);
        void SetCallPopState(bool callPopState);
        void SetCallUpdate(bool callUpdate);

    private:
        bool GetBoolParam(std::string value, bool currentValue);
};
 
#endif