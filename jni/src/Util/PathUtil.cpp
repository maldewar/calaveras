#include "PathUtil.h"
#include "Log.h"
#include <sstream>

std::string PathUtil::m_areaCatalog  = "area.catalog.json";
std::string PathUtil::m_animCatalog  = "anim.catalog.json";
std::string PathUtil::m_bgCatalog    = "bg.catalog.json";
std::string PathUtil::m_stillCatalog = "still.catalog.json";
std::string PathUtil::m_actorCatalog = "actor.catalog.json";

int PathUtil::m_topMToPxRatio            = 0;
int PathUtil::m_mToPxRatios[]            = {192, 384, 512, 819};

std::string PathUtil::GetAreaCatalog() {
    return m_areaCatalog;
};

std::string PathUtil::GetAnimationCatalog() {
    return m_animCatalog;
};

std::string PathUtil::GetBgCatalog() {
    return m_bgCatalog;
};

std::string PathUtil::GetStillCatalog() {
    return m_stillCatalog;
};

std::string PathUtil::GetActorCatalog() {
  return m_actorCatalog;
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

std::string PathUtil::GetCategoryFile(std::string category, std::string filePath) {
    std::stringstream sstm;
    sstm << category << "/" << filePath;
    return sstm.str();
};

std::string PathUtil::GetCategoryFile(std::string category, std::string filePath, int mToPxRatio) {
    std::stringstream sstm;
    sstm << category << "/" << GetTopMToPxRatio(mToPxRatio) << "/" << filePath;
    return sstm.str();
};

int PathUtil::GetTopMToPxRatio(int mToPxRatio) {
    if (m_topMToPxRatio == 0) {
        int length = (sizeof(m_mToPxRatios)/sizeof(*m_mToPxRatios));
        for(int i=0; i < length; i++) {
            m_topMToPxRatio = m_mToPxRatios[i];
            if (m_topMToPxRatio >= mToPxRatio)
                break;
        }
    }
    return m_topMToPxRatio;
};

int PathUtil::GetTopMToPxRatio() {
    return m_topMToPxRatio;
};
