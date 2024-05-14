#include "Canli.h"

Canli OlusturucuCanli(int guc, int tip){
	Canli canli;
	canli = (Canli)malloc(sizeof(struct CANLI));
	canli->guc = guc;
	canli->tip = tip;
	canli->yoket = &YokediciCanli;

	return canli;
}

void YokediciCanli(const Canli canli){
	if(canli == NULL)
		return;
	free(canli);
}