#include "AppStateMain.h"
#include "AppStateManager.h"
#include "Manager/ConfigManager.h"
#include "Util/CLog.h"
#include "Util/RocketUtil.h"
#include "Event/EventChangeAppState.h"
#include "Event/EventChangeAppStateToGame.h"
#include "Event/EventSlotOnClick.h"
#include "Event/EventMusicOnClick.h"
#include "Event/EventSoundOnClick.h"
#include "Event/EventPushStateOnClick.h"
#include "Event/EventPopStateOnClick.h"
#include "Event/EventSetSettings.h"
 
AppStateMain AppStateMain::Instance;
 
AppStateMain::AppStateMain() {
    m_startTime = 0;
    m_slotIndex = 0;
}
 
void AppStateMain::OnActivate(SDL_Renderer* renderer) {
    m_startTime = SDL_GetTicks();
    LoadDocument("ui/main.html");
    if (m_rocketDocument) {
        EventChangeAppStateToGame* startOnClick = new EventChangeAppStateToGame(1,1);
        EventPushStateOnClick* continueOnClick = new EventPushStateOnClick(this, STATE_SLOTS);
        EventPopStateOnClick* returnOnClick = new EventPopStateOnClick(this);
        EventSlotOnClick* slot1OnClick = new EventSlotOnClick(this, 0);
        EventSlotOnClick* slot2OnClick = new EventSlotOnClick(this, 1);
        EventSlotOnClick* slot3OnClick = new EventSlotOnClick(this, 2);
        EventSlotOnClick* slot4OnClick = new EventSlotOnClick(this, 3);
        EventChangeAppStateToGame* test1OnClick = new EventChangeAppStateToGame(0,1);
        EventChangeAppStateToGame* test2OnClick = new EventChangeAppStateToGame(0,2);
        EventChangeAppStateToGame* test3OnClick = new EventChangeAppStateToGame(0,3);
        EventChangeAppStateToGame* test4OnClick = new EventChangeAppStateToGame(0,4);
        EventChangeAppStateToGame* test5OnClick = new EventChangeAppStateToGame(0,5);
        EventChangeAppStateToGame* test6OnClick = new EventChangeAppStateToGame(0,6);
        EventPushStateOnClick* settingsOnClick = new EventPushStateOnClick(this, STATE_SETTINGS);
        EventPushStateOnClick* testOnClick = new EventPushStateOnClick(this, STATE_TEST);
        EventSetSettings* setSettings = new EventSetSettings(this);
        setSettings->SetCallPopState(true);
        EventSetSettings* setSettingsNoPop = new EventSetSettings(this);

        // Select elements.
        m_startBtn = m_rocketDocument->GetElementById("startBtn");
        m_continueBtn = m_rocketDocument->GetElementById("continueBtn");
        m_loadBtn = m_rocketDocument->GetElementById("loadBtn");
        m_returnBtn = m_rocketDocument->GetElementById("returnBtn");
        m_slot1Btn = m_rocketDocument->GetElementById("slot1Btn");
        m_slot2Btn = m_rocketDocument->GetElementById("slot2Btn");
        m_slot3Btn = m_rocketDocument->GetElementById("slot3Btn");
        m_slot4Btn = m_rocketDocument->GetElementById("slot4Btn");
        m_test1Btn = m_rocketDocument->GetElementById("test1Btn");
        m_test2Btn = m_rocketDocument->GetElementById("test2Btn");
        m_test3Btn = m_rocketDocument->GetElementById("test3Btn");
        m_test4Btn = m_rocketDocument->GetElementById("test4Btn");
        m_test5Btn = m_rocketDocument->GetElementById("test5Btn");
        m_test6Btn = m_rocketDocument->GetElementById("test6Btn");
        m_settingsBtn = m_rocketDocument->GetElementById("settingsBtn");
        m_musicBtn = m_rocketDocument->GetElementById("musicBtn");
        m_soundBtn = m_rocketDocument->GetElementById("soundBtn");
        m_testBtn = m_rocketDocument->GetElementById("testBtn");
        m_mainContainer = m_rocketDocument->GetElementById("mainContainer");
        m_settingsContainer = m_rocketDocument->GetElementById("settingsContainer");
        m_slotContainer = m_rocketDocument->GetElementById("slotContainer");
        m_slotsContainer = m_rocketDocument->GetElementById("slotsContainer");
        m_testContainer = m_rocketDocument->GetElementById("testContainer");

        
        m_settingsForm = dynamic_cast<Rocket::Controls::ElementForm*>(m_rocketDocument->GetElementById("settingsForm"));
        m_musicForm = dynamic_cast<Rocket::Controls::ElementForm*>(m_rocketDocument->GetElementById("musicForm"));
        m_soundForm = dynamic_cast<Rocket::Controls::ElementForm*>(m_rocketDocument->GetElementById("soundForm"));
        m_langSelect = dynamic_cast<Rocket::Controls::ElementFormControlSelect*>(m_rocketDocument->GetElementById("langSelect"));
        
        if (m_startBtn)
            m_startBtn->AddEventListener("click", startOnClick, false);
        if (m_continueBtn)
            m_continueBtn->AddEventListener("click", continueOnClick, false);
        if (m_returnBtn)
            m_returnBtn->AddEventListener("click", returnOnClick, false);
        if (m_slot1Btn)
            m_slot1Btn->AddEventListener("click", slot1OnClick, false);
        if (m_slot2Btn)
            m_slot2Btn->AddEventListener("click", slot2OnClick, false);
        if (m_slot3Btn)
            m_slot3Btn->AddEventListener("click", slot3OnClick, false);
        if (m_slot4Btn)
            m_slot4Btn->AddEventListener("click", slot4OnClick, false);
        if (m_test1Btn)
            m_test1Btn->AddEventListener("click", test1OnClick, false);
        if (m_test2Btn)
            m_test2Btn->AddEventListener("click", test2OnClick, false);
        if (m_test3Btn)
            m_test3Btn->AddEventListener("click", test3OnClick, false);
        if (m_test4Btn)
            m_test4Btn->AddEventListener("click", test4OnClick, false);
        if (m_test5Btn)
            m_test5Btn->AddEventListener("click", test5OnClick, false);
        if (m_test6Btn)
            m_test6Btn->AddEventListener("click", test6OnClick, false);
        if (m_settingsBtn)
            m_settingsBtn->AddEventListener("click", settingsOnClick, false);
        if (m_musicBtn && !ConfigManager::IsMusicEnabled())
            m_musicBtn->SetClass("disabled", true);
        if (m_soundBtn && !ConfigManager::IsSoundEnabled())
            m_soundBtn->SetClass("disabled", true);
        if (m_testBtn)
            m_testBtn->AddEventListener("click", testOnClick, false);
        if (m_settingsForm)
            m_settingsForm->AddEventListener("submit", setSettings, false);
        if (m_musicForm)
            m_musicForm->AddEventListener("submit", setSettingsNoPop, false);
        if (m_soundForm)
            m_soundForm->AddEventListener("submit", setSettingsNoPop, false);
    }
}
 
void AppStateMain::OnDeactivate() {
    CLog::Log("AppStateMain::OnDeactivate");
    UnloadDocument();
    ClearStateStack();
};
 
void AppStateMain::OnLoop() {
    UpdateDocument();
};
 
void AppStateMain::OnRender(SDL_Renderer* renderer) {
    RenderDocument();
};

void AppStateMain::Update() {
    if (ConfigManager::IsMusicEnabled())
        m_musicBtn->SetClass("disabled", false);
    else
        m_musicBtn->SetClass("disabled", true);

    if (ConfigManager::IsSoundEnabled())
        m_soundBtn->SetClass("disabled", false);
    else
        m_soundBtn->SetClass("disabled", true);

    m_rocketDocument->UpdateLayout();
};
 
AppStateMain* AppStateMain::GetInstance() {
    return &Instance;
};

void AppStateMain::DisplaySlot(int slotIndex) {
    m_slotIndex = slotIndex;
    PushState(STATE_SLOT_CONFIRM);
};

void AppStateMain::ChangeState(int newState, int oldState) {
    switch(newState) {
        case STATE_DEFAULT:
            RocketUtil::Show(m_mainContainer);
            RocketUtil::Hide(m_settingsContainer);
            RocketUtil::Hide(m_slotsContainer);
            RocketUtil::Hide(m_slotContainer);
            RocketUtil::Hide(m_testContainer);
            RocketUtil::Show(m_continueBtn);
            break;
        case STATE_SLOTS:
            RocketUtil::Show(m_mainContainer);
            RocketUtil::Hide(m_continueBtn);
            RocketUtil::Show(m_slotsContainer);
            break;
        case STATE_SLOT_CONFIRM:
            RocketUtil::Hide(m_mainContainer);
            RocketUtil::Hide(m_settingsContainer);
            RocketUtil::Show(m_slotContainer);
            break;
        case STATE_SETTINGS:
            RocketUtil::Hide(m_mainContainer);
            RocketUtil::Show(m_settingsContainer);
            RocketUtil::Hide(m_testContainer);
            m_langSelect->SetValue(ConfigManager::GetLocale().c_str());
            break;
        case STATE_TEST:
            RocketUtil::Hide(m_mainContainer);
            RocketUtil::Hide(m_settingsContainer);
            RocketUtil::Show(m_testContainer);
            break;
    }
    if (newState == STATE_DEFAULT)
        RocketUtil::Hide(m_returnBtn);
    else
        RocketUtil::Show(m_returnBtn);
}

void AppStateMain::OnKeyDown(SDL_Scancode scancode, SDL_Keycode sym, Uint16 mod) {
    switch(scancode) {
        case SDL_SCANCODE_AC_BACK:
            PopState();
            break;
        case SDL_SCANCODE_MENU:
            break;
    }
}
