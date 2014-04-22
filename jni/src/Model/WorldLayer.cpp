#include "WorldLayer.h"
#include "../Engine/WorldContactListener.h"
#include "../Util/Log.h"

WorldLayer::WorldLayer() : Layer() {
    m_choiceGraph = new ChoiceGraph(this);
    m_isDefault = false;
    Log::L("Creating WorldLayer.");
};

void WorldLayer::AddUnit(Unit* unit) {
    m_units.push_back(unit);
};

void WorldLayer::SetUnits(std::vector<Unit*> units) {
    m_units = units;
};

std::vector<Unit*> WorldLayer::GetUnits() {
    return m_units;
};

void WorldLayer::AddEntry(Entry* entry) {
    m_entries.push_back(entry);
};

void WorldLayer::SetEntries(std::vector<Entry*> entries) {
    m_entries = entries;
};

std::vector<Entry*> WorldLayer::GetEntries() {
    return m_entries;
};

void WorldLayer::AddExit(Exit* exit) {
    m_exits.push_back(exit);
};

void WorldLayer::SetExits(std::vector<Exit*> exits) {
    m_exits = exits;
};

std::vector<Exit*> WorldLayer::GetExits() {
    return m_exits;
};

void WorldLayer::SetDefault(bool isDefault) {
    m_isDefault = isDefault;
};

bool WorldLayer::IsDefault() {
    return m_isDefault;
};

ChoiceGraph* WorldLayer::GetChoiceGraph() {
    return m_choiceGraph;
};

void WorldLayer::OnInit() {
    for(auto &entry : m_entries)
        entry->OnInit();
    for(auto &unit : m_units)
        unit->OnInit();
    m_choiceGraph->Build();
    WorldContactListener* worldContactListener = new WorldContactListener();
    m_world->SetContactListener(worldContactListener);
};

void WorldLayer::OnLoop() {
    m_world->Step(1.0f/60.0f,10,10);
    for(auto &entry : m_entries) 
        entry->OnLoop();
    for(auto &unit : m_units)
        unit->OnLoop();
};
