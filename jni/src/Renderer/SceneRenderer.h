#ifndef _SCENERENDERER_H_
    #define _SCENERENDERER_H_
#include <SDL.h>
#include <Box2D.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "../Model/CScene.h"
#include "../Model/WorldLayer.h"
#include "../Model/BgLayer.h"
#include "../Model/CArea.h"
#include "../Engine/Camera.h"
#include "../Engine/CAnimation.h"
#include "CompositeRenderer.h"
#include "ChoiceGraphRenderer.h"

class SceneRenderer {
    private:
        void RenderWorldLayer(WorldLayer* worldLayer, SDL_Renderer* renderer);
        void RenderBgLayer(BgLayer* bgLayer, SDL_Renderer* renderer);
        //static void RenderFgLayer(const CFgLayer* fgLayer, SDL_Renderer* renderer);
        void RenderArea(CArea* area, SDL_Renderer* renderer);
        void RenderUnit(CUnit* unit, SDL_Renderer* renderer);
        void RenderEntry(Entry* entry, SDL_Renderer* renderer);
        void RenderExit(Exit* exit, SDL_Renderer* renderer);
        void RenderAnimation(float centerX, float centerY, float rotationRad, CAnimation* animation, SDL_Renderer* renderer);
        void RenderShape(b2Shape* shape, b2Body* body, SDL_Renderer* renderer, bool closed);

    private:
        CScene* m_scene;
        SDL_Renderer* m_renderer;
        float m_scene_height;
        std::unordered_map<std::string, CompositeRenderer*> m_bgRenderers;
        std::vector<ChoiceGraphRenderer*> m_choiceGraphRenderers;

    public:
        SceneRenderer();
        ~SceneRenderer();
        void Activate(CScene* scene, SDL_Renderer* renderer);
        void Deactivate();
        void Render(Camera* camera);
};
#endif
