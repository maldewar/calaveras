#include "EventSetSettings.h"
#include "Manager/ConfigManager.h"
#include "Engine/I18NCatalog.h"
#include "Util/Log.h"

EventSetSettings::EventSetSettings(AppState* appState) {
    m_appState = appState;
    m_callPopState = false;
    m_callUpdate = true;
}

void EventSetSettings::ProcessEvent(Rocket::Core::Event& event) {
    std::string languageParam = event.GetParameter<Rocket::Core::String>("language","").CString();
    if (!languageParam.empty()) {
        if (ConfigManager::IsValidLocale(languageParam)) {
            ConfigManager::SetLocale(languageParam);
            I18NCatalog::SetLocale(languageParam);
            I18NCatalog::Init();
        }
    }
    std::string musicParam = event.GetParameter<Rocket::Core::String>("music","").CString();
    if (!musicParam.empty()) {
        ConfigManager::SetMusicEnabled(GetBoolParam(musicParam, ConfigManager::IsMusicEnabled()));
    }
    std::string soundParam = event.GetParameter<Rocket::Core::String>("sound","").CString();
    Log::L("Turning sound %s .", soundParam.c_str());
    if (!soundParam.empty()) {
        ConfigManager::SetSoundEnabled(GetBoolParam(soundParam, ConfigManager::IsSoundEnabled()));
    }
    std::string dGraphParam = event.GetParameter<Rocket::Core::String>("dgraph","").CString();
    Log::L("Turning dGraph %s .", dGraphParam.c_str());
    if (!dGraphParam.empty()) {
        ConfigManager::SetDebugDrawGraphEnabled(GetBoolParam(dGraphParam, ConfigManager::IsDebugDrawGraphEnabled()));
    }
    if (m_callPopState)
        m_appState->PopState();
    if (m_callUpdate) 
        m_appState->Update();
}

void EventSetSettings::SetCallPopState(bool callPopState) {
    m_callPopState = callPopState;
};

void EventSetSettings::SetCallUpdate(bool callUpdate) {
    m_callUpdate = callUpdate;
};

bool EventSetSettings::GetBoolParam(std::string value, bool currentValue) {
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
