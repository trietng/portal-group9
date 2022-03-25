#include "display.h"

void clrscr() {
    #ifdef _WIN32
        std::system("cls");
    #else
        // Assume POSIX
        std::system("clear");
    #endif
}

void thread_sleep(const unsigned int& time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

