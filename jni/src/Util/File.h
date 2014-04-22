#ifndef _FILE_H_
    #define _FILE_H_
#include <SDL.h>
#include <string>
class File {
    private:
        File();

    public:
        static std::string ReadText(const char* filePath);
        static std::string ReadText(std::string filePath);
};
#endif
