#ifndef _PATHUTIL_H_
    #define _PATHUTIL_H_

#include <string>

class PathUtil
{
    private:
        PathUtil();
        static int GetTopMToPxRatio(int mToPxRatio);

    private:
        static std::string m_areaCatalog;
        static std::string m_animCatalog;
        static std::string m_bgCatalog;
        static std::string m_stillCatalog;
        static std::string m_actorCatalog;
        static int m_mToPxRatios[];
        static int m_topMToPxRatio;

    public:
        static std::string GetAreaCatalog();
        static std::string GetAnimationCatalog();
        static std::string GetBgCatalog();
        static std::string GetStillCatalog();
        static std::string GetActorCatalog();
        static std::string GetScene(int act, int level);
        static std::string GetI18NFile(const std::string locale, const std::string filename);
        static std::string GetCategoryFile(const std::string category, const std::string filePath);
        static std::string GetCategoryFile(const std::string category, const std::string filePath, int mToPxRatio);
        static int GetTopMToPxRatio();
};

#endif
