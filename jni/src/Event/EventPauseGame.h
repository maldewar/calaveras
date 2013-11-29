#ifndef __EVENTPAUSEGAME__H__
    #define __EVENTPAUSEGAME_H__
 
#include "Rocket/Core/EventListener.h"
#include "../AppStateGame.h"

class EventPauseGame : public Rocket::Core::EventListener {
    private:
        AppStateGame* m_appStateGame;
        
    public:
        EventPauseGame(AppStateGame* appStateGame);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);
};
 
#endif
