#include "BgLayer.h"

BgLayer::BgLayer() : Layer() {
    m_bg = 0;
}

void BgLayer::SetBg(int bg) {
    m_bg = bg;
}

int BgLayer::GetBg() {
    return m_bg;
}

void BgLayer::OnInit() {
}

void BgLayer::OnLoop() {
}
