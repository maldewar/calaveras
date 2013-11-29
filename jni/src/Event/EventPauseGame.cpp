#include "EventPauseGame.h"
#include "Util/CLog.h"

EventPauseGame::EventPauseGame(AppStateGame* appStateGame) {
    m_appStateGame = appStateGame;
}

void EventPauseGame::ProcessEvent(Rocket::Core::Event& event)
{
    m_appStateGame->TogglePause();
}
