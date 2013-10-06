#ifndef _CFPSMANAGER_H_
    #define _CFPSMANAGER_H_

#define FPS_MAX 120

#include <SDL.h>
#include <stdint.h>

struct FPS_Data {
    uint32_t frameMin;
    uint32_t frameMax;
    double frameAverage;
    int FPS;
};

class FPSManager {
    private:
        FPSManager();

    private:
        static float maxFrameTicks;
        static uint32_t lastSecondTicks;
        static int frameCount;
        static uint32_t minTicks;
        static uint32_t maxTicks;
        static double averageTicks;
        static uint32_t lastFrameTicks;
        static uint32_t currentTicks;
        static uint32_t targetTicks;
        static FPS_Data FPSData;

    public:
        static void Init();
        static bool Limit();
        static int GetFPS();
};

#endif
