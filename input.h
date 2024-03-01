#ifndef INPUT_H
#define INPUT_H

#ifdef _WIN32
#include <conio.h>
#elif __linux__
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#endif

char input() {
    char inputChar;
    #ifdef _WIN32
        inputChar = getch();
    #elif __linux__
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        inputChar = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #endif
    return inputChar;
}

#endif