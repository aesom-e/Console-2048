#include <stdio.h>

#ifndef PRINTTOOLS_H
#define PRINTTOOLS_H

#ifdef _WIN32
    #include <windows.h>
    #define RED     12
    #define ORANGE  6
    #define YELLOW  14
    #define GREEN   10
    #define BLUE    9
    #define PURPLE  5
    #define PINK    13
    #define WHITE   15
    #define GREY    8
    #define BLACK   0
#elif __linux__
    #define RED     "\033[1;31m"
    #define ORANGE  "\033[1;33m"
    #define YELLOW  "\033[1;33m"
    #define GREEN   "\033[1;32m"
    #define BLUE    "\033[1;34m"
    #define PURPLE  "\033[1;35m"
    #define PINK    "\033[1;35m"
    #define WHITE   "\033[1;37m"
    #define GREY    "\033[1;30m"
    #define BLACK   "\033[1;30m"
#endif

void setColour(const char* colourCode) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (WORD)colourCode);
    #elif __linux__
        printf("%s", colourCode);
    #endif
}

void clearConsole() {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        DWORD written;
        COORD topLeft = {0, 0};
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(console, &bufferInfo);
        FillConsoleOutputCharacterA(console, ' ', bufferInfo.dwSize.X * bufferInfo.dwSize.Y, topLeft, &written);
        FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, bufferInfo.dwSize.X * bufferInfo.dwSize.Y, topLeft, &written);
        SetConsoleCursorPosition(console, topLeft);
    #elif __linux__
        printf("\033[2J\033[1;1H");
    #endif
}

#endif
