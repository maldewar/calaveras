#include "LayeredGraphicRenderer.h"
#include "../Util/CMath.h"
#include "../Util/RendererUtil.h"
#include "../Model/AreaNode.h"
#include "../Util/Log.h"


LayeredGraphicRenderer::LayeredGraphicRenderer(){
    m_renderer = NULL;
    m_scene_height = 0.0f;
};

LayeredGraphicRenderer::~LayeredGraphicRenderer() {
};

void LayeredGraphicRenderer::Activate(SDL_Renderer* renderer, float sceneHeight) {
    m_renderer = renderer;
    m_scene_height = sceneHeight;
}

void LayeredGraphicRenderer::Deactivate() {
}

void LayeredGraphicRenderer::RenderBack(LayeredGraphic* layeredGraphic, Camera* camera) {
    SDL_RenderSetScale(m_renderer, camera->GetZoom(), camera->GetZoom());
    SDL_RenderSetViewport(m_renderer, camera->GetViewport());
    Render(layeredGraphic, camera, true);
    SDL_RenderSetScale(m_renderer, 1, 1);
    SDL_RenderSetViewport(m_renderer, NULL);
};

void LayeredGraphicRenderer::RenderFront(LayeredGraphic* layeredGraphic, Camera* camera) {
    SDL_RenderSetScale(m_renderer, camera->GetZoom(), camera->GetZoom());
    SDL_RenderSetViewport(m_renderer, camera->GetViewport());
    Render(layeredGraphic, camera, false);
    SDL_RenderSetScale(m_renderer, 1, 1);
    SDL_RenderSetViewport(m_renderer, NULL);
};

void LayeredGraphicRenderer::Render(LayeredGraphic* layeredGraphic, Camera* camera, bool isBack) {
    int total;
    if (isBack)
        total = layeredGraphic->GetTotalBack();
    else
        total = layeredGraphic->GetTotalFront();
    if (total > 0) {
        int graphicType;
        for (int i = 0; i < total; i++) {
            //TODO check for stills or animation on each index slot, then render them.
        }
    }
    /*CIndexMap index = boost::get(boost::vertex_index, *m_graph);
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
    RendererUtil::ResetColor(m_renderer);*/
};
