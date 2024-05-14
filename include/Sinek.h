#ifndef SINEK_H
#define SINEK_H

#include "Canli.h"

struct SINEK {
    Canli base;
    void (*yoket)(struct SINEK*);
};
typedef struct SINEK* Sinek;

Sinek OlusturucuSinek(int, int);
char* GorunumSinek();
void YokediciSinek(const Sinek);

#endif // SINEK_H
