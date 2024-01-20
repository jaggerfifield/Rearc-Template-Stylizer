//#include "keys.h"

typedef struct node{
	line_t* line;
	void* next;
}node_t;

typedef struct settings{
	int width;
	int height;

	int mouse_x;
	int mouse_y;

	int cap_mouse_x;
	int cap_mouse_y;

	bool quit;
	bool draw;

	bool curve_line;
	bool move_line;

	keys_t* keys;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;

	line_t* selected;
	node_t* layer;
} settings_t;


int call_program(SDL_Window*);

