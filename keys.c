#include <stdbool.h>
#include <stdlib.h>

#include "keys.h"

void purge_keys(keys_t*);

keys_t* init_keys( void ){
	keys_t* new_keys = (keys_t*)malloc(sizeof(keys_t));
	
	purge_keys(new_keys);

	return new_keys;
}

void purge_keys(keys_t* keys){
	keys->A = false;
	keys->B = false;
	keys->C = false;
	keys->D = false;
	keys->E = false;
	keys->F = false;
	keys->G = false;
	keys->H = false;
	keys->I = false;
	keys->J = false;
	keys->K = false;
	keys->L = false;
	keys->M = false;
	keys->N = false;
	keys->O = false;
	keys->P = false;
	keys->Q = false;
	keys->R = false;
	keys->S = false;
	keys->T = false;
	keys->U = false;
	keys->V = false;
	keys->W = false;
	keys->X = false;
	keys->Y = false;
	keys->Z = false;
	
	keys->SHIFT = false;
}

void free_keys(keys_t* keys){
	free(keys);
	keys = NULL;
}
