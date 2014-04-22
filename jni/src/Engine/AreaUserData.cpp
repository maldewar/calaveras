#include "AreaUserData.h"
#include "../Util/Log.h"

AreaUserData::AreaUserData(int dataType) : UserData(dataType) {
    type = dataType;
};

void AreaUserData::SetArea(Area* area) {
    m_area = area;
};

Area* AreaUserData::GetArea() {
    return m_area;
};

void AreaUserData::GetSection(int index, AreaNode*& nodeA, AreaNode*& nodeB) {
    if ( index <= m_area->GetPoints().size() - 1 ) {
        nodeA = m_area->GetPoints()[index];
        if ( m_area->IsClosed() && index == m_area->GetPoints().size() - 1 ) {
            nodeB = m_area->GetPoints()[0];
        } else if ( index < m_area->GetPoints().size() - 1 ) {
            nodeB = m_area->GetPoints()[index + 1];
        } else {
            nodeB = NULL;
        }
    } else {
        nodeA = NULL;
        nodeB = NULL;
    }
};
