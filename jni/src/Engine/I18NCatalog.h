#ifndef _I18NCATALOG_H_
    #define _I18NCATALOG_H_

#include <SDL.h>
#include <fstream>
#include <map>
#include <string>
#include <regex>
#include "json.h"

/**
 * Catalog that provides strings to support internationalization.
 */
class I18NCatalog
{
    public:
        enum Locale{
            en_US,
            es_MX,
            fr_FR,
            de_DE
        };

    private:
        static Locale m_locale;
        static std::map<std::string, std::string> m_i18nMap;
        static std::map<std::string, std::string> m_i18nFiles;

    public:
        static void SetLocale(Locale locale);
        static void SetLocale(std::string locale);
        static void AddFile(std::string id, std::string filename);
        static void RemoveFile(std::string id);
        static void Init();
        static void Flush();
        static std::string Replace(std::string text);

    private:
        static void AddCatalog(Json::Value root);
        static std::string GetLocaleString(Locale locale);
        
};
#endif
