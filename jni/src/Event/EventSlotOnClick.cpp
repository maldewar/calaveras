#include "EventSlotOnClick.h"

EventSlotOnClick::EventSlotOnClick(AppStateMain* appStateMain, int slotIndex) {
    m_appState = appStateMain;
    m_slotIndex = slotIndex;
}

void EventSlotOnClick::ProcessEvent(Rocket::Core::Event& event)
{
    m_appState->DisplaySlot(m_slotIndex);
}
