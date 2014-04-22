#ifndef _LOG_H_
    #define _LOG_H_
#include <android/log.h>
#include <string>
class Log {
    private:
        Log();

    public:
        static void L(const char *fmt, ...);
        static void L(const std::string fmt, ...);
};
#endif
