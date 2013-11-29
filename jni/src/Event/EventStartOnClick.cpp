#include "EventStartOnClick.h"
#include "Util/CLog.h"

EventStartOnClick::EventStartOnClick(AppStateMain* appStateMain) {
    m_appState = appStateMain;
}

void EventStartOnClick::ProcessEvent(Rocket::Core::Event& event)
{
    CLog::Log("Start was pressed.");
}
