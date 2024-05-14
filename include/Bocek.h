#ifndef BOCEK_H
#define BOCEK_H

#include "Canli.h"

struct BOCEK {
    Canli base;
    void (*yoket)(struct BOCEK*);
};
typedef struct BOCEK* Bocek;

Bocek OlusturucuBocek(int, int);
char* GorunumBocek();
void YokediciBocek(const Bocek);

#endif // BOCEK_H
