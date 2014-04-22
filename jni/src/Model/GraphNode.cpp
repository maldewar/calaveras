#include "GraphNode.h"

GraphNode::GraphNode() : GraphNode(0, 0, 0) {};

GraphNode::GraphNode(int id) : GraphNode(id, 0, 0) {};

GraphNode::GraphNode(int id, float x, float y) : Vector2(x, y) {
    this->id = id;
    intern   = false;
    terminal = false;
    action   = 0;
    anchor   = NULL;
};

int GraphNode::GetId() {
    return id;
};

bool GraphNode::IsIntern() {
    return intern;
};
