#include "SceneLoader.h"
#include "../Util/CFile.h"
#include "../Util/CLog.h"
#include "../Util/CMath.h"
#include "../Util/PathUtil.h"

SceneLoader::SceneLoader() {
    m_sceneHeight = 0;
}

SceneLoader::~SceneLoader() {
}

CScene* SceneLoader::LoadScene(int act, int level) {
    std::string filePath = PathUtil::GetScene(act, level);
    std::string document = CFile::ReadText(filePath.c_str());
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(document.c_str(), root, false);
    if (! parsingSuccessful) {
        CLog::Log(reader.getFormatedErrorMessages());
        return NULL;
    }
    BuildScene(root);
    CLog::Log("Scene Built.");
    return m_scene;
}

CScene* SceneLoader::BuildScene(const Json::Value root) {
    m_scene = new CScene();
    m_scene->SetVersion(root.get("version", "0.0").asString());
    m_scene->SetWidth(root.get("width", 3.0f).asDouble());
    m_scene->SetHeight(root.get("height", 3.0f).asDouble());
    m_sceneHeight = m_scene->GetHeight();
    const Json::Value jarrFgLayers = root["fgLayers"];
    for(int fgLayerIndex = 0; fgLayerIndex < jarrFgLayers.size(); fgLayerIndex++) {
        const Json::Value jFgLayer = jarrFgLayers[fgLayerIndex];
        FgLayer* fgLayer = new FgLayer();
        fgLayer->SetId(jFgLayer.get("id","").asString());
        fgLayer->SetDistance(jFgLayer.get("distance",0.0f).asDouble());
        m_scene->AddFgLayer(fgLayer);
    }
    const Json::Value jarrWorldLayers = root["worldLayers"];
    for(int worldLayerIndex = 0; worldLayerIndex < jarrWorldLayers.size(); worldLayerIndex++) {
        const Json::Value jWorldLayer = jarrWorldLayers[worldLayerIndex];
        WorldLayer* worldLayer = new WorldLayer();
        worldLayer->SetId(jWorldLayer.get("id","").asString());
        worldLayer->SetDistance(jWorldLayer.get("distance",0.0f).asDouble());
        const Json::Value jarrAreas = jWorldLayer["areas"];
        worldLayer->SetAreas(BuildAreas(jarrAreas, worldLayer));
        const Json::Value jarrAssets = jWorldLayer["assets"];
        BuildAssets(jarrAssets, worldLayer);
        m_scene->AddWorldLayer(worldLayer);
    }
    const Json::Value jarrBgLayers = root["bgLayers"];
    for(int bgLayerIndex = 0; bgLayerIndex < jarrBgLayers.size(); bgLayerIndex++) {
        const Json::Value jBgLayer = jarrBgLayers[bgLayerIndex];
        BgLayer* bgLayer = new BgLayer();
        bgLayer->SetId(jBgLayer.get("id", "").asString());
        bgLayer->SetBg(jBgLayer.get("bgId", 0).asInt());
        bgLayer->SetDistance(jBgLayer.get("distance", 0.0f).asDouble());
        m_scene->AddBgLayer(bgLayer);
    }
    CLog::Log(m_scene->GetVersion());
    return m_scene;
}

std::vector<CArea*> SceneLoader::BuildAreas(const Json::Value jarrAreas, Layer* layer) {
    std::vector<CArea*> areas;
    for(int index = 0; index < jarrAreas.size(); ++index ) {
        const Json::Value jArea = jarrAreas[index];
        CArea* area = new CArea(layer);
        area->SetMaterial(jArea.get("material",0).asInt());
        area->SetNature(jArea.get("nature",0).asInt());
        const Json::Value jarrPoints = jArea["points"];
        for(int jindex = 0; jindex < jarrPoints.size(); ++jindex) {
            const Json::Value jPoint = jarrPoints[jindex];
            area->AddPoint(jPoint.get("x",0.0f).asDouble(),CMath::ToCartesian(jPoint.get("y",0.0f).asDouble(), m_sceneHeight));
        }
        area->SetClosed(jArea.get("closed",true).asBool());
        area->SetBody();
        areas.push_back(area);
    }
    return areas;
};

void SceneLoader::BuildAssets(Json::Value jarrAssets, WorldLayer* worldLayer) {
    for(int index = 0; index < jarrAssets.size(); ++index) {
        const Json::Value jAsset = jarrAssets[index];
        std::string assetType = jAsset.get("type","").asString();
        if (assetType.compare("unit") == 0)
            worldLayer->AddUnit(BuildUnit(jAsset, worldLayer));
        else if (assetType.compare("entry") == 0)
            worldLayer->AddEntry(BuildEntry(jAsset, worldLayer));
        else if (assetType.compare("exit") == 0)
            worldLayer->AddExit(BuildExit(jAsset, worldLayer));
    }
};

void SceneLoader::BuildElem(const Json::Value jElem, CElem* elem) {
    elem->SetWidth(jElem.get("width",0.0f).asDouble());
    elem->SetHeight(jElem.get("height",0.0f).asDouble());
    elem->SetX(jElem.get("x",0.0f).asDouble());
    elem->SetY(jElem.get("y",0.0f).asDouble());
    elem->SetY(CMath::ToCartesian(jElem.get("y",0.0f).asDouble(), m_sceneHeight));
    elem->SetScale(jElem.get("scale",1.0f).asDouble());
    elem->SetRotation(jElem.get("rotation",1.0f).asDouble()*M_PI);
};

CUnit* SceneLoader::BuildUnit(const Json::Value jUnit, WorldLayer* worldLayer) {
    CUnit* unit = new CUnit(worldLayer);
    BuildElem(jUnit, unit);
    unit->SetBody();
    return unit;
};

Entry* SceneLoader::BuildEntry(const Json::Value jEntry, WorldLayer* worldLayer) {
    Entry* entry = new Entry(worldLayer);
    BuildElem(jEntry, entry);
    entry->SetCapacity(jEntry.get("capacity",0).asInt());
    entry->SetOpen(jEntry.get("isOpen",false).asBool());
    entry->SetOpenTimer(jEntry.get("openTimer",1000).asInt());
    entry->SetInterval(jEntry.get("interval",100).asInt());
    entry->SetForceMinDistance(jEntry.get("forceMinDistance",0.0f).asDouble());
    entry->SetForceMaxDistance(jEntry.get("forceMaxDistance",0.0f).asDouble());
    entry->SetForceMaxAngle(jEntry.get("forceMaxAngle",0.0f).asDouble()*M_PI);
    entry->SetForceMinAngularImpulse(jEntry.get("forceMinAngularImpulse",0.0f).asDouble());
    entry->SetForceMaxAngularImpulse(jEntry.get("forceMaxAngularImpulse",0.0f).asDouble());
    return entry;
};

Exit* SceneLoader::BuildExit(const Json::Value jExit, WorldLayer* worldLayer) {
    Exit* exit = new Exit(worldLayer);
    BuildElem(jExit, exit);
    return exit;
};
