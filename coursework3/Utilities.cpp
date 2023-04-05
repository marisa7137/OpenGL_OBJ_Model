#include "Utilities.h"

int countInteger(std::string s)
{
    std::istringstream ss(s);
    std::string word;
    int counter = 0;
    while (ss >> word)
    {
        size_t i = 0;
        while (i < word.size()) {
            if (isdigit(word[i]))
            {
                counter++;
                while (isdigit(word[i]) && i < word.size())
                {
                    i++;
                }
            }
            else {
                i++;
            }
        }
    }
    return counter;
}

char* read_file(const char* filename)
{
    FILE* f;
    fopen_s(&f, filename, "rb");
    if (f == NULL)
        return NULL;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    char* bfr = (char*)malloc(sizeof(char) * (size + 1));
    if (bfr == NULL)
        return NULL;
    long ret = fread(bfr, 1, size, f);
    if (ret != size)
        return NULL;
    bfr[size] = '\0';
    return bfr;
}