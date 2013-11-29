#include "Node.h"

Node::Node() : Vector2() {
    id = 0;
};

Node::Node(int id) : Vector2() {
    this->id = id;
};

Node::Node(int id, float x, float y) : Vector2(x, y) {
    this->id = id;
};

int Node::GetId() {
    return id;
};
