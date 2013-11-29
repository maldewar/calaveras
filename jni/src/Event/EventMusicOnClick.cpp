#include "EventMusicOnClick.h"
#include "Util/CLog.h"

EventMusicOnClick::EventMusicOnClick(AppStateMain* appStateMain) {
    m_appState = appStateMain;
}

void EventMusicOnClick::ProcessEvent(Rocket::Core::Event& event)
{
    CLog::Log("Music was pressed.");
}
