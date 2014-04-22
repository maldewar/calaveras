#ifndef _AREAUSERDATA_H_
    #define _AREAUSERDATA_H_

#include "../Model/Area.h"
#include "UserData.h"
#include <vector>

/**
 * UserData for ChainShapes from Box2D used in Area objects.
 */
class AreaUserData : public UserData {
    private:
        Area* m_area;

    public:
        /**
         * Class constructor.
         */
        AreaUserData(int dataType);
        void SetArea(Area* area);
        Area* GetArea();
        void GetSection(int index, AreaNode*& nodeA, AreaNode*& nodeB);

};
#endif
