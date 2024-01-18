//#include "keys.h"

typedef struct settings{
	bool quit;
	bool draw;

	keys_t* keys;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
} settings_t;

int call_program(SDL_Window*);
