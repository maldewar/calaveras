#ifndef __APPSTATEMAIN_H__
    #define __APPSTATEMAIN_H__
 
#include "AppState.h"
#include "Engine/RocketGlue.h"
 
class AppStateMain : public AppState {
    private:
        static AppStateMain Instance;
        int m_startTime;
        int m_slotIndex;
        Rocket::Core::Element* m_startBtn;
        Rocket::Core::Element* m_continueBtn;
        Rocket::Core::Element* m_loadBtn;
        Rocket::Core::Element* m_returnBtn;
        Rocket::Core::Element* m_slot1Btn;
        Rocket::Core::Element* m_slot2Btn;
        Rocket::Core::Element* m_slot3Btn;
        Rocket::Core::Element* m_slot4Btn;
        Rocket::Core::Element* m_test1Btn;
        Rocket::Core::Element* m_test2Btn;
        Rocket::Core::Element* m_test3Btn;
        Rocket::Core::Element* m_test4Btn;
        Rocket::Core::Element* m_test5Btn;
        Rocket::Core::Element* m_test6Btn;
        Rocket::Core::Element* m_settingsBtn;
        Rocket::Core::Element* m_musicBtn;
        Rocket::Core::Element* m_soundBtn;
        Rocket::Core::Element* m_testBtn;
        Rocket::Core::Element* m_mainContainer;
        Rocket::Core::Element* m_settingsContainer;
        Rocket::Core::Element* m_slotContainer;
        Rocket::Core::Element* m_slotsContainer;
        Rocket::Core::Element* m_testContainer;
        Rocket::Controls::ElementForm* m_settingsForm;
        Rocket::Controls::ElementForm* m_musicForm;
        Rocket::Controls::ElementForm* m_soundForm;
        Rocket::Controls::ElementFormControlSelect* m_langSelect;

    public:
        enum {
            STATE_DEFAULT,
            STATE_SLOTS,
            STATE_SLOT_CONFIRM,
            STATE_SETTINGS,
            STATE_TEST
        };
 
    private:
        AppStateMain();
        void ChangeState(int newState, int oldState);
        void OnKeyDown(SDL_Scancode scancode, SDL_Keycode sym, Uint16 mod);
 
    public:
        void OnActivate(SDL_Renderer* renderer);
        void OnDeactivate();
        void OnLoop();
        void OnRender(SDL_Renderer* renderer);
        void DisplaySlot(int slotIndex);
        void Update();
 
    public:
        static AppStateMain* GetInstance();
};
 
#endif
