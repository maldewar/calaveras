#ifndef _CHOICEGRAPHRENDERER_H_
    #define _CHOICEGRAPHRENDERER_H_
#include "../Model/ChoiceGraph.h"
#include "../Engine/Camera.h"

class ChoiceGraphRenderer {
    private:
        void Render();

    private:
        ChoiceGraph* m_choiceGraph;
        CGraph* m_graph;
        SDL_Renderer* m_renderer;
        float m_scene_height;
        SDL_Rect* m_pointRect;

    public:
        ChoiceGraphRenderer();
        ~ChoiceGraphRenderer();
        void Activate(ChoiceGraph* choiceGraph, SDL_Renderer* renderer, float sceneHeight);
        void Deactivate();
        void Render(Camera* camera);
};
#endif
