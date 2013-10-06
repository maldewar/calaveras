#ifndef _CWORLDLAYER_H_
    #define _CWORLDLAYER_H_

#include "CLayer.h"
#include "CUnit.h"
#include "CEntry.h"
class CUnit;
class CEntry;

/**
 * Models a layer for the scene with world physics.
 */
class CWorldLayer : public CLayer {
    private:
        std::vector<CUnit*> m_units;
        std::vector<CEntry*> m_entries;

    public:
        /**
         * Class constructor.
         */
        CWorldLayer();
        /**
         * Class constructor and typecaster.
         */
        CWorldLayer(CLayer* layer);
        /**
         * Class destructor.
         */
        ~CWorldLayer();
        /**
         * Adds an Unit instance to this scene.
         * @param unit Unit instance.
         */
        void AddUnit(CUnit* unit);
        /**
         * Adds a list of Unit instances to this scene.
         * @param units Unit instances to add.
         */
        void SetUnits(std::vector<CUnit*> units);
        /**
         * Get all the Unit instances contained in this scene.
         * @returns List of Unit instances contained in this scene.
         */
        std::vector<CUnit*> GetUnits();
        /**
         * Add an Entry instance to this scene.
         * @param entry Entry instance.
         */
        void AddEntry(CEntry* entry);
        /**
         * Sets a list of Entry instances contained in this scene.
         * @param entries List of Entry instances.
         */
        void SetEntries(std::vector<CEntry*> entries);
        /**
         * Gets the Entry instances contained in this scene.
         * @return List of Entry instances.
         */
        std::vector<CEntry*> GetEntries();
        void OnInit();
        void OnLoop();

};
#endif
