#include "SceneLoader.h"
#include "../Util/File.h"
#include "../Util/Log.h"
#include "../Util/CMath.h"
#include "../Util/PathUtil.h"
#include "../Engine/StillCatalog.h"

SceneLoader::SceneLoader() {
    m_sceneHeight = 0;
}

SceneLoader::~SceneLoader() {
}

Scene* SceneLoader::LoadScene(int act, int level) {
    std::string filePath = PathUtil::GetScene(act, level);
    std::string document = File::ReadText(filePath.c_str());
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(document.c_str(), root, false);
    if (! parsingSuccessful) {
        Log::L(reader.getFormatedErrorMessages());
        return NULL;
    }
    BuildScene(root);
    Log::L("Scene Built.");
    return m_scene;
}

Scene* SceneLoader::BuildScene(const Json::Value root) {
    m_scene = new Scene();
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
    bool isFirstWorldLayer = true;
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
        if (isFirstWorldLayer) {
            m_scene->SetWorldLayer(worldLayer);
            isFirstWorldLayer = false;
        } else if (jWorldLayer.get("isDefault",false).asBool()) {
            m_scene->SetWorldLayer(worldLayer);
        }
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
    Log::L(m_scene->GetVersion());
    return m_scene;
}

std::vector<Area*> SceneLoader::BuildAreas(const Json::Value jarrAreas, Layer* layer) {
    std::vector<Area*> areas;
    AreaNode* prevNode = NULL;
    AreaNode* firstNode = NULL;
    for(int index = 0; index < jarrAreas.size(); ++index ) {
        prevNode = NULL;
        firstNode = NULL;
        const Json::Value jArea = jarrAreas[index];
        Area* area = new Area(layer);
        area->SetMaterial(jArea.get("material",0).asInt());
        area->SetNature(jArea.get("nature",0).asInt());
        const Json::Value jarrPoints = jArea["points"];
        for(int jindex = 0; jindex < jarrPoints.size(); ++jindex) {
            const Json::Value jPoint = jarrPoints[jindex];
            AreaNode* areaNode = new AreaNode(jPoint.get("x",0.0f).asDouble(),CMath::ToCartesian(jPoint.get("y",0.0f).asDouble(), m_sceneHeight));
            areaNode->area = area;
            area->AddPoint(areaNode);
            if (!firstNode)
                firstNode = areaNode;
            if (prevNode) {
                prevNode->neighborB = areaNode;
                areaNode->neighborA = prevNode;
            }
            prevNode = areaNode;
        }
        area->SetClosed(jArea.get("closed",true).asBool());
        area->SetCenter(jArea.get("centerX", 0.0f).asDouble(), CMath::ToCartesian(jArea.get("centerY", 0.0f).asDouble(), m_sceneHeight));
        area->SetLayeredGraphic(BuildLayeredGraphic(jArea, area->GetCenter()));
        if (area->IsClosed() && prevNode) {
            prevNode->neighborB = firstNode;
            firstNode->neighborA = prevNode;
        }
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

void SceneLoader::BuildElem(const Json::Value jElem, Elem* elem) {
    elem->SetWidth(jElem.get("width",0.0f).asDouble());
    elem->SetHeight(jElem.get("height",0.0f).asDouble());
    elem->SetX(jElem.get("x",0.0f).asDouble());
    elem->SetY(jElem.get("y",0.0f).asDouble());
    elem->SetY(CMath::ToCartesian(jElem.get("y",0.0f).asDouble(), m_sceneHeight));
    elem->SetScale(jElem.get("scaleFactor",1.0f).asDouble());
    elem->SetRotation(jElem.get("rotation",1.0f).asDouble()*M_PI);
    Log::L("Stack index is %d", jElem.get("stackIndex", 0).asInt());
    elem->SetStackIndex(jElem.get("stackIndex", 0).asInt());
};

Unit* SceneLoader::BuildUnit(const Json::Value jUnit, WorldLayer* worldLayer) {
    Unit* unit = new Unit(worldLayer);
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

LayeredGraphic* SceneLoader::BuildLayeredGraphic(const Json::Value jLGraphic, Vector2* reference) {
    LayeredGraphic* layeredGraphic = new LayeredGraphic();
    layeredGraphic->SetReference(reference->x, reference->y);
    std::vector<Still*> vStills;
    const Json::Value jarrStills = jLGraphic["stills"];
    for(int jindex = 0; jindex < jarrStills.size(); ++jindex) {
        const Json::Value jStill = jarrStills[jindex];
        Still* still = StillCatalog::GetByName(jStill.get("name","").asString());
        if (still) {
            BuildElem(jStill, still);
            OffsetElem(still, reference);
            vStills.push_back(still);
        }
    }
    std::sort(vStills.begin(), vStills.end(), SceneLoader::SortIndex);
    for(auto &_still : vStills) {
        if (_still->GetStackIndex() < 0)
            layeredGraphic->AddBack(_still);
        else
            layeredGraphic->AddFront(_still);
    }
    return layeredGraphic;
};

void SceneLoader::OffsetElem(Elem* elem, Vector2* reference) {
    elem->SetX(elem->GetX() - reference->x);
    elem->SetY(elem->GetY() - reference->y);
};

bool SceneLoader::SortIndex(Elem* elemA, Elem* elemB) {
    return (elemA->GetStackIndex() < elemB->GetStackIndex());
};
