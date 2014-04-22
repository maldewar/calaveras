#include "AnimationCatalog.h"
#include "../Util/File.h"
#include "../Util/TextureUtil.h"
#include "../Util/Log.h"
#include "../Util/PathUtil.h"
#include "../Util/CMath.h"

std::unordered_map<int, AnimationDef> AnimationCatalog::m_animDef;
std::unordered_map<int, Sprite*> AnimationCatalog::m_animSprite;
std::string AnimationCatalog::m_filename = PathUtil::GetAnimationCatalog();
SDL_Renderer* AnimationCatalog::m_renderer;

void AnimationCatalog::Init(SDL_Renderer* renderer) {
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

void AnimationCatalog::BuildCatalog(Json::Value root) {
    const Json::Value jarrCatalog = root["animCatalog"];
    for(int catalogIndex = 0; catalogIndex < jarrCatalog.size(); catalogIndex++) {
        const Json::Value jAnimDef = jarrCatalog[catalogIndex];
        AnimationDef animDef;
        animDef.elemType     = jAnimDef.get("elemType",0).asInt();
        animDef.elemState    = jAnimDef.get("elemState",0).asInt();
        animDef.elemSubstate = jAnimDef.get("elemSubstate",0).asInt();
        animDef.animType     = jAnimDef.get("animType",0).asInt();
        animDef.isBackwards  = jAnimDef.get("isBackwards",false).asBool();
        animDef.currentFrame = jAnimDef.get("currentFrame",0).asInt();
        animDef.maxFrames    = jAnimDef.get("maxFrames",1).asInt();
        animDef.framerate    = jAnimDef.get("framerate",0).asInt();
        animDef.tilesX       = jAnimDef.get("tilesX",1).asInt();
        animDef.tilesY       = jAnimDef.get("tilesY",1).asInt();
        animDef.tileWidth    = jAnimDef.get("tileWidth",1).asDouble();
        animDef.tileHeight   = jAnimDef.get("tileHeight",1).asDouble();
        animDef.offsetX      = jAnimDef.get("offsetX",0).asInt();
        animDef.offsetY      = jAnimDef.get("offsetY",0).asInt();
        animDef.fileCategory = jAnimDef.get("fileCategory", 0).asString();
        animDef.filePath     = jAnimDef.get("filePath", 0).asString();
        animDef.file         = PathUtil::GetCategoryFile(animDef.fileCategory, animDef.filePath, CMath::GetMToPxRatio());
        
        m_animDef[animDef.elemType * 10000 + animDef.elemState * 100 + animDef.elemSubstate] = animDef;
    }
}

void AnimationCatalog::Flush() {
}

Animation* AnimationCatalog::GetAnimation(int type, int state, int substate) {
    if (m_renderer) {
        int index = type * 10000 + state * 100 + substate;
        if (m_animDef.count(index) == 0)
            return NULL;
        AnimationDef animDef = m_animDef[index];
        Animation* animation = new Animation();
        animation->SetFramerate(animDef.framerate);
        animation->SetMaxFrames(animDef.maxFrames);
        Sprite* sprite;
        if (m_animSprite.count(index) == 0) {
            int tileWidthPx   = PathUtil::GetTopMToPxRatio() * animDef.tileWidth;
            int tileHeightPx = PathUtil::GetTopMToPxRatio() * animDef.tileHeight;
            Log::L("Sprite mToPxRatio:%d", PathUtil::GetTopMToPxRatio());
            sprite = new Sprite(animDef.tilesX, animDef.tilesY, tileWidthPx, tileHeightPx);
            sprite->SetFilename(animDef.file);
            m_animSprite[index] = sprite;
        } else
            sprite = m_animSprite[index];
        animation->SetSprite(sprite);
        animation->SetTexture(TextureUtil::LoadTexture(animDef.file, m_renderer));
        animation->SetCurrentFrame(animDef.currentFrame);
        return animation;
    } else
        return NULL;
}

Animation* AnimationCatalog::GetByType(int type) {
    return GetAnimation(type, 0, 0);
}

Animation* AnimationCatalog::GetByState(int type, int state) {
    return GetAnimation(type, state, 0);
}

Animation* AnimationCatalog::GetBySubstate(int type, int state, int substate) {
    return GetAnimation(type, state, substate);
}
