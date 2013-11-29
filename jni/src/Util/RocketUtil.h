#ifndef _ROCKETUTIL_H_
    #define _ROCKETUTIL_H_
#include "../Engine/RocketGlue.h"
class RocketUtil {
    private:
        RocketUtil();

    public:
        static void Show(Rocket::Core::Element* element);
        static void Hide(Rocket::Core::Element* element);
};
#endif
