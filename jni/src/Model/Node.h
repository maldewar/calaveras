#ifndef _NODE_H_
    #define _NODE_H_

#include "Vector2.h"

class Node : public Vector2 {
    public:
        int id;

    public:
        Node();
        Node(int id);
        Node(int id, float x, float y);
        int GetId();
};

#endif
