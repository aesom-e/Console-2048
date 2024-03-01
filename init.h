#include <stdlib.h>
#include <time.h>

#ifndef INIT_H
#define INIT_H

void init() {
    srand(time(NULL));
}

#endif