#include "StillCatalog.h"
#include "../Util/File.h"
#include "../Util/TextureUtil.h"
#include "../Util/Log.h"
#include "../Util/PathUtil.h"
#include "../Util/CMath.h"

std::unordered_map<std::string, StillDef> StillCatalog::m_stillDef;
std::unordered_map<std::string, Sprite*> StillCatalog::m_stillSprite;
std::string StillCatalog::m_filename = PathUtil::GetStillCatalog();
SDL_Renderer* StillCatalog::m_renderer;

void StillCatalog::Init(SDL_Renderer* renderer) {
    m_renderer = renderer;
    std::string document = File::ReadText(m_filename.c_str());
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(document.c_str(), root, false);
    if (! parsingSuccessful) {
        return;
    }
    BuildCatalog(root);
}

void StillCatalog::BuildCatalog(Json::Value root) {
    const Json::Value jarrCatalog = root["stillCatalog"];
    for(int catalogIndex = 0; catalogIndex < jarrCatalog.size(); catalogIndex++) {
        const Json::Value jStillDef = jarrCatalog[catalogIndex];
        StillDef stillDef;
        stillDef.name     = jStillDef.get("name","").asString();
        stillDef.tileIndex = jStillDef.get("tileIndex",0).asInt();
        stillDef.tilesX       = jStillDef.get("tilesX",0).asInt();
        stillDef.tilesY       = jStillDef.get("tilesY",0).asInt();
        stillDef.width    = jStillDef.get("width",0).asDouble();
        stillDef.height   = jStillDef.get("height",0).asDouble();
        stillDef.fileCategory = jStillDef.get("fileCategory", 0).asString();
        stillDef.filePath     = jStillDef.get("filePath", 0).asString();
        stillDef.file         = PathUtil::GetCategoryFile(stillDef.fileCategory, stillDef.filePath, CMath::GetMToPxRatio());
        m_stillDef[stillDef.name] = stillDef;
    }
}

void StillCatalog::Flush() {
}

Still* StillCatalog::GetByName(std::string name) {
    if (m_renderer) {
        if (m_stillDef.count(name) == 0)
            return NULL;
        StillDef stillDef = m_stillDef[name];
        Still* still = new Still();
        Sprite* sprite;
        if (m_stillSprite.count(name) == 0) {
            int tileWidthPx   = PathUtil::GetTopMToPxRatio() * stillDef.width;
            int tileHeightPx = PathUtil::GetTopMToPxRatio() * stillDef.height;
            sprite = new Sprite(stillDef.tilesX, stillDef.tilesY, tileWidthPx, tileHeightPx);
            sprite->SetFilename(stillDef.file);
            m_stillSprite[name] = sprite;
        } else
            sprite = m_stillSprite[name];
        still->SetSprite(sprite);
        still->SetTexture(TextureUtil::LoadTexture(stillDef.file, m_renderer));
        return still;
    } else
        return NULL;
}
