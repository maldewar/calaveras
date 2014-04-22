#include "Sprite.h"

Sprite::Sprite(int tilesX, int tilesY, int tileWidth, int tileHeight, bool perColumn) {
    if (tilesX > 0)
        m_tilesX = tilesX;
    else
        m_tilesX = 1;
    if (tilesY > 0)
        m_tilesY = tilesY;
    else
        m_tilesY = 1;
    m_tiles = m_tilesX * m_tilesY;
    if (tileWidth > 0)
        m_tileWidth = tileWidth;
    else
        m_tileWidth = 1;
    if (tileHeight > 0)
        m_tileHeight = tileHeight;
    else
        m_tileHeight = 0;
    m_rect = new SDL_Rect();
    m_dstRect =  new SDL_Rect();
    m_rect->w = (float)m_tileWidth;
    m_rect->h = (float)m_tileHeight;
    m_perColumn = perColumn;
    m_dstXOffset = 0;
    m_dstYOffset = 0;
    m_dstWidth = 0;
    m_dstHeight = 0;
    m_filename = "";
}

Sprite::Sprite(int tilesX, int tilesY, int tileWidth, int tileHeight) : Sprite(tilesX, tilesY, tileWidth, tileHeight, true) {}

SDL_Rect* Sprite::GetTile(int tile) {
    if (tile < m_tiles) {
        if (m_perColumn) {
            m_rect->y = (tile % m_tilesY) * m_tileHeight;
            m_rect->x = (tile / m_tilesY) * m_tileWidth;
        } else {
            m_rect->x = (tile % m_tilesX) * m_tileWidth;
            m_rect->y = (tile / m_tilesX) * m_tileHeight;
        }
    } else {
        m_rect->x = 0;
        m_rect->y = 0;
    }
    return m_rect;
}

SDL_Rect* Sprite::GetDstTile(int tile, int centerX, int centerY) {
    m_dstRect->x = (int)(centerX - m_dstXOffset);
    m_dstRect->y = (int)(centerY - m_dstYOffset);
    return m_dstRect;
}

void Sprite::SetFilename(std::string filename) {
    m_filename = filename;
}

std::string Sprite::GetFilename() {
    return m_filename;
}

int Sprite::GetTilesX() {
    return m_tilesX;
}

int Sprite::GetTilesY() {
    return m_tilesY;
}

int Sprite::GetTileWidth() {
    return m_tileWidth;
}

int Sprite::GetTileHeight() {
    return m_tileHeight;
}

void Sprite::SetPerColumn(bool perColumn) {
    m_perColumn = perColumn;
}

bool Sprite::IsPerColumn() {
    return m_perColumn;
}

void Sprite::SetDstXOffset(int dstXOffset) {
    m_dstXOffset = dstXOffset;
}

int Sprite::GetDstXOffset() {
    return m_dstXOffset;
}

void Sprite::SetDstYOffset(int dstYOffset) {
    m_dstYOffset = dstYOffset;
}

int Sprite::GetDstYOffset() {
    return m_dstYOffset;
}

void Sprite::SetDstWidth(int dstWidth) {
    m_dstWidth = dstWidth;
    m_dstRect->w = dstWidth;
    m_dstXOffset = dstWidth/2;
}

int Sprite::GetDstWidth() {
    return m_dstWidth;
}

void Sprite::SetDstHeight(int dstHeight) {
    m_dstHeight = dstHeight;
    m_dstRect->h = dstHeight;
    m_dstYOffset = dstHeight/2;
}

int Sprite::GetDstHeight() {
    return m_dstHeight;
}
