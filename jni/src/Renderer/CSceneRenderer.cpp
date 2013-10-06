#include "CSceneRenderer.h"
#include "../Util/CMath.h"
#include "../Util/CLog.h"


float CSceneRenderer::m_scene_height = 0.0f;

CSceneRenderer::CSceneRenderer(){
};

void CSceneRenderer::Render(CScene* scene, SDL_Renderer* renderer) {
    m_scene_height = scene->GetHeight();
    for (auto &worldLayer : scene->GetWorldLayers()) {
        RenderWorldLayer(worldLayer, renderer);
    }
};

void CSceneRenderer::RenderWorldLayer(CWorldLayer* worldLayer, SDL_Renderer* renderer) {
    for (auto &area : worldLayer->GetAreas()) {
        RenderArea(area, renderer);
    }
    for (auto &unit : worldLayer->GetUnits()) {
        RenderUnit(unit, renderer);
    }
    for (auto &entry : worldLayer->GetEntries()) {
        RenderEntry(entry, renderer);
    }
};
/*
void CSceneRenderer::RenderArea(CArea* area, SDL_Renderer* renderer) {
    float lastX = -1;
    float lastY = -1;
    float startX = -1;
    float startY = -1;
    if(area->GetTotalPoints() > 0) {
        for(auto &point : area->GetPoints()) {
            if (lastX >= 0) { 
               SDL_RenderDrawLine(renderer,
                CMath::MToPxInt(lastX),
                CMath::MToPxInt(lastY),
                CMath::MToPxInt(point.x),
                CMath::MToPxInt(point.y));
            } else {
                startX = point.x;
                startY = point.y;
            }       
            lastX = point.x;
            lastY = point.y;
        }       
        if (area->IsClosed()) {
            SDL_RenderDrawLine(renderer,
            CMath::MToPxInt(lastX),
            CMath::MToPxInt(lastY),
            CMath::MToPxInt(startX),
            CMath::MToPxInt(startY));
        }       
    }
};
*/
void CSceneRenderer::RenderArea(CArea* area, SDL_Renderer* renderer) {
    if (area->GetBody()) {
        for (b2Fixture* f = area->GetBody()->GetFixtureList(); f; f = f->GetNext()) {
            RenderShape(f->GetShape(), area->GetBody(),renderer, area->IsClosed());
        }
    }
}

void CSceneRenderer::RenderUnit(CUnit* unit, SDL_Renderer* renderer) {
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
}

void CSceneRenderer::RenderEntry(CEntry* entry, SDL_Renderer* renderer) {
    RenderAnimation(entry->GetX(),
        CMath::ToCanvas(entry->GetY(), m_scene_height),
        entry->GetRotation(),
        entry->GetAnimation(),
        renderer);
}

void CSceneRenderer::RenderAnimation(float centerX, float centerY, float rotationRad, CAnimation* animation, SDL_Renderer* renderer) {
    if (animation->GetTexture()) {
        SDL_RenderCopyEx(renderer,
            animation->GetTexture(),
            animation->GetSrcRect(),
            animation->GetDstRect(CMath::MToPxInt(centerX), CMath::MToPxInt(centerY)),
            CMath::ToDeg(rotationRad) * -1,
            NULL,
            SDL_FLIP_NONE);
    }
}

void CSceneRenderer::RenderShape(b2Shape* shape, b2Body* body, SDL_Renderer* renderer, bool closed) {
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
}
