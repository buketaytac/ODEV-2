#include "Bocek.h"

Bocek OlusturucuBocek(int guc, int tip){
    Bocek bocek;
    bocek = (Bocek)malloc(sizeof(struct BOCEK));
    bocek->base = OlusturucuCanli(guc, tip);
    bocek->base->gorunum = &GorunumBocek;
    bocek->yoket = &YokediciBocek;
    
    return bocek;
}

char* GorunumBocek(){
    return "C ";
}

void YokediciBocek(const Bocek bocek){
    if(bocek == NULL)
        return;
    bocek->base->yoket(bocek->base);
    free(bocek);
}
