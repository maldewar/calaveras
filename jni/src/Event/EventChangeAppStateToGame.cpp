#include "EventChangeAppStateToGame.h"
#include "../AppStateManager.h"
#include "Util/Log.h"

EventChangeAppStateToGame::EventChangeAppStateToGame(int act, int level) {
    m_act = act;
    m_level = level;
}

void EventChangeAppStateToGame::ProcessEvent(Rocket::Core::Event& event)
{
    AppStateManager::SetAppStateToGame(m_act, m_level);
}
