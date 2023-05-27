#include <iostream>

int main()
{
    #ifdef _WIN32
        system("bin/windows.exe");
    #elif __linux__
        system("./bin/linux.bin");
    #else
        std::cout << "Unsupported operating system" << std::endl;
    #endif

    return 0;
}