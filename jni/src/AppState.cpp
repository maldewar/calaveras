#include "AppState.h"
#include "AppStateManager.h"
#include "Util/Log.h"

AppState::AppState() {
    m_rocketDocument = NULL;
    m_currentState = 0;
}

void AppState::LoadDocument(const char* documentName) {
    m_rocketDocument = AppStateManager::GetRocketContext()->LoadDocument(documentName);
    if (m_rocketDocument)
        m_rocketDocument->Show();
}

void AppState::UnloadDocument() {
    if (m_rocketDocument)
        m_rocketDocument->GetContext()->UnloadDocument(m_rocketDocument);
}

void AppState::UpdateDocument() {
    if (m_rocketDocument)
        m_rocketDocument->Update();
}

void AppState::RenderDocument() {
    if (m_rocketDocument)
        m_rocketDocument->Render();
}

void AppState::OnAfterEvent(SDL_Event* Event) {
    if (m_rocketDocument) {
        InjectRocket(AppStateManager::GetRocketContext(), *Event);
    }
}

void AppState::PushState(int state) {
    if (state != m_currentState) {
        m_stateStack.push(state);
        ChangeState(state, m_currentState);
        m_currentState = state;
        OnPushState(state);
    }
}

void AppState::PopState() {
    if (!m_stateStack.empty()) {
        int oldState, newState;
        oldState = m_stateStack.top();
        m_stateStack.pop();
        if (m_stateStack.empty())
            newState = 0;
        else
            newState = m_stateStack.top();
        m_currentState = newState;
        ChangeState(newState, oldState);
        OnPopState(oldState);
    }
}

void AppState::ClearStateStack() {
    while ( ! m_stateStack.empty() ) {
        m_stateStack.pop();
        m_currentState = 0;
    }
}

void AppState::ChangeState(const int newState, const int oldState) {
    //Pure virtual, do nothing
}

void AppState::OnPushState(int state) {
    //Pure virtual, do nothing
}

void AppState::OnPopState(int state) {
    //Pure virtual, do nothing
}

void AppState::SetParams(bool dummy, ...) {
    Log::L("AppState::SetParams");
    //Pure virtual, do nothing
}

void AppState::Update() {
    //Pure virtual, do nothing.
};
