#ifndef _SPRITE_NODE_H_
    #define _SPRITE_NODE_H_

#include "Elem.h"
#include <SDL.h>

/**
 * Models a sprite node.
 */
class SpriteNode : public Elem {
    protected:
        int m_vtiles;
        int m_htiles;
        int m_frame;
        bool m_centered;
        bool m_flip_h;
        bool m_flip_v;
        std::string m_path;
        SDL_Texture* m_texture;
        SDL_Rect* m_src_rect;
        SDL_Rect* m_dst_rect;
        SDL_RendererFlip m_flip;
        int m_texture_w;
        int m_texture_h;
        float m_center_offset_x;
        float m_center_offset_y;

    public:
        /**
         * Class constructor.
         */
        SpriteNode();
        void SetWidth(float width);
        void SetHeight(float height);
        void SetVTiles(int vtiles);
        int GetVTiles();
        void SetHTiles(int htiles);
        int GetHTiles();
        void SetFrame(int frame);
        int GetFrame();
        void SetCentered(bool centered);
        bool IsCentered();
        void SetFlipH(bool flip_h);
        bool IsFlipH();
        void SetFlipV(bool flip_v);
        bool IsFlipV();
        void SetPath(std::string path);
        std::string GetPath();
        void OnInit();
        void OnRender();
        void OnCleanUp();

};
#endif
