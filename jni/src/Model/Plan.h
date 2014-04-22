#ifndef _PLAN_H_
    #define _PLAN_H_

#include "GraphNode.h"

/**
 * Models an Plan for a Unit.
 * Contains steps and feasibility on Unit's AI..
 */
class Plan
{
    private:
        GraphNode* m_origin;
        GraphNode* m_target;

    public:
        /**
         * Class constructor.
         */
        Plan();

};
#endif
