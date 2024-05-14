#include "Bitki.h"

Bitki OlusturucuBitki(int guc, int tip){
    Bitki bitki;
    bitki = (Bitki)malloc(sizeof(struct BITKI));
    bitki->base = OlusturucuCanli(guc, tip);
    bitki->base->gorunum = &GorunumBitki;
    bitki->yoket = &YokediciBitki;

    return bitki;
}

char* GorunumBitki(){
    return "B ";
}

void YokediciBitki(const Bitki bitki){
    if(bitki == NULL)
        return;
    bitki->base->yoket(bitki->base);
    free(bitki);
}

