#include "ChoiceGraphRenderer.h"
#include "../Util/CMath.h"
#include "../Util/CLog.h"


ChoiceGraphRenderer::ChoiceGraphRenderer(){
    m_choiceGraph = NULL;
    m_renderer = NULL;
    m_scene_height = 0.0f;
    m_pointRect = new SDL_Rect();
    m_pointRect->w = 3;
    m_pointRect->h = 3;
};

ChoiceGraphRenderer::~ChoiceGraphRenderer() {
    delete m_choiceGraph;
};

void ChoiceGraphRenderer::Activate(ChoiceGraph* choiceGraph, SDL_Renderer* renderer, float sceneHeight) {
    m_choiceGraph = choiceGraph;
    m_renderer = renderer;
    m_scene_height = sceneHeight;
    m_graph = choiceGraph->GetGraph();
}

void ChoiceGraphRenderer::Deactivate() {
}

void ChoiceGraphRenderer::Render(Camera* camera) {
    SDL_RenderSetScale(m_renderer, camera->GetZoom(), camera->GetZoom());
    SDL_RenderSetViewport(m_renderer, camera->GetViewport());
    Render();
    SDL_RenderSetScale(m_renderer, 1, 1);
    SDL_RenderSetViewport(m_renderer, NULL);
};

void ChoiceGraphRenderer::Render() {
    CIndexMap index = boost::get(boost::vertex_index, *m_graph);
    vertex_t v, _v;
    std::pair<CVertexIter, CVertexIter> vp;
    CGraph::adjacency_iterator neighbourIt, neighbourEnd;
    for (vp = boost::vertices(*m_graph); vp.first != vp.second; ++vp.first) {
        v = index[*vp.first];
        m_pointRect->x = CMath::MToPxInt((*m_graph)[v].x);
        m_pointRect->y = CMath::MToPxInt(CMath::ToCanvas((*m_graph)[v].y, m_scene_height));
        SDL_RenderFillRect(m_renderer, m_pointRect);
        boost::tie(neighbourIt, neighbourEnd) = boost::adjacent_vertices(v, *m_graph);
        for (; neighbourIt != neighbourEnd; ++neighbourIt){
            //VertexID vertexID = *vertexIt; // dereference vertexIt, get the ID
            //Vertex & vertex = graph[vertexID];
            _v = index[*neighbourIt];
            SDL_RenderDrawLine(m_renderer,
                CMath::MToPxInt((*m_graph)[v].x),
                CMath::MToPxInt(CMath::ToCanvas((*m_graph)[v].y, m_scene_height)),
                CMath::MToPxInt((*m_graph)[_v].x),
                CMath::MToPxInt(CMath::ToCanvas((*m_graph)[_v].y, m_scene_height)));
        }
    }
/*
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
*/
};
