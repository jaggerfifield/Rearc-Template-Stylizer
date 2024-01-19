//#include "keys.h"

typedef struct node{
	line_t* line;
	void* next;
}node_t;

typedef struct settings{
	bool quit;
	bool draw;

	keys_t* keys;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;

	line_t* selected;
	node_t* layer;
} settings_t;


int call_program(SDL_Window*);
