#include "EventStartOnClick.h"
#include "Util/Log.h"

EventStartOnClick::EventStartOnClick(AppStateMain* appStateMain) {
    m_appState = appStateMain;
}

void EventStartOnClick::ProcessEvent(Rocket::Core::Event& event)
{
    Log::L("Start was pressed.");
}
