#include "I18NCatalog.h"
#include "../Util/CFile.h"
#include "../Util/CLog.h"
#include "../Util/PathUtil.h"

I18NCatalog::Locale I18NCatalog::m_locale = en_US;
std::map<std::string, std::string> I18NCatalog::m_i18nMap;
std::map<std::string, std::string> I18NCatalog::m_i18nFiles;

void I18NCatalog::SetLocale(Locale locale) {
    m_locale = locale;
};

void I18NCatalog::SetLocale(std::string locale) {
    CLog::Log("Setting locale in i18n to: %s", locale.c_str());
    if (locale.compare("en_US") == 0)
        m_locale = en_US;
    else if (locale.compare("es_MX") == 0) {
        m_locale = es_MX;
        CLog::Log("Locale set to enum: %s", GetLocaleString(m_locale).c_str());
    } else if (locale.compare("fr_FR") == 0)
        m_locale = fr_FR;
    else if (locale.compare("de_DE") == 0)
        m_locale = de_DE;
    else
        m_locale = en_US;
};

void I18NCatalog::AddFile(std::string id, std::string filename) {
    m_i18nFiles[id] = filename;
};

void I18NCatalog::RemoveFile(std::string id) {
    m_i18nFiles.erase(id);
};

void I18NCatalog::Init() {
    CLog::Log("Calling to init i18n with locale: %s.", GetLocaleString(m_locale).c_str());
    m_i18nMap.clear();
    std::map<std::string, std::string>::iterator it;
    for(it = m_i18nFiles.begin();it != m_i18nFiles.end(); it++) {
        std::string filename = PathUtil::GetI18NFile(GetLocaleString(m_locale),
                                it->second.c_str());
        std::string document = CFile::ReadText(filename);
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(document.c_str(), root, false);
        if (! parsingSuccessful) {
            CLog::Log(reader.getFormatedErrorMessages());
        } else {
            AddCatalog(root);
        }
    };
};

void I18NCatalog::Flush() {
    m_i18nMap.clear();
    m_i18nFiles.clear();
};

std::string I18NCatalog::Replace(std::string text) {
    std::size_t openPos = text.find("[");
    std::string token;
    if (openPos != std::string::npos) {
        std::size_t closePos = text.find("]");
        while (openPos != std::string::npos && closePos != std::string::npos && closePos > openPos) {
            token = text.substr(openPos + 1, closePos - openPos - 1);
            if (m_i18nMap.count(token) > 0)
                text.replace(openPos, closePos - openPos + 1, m_i18nMap[token]);
            else
                text.replace(openPos, closePos - openPos + 1, token);
            openPos = text.find("[");
            closePos = text.find("]");
        }
    }
    return text;
};

void I18NCatalog::AddCatalog(Json::Value root) {
    if (root.size() == 0)
        return;
    for( Json::ValueIterator itr = root.begin() ; itr != root.end() ; itr++ ) {
        m_i18nMap[itr.key().asString()] = root[itr.key().asString()].asString(); 
    }
}

std::string I18NCatalog::GetLocaleString(Locale locale) {
    std::string localeString;
    switch(locale) {
        case en_US:
            localeString = "en_US";
            break;
        case es_MX:
            localeString = "es_MX";
            break;
        case fr_FR:
            localeString = "fr_FR";
            break;
        case de_DE:
            localeString = "de_DE";
            break;
        default:
            localeString = "en_US";
    }
    return localeString;
};
