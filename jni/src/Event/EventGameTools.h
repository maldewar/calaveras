#ifndef _EVENTGAMETOOLS_H_
    #define _EVENTGAMETOOLS_H_
 
#include "Rocket/Core/EventListener.h"
#include "../AppStateGame.h"

class EventGameTools : public Rocket::Core::EventListener {
    private:
        AppStateGame* m_appStateGame;
        
    public:
        EventGameTools(AppStateGame* appStateGame);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);

    private:
        bool GetBoolParam(std::string value, bool currentValue);
};
 
#endif
