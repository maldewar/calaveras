#include "CApp.h"

void CApp::OnLoop() {
    AppStateManager::OnLoop();
    FPS::FPSControl.OnLoop();
    //char Buffer[255];
    //sprintf(Buffer, "FPS: %d", FPS::FPSControl.GetFPS());
    //SDL_WM_SetCaption(Buffer, Buffer);
}
