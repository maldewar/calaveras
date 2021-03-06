#include "CApp.h"
#include "Util/TextureUtil.h"
#include "Util/Text.h"

void CApp::OnRender(SDL_Renderer* Renderer) {
    SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(Renderer);
    SDL_SetRenderDrawColor(Renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    //SDL_RenderDrawLine(Renderer, 0, 0, 500, 500);
    //TextureUtil::OnDraw(0, 0, m_text, Renderer);

    SDL_Rect DestR;
    DestR.x = 0;
    DestR.y = 0;
    //SDL_BlitSurface(m_text, NULL, m_surface, &DestR);

    AppStateManager::OnRender(Renderer);
    TextureUtil::OnDraw(0, 0, m_text, Renderer);
    /* Update the screen! */
    SDL_RenderPresent(Renderer);
    //SDL_Delay(10);
    if (FPSManager::Limit() == true) {
        char fpsText[32];
        sprintf(fpsText,"FPS: %i, Ticks: %i",FPSManager::GetFPS(), SDL_GetTicks());
        m_text = Text::GetTextureSolid(fpsText, "font/SourceSansPro-Regular.ttf", {255,255,0,255}, 22, Renderer);
        //std::string fileContent = File::ReadText("test.json");
        //m_text = Text::GetTextureSolid(fileContent.c_str(), "font/SourceSansPro-Regular.ttf", {255,255,0,255}, 22, Renderer);
    }
}
