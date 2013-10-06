#include "CApp.h"
 
CApp::CApp() {
    m_running = true;
    m_window = NULL;
    m_renderer = NULL;
    m_surface = NULL;
    m_texture = NULL;
    m_text = NULL;
}
 
int CApp::OnExecute() {
    if (OnInit() == false) {
        return -1;
    }
    SDL_Event Event;
    while(m_running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }
        OnLoop();
        OnRender(m_renderer);
    }
    OnCleanup();
    return 0;
}
 
int main(int argc, char* argv[]) {
    CApp theApp;
    return theApp.OnExecute();
}
