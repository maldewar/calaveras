#include "AreaCatalog.h"
#include "../Util/CFile.h"
#include "../Util/PathUtil.h"
//#include "../Util/TextureUtil.h"
//#include "../Util/CLog.h"

std::unordered_map<int, AreaDef> AreaCatalog::m_areaDef;
std::string AreaCatalog::m_filename = PathUtil::GetAreaCatalog();
SDL_Renderer* AreaCatalog::m_renderer;

void AreaCatalog::Init(SDL_Renderer* renderer) {
    m_renderer = renderer;
    std::string document = CFile::ReadText(m_filename.c_str());
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(document.c_str(), root, false);
    if (! parsingSuccessful) {
        return;
    }
    BuildCatalog(root);
}

void AreaCatalog::BuildCatalog(Json::Value root) {
    const Json::Value jarrCatalog = root["catalog"];
    for(int catalogIndex = 0; catalogIndex < jarrCatalog.size(); catalogIndex++) {
        const Json::Value jAreaDef = jarrCatalog[catalogIndex];
        AreaDef areaDef;
        areaDef.name             = jAreaDef.get("name","Default").asString();
        areaDef.nature           = jAreaDef.get("nature",0).asInt();
        areaDef.restitution      = jAreaDef.get("restitution",0).asDouble();
        areaDef.friction         = jAreaDef.get("friction",0).asDouble();
        areaDef.density          = jAreaDef.get("density",0).asDouble();
        areaDef.angularDamping   = jAreaDef.get("angularDamping",0).asDouble();
        areaDef.linearDamping    = jAreaDef.get("linearDamping",0).asDouble();
        areaDef.linearTolerance  = jAreaDef.get("linearTolerance",0).asDouble();
        areaDef.angularTolerance = jAreaDef.get("angularTolerance",0).asDouble();
        m_areaDef[areaDef.nature] = areaDef;
    }
}

void AreaCatalog::Flush() {
}

void AreaCatalog::Set(CArea* area) {
    if (m_areaDef.count(area->GetNature()) == 0)
        return;
    AreaDef areaDef = m_areaDef[area->GetNature()];
    area->SetAngularDamping(areaDef.angularDamping);
    area->SetLinearDamping(areaDef.linearDamping);
}
