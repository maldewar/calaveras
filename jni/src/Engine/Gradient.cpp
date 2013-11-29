#include "Gradient.h"
#include "../Util/SurfaceUtil.h"

Gradient::Gradient() {
    m_angle = 0;
    m_x = -1;
    m_y = -1;
    m_type = Gradient::LINEAR;
    m_basePosition = 0;
    m_nextPosition = 0;
    m_colorFrom = 0;
    m_colorTo = 0;
    m_refSurface = SurfaceUtil::GetSurface(1, 1);
};

Gradient::~Gradient() {
    SDL_FreeSurface(m_refSurface);
    m_steps.clear();
};

bool Gradient::AddStep(Uint32 color, float position) {
    if (position <= 1 && position >= 0) {
        if (m_steps.count(position) > 0)
            m_steps.erase(position);
        m_steps.insert(std::pair<float, Uint32>(position, color));
        return true;
    }
    return false;
};

bool Gradient::AddStep(Uint8 red, Uint8 green, Uint8 blue, float position) {
    return AddStep(red, green, blue, 255, position);
}

bool Gradient::AddStep(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, float position) {
    return AddStep(SDL_MapRGBA(m_refSurface->format, red, green, blue, alpha), position);
};

void Gradient::AddSteps(std::vector<Uint32> colors, std::vector<float> positions) {
    if (colors.size() == positions.size())
        for (int i = 0; i < colors.size(); ++i)
            AddStep(colors[i], positions[i]);
};

void Gradient::AddSteps(std::vector<Uint8> reds,
                    std::vector<Uint8> greens,
                    std::vector<Uint8> blues,
                    std::vector<Uint8> alphas,
                    std::vector<float> positions) {
    if (reds.size() == greens.size() == blues.size() == alphas.size() == positions.size())
        for (int i = 0; i < reds.size(); ++i)
            AddStep(reds[i], greens[i], blues[i], alphas[i], positions[i]);
};

void Gradient::SetBaseColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    if (m_steps.count(0) == 0)
        AddStep(red, green, blue, alpha, 0);
    if (m_steps.count(1) == 0)
        AddStep(red, green, blue, alpha, 1);
}

void Gradient::Clear() {
    m_steps.clear();
    m_colorFrom = 0;
    m_colorTo = 0;
    m_basePosition = 0;
    m_nextPosition = 0;
}

void Gradient::SetAngle(float angle) {
    m_angle = angle;
};

float Gradient::GetAngle() {
    return m_angle;
};

void Gradient::SetX(float x) {
    m_x = x;
};

float Gradient::GetX() {
    return m_x;
};

void Gradient::SetY(float y) {
    m_y = y;
};

float Gradient::GetY() {
    return m_y;
};

void Gradient::SetType(int type) {
    m_type = type;
};

int Gradient::GetType() {
    return m_type;
};

SDL_Texture* Gradient::Draw(int width, int height, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = SurfaceUtil::GetSurface(width, height);
    SDL_Texture* gradientTexture;
    float n, m;
    Uint8 r, g, b, a, rS, gS, bS, aS, rE, gE, bE, aE;
    Uint32 startColor, endColor;
    SDL_LockSurface(tempSurface);
    for (int j = 0; j < height; j++) {
        n = (float)j / (float) (height-1);
        startColor = GetColorFrom(n);
        endColor = GetColorTo(n);
        if (startColor != endColor) {
            SDL_GetRGBA(startColor, tempSurface->format, &rS, &gS, &bS, &aS);
            SDL_GetRGBA(endColor, tempSurface->format, &rE, &gE, &bE, &aE);
            m = (n - m_basePosition) / (m_nextPosition - m_basePosition);
            r = (float)rS * (1.0f-m) + (float)rE * m;
            g = (float)gS * (1.0f-m) + (float)gE * m;
            b = (float)bS * (1.0f-m) + (float)bE * m;
            a = (float)aS * (1.0f-m) + (float)aE * m;
        } else {
            SDL_GetRGBA(startColor, tempSurface->format, &r, &g, &b, &a);
        }
        for (int i = 0; i < width; i++)
            SurfaceUtil::PutPixel32_nolock(tempSurface, i, j, SDL_MapRGBA(tempSurface->format, r, g, b, a));
    }
    SDL_UnlockSurface(tempSurface);
    gradientTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return gradientTexture;
};

void Gradient::SetColorsAt(float position) {
    if (position > m_nextPosition) {
        if (m_steps.empty()) {
            m_nextPosition = 1;
        } else {
            m_basePosition = m_nextPosition;
            std::map<float, Uint32>::iterator itlow, itup;
            itlow = m_steps.lower_bound(m_basePosition);
            m_colorFrom = itlow->second;
            itup = m_steps.upper_bound(m_basePosition);
            if (itup == m_steps.end()) {
                m_colorTo = itlow->second;
                m_nextPosition = 1;
            } else {
                m_colorTo = itup->second;
                m_nextPosition = itup->first;
            }
        }
    }
}

Uint32 Gradient::GetColorFrom(float position) {
    SetColorsAt(position);
    return m_colorFrom;
};

Uint32 Gradient::GetColorTo(float position) {
    SetColorsAt(position);
    return m_colorTo;
};
