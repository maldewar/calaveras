#include "CApp.h"

void CApp::OnLoop() {
    AppStateManager::OnLoop();
    CFPS::FPSControl.OnLoop();
    //char Buffer[255];
    //sprintf(Buffer, "FPS: %d", CFPS::FPSControl.GetFPS());
    //SDL_WM_SetCaption(Buffer, Buffer);
}
