#ifndef _CFILE_H_
    #define _CFILE_H_
#include <SDL.h>
#include <string>
class CFile {
    private:
        CFile();

    public:
        static std::string ReadText(const char* filePath);
        static std::string ReadText(std::string filePath);
};
#endif
