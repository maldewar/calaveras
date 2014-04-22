#ifndef _FGLAYER_H_
    #define _FGLAYER_H_

#include "Layer.h"
#include "Unit.h"
#include "Entry.h"
class Unit;
class Entry;

/**
 * Models the background graphics.
 */
class FgLayer : public Layer {
    private:
        std::vector<Unit*> m_units;
        std::vector<Entry*> m_entries;

    public:
        /**
         * Class constructor.
         */
        FgLayer();
        /**
         * Class constructor and typecaster.
         */
        FgLayer(Layer* layer);
        /**
         * Class destructor.
         */
        ~FgLayer();
        void OnInit();
        void OnLoop();

};
#endif
