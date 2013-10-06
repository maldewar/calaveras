#include "FPSManager.h"

FPSManager::FPSManager() {};

float FPSManager::maxFrameTicks = 0;
uint32_t FPSManager::lastSecondTicks = 0;
int FPSManager::frameCount = 0;
uint32_t FPSManager::minTicks = 0;
uint32_t FPSManager::maxTicks = 0;
double FPSManager::averageTicks = 0;
uint32_t FPSManager::lastFrameTicks = 0;
uint32_t FPSManager::currentTicks = 0;
uint32_t FPSManager::targetTicks = 0;
FPS_Data FPSManager::FPSData = {};

void FPSManager::Init() {
    maxFrameTicks = (1000.0/(float)FPS_MAX)+0.00001;
    frameCount = 0;
    lastSecondTicks = SDL_GetTicks();
};

bool FPSManager::Limit() {
    frameCount++;
    targetTicks = lastSecondTicks + Uint32(frameCount * maxFrameTicks);
    currentTicks = SDL_GetTicks();
    averageTicks += currentTicks - lastFrameTicks;
    if(currentTicks - lastFrameTicks <= minTicks) {
        minTicks = currentTicks - lastFrameTicks;
    }
    if(currentTicks - lastFrameTicks >= maxFrameTicks) {
        maxTicks = currentTicks - lastFrameTicks;
    }
    if(currentTicks<targetTicks) {
        SDL_Delay(targetTicks - currentTicks);
        currentTicks = SDL_GetTicks();
    }
    lastFrameTicks = currentTicks;
    if(currentTicks - lastSecondTicks >= 1000) {
        FPSData.FPS = frameCount;
        FPSData.frameAverage = averageTicks/frameCount;
        FPSData.frameMin = minTicks;
        FPSData.frameMax = maxTicks;
        frameCount=0;
        minTicks=1000;
        maxTicks=0;
        averageTicks=0;
        lastSecondTicks=SDL_GetTicks();
        return true;
    }
    return false;
};

int FPSManager::GetFPS() {
    return FPSData.FPS;
};
