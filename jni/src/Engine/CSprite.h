#ifndef _CSPRITE_H_
    #define _CSPRITE_H_
#include <SDL.h>
#include <string>

class CSprite {
    protected:
        std::string m_filename;
        int m_tilesX;
        int m_tilesY;
        int m_tileWidth;
        int m_tileHeight;
        SDL_Rect* m_rect;
        SDL_Rect* m_dstRect;
        int m_tiles;
        bool m_perColumn;
        int m_dstXOffset;
        int m_dstYOffset;
        int m_dstWidth;
        int m_dstHeight;

    public:
        CSprite(int tilesX, int tilesY, int tileWidth, int tileHeight, bool perColumn);
        CSprite(int tilesX, int tilesY, int tileWidth, int tileHeight);
        SDL_Rect* GetTile(int tile);
        SDL_Rect* GetDstTile(int tile, int centerX, int centerY);
        void SetFilename(std::string filename);
        std::string GetFilename();
        int GetTilesX();
        int GetTilesY();
        int GetTileWidth();
        int GetTileHeight();
        void SetPerColumn(bool perColumn);
        bool IsPerColumn();
        void SetDstXOffset(int dstXOffset);
        int GetDstXOffset();
        void SetDstYOffset(int dstYOffset);
        int GetDstYOffset();
        void SetDstWidth(int dstWidth);
        int GetDstWidth();
        void SetDstHeight(int dstHeight);
        int GetDstHeight();

};

#endif
