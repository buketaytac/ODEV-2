#include "Sinek.h"

Sinek OlusturucuSinek(int guc, int tip){
    Sinek sinek;
    sinek = (Sinek)malloc(sizeof(struct SINEK));
    sinek->base = OlusturucuCanli(guc, tip);
    sinek->base->gorunum = &GorunumSinek;
    sinek->yoket = &YokediciSinek;

    return sinek;
}

char* GorunumSinek(){
    return "S ";
}

void YokediciSinek(const Sinek sinek){
    if(sinek == NULL)
        return;
    sinek->base->yoket(sinek->base);
    free(sinek);
}
