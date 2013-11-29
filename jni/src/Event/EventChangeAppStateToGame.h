#ifndef __EVENTCHANGEAPPSTATETOGAME__H__
    #define __EVENTCHANGEAPPSTATETOGAME_H__
 
#include "Rocket/Core/EventListener.h"

class EventChangeAppStateToGame : public Rocket::Core::EventListener {
    private:
        int m_act;
        int m_level;
        
    public:
        EventChangeAppStateToGame(int act, int level);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);
};
 
#endif
