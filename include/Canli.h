#ifndef CANLI_H
#define CANLI_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct CANLI {
    int guc; // guc
    int tip; // bitki, bocek, sinek, pire

    char* (*gorunum)();
    void (*yoket)(struct CANLI*);
};
typedef struct CANLI* Canli;

Canli OlusturucuCanli(int, int);
void YokediciCanli(const Canli);

#endif // CANLI_H
