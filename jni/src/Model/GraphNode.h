#ifndef _GRAPHNODE_H_
    #define _GRAPHNODE_H_

#include "Vector2.h"
#include "AreaNode.h"
class AreaNode;

class GraphNode : public Vector2 {
    public:
        int id;
        bool intern;
        bool terminal;
        int action;
        AreaNode* anchor;

    public:
        GraphNode();
        GraphNode(int id);
        GraphNode(int id, float x, float y);
        int GetId();
        bool IsIntern();

};

#endif
