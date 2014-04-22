#ifndef _AREANODE_H_
    #define _AREANODE_H_

#include "Vector2.h"
#include "Area.h"
class GraphNode;
class Area;

class AreaNode : public Vector2 {
    public:
        int graphNodeId;
        Area* area;
        AreaNode* neighborA;
        AreaNode* neighborB;

    public:
        AreaNode();
        AreaNode(float x, float y);
};

#endif
