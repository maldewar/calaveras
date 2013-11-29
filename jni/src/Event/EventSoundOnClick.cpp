#include "EventSoundOnClick.h"
#include "Util/CLog.h"

EventSoundOnClick::EventSoundOnClick(AppStateMain* appStateMain) {
    m_appState = appStateMain;
}

void EventSoundOnClick::ProcessEvent(Rocket::Core::Event& event)
{
    CLog::Log("Sound was pressed.");
}
