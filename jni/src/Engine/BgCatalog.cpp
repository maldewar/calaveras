#include "BgCatalog.h"
#include "../Util/File.h"
#include "../Util/Log.h"
#include "../Util/PathUtil.h"

std::unordered_map<int, BgDef> BgCatalog::m_bgDef;
std::string BgCatalog::m_filename = PathUtil::GetBgCatalog();
SDL_Renderer* BgCatalog::m_renderer;

void BgCatalog::Init(SDL_Renderer* renderer) {
    m_renderer = renderer;
    std::string document = File::ReadText(m_filename.c_str());
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(document.c_str(), root, false);
    if (! parsingSuccessful) {
        Log::L(reader.getFormatedErrorMessages());
        return;
    }
    BuildCatalog(root);
}

void BgCatalog::BuildCatalog(Json::Value root) {
    const Json::Value jarrCatalog = root["bgCatalog"];
    for(int catalogIndex = 0; catalogIndex < jarrCatalog.size(); catalogIndex++) {
        const Json::Value jBgDef = jarrCatalog[catalogIndex];
        BgDef bgDef;
        bgDef.r               = jBgDef.get("r", 0).asInt();
        bgDef.g               = jBgDef.get("g", 0).asInt();
        bgDef.b               = jBgDef.get("b", 0).asInt();
        bgDef.a               = jBgDef.get("a", 0).asInt();
        bgDef.baseType        = jBgDef.get("baseType", 0).asInt();
        bgDef.angle           = jBgDef.get("angle", 0.0f).asInt();
        bgDef.x               = jBgDef.get("x", 0.5f).asDouble();
        bgDef.y               = jBgDef.get("y", 0.5f).asDouble();
        bgDef.gradientType    = jBgDef.get("gradientType", 0).asInt();
        bgDef.textureFile     = jBgDef.get("textureFile", "").asString();
        bgDef.textureWidth    = jBgDef.get("textureWidth", 0.0f).asDouble();
        bgDef.textureHeight   = jBgDef.get("textureHeight", 0.0f).asDouble();
        bgDef.textureRepeatX  = jBgDef.get("textureRepeatX", false).asBool();
        bgDef.textureRepeatY  = jBgDef.get("textureRepeatY", false).asBool();;
        bgDef.textureAlpha    = jBgDef.get("textureAlpha", 0.0f).asDouble();
        bgDef.textureBlending = jBgDef.get("textureBlending", 0).asInt();
        const Json::Value jarrReds    = jBgDef["reds"];
        const Json::Value jarrGreens    = jBgDef["greens"];
        const Json::Value jarrBlues    = jBgDef["blues"];
        const Json::Value jarrAlphas    = jBgDef["alphas"];
        const Json::Value jarrPositions = jBgDef["positions"];
        for (int colorIndex = 0; colorIndex < jarrReds.size(); colorIndex++) {
            const Json::Value jColor = jarrReds[colorIndex];
            bgDef.reds.push_back(jColor.asInt());
        }
        for (int colorIndex = 0; colorIndex < jarrGreens.size(); colorIndex++) {
            const Json::Value jColor = jarrGreens[colorIndex];
            bgDef.greens.push_back(jColor.asInt());
        }
        for (int colorIndex = 0; colorIndex < jarrBlues.size(); colorIndex++) {
            const Json::Value jColor = jarrBlues[colorIndex];
            bgDef.blues.push_back(jColor.asInt());
        }
        for (int colorIndex = 0; colorIndex < jarrAlphas.size(); colorIndex++) {
            const Json::Value jColor = jarrAlphas[colorIndex];
            bgDef.alphas.push_back(jColor.asInt());
        }
        for (int positionIndex = 0; positionIndex < jarrPositions.size(); positionIndex++) {
            const Json::Value jPosition = jarrPositions[positionIndex];
            bgDef.positions.push_back(jPosition.asDouble());
        }

        m_bgDef[jBgDef.get("id", 0).asInt()] = bgDef;
        Log::L("Adding bg with id=%d to the catalog.", jBgDef.get("id", 0).asInt());
    }
}

void BgCatalog::Flush() {
    //TODO:
};

void BgCatalog::FillRenderer(int id, CompositeRenderer* compositeRenderer) {
    if (m_bgDef.find(id) == m_bgDef.end()) {
        return;
    }
    BgDef bgDef = m_bgDef.find(id)->second;
    compositeRenderer->SetRed(bgDef.r);
    compositeRenderer->SetGreen(bgDef.g);
    compositeRenderer->SetBlue(bgDef.b);
    compositeRenderer->SetAlpha(bgDef.a);
    compositeRenderer->SetBaseType(bgDef.baseType);
    compositeRenderer->SetTextureFile(bgDef.textureFile);
    compositeRenderer->SetTextureWidth(bgDef.textureWidth);
    compositeRenderer->SetTextureHeight(bgDef.textureHeight);
    compositeRenderer->SetTextureRepeatX(bgDef.textureRepeatX);
    compositeRenderer->SetTextureRepeatY(bgDef.textureRepeatY);
    compositeRenderer->SetTextureAlpha(bgDef.textureAlpha);
    compositeRenderer->SetTextureBlending(bgDef.textureBlending);
    if (compositeRenderer->GetGradient())
    {
        compositeRenderer->GetGradient()->SetType(bgDef.gradientType);
        compositeRenderer->GetGradient()->SetAngle(bgDef.angle);
        compositeRenderer->GetGradient()->SetX(bgDef.x);
        compositeRenderer->GetGradient()->SetY(bgDef.y);
        compositeRenderer->GetGradient()->AddSteps(bgDef.reds, bgDef.greens, bgDef.blues, bgDef.alphas, bgDef.positions);
    }
};
