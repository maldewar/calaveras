#include "ChoiceGraphRenderer.h"
#include "../Util/CMath.h"
#include "../Util/RendererUtil.h"
#include "../Model/AreaNode.h"
#include "../Util/Log.h"


ChoiceGraphRenderer::ChoiceGraphRenderer(){
    m_choiceGraph = NULL;
    m_renderer = NULL;
    m_scene_height = 0.0f;
    m_pointRect = new SDL_Rect();
    m_pointRect->w = 5;
    m_pointRect->h = 5;
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
    GraphNode* node;
    GraphNode* neighbourNode;
    std::pair<CVertexIter, CVertexIter> vp;
    CGraph::adjacency_iterator neighbourIt, neighbourEnd;
    RendererUtil::RememberColor(m_renderer);
    for (vp = boost::vertices(*m_graph); vp.first != vp.second; ++vp.first) {
        v = index[*vp.first];
        node = &(*m_graph)[v];
        m_pointRect->x = CMath::MToPxInt(node->x) - m_pointRect->w/2;
        m_pointRect->y = CMath::MToPxInt(CMath::ToCanvas(node->y, m_scene_height)) - m_pointRect->h/2;
        if (node->terminal) {
            RendererUtil::SetColor(m_renderer, RendererUtil::Color::ORANGE, 192);
            if (node->action == ACTION_DESCEND)
                RendererUtil::SetColor(m_renderer, RendererUtil::Color::RED);
        } else {
            RendererUtil::SetColor(m_renderer, RendererUtil::Color::YELLOW, 192);
        }
        SDL_RenderFillRect(m_renderer, m_pointRect);
        if (node->anchor) {
            RendererUtil::SetColor(m_renderer, RendererUtil::Color::GREEN, 92);
            SDL_RenderDrawLine(m_renderer,
                CMath::MToPxInt(node->x),
                CMath::MToPxInt(CMath::ToCanvas(node->y, m_scene_height)),
                CMath::MToPxInt(node->anchor->x),
                CMath::MToPxInt(CMath::ToCanvas(node->anchor->y, m_scene_height)));
            m_pointRect->x = CMath::MToPxInt(node->anchor->x) - m_pointRect->w/2;
            m_pointRect->y = CMath::MToPxInt(CMath::ToCanvas(node->anchor->y, m_scene_height)) - m_pointRect->h/2;
            SDL_RenderFillRect(m_renderer, m_pointRect);
        }
        RendererUtil::SetColor(m_renderer, RendererUtil::Color::WHITE);
        boost::tie(neighbourIt, neighbourEnd) = boost::adjacent_vertices(v, *m_graph);
        for (; neighbourIt != neighbourEnd; ++neighbourIt){
            _v = index[*neighbourIt];
            neighbourNode = &(*m_graph)[_v];
            if (node->IsIntern())
                RendererUtil::SetColor(m_renderer, RendererUtil::Color::RED, 92);
            else
                RendererUtil::SetColor(m_renderer, RendererUtil::Color::GREEN, 92);
            SDL_RenderDrawLine(m_renderer,
                CMath::MToPxInt(node->x),
                CMath::MToPxInt(CMath::ToCanvas(node->y, m_scene_height)),
                CMath::MToPxInt(neighbourNode->x),
                CMath::MToPxInt(CMath::ToCanvas(neighbourNode->y, m_scene_height)));
        }
    }
    RendererUtil::ResetColor(m_renderer);
};
