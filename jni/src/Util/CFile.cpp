#include "CFile.h"

CFile::CFile(){
};

std::string CFile::ReadText(const char* filePath) {
    std::string content;
    SDL_RWops* file = SDL_RWFromFile(filePath, "r");
    if (file == NULL) {
        content = "";
        return content;
    }
    char* destination = NULL;
    // Find the length of the file
    size_t fileLength = SDL_RWseek(file, 0, SEEK_END);
    destination = new char[fileLength+1]; // allow an extra character for '\0'
    // Reset seek to beginning of file and read text
    SDL_RWseek(file, 0, SEEK_SET);
    int n_blocks = SDL_RWread(file, destination, 1, fileLength);
    SDL_RWclose(file);
    // C strings should always be NULL terminated
    destination[fileLength] = '\0';
    content = destination;
    delete[] destination;
    // Success!
    return content;
};

std::string CFile::ReadText(std::string filePath) {
    return ReadText(filePath.c_str());
};
