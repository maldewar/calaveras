#include "CompositeRenderer.h"
#include "../Util/CMath.h"
#include "../Util/CLog.h"
#include "../Util/TextureUtil.h"
#include "../Util/SurfaceUtil.h"


CompositeRenderer::CompositeRenderer(int width, int height){
    m_width = width;
    m_height = height;
    m_texture = NULL;
    m_baseTexture = NULL;
    m_gradient = NULL;
    m_baseType = CompositeRenderer::BASE_TYPE_PLAIN;
    m_red = 0;
    m_green = 0;
    m_blue = 0;
    m_alpha = 255;
    m_texture = NULL;
    m_textureFile = "";
    m_textureRepeatX = true;
    m_textureRepeatY = true;
    m_textureAlpha = 255;
    m_textureBlending = 0;
    m_textureWidthPx = 0;
    m_textureHeightPx = 0;
    m_textureWidthM = 0;
    m_textureHeightM = 0;

    m_maxZoom = 1.0;
};

void CompositeRenderer::Activate(SDL_Renderer* renderer) {
    m_renderer = renderer;
    if (m_baseType == CompositeRenderer::BASE_TYPE_GRADIENT) {
        m_baseTexture = m_gradient->Draw(m_width, m_height, m_renderer);
    }
    if (!m_textureFile.empty()) {
        int scaledW, scaledH;
        scaledW = CMath::MToPxInt(m_textureWidthM, m_maxZoom);
        scaledH = CMath::MToPxInt(m_textureHeightM, m_maxZoom);
        m_texture = TextureUtil::LoadTexture(m_textureFile, scaledW, scaledH, m_renderer);
        Uint32 format;
        int access;
        SDL_QueryTexture(m_texture, &format, &access, &m_textureWidthPx, &m_textureHeightPx);
    }
    
};

void CompositeRenderer::Deactivate() {
    if (m_baseTexture)
        SDL_DestroyTexture(m_baseTexture);
    if (m_texture)
        SDL_DestroyTexture(m_texture);
};

void CompositeRenderer::Render() {
    RenderBase();
    RenderTexture();
};

void CompositeRenderer::RenderBase() {
    if (m_baseType == CompositeRenderer::BASE_TYPE_PLAIN) {
        SDL_SetRenderDrawColor(m_renderer, m_red, m_green, m_blue, m_alpha);
        SDL_RenderClear(m_renderer);
    } else {
        TextureUtil::OnDraw(0, 0, m_baseTexture, m_renderer);
    }
};

void CompositeRenderer::RenderTexture() {
    if (m_texture) {
        //SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_ADD);
        SDL_SetTextureAlphaMod(m_texture, m_textureAlpha);
        if (m_textureRepeatX && m_textureRepeatY)
            for (int i = 0; i < m_width; i += m_textureWidthPx)
                for (int j = 0; j < m_height; j += m_textureHeightPx)
                    TextureUtil::OnDraw(i, j, m_texture, m_renderer);
        else if (m_textureRepeatX)
            for (int i = 0; i < m_width; i += m_textureWidthPx)
                TextureUtil::OnDraw(i, 0, m_texture, m_renderer);
        else if (m_textureRepeatY)
                for (int j = 0; j < m_height; j += m_textureHeightPx)
                    TextureUtil::OnDraw(0, j, m_texture, m_renderer);
        else
            TextureUtil::OnDraw(0, 0, m_texture, m_renderer);
    }
};

void CompositeRenderer::SetBaseType(Uint8 baseType) {
    m_baseType = baseType;
    if (baseType == CompositeRenderer::BASE_TYPE_GRADIENT && !m_gradient) {
        m_gradient = new Gradient();
        m_gradient->SetBaseColor(m_red, m_green, m_blue, m_alpha);
    }
};

void CompositeRenderer::SetRed(Uint8 red) {
    m_red = red;
    if (m_baseType == CompositeRenderer::BASE_TYPE_GRADIENT)
        m_gradient->SetBaseColor(m_red, m_green, m_blue, m_alpha);
};

void CompositeRenderer::SetGreen(Uint8 green) {
    m_green = green;
    if (m_baseType == CompositeRenderer::BASE_TYPE_GRADIENT)
        m_gradient->SetBaseColor(m_red, m_green, m_blue, m_alpha);
};

void CompositeRenderer::SetBlue(Uint8 blue) {
    m_blue = blue;
    if (m_baseType == CompositeRenderer::BASE_TYPE_GRADIENT)
        m_gradient->SetBaseColor(m_red, m_green, m_blue, m_alpha);
};

void CompositeRenderer::SetAlpha(Uint8 alpha) {
    m_alpha = alpha;
    if (m_baseType == CompositeRenderer::BASE_TYPE_GRADIENT)
        m_gradient->SetBaseColor(m_red, m_green, m_blue, m_alpha);
};

Gradient* CompositeRenderer::GetGradient() {
    return m_gradient;
};

void CompositeRenderer::SetTextureFile(std::string file) {
    m_textureFile = file;
};

void CompositeRenderer::SetTextureWidth(float width) {
    m_textureWidthM = width;
};

void CompositeRenderer::SetTextureHeight(float height) {
    m_textureHeightM = height;
};

void CompositeRenderer::SetTextureRepeatX(bool repeat) {
    m_textureRepeatX = repeat;
};

void CompositeRenderer::SetTextureRepeatY(bool repeat) {
    m_textureRepeatY = repeat;
};

void CompositeRenderer::SetTextureAlpha(Uint8 alpha) {
    m_textureAlpha = alpha;
};

void CompositeRenderer::SetTextureBlending(Uint8 blending) {
    m_textureBlending = blending;
};
