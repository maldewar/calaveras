#ifndef _CLOG_H_
    #define _CLOG_H_
#include <android/log.h>
#include <string>
class CLog {
    private:
        CLog();

    public:
        static void Log(const char *fmt, ...);
        static void Log(const std::string fmt, ...);
};
#endif
