#ifndef _LAYEREDGRAPHIC_H_
    #define _LAYEREDGRAPHIC_H_

#include <SDL.h>
#include "Animation.h"
#include "Still.h"
#include <vector>
#include "../Model/Vector2.h"

const int STACK_ELEM_ANIMATION = 0;
const int STACK_ELEM_STILL     = 1;

/**
 *  Contains a collection of rendereable graphics layer-stacked.
 */
class LayeredGraphic {
    private:
        Vector2* m_reference;
        typedef std::pair<int, int> lgPair;
        std::vector<lgPair> m_stackBack;
        std::vector<lgPair> m_stackFront;
        std::vector<Still*> m_stackStill;
        std::vector<Animation*> m_stackAnimation;
        bool m_hasReference;
        lgPair* m_tmpPair;

    public:
        LayeredGraphic();
        void SetReference(float x, float y);
        bool HasReference();
        void AddFront(Animation* animation);
        void AddBack(Animation* animation);
        void AddFront(Still* still);
        void AddBack(Still* still);
        int GetTypeAtBack(int index);
        int GetTypeAtFront(int index);
        Animation* GetAnimation(int index, bool isBack);
        Still* GetStill(int index, bool isBack);
        int GetTotal();
        int GetTotalFront();
        int GetTotalBack();

    private:
        void AddAnimation(Animation* animation, bool isBack);
        void AddStill(Still* still, bool isBack);

};

#endif
