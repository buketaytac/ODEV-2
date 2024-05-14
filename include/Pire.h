#ifndef PIRE_H
#define PIRE_H

#include "Canli.h"

struct PIRE {
    Canli base;
    void (*yoket)(struct PIRE*);
};
typedef struct PIRE* Pire;

Pire OlusturucuPire(int, int);
char* GorunumPire();
void YokediciPire(const Pire);

#endif // PIRE_H
