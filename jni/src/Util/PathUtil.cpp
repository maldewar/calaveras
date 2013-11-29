#include "PathUtil.h"
#include <sstream>

std::string PathUtil::m_areaCatalog      = "AreaCatalog.json";
std::string PathUtil::m_animationCatalog = "AnimationCatalog.json";
std::string PathUtil::m_bgCatalog        = "BgCatalog.json";

std::string PathUtil::GetAreaCatalog() {
    return m_areaCatalog;
};

std::string PathUtil::GetAnimationCatalog() {
    return m_animationCatalog;
};

std::string PathUtil::GetBgCatalog() {
    return m_bgCatalog;
};

std::string PathUtil::GetScene(int act, int level) {
    std::stringstream sstm;
    sstm << "scene/" << act << "/" << level << "/scene.json";
    return sstm.str();
};

std::string PathUtil::GetI18NFile(std::string locale, std::string filename) {
    std::stringstream sstm;
    sstm << "i18n/" << locale << "/" << filename;
    return sstm.str();
};
