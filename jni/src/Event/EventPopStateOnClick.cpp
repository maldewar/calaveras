#include "EventPopStateOnClick.h"
#include "Util/Log.h"

EventPopStateOnClick::EventPopStateOnClick(AppState* appState, bool callUpdate) {
    m_appState = appState;
    m_callUpdate = callUpdate;
}

void EventPopStateOnClick::ProcessEvent(Rocket::Core::Event& event)
{
    m_appState->PopState();
    if (m_callUpdate)
        m_appState->Update();
}
