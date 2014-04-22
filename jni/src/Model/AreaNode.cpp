#include "AreaNode.h"

AreaNode::AreaNode() : AreaNode(0, 0) {};

AreaNode::AreaNode(float x, float y) : Vector2(x, y) {
    graphNodeId = -1;
    area = NULL;
    neighborA = NULL;
    neighborB = NULL;
};
