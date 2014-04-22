#include "EventChangeAppStateToCinematic.h"
#include "../AppStateManager.h"
#include "Util/Log.h"

EventChangeAppStateToCinematic::EventChangeAppStateToCinematic(int id) {
    m_id = id;
}

void EventChangeAppStateToCinematic::ProcessEvent(Rocket::Core::Event& event)
{
    AppStateManager::SetAppStateToCinematic(m_id);
}
