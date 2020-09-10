#include "crc32FileReader.hpp"

using namespace std;

uint32_t crc32(const string& filePath) {
    //reads the file as needed
    string s =  "";
    s += readFileContent(filePath);

    return crc32FromString(s);
}

uint32_t crc32FromString(const string& file) {
    //because of /0
    unsigned int length = file.length() + 1;

   // declaring character array 
    char *buffer = new char[length];

    // copying the contents of the 
    // string to char array 
    strcpy(buffer, file.c_str());

    //calculating crc32
    uint32_t result = crc32((unsigned char *) buffer, length -1);

    //deletes the buffer 
    delete[] buffer;
    return result;
}