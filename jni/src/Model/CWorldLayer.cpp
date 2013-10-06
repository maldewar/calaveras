#include "CWorldLayer.h"
#include "../Engine/WorldContactListener.h"

CWorldLayer::CWorldLayer() : CLayer() {
}

void CWorldLayer::AddUnit(CUnit* unit) {
    m_units.push_back(unit);
}

void CWorldLayer::SetUnits(std::vector<CUnit*> units) {
    m_units = units;
}

std::vector<CUnit*> CWorldLayer::GetUnits() {
    return m_units;
}

void CWorldLayer::AddEntry(CEntry* entry) {
    m_entries.push_back(entry);
}

void CWorldLayer::SetEntries(std::vector<CEntry*> entries) {
    m_entries = entries;
}

std::vector<CEntry*> CWorldLayer::GetEntries() {
    return m_entries;
}

void CWorldLayer::OnInit() {
    for(auto &entry : m_entries)
        entry->OnInit();
    for(auto &unit : m_units)
        unit->OnInit();
    WorldContactListener* worldContactListener = new WorldContactListener();
    m_world->SetContactListener(worldContactListener);
}

void CWorldLayer::OnLoop() {
    m_world->Step(1.0f/60.0f,10,10);
    for(auto &entry : m_entries) 
        entry->OnLoop();
    for(auto &unit : m_units)
        unit->OnLoop();
}
