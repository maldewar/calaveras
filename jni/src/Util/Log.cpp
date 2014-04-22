#include "Log.h"

Log::Log() {
};

void Log::L(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    char msg[1024]; //TODO Text might overflow //25/11/2013 and when it does, it crashes the app...
    vsprintf(msg,fmt,ap);
    __android_log_print(ANDROID_LOG_INFO, "Calaveras", msg);
    va_end(ap);
};

void Log::L(const std::string fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    L(fmt.c_str(), ap);
    va_end(ap);
};
