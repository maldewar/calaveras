#include "RocketUtil.h"

RocketUtil::RocketUtil() {
};

void RocketUtil::Show(Rocket::Core::Element* element) {
    element->SetClass("ui-hidden", false);
}

void RocketUtil::Hide(Rocket::Core::Element* element) {
    element->SetClass("ui-hidden", true);
}
