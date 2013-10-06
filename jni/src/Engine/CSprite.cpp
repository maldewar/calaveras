#include "CSprite.h"

CSprite::CSprite(int tilesX, int tilesY, int tileWidth, int tileHeight, bool perColumn) {
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

CSprite::CSprite(int tilesX, int tilesY, int tileWidth, int tileHeight) : CSprite(tilesX, tilesY, tileWidth, tileHeight, true) {}

SDL_Rect* CSprite::GetTile(int tile) {
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

SDL_Rect* CSprite::GetDstTile(int tile, int centerX, int centerY) {
    m_dstRect->x = (int)(centerX - m_dstXOffset);
    m_dstRect->y = (int)(centerY - m_dstYOffset);
    return m_dstRect;
}

void CSprite::SetFilename(std::string filename) {
    m_filename = filename;
}

std::string CSprite::GetFilename() {
    return m_filename;
}

int CSprite::GetTilesX() {
    return m_tilesX;
}

int CSprite::GetTilesY() {
    return m_tilesY;
}

int CSprite::GetTileWidth() {
    return m_tileWidth;
}

int CSprite::GetTileHeight() {
    return m_tileHeight;
}

void CSprite::SetPerColumn(bool perColumn) {
    m_perColumn = perColumn;
}

bool CSprite::IsPerColumn() {
    return m_perColumn;
}

void CSprite::SetDstXOffset(int dstXOffset) {
    m_dstXOffset = dstXOffset;
}

int CSprite::GetDstXOffset() {
    return m_dstXOffset;
}

void CSprite::SetDstYOffset(int dstYOffset) {
    m_dstYOffset = dstYOffset;
}

int CSprite::GetDstYOffset() {
    return m_dstYOffset;
}

void CSprite::SetDstWidth(int dstWidth) {
    m_dstWidth = dstWidth;
    m_dstRect->w = dstWidth;
    m_dstXOffset = dstWidth/2;
}

int CSprite::GetDstWidth() {
    return m_dstWidth;
}

void CSprite::SetDstHeight(int dstHeight) {
    m_dstHeight = dstHeight;
    m_dstRect->h = dstHeight;
    m_dstYOffset = dstHeight/2;
}

int CSprite::GetDstHeight() {
    return m_dstHeight;
}
