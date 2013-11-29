#ifndef _BGLAYER_H_
    #define _BGLAYER_H_

#include "Layer.h"
#include "CUnit.h"
#include "Entry.h"
class CUnit;
class Entry;

/**
 * Models the background graphics.
 */
class BgLayer : public Layer {
    private:
        std::vector<CUnit*> m_units;
        std::vector<Entry*> m_entries;
        int m_bg;

    public:
        /**
         * Class constructor.
         */
        BgLayer();
        /**
         * Class constructor and typecaster.
         */
        BgLayer(Layer* layer);
        /**
         * Class destructor.
         */
        ~BgLayer();
        /**
         * Sets a background style id from a catalog.
         */
        void SetBg(int bg);
        /**
         * Gets the background style id set from a catalog.
         */
        int GetBg();
        void OnInit();
        void OnLoop();

};
#endif
