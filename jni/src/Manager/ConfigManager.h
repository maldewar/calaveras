#ifndef _CONFIGMANAGER_H_
    #define _CONFIGMANAGER_H_

#include <string>

class ConfigManager {
    public:
        static void Init();
        static void SetLocale(std::string locale);
        static std::string GetLocale();
        static bool IsValidLocale(std::string locale);
        static void SetMusicEnabled(bool musicEnabled);
        static bool IsMusicEnabled();
        static void SetSoundEnabled(bool soundEnabled);
        static bool IsSoundEnabled();

    private:
        static std::string m_locale;
        static bool m_musicEnabled;
        static bool m_soundEnabled;

};

#endif
