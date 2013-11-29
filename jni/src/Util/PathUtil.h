#ifndef _PATHUTIL_H_
    #define _PATHUTIL_H_

#include <string>

class PathUtil
{
    private:
        PathUtil();

    private:
        static std::string m_areaCatalog;
        static std::string m_animationCatalog;
        static std::string m_bgCatalog;

    public:
        static std::string GetAreaCatalog();
        static std::string GetAnimationCatalog();
        static std::string GetBgCatalog();
        static std::string GetScene(int act, int level);
        static std::string GetI18NFile(const std::string locale, const std::string filename);
};

#endif
