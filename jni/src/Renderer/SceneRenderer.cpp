#include "SceneRenderer.h"
#include "../Engine/BgCatalog.h"
#include "../Util/CMath.h"
#include "../Util/CLog.h"
#include "../AppStateManager.h"


SceneRenderer::SceneRenderer(){
    m_scene = NULL;
    m_renderer = NULL;
    m_scene_height = 0.0f;
};

void SceneRenderer::Activate(CScene* scene, SDL_Renderer* renderer) {
    m_scene = scene;
    m_renderer = renderer;
    m_scene_height = m_scene->GetHeight();
    for (auto &bgLayer : m_scene->GetBgLayers()) {
        CompositeRenderer* bgRenderer =
            new CompositeRenderer(AppStateManager::GetWindowWidth(), AppStateManager::GetWindowHeight());
        BgCatalog::FillRenderer(bgLayer->GetBg(), bgRenderer);
        bgRenderer->Activate(m_renderer);
        m_bgRenderers[bgLayer->GetId()] = bgRenderer;
    }
    for (auto &worldLayer : m_scene->GetWorldLayers()) {
        ChoiceGraphRenderer* choiceGraphRenderer = new ChoiceGraphRenderer();
        choiceGraphRenderer->Activate(worldLayer->GetChoiceGraph(), m_renderer, m_scene->GetHeight());
        m_choiceGraphRenderers.push_back(choiceGraphRenderer);
    }
}

void SceneRenderer::Deactivate() {
    for (auto &bgRenderer : m_bgRenderers)
        bgRenderer.second->Deactivate();
    for (auto &choiceGraphRenderer : m_choiceGraphRenderers) {
        choiceGraphRenderer->Deactivate();
        delete choiceGraphRenderer;//TODO: clear CGraph objects.
    }
    m_choiceGraphRenderers.clear();
    m_bgRenderers.clear();
}

void SceneRenderer::Render(Camera* camera) {
    /*
    for (auto &bgLayer : m_scene->GetBgLayers()) {
        RenderBgLayer(bgLayer, m_renderer);
    }
    for (auto &worldLayer : m_scene->GetWorldLayers()) {
        SDL_RenderSetScale(m_renderer, zoom, zoom);
        SDL_RenderSetViewport(m_renderer, &viewport);
        //CLog::Log("Viewport x:%d y:%d w:%d h:%d", viewport.x, viewport.y, viewport.w, viewport.h);
        //SDL_RenderSetScale(m_renderer, zoom, zoom);
        RenderWorldLayer(worldLayer, m_renderer);
        //SDL_RenderSetScale(m_renderer, 1.0f, 1.0f);
        SDL_RenderSetViewport(m_renderer, NULL);
        SDL_RenderSetScale(m_renderer, 1, 1);
    }
    */
    for (auto &bgLayer : m_scene->GetBgLayers()) {
        RenderBgLayer(bgLayer, m_renderer);
    }
    for (auto &worldLayer : m_scene->GetWorldLayers()) {
        SDL_RenderSetScale(m_renderer, camera->GetZoom(), camera->GetZoom());
        SDL_RenderSetViewport(m_renderer, camera->GetViewport());
        RenderWorldLayer(worldLayer, m_renderer);
        SDL_RenderSetScale(m_renderer, 1, 1);
        SDL_RenderSetViewport(m_renderer, NULL);
    }
    for (auto &choiceGraphRenderer : m_choiceGraphRenderers) {
        choiceGraphRenderer->Render(camera);
    }
};

void SceneRenderer::RenderWorldLayer(WorldLayer* worldLayer, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (auto &area : worldLayer->GetAreas()) {
        RenderArea(area, renderer);
    }
    for (auto &unit : worldLayer->GetUnits()) {
        RenderUnit(unit, renderer);
    }
    for (auto &entry : worldLayer->GetEntries()) {
        RenderEntry(entry, renderer);
    }
    for (auto &exit : worldLayer->GetExits()) {
        RenderExit(exit, renderer);
    }
};

void SceneRenderer::RenderBgLayer(BgLayer* bgLayer, SDL_Renderer* renderer) {
    m_bgRenderers[bgLayer->GetId()]->Render();
};

void SceneRenderer::RenderArea(CArea* area, SDL_Renderer* renderer) {
    if (area->GetBody()) {
        for (b2Fixture* f = area->GetBody()->GetFixtureList(); f; f = f->GetNext()) {
            RenderShape(f->GetShape(), area->GetBody(),renderer, area->IsClosed());
        }
    }
}

void SceneRenderer::RenderUnit(CUnit* unit, SDL_Renderer* renderer) {
    if (unit->GetBody()) {
        RenderAnimation(unit->GetBody()->GetPosition().x,
            CMath::ToCanvas(unit->GetBody()->GetPosition().y, m_scene_height),
            unit->GetBody()->GetAngle(),
            unit->GetAnimation(), 
            renderer);
        /*for (b2Fixture* f = unit->GetBody()->GetFixtureList(); f; f = f->GetNext()) {
            RenderShape(f->GetShape(), unit->GetBody(),renderer, false);
        }*/
    }
};

void SceneRenderer::RenderEntry(Entry* entry, SDL_Renderer* renderer) {
    //CLog::Log("Entry y:%f", CMath::ToCanvas(entry->GetY(), m_scene_height));
    RenderAnimation(entry->GetX(),
        CMath::ToCanvas(entry->GetY(), m_scene_height),
        entry->GetRotation(),
        entry->GetAnimation(),
        renderer);
};

void SceneRenderer::RenderExit(Exit* exit, SDL_Renderer* renderer) {
    //CLog::Log("Exit y:%f", CMath::ToCanvas(exit->GetY(), m_scene_height));
    //CLog::Log("Exit y:%f", exit->GetY());
    RenderAnimation(exit->GetX(),
        CMath::ToCanvas(exit->GetY(), m_scene_height),
        exit->GetRotation(),
        exit->GetAnimation(),
        renderer);
};

void SceneRenderer::RenderAnimation(float centerX, float centerY, float rotationRad, CAnimation* animation, SDL_Renderer* renderer) {
    if (animation->GetTexture()) {
        SDL_Rect* dest = animation->GetDstRect(CMath::MToPxInt(centerX), CMath::MToPxInt(centerY));
        SDL_RenderCopyEx(renderer,
            animation->GetTexture(),
            animation->GetSrcRect(),
            dest,
            CMath::ToDeg(rotationRad) * -1,
            NULL,
            SDL_FLIP_NONE);
        //SDL_Rect* viewport = animation->GetDstRect(CMath::MToPxInt(centerX), CMath::MToPxInt(centerY));
        //CLog::Log("Viewport x:%d y:%d w:%d h:%d", viewport->x, viewport->y, viewport->w, viewport->h);
    }
};

void SceneRenderer::RenderShape(b2Shape* shape, b2Body* body, SDL_Renderer* renderer, bool closed) {
    float lastX, lastY, startX, startY;
    if (shape->GetType() ==  b2Shape::e_chain) {
            b2ChainShape* chain = (b2ChainShape*)shape;
            lastX = -1;
            lastY = -1;
            startX = -1;
            startY = -1;
            for (int32 i = 0; i < chain->m_count; ++i)
            {
                if (lastX >= 0) { 
                   SDL_RenderDrawLine(renderer,
                        CMath::MToPxInt(lastX),
                        CMath::MToPxInt(CMath::ToCanvas(lastY, m_scene_height)),
                        CMath::MToPxInt(chain->m_vertices[i].x + body->GetPosition().x),
                        CMath::MToPxInt(CMath::ToCanvas(chain->m_vertices[i].y + body->GetPosition().y, m_scene_height)));
                } else {
                    startX = chain->m_vertices[i].x + body->GetPosition().x;
                    startY = chain->m_vertices[i].y + body->GetPosition().y;
                }
                lastX = chain->m_vertices[i].x + body->GetPosition().x;
                lastY = chain->m_vertices[i].y + body->GetPosition().y;
            }
            if (closed) {
                SDL_RenderDrawLine(renderer,
                CMath::MToPxInt(lastX),
                CMath::MToPxInt(CMath::ToCanvas(lastY, m_scene_height)),
                CMath::MToPxInt(startX),
                CMath::MToPxInt(CMath::ToCanvas(startY, m_scene_height)));
            }
    } else if (shape->GetType() == b2Shape::e_polygon) {
            b2PolygonShape* polygon = (b2PolygonShape*)shape;
            lastX = -1;
            lastY = -1;
            startX = -1;
            startY = -1;
            for (int32 i = 0; i < polygon->GetVertexCount(); ++i)
            {
                if (lastX >= 0) { 
                   SDL_RenderDrawLine(renderer,
                        CMath::MToPxInt(lastX),
                        CMath::MToPxInt(CMath::ToCanvas(lastY, m_scene_height)),
                        CMath::MToPxInt(polygon->m_vertices[i].x + body->GetPosition().x),
                        CMath::MToPxInt(CMath::ToCanvas(polygon->m_vertices[i].y + body->GetPosition().y, m_scene_height)));
                } else {
                    startX = polygon->m_vertices[i].x + body->GetPosition().x;
                    startY = polygon->m_vertices[i].y + body->GetPosition().y;
                }
                lastX = polygon->m_vertices[i].x + body->GetPosition().x;
                lastY = polygon->m_vertices[i].y + body->GetPosition().y;
            }
            SDL_RenderDrawLine(renderer,
            CMath::MToPxInt(lastX),
            CMath::MToPxInt(CMath::ToCanvas(lastY, m_scene_height)),
            CMath::MToPxInt(startX),
            CMath::MToPxInt(CMath::ToCanvas(startY, m_scene_height)));
    }
};
