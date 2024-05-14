#ifndef BITKI_H
#define BITKI_H

#include "Canli.h"

struct BITKI {
    Canli base;
    void (*yoket)(struct BITKI*);
};
typedef struct BITKI* Bitki;

Bitki OlusturucuBitki(int, int);
char* GorunumBitki();
void YokediciBitki(const Bitki);

#endif // BITKI_H
