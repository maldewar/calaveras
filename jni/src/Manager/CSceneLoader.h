#ifndef _CSCENELOADER_H_
    #define _CSCENELOADER_H_

#include <fstream>
#include "json.h"
#include "../Model/CScene.h"

class CSceneLoader {
    public:
        CSceneLoader(int act, int level);
        ~CSceneLoader();

    public:
        CScene* LoadScene();

    private:
        int m_act;
        int m_level;
        float m_sceneHeight;
        CScene* m_scene;

    private:
        std::string GetScenePath(int act, int level);
        CScene* BuildScene(Json::Value root);
        std::vector<CArea*> BuildAreas(Json::Value jarrAreas, CLayer* layer);
        void BuildAssets(Json::Value jarrAssets, CWorldLayer* worldLayer);
        CUnit* BuildUnit(Json::Value jUnit, CWorldLayer* worldLayer);
        CEntry* BuildEntry(Json::Value jEntry, CWorldLayer* worldLayer);

};

#endif
