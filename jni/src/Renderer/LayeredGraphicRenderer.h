#ifndef _LAYEREDGRAPHICRENDERER_H_
    #define _LAYEREDGRAPHICRENDERER_H_
#include "../Engine/LayeredGraphic.h"
#include "../Engine/Camera.h"

class LayeredGraphicRenderer {
    private:
        void Render(LayeredGraphic* layeredGraphic, Camera* camera, bool isBack);

    private:
        SDL_Renderer* m_renderer;
        float m_scene_height;

    public:
        LayeredGraphicRenderer();
        ~LayeredGraphicRenderer();
        void Activate(SDL_Renderer* renderer, float sceneHeight);
        void Deactivate();
        void RenderBack(LayeredGraphic* layeredGraphic, Camera* camera);
        void RenderFront(LayeredGraphic* layeredGraphic, Camera* camera);
};
#endif
