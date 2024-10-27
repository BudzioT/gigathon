#include "headers/utils.h"

#include <cstdlib>

// Clear the console considering the OS
void clearConsole() {
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined(__APPLE__)
    system("\033[2J\033[1;1H");
#endif
}

// Find nth occurrence of target text in a string
int nthOccurrence(const std::string& str, const std::string& target, int nth) {
    size_t pos = -1;
    while (nth--) {
        pos = str.find(target, pos + 1);
        if (pos == std::string::npos)
            return -1;
    }

    return (int)pos;
}