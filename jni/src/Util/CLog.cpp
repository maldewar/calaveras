#include "CLog.h"

CLog::CLog() {
};

void CLog::Log(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    char msg[512]; //TODO Text might overflow
    vsprintf(msg,fmt,ap);
    __android_log_print(ANDROID_LOG_INFO, "Calaveras", msg);
    va_end(ap);
};

void CLog::Log(const std::string fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    Log(fmt.c_str(), ap);
    va_end(ap);
};
