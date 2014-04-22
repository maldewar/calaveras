#include "ConfigManager.h"
#include "../Util/Log.h"

std::string ConfigManager::m_locale = "en_US";
bool ConfigManager::m_musicEnabled = true;
bool ConfigManager::m_soundEnabled = true;
bool ConfigManager::m_debugDrawGraph = false;

void ConfigManager::Init() {
};

void ConfigManager::SetLocale(std::string locale) {
    if (IsValidLocale(locale))
        m_locale = locale;
};

std::string ConfigManager::GetLocale() {
    return m_locale;
};

bool ConfigManager::IsValidLocale(std::string locale) {
    if (locale.compare("en_US"))
        return true;
    else if (locale.compare("es_MX"))
        return true;
    else if (locale.compare("fr_FR"))
        return true;
    else if (locale.compare("de_DE"))
        return true;
    else
        return false;
};

void ConfigManager::SetMusicEnabled(bool musicEnabled) {
    m_musicEnabled = musicEnabled;
};

bool ConfigManager::IsMusicEnabled() {
    return m_musicEnabled;
};

void ConfigManager::SetSoundEnabled(bool soundEnabled) {
    m_soundEnabled = soundEnabled;
};

bool ConfigManager::IsSoundEnabled() {
    return m_soundEnabled;
};

void ConfigManager::SetDebugDrawGraphEnabled(bool debugDrawGraph) {
    m_debugDrawGraph = debugDrawGraph;
};

bool ConfigManager::IsDebugDrawGraphEnabled() {
    return m_debugDrawGraph;
};
