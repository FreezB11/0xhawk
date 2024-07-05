#include <iostream>

#ifdef _WIN32
    #include "windows_specific.h"
#elif __linux__
    #include "linux_specific.h"
#else
    #error "Unknown operating system"
#endif

int main() {
    #ifdef _WIN32
        std::cout << "Running on Windows." << std::endl;
        // Call a function from windows_specific.h
        windows_specific_function();
    #elif __linux__
        std::cout << "Running on Linux." << std::endl;
        // Call a function from linux_specific.h
        linux_specific_function();
    #endif

    return 0;
}
