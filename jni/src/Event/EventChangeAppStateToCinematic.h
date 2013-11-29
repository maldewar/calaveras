#ifndef __EVENTCHANGEAPPSTATETOCINEMATIC__H__
    #define __EVENTCHANGEAPPSTATETOCINEMATIC_H__
 
#include "Rocket/Core/EventListener.h"

class EventChangeAppStateToCinematic : public Rocket::Core::EventListener {
    private:
        int m_id;
        
    public:
        EventChangeAppStateToCinematic(int id);
 
    public:
        void ProcessEvent(Rocket::Core::Event& event);
};
 
#endif
