#ifndef _WORLDLAYER_H_
    #define _WORLDLAYER_H_

#include "Layer.h"
#include "CUnit.h"
#include "Entry.h"
#include "Exit.h"
#include "ChoiceGraph.h"
class ChoiceGraph;
class CUnit;
class Entry;

/**
 * Models a layer for the scene with world physics.
 */
class WorldLayer : public Layer {
    private:
        std::vector<CUnit*> m_units;
        std::vector<Entry*> m_entries;
        std::vector<Exit*> m_exits;
        ChoiceGraph* m_choiceGraph;

    public:
        /**
         * Class constructor.
         */
        WorldLayer();
        /**
         * Class constructor and typecaster.
         */
        WorldLayer(Layer* layer);
        /**
         * Class destructor.
         */
        ~WorldLayer();
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
         * @return List of Unit instances contained in this scene.
         */
        std::vector<CUnit*> GetUnits();
        /**
         * Add an Entry instance to this scene.
         * @param entry Entry instance.
         */
        void AddEntry(Entry* entry);
        /**
         * Sets a list of Entry instances contained in this scene.
         * @param entries List of Entry instances.
         */
        void SetEntries(std::vector<Entry*> entries);
        /**
         * Gets the Entry instances contained in this scene.
         * @return List of Entry instances.
         */
        std::vector<Entry*> GetEntries();
        /**
         * Add and Exit instance to this scene.
         * @param exit Exit instance.
         */
        void AddExit(Exit* exit);
        /**
         * sets a list of Exit instances contained in this scene.
         * @param exits List of Exit instances.
         */
        void SetExits(std::vector<Exit*> exits);
        /**
         * Gets the Exit instances contained in this scene.
         * @return List of Exit instances.
         */
        std::vector<Exit*> GetExits();
        /**
         * Gets the ChoiceGraph built for this layer.
         * @return ChoiceGraph built for this layer.
         */
        ChoiceGraph* GetChoiceGraph();
        void OnInit();
        void OnLoop();

};
#endif
