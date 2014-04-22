#include "EventGameTools.h"
#include "Util/Log.h"

EventGameTools::EventGameTools(AppStateGame* appStateGame) {
    m_appStateGame = appStateGame;
}

void EventGameTools::ProcessEvent(Rocket::Core::Event& event) {
    std::string pauseParam = event.GetParameter<Rocket::Core::String>("pause","").CString();
    if (!pauseParam.empty()) {
        m_appStateGame->TogglePause();
    }
    std::string selectParam = event.GetParameter<Rocket::Core::String>("select","").CString();
    if (!selectParam.empty()) {
        m_appStateGame->ToggleUsingSelectTool();
    }
    m_appStateGame->Update();
}

bool EventGameTools::GetBoolParam(std::string value, bool currentValue) {
    if (value.compare("toggle") == 0)
        if (currentValue)
            return false;
        else
            return true;
    else if (value.compare("enabled") == 0)
        return true;
    else if (value.compare("disabled") == 0)
        return false;
    else
        return currentValue;
        
};
