#include "EventPushStateOnClick.h"
#include "Util/Log.h"

EventPushStateOnClick::EventPushStateOnClick(AppState* appState, int state, bool callUpdate) {
    m_appState = appState;
    m_state = state;
    m_callUpdate = callUpdate;
}

void EventPushStateOnClick::ProcessEvent(Rocket::Core::Event& event)
{
    m_appState->PushState(m_state);
    if (m_callUpdate)
        m_appState->Update();
}
