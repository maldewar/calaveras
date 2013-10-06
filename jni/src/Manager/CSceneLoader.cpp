#include "CSceneLoader.h"
#include "../Util/CFile.h"
#include "../Util/CLog.h"
#include "../Util/CMath.h"

CSceneLoader::CSceneLoader(int act, int level) {
    m_act = act;
    m_level = level;
    m_sceneHeight = 0;
}

CSceneLoader::~CSceneLoader() {
}

CScene* CSceneLoader::LoadScene() {
    CLog::Log("Trying to load scene");
    std::string filePath = GetScenePath(m_act, m_level);
    std::string document = CFile::ReadText(filePath.c_str());
    Json::Value root;
    Json::Reader reader;
    CLog::Log("About to parse scene json.");
    bool parsingSuccessful = reader.parse(document.c_str(), root, false);
    if (! parsingSuccessful) {
        CLog::Log(reader.getFormatedErrorMessages());
        return NULL;
    }
    BuildScene(root);
    CLog::Log("Scene Built.");
    return m_scene;
}

std::string CSceneLoader::GetScenePath(int act, int level) {
    return "scene/1/1/scene.json";
}

CScene* CSceneLoader::BuildScene(const Json::Value root) {
    m_scene = new CScene();
    m_scene->SetVersion(root.get("version", "0.0").asString());
    m_scene->SetWidth(root.get("width", 3.0f).asDouble());
    m_scene->SetHeight(root.get("height", 3.0f).asDouble());
    m_sceneHeight = m_scene->GetHeight();
    const Json::Value jarrWorldLayers = root["worldLayers"];
    for(int worldLayerIndex = 0; worldLayerIndex < jarrWorldLayers.size(); worldLayerIndex++) {
        const Json::Value jWorldLayer = jarrWorldLayers[worldLayerIndex];
        CWorldLayer* worldLayer = new CWorldLayer();
        worldLayer->SetId(jWorldLayer.get("id","").asString());
        worldLayer->SetDistance(jWorldLayer.get("distance",0.0f).asDouble());
        const Json::Value jarrAreas = jWorldLayer["areas"];
        worldLayer->SetAreas(BuildAreas(jarrAreas, worldLayer));
        const Json::Value jarrAssets = jWorldLayer["assets"];
        BuildAssets(jarrAssets, worldLayer);
        m_scene->AddWorldLayer(worldLayer);
    }
    CLog::Log(m_scene->GetVersion());
    return m_scene;
}

std::vector<CArea*> CSceneLoader::BuildAreas(const Json::Value jarrAreas, CLayer* layer) {
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
        CLog::Log("total de puntos: %d", area->GetTotalPoints());
    }
    return areas;
}

void CSceneLoader::BuildAssets(Json::Value jarrAssets, CWorldLayer* worldLayer) {
    for(int index = 0; index < jarrAssets.size(); ++index) {
        const Json::Value jAsset = jarrAssets[index];
        std::string assetType = jAsset.get("type","").asString();
        if (assetType.compare("unit") == 0)
            worldLayer->AddUnit(BuildUnit(jAsset, worldLayer));
        else if (assetType.compare("entry") == 0)
            worldLayer->AddEntry(BuildEntry(jAsset, worldLayer));
    }
}

CUnit* CSceneLoader::BuildUnit(const Json::Value jUnit, CWorldLayer* worldLayer) {
    CUnit* unit = new CUnit(worldLayer);
    unit->SetWidth(jUnit.get("width",0.0f).asDouble());
    unit->SetHeight(jUnit.get("height",0.0f).asDouble());
    unit->SetX(jUnit.get("x",0.0f).asDouble());
    unit->SetY(CMath::ToCartesian(jUnit.get("y",0.0f).asDouble(), m_sceneHeight));
    unit->SetScale(jUnit.get("scale",1.0f).asDouble());
    unit->SetRotation(jUnit.get("rotation",1.0f).asDouble()*M_PI);
    unit->SetBody();
    return unit;
}

CEntry* CSceneLoader::BuildEntry(const Json::Value jEntry, CWorldLayer* worldLayer) {
    CEntry* entry = new CEntry(worldLayer);
    entry->SetWidth(jEntry.get("width",0.0f).asDouble());
    entry->SetHeight(jEntry.get("height",0.0f).asDouble());
    entry->SetX(jEntry.get("x",0.0f).asDouble());
    entry->SetY(CMath::ToCartesian(jEntry.get("y",0.0f).asDouble(), m_sceneHeight));
    entry->SetScale(jEntry.get("scale",1.0f).asDouble());
    entry->SetRotation(jEntry.get("rotation",1.0f).asDouble()*M_PI);
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
}
