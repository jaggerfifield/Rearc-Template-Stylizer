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
	
	keys->SHIFT = false;
}

void free_keys(keys_t* keys){
	free(keys);
	keys = NULL;
}
