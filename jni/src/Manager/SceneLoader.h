#ifndef _SCENELOADER_H_
    #define _SCENELOADER_H_

#include <fstream>
#include "json.h"
#include "../Model/CScene.h"

class SceneLoader {
    public:
        SceneLoader();
        ~SceneLoader();

    public:
        CScene* LoadScene(int act, int level);

    private:
        float m_sceneHeight;
        CScene* m_scene;

    private:
        CScene* BuildScene(Json::Value root);
        std::vector<CArea*> BuildAreas(Json::Value jarrAreas, Layer* layer);
        void BuildAssets(Json::Value jarrAssets, WorldLayer* worldLayer);
        void BuildElem(Json::Value jElem, CElem* elem);
        CUnit* BuildUnit(Json::Value jUnit, WorldLayer* worldLayer);
        Entry* BuildEntry(Json::Value jEntry, WorldLayer* worldLayer);
        Exit* BuildExit(Json::Value jExit, WorldLayer* worldLayer);

};

#endif
