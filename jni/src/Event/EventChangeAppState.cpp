#include "EventChangeAppState.h"
#include "../AppStateManager.h"
#include "Util/CLog.h"

EventChangeAppState::EventChangeAppState(int appState) {
    m_appState = appState;
}

void EventChangeAppState::ProcessEvent(Rocket::Core::Event& event)
{
    AppStateManager::SetActiveAppState(m_appState);
}
