#include "SpriteNode.h"
#include "../Manager/TextureManager.h"
#include "../Util/CMath.h"
#include "../Util/Log.h"

SpriteNode::SpriteNode() : Elem() {
  m_vtiles = 1;
  m_htiles = 1;
  m_frame = 0;
  m_centered = true;
  m_flip_h = false;
  m_flip_h = false;
  m_path = "";
  m_texture = nullptr;
  m_src_rect = new SDL_Rect();
  m_dst_rect = new SDL_Rect();
  m_flip = SDL_FLIP_NONE;
  m_texture_w = 0;
  m_texture_h = 0;
  m_center_offset_x = 0;
  m_center_offset_y = 0;
};

void SpriteNode::SetWidth(float width) {
  Elem::SetWidth(width);
  if (m_centered)
    m_center_offset_x = m_width / 2;
  else
    m_center_offset_x = 0;
};

void SpriteNode::SetHeight(float height) {
  Elem::SetHeight(height);
  if (m_centered)
    m_center_offset_y = m_height / 2;
  else
    m_center_offset_y = 0;
};

void SpriteNode::SetVTiles(int vtiles) {
  m_vtiles = vtiles;
};

int SpriteNode::GetVTiles() {
  return m_vtiles;
};

void SpriteNode::SetHTiles(int htiles) {
  m_htiles = htiles;
};

int SpriteNode::GetHTiles() {
  return m_htiles;
};

void SpriteNode::SetFrame(int frame) {
  m_frame = frame;
  m_src_rect->y = m_src_rect->w * m_frame;
};

int SpriteNode::GetFrame() {
  return m_frame;
};

void SpriteNode::SetCentered(bool centered) {
  m_centered = centered;
  if (m_centered) {
    m_center_offset_x = m_width / 2;
    m_center_offset_y = m_height / 2;
  } else {
    m_center_offset_x = 0;
    m_center_offset_y = 0;
  }
};

bool SpriteNode::IsCentered() {
  return m_centered;
};

void SpriteNode::SetFlipH(bool flip_h) {
  m_flip_h = flip_h;
  if (m_flip_h && m_flip_v)
    m_flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
  else if (m_flip_v)
    m_flip = SDL_FLIP_VERTICAL;
  else if (m_flip_h)
    m_flip = SDL_FLIP_HORIZONTAL;
  else
    m_flip = SDL_FLIP_NONE;
};

bool SpriteNode::IsFlipH() {
  return m_flip_h;
};

void SpriteNode::SetFlipV(bool flip_v) {
  m_flip_v = flip_v;
  if (m_flip_h && m_flip_v)
    m_flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
  else if (m_flip_v)
    m_flip = SDL_FLIP_VERTICAL;
  else if (m_flip_h)
    m_flip = SDL_FLIP_HORIZONTAL;
  else
    m_flip = SDL_FLIP_NONE;
};

bool SpriteNode::IsFlipV() {
  return m_flip_v;
};

void SpriteNode::SetPath(std::string path) {
  m_path = path;
};

std::string SpriteNode::GetPath() {
  return m_path;
};

void SpriteNode::OnInit() {
  m_texture = TextureManager::RequestTexture(m_path);
  if (m_texture) {
    TextureManager::GetInfo(m_path, m_texture_w, m_texture_h);
    m_src_rect->w = m_texture_w / m_htiles;
    m_src_rect->h = m_texture_h / m_vtiles;
    m_src_rect->x = 0;
    m_src_rect->y = m_src_rect->w * m_frame;
    m_dst_rect->w = CMath::MToPxInt(m_width);
    m_dst_rect->h = CMath::MToPxInt(m_height);
    Log::L("src.w:%d, src.h:%d, src.x:%d, src.y:%d, dst.w:%d, dst.h:%d, dst.x:%d, dst.y:%d",
        m_src_rect->w, m_src_rect->h, m_src_rect->x, m_src_rect->y,
        m_dst_rect->w, m_dst_rect->h, m_dst_rect->x, m_dst_rect->y);
  }
  Node::OnInit();
};

void SpriteNode::OnRender() {
  if (m_parent) {
    rotation_offset = m_rotation + m_parent->rotation_offset;
    scale_offset = m_scale * m_parent->scale_offset;
    if (rotation_offset != 0) {
      x_offset = (cos(rotation_offset) * m_x * scale_offset - sin(rotation_offset) * m_y * scale_offset) + m_parent->x_offset;
      y_offset = (sin(rotation_offset) * m_x * scale_offset + cos(rotation_offset) * m_y * scale_offset) + m_parent->y_offset;
    } else {
      x_offset = m_x * scale_offset + m_parent->x_offset;
      y_offset = m_y * scale_offset + m_parent->y_offset;
    }
  } else {
    rotation_offset = m_rotation;
    scale_offset = m_scale;
    x_offset = m_x;
    y_offset = m_y;
  }
  m_dst_rect->x = CMath::MToPxInt(x_offset - (m_center_offset_x * scale_offset));
  m_dst_rect->y = CMath::MToPxInt(y_offset - (m_center_offset_y * scale_offset));
  m_dst_rect->w = CMath::MToPxInt(m_width * scale_offset);
  m_dst_rect->h = CMath::MToPxInt(m_height * scale_offset);
  //SDL_SetTextureAlphaMod(m_texture, 128);
  SDL_RenderCopyEx(TextureManager::GetRenderer(),
    m_texture,
    m_src_rect,
    m_dst_rect,
    CMath::ToDeg(rotation_offset),
    NULL,
    m_flip
  );
  Node::OnRender();
};

void SpriteNode::OnCleanUp() {
  TextureManager::ReleaseTexture(m_path);
  m_texture = nullptr;
  Node::OnCleanUp();
};
