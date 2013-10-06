#ifndef _CSCENERENDERER_H_
    #define _CSCENERENDERER_H_
#include <SDL.h>
#include <Box2D.h>
#include <string>
#include "../Model/CScene.h"
#include "../Model/CWorldLayer.h"
#include "../Model/CArea.h"
#include "../Engine/CAnimation.h"

class CSceneRenderer {
    private:
        CSceneRenderer();
        static void RenderWorldLayer(CWorldLayer* worldLayer, SDL_Renderer* renderer);
        //static void RenderBgLayer(const CBgLayer* bgLayer, SDL_Renderer* renderer);
        //static void RenderFgLayer(const CFgLayer* fgLayer, SDL_Renderer* renderer);
        static void RenderArea(CArea* area, SDL_Renderer* renderer);
        static void RenderUnit(CUnit* unit, SDL_Renderer* renderer);
        static void RenderEntry(CEntry* entry, SDL_Renderer* renderer);
        static void RenderAnimation(float centerX, float centerY, float rotationRad, CAnimation* animation, SDL_Renderer* renderer);
        static void RenderShape(b2Shape* shape, b2Body* body, SDL_Renderer* renderer, bool closed);

    private:
        static float m_scene_height;

    public:
        static void Render(CScene* scene, SDL_Renderer* renderer);
};
#endif
