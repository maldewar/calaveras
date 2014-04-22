#include "LayeredGraphic.h"
#include "../Util/Log.h"

LayeredGraphic::LayeredGraphic() {
    m_reference = new Vector2(0, 0);
    m_hasReference = false;
};

void LayeredGraphic::SetReference(float x, float y) {
    m_reference->x = x;
    m_reference->y = y;
    m_hasReference = true;;
};

bool LayeredGraphic::HasReference() {
    return m_hasReference;
};

void LayeredGraphic::AddFront(Animation* animation) {
    AddAnimation(animation, false);
};

void LayeredGraphic::AddFront(Still* still) {
    AddStill(still, false);
};

void LayeredGraphic::AddBack(Animation* animation) {
    AddAnimation(animation, true);
};

void LayeredGraphic::AddBack(Still* still) {
    AddStill(still, true);
};

int LayeredGraphic::GetTypeAtBack(int index) {
    m_tmpPair = &m_stackBack[index];
    return m_tmpPair->first;
};

int LayeredGraphic::GetTypeAtFront(int index) {
    m_tmpPair =  &m_stackFront[index];
    return m_tmpPair->first;
};

Animation* LayeredGraphic::GetAnimation(int index, bool isBack) {
    if (isBack)
        m_tmpPair = &m_stackBack[index];
    else
        m_tmpPair = &m_stackFront[index];
    return m_stackAnimation[m_tmpPair->second];
};

Still* LayeredGraphic::GetStill(int index, bool isBack) {
    if (isBack)
        m_tmpPair = &m_stackBack[index];
    else
        m_tmpPair = &m_stackFront[index];
    return m_stackStill[m_tmpPair->second];
};

int LayeredGraphic::GetTotal() {
    return GetTotalFront() + GetTotalBack();
};

int LayeredGraphic::GetTotalFront() {
    return m_stackFront.size();
};

int LayeredGraphic::GetTotalBack() {
    return m_stackBack.size();
};

void LayeredGraphic::AddAnimation(Animation* animation, bool isBack) {
    int index;
    lgPair pair (0, 0);
    m_stackAnimation.push_back(animation);
    pair.second = m_stackAnimation.size() - 1;
    if (isBack) {
        pair.first = STACK_ELEM_ANIMATION;
        m_stackBack.push_back(pair);
    } else {
        pair.first = STACK_ELEM_STILL;
        m_stackFront.push_back(pair);
    }
};

void LayeredGraphic::AddStill(Still* still, bool isBack) {
    int index;
    lgPair pair (0, 0);
    m_stackStill.push_back(still);
    pair.second = m_stackStill.size() - 1;
    if (isBack) {
        pair.first = STACK_ELEM_ANIMATION;
        m_stackBack.push_back(pair);
    } else {
        pair.first = STACK_ELEM_STILL;
        m_stackFront.push_back(pair);
    }
};
