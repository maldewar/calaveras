#ifndef _SCENELOADER_H_
    #define _SCENELOADER_H_

#include <fstream>
#include "json.h"
#include "../Model/Scene.h"

class SceneLoader {
    public:
        SceneLoader();
        ~SceneLoader();

    public:
        Scene* LoadScene(int act, int level);

    private:
        float m_sceneHeight;
        Scene* m_scene;

    private:
        Scene* BuildScene(Json::Value root);
        std::vector<Area*> BuildAreas(Json::Value jarrAreas, Layer* layer);
        void BuildAssets(Json::Value jarrAssets, WorldLayer* worldLayer);
        void BuildElem(Json::Value jElem, Elem* elem);
        Unit* BuildUnit(Json::Value jUnit, WorldLayer* worldLayer);
        Entry* BuildEntry(Json::Value jEntry, WorldLayer* worldLayer);
        Exit* BuildExit(Json::Value jExit, WorldLayer* worldLayer);
        LayeredGraphic* BuildLayeredGraphic(Json::Value jLGraphic, Vector2* center);
        void OffsetElem(Elem* elem, Vector2* reference);
        static bool SortIndex(Elem* elemA, Elem* elemB);

};

#endif
