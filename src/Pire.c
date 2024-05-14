#include "Pire.h"

Pire OlusturucuPire(int guc, int tip){
    Pire pire;
    pire = (Pire)malloc(sizeof(struct PIRE));
    pire->base = OlusturucuCanli(guc, tip);
    pire->base->gorunum = &GorunumPire;
    pire->yoket = &YokediciPire;

    return pire;
}

char* GorunumPire(){
    return "P ";
}

void YokediciPire(const Pire pire){
    if(pire == NULL)
        return;
    pire->base->yoket(pire->base);
    free(pire);
}

