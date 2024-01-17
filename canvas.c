#ifdef Windows_NT
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "line.h"
#include "keys.h"
#include "canvas.h"
#include "menu.h"

#define MAX_POINTS 1920

/*
typedef struct settings{
	bool quit;
	bool draw;

	keys_t* keys;

	SDL_Window* window;
	SDL_Renderer* renderer;
} settings_t;
*/

void draw(settings_t*);
void event(settings_t*);
void update(settings_t*);
void read_keys(settings_t*);
void handle_keyswap(SDL_Event, settings_t*, bool);

settings_t* init_settings(SDL_Window* window){
	settings_t* new_settings = (settings_t*)malloc(sizeof(settings_t));
	
	new_settings->window = window;
	new_settings->renderer = SDL_GetRenderer(window);
	
	keys_t* key_profile = init_keys();
	new_settings->keys = key_profile;

	new_settings->quit = false;
	new_settings->draw = true;
	return new_settings;
}

void free_settings(settings_t* settings){
	free(settings);
	settings = NULL;
}

int call_program(SDL_Window* window){
	settings_t* ps = init_settings(window);

	while(!ps->quit){
		if(ps->draw)
			draw(ps);
		event(ps);
		update(ps);
	}

	free_settings(ps);
	return 0;
}

void draw(settings_t* ps){
	int top, left, bottom, right;

	if(SDL_GetWindowBordersSize(ps->window, &top, &left, &bottom, &right) != 0)
		SDL_LogError(0, "Border size problem! %s", SDL_GetError());

	SDL_LogInfo(0, "Border is of size (%d, %d, %d, %d)", top, left, bottom, right);

	SDL_Point points[MAX_POINTS];
	SDL_Point center_line[1080];

	menu_t* add_menu = create_menu(0,0,2,"menus/eng/add.m");

	int middle = (int) (1920 / 2);

	// Build center line
	for(int i = 0; i < 1080; i++){
		SDL_Point point;
		point.x = middle;
		point.y = i;
		center_line[i] = point;
	}

	// Build linear line
	for(int i = 0; i < MAX_POINTS; i++){
		SDL_Point point;
		point.x = i;
		if(i > 1080-top-1)
			point.y = 1080 - top -1;
		else
			point.y = i;
		points[i] = point;
	}

	// Build parabola
	// y = ax^2 + b
	SDL_Point prab[1920];

	for(int i = 0; i < 1920; i++){
		int xp = i - middle;
		SDL_Point point;
		point.x = i;
		point.y = -floor((xp * xp)/1000) + 1080;
		prab[i] = point;
	}

	line_t* my_line = make_line(100,100,1920);
	set_a(my_line, 0.2);
	set_scale(my_line, 0.001);

	render_line(my_line);

	SDL_Color c;
	c.r = 255;
	c.g = 255;
	c.b = 255;
	c.a = 255;

	if(SDL_SetRenderDrawColor(ps->renderer, c.r, c.g, c.b, c.a) != 0){
		SDL_LogError(0, "Could not set draw color. %s", SDL_GetError());
	}

	SDL_RenderClear(ps->renderer);

	SDL_SetRenderDrawColor(ps->renderer, 255, 0, 0, 255);

	SDL_RenderDrawPoints(ps->renderer, points, MAX_POINTS);
	SDL_RenderDrawPoints(ps->renderer, center_line, 1080);
	SDL_RenderDrawPoints(ps->renderer, prab, 1920);

	SDL_SetRenderDrawColor(ps->renderer, 0, 255, 255, 255);
	render_menu(ps, add_menu);

	SDL_SetRenderDrawColor(ps->renderer, 0,0,255,255);
	SDL_RenderDrawPoints(ps->renderer, my_line->points, my_line->size);

	free_line(my_line);

	// Push to screen
	SDL_RenderPresent(ps->renderer);
	
	ps->draw = false;
}

void event(settings_t* ps){
	SDL_Event e;

	while(SDL_PollEvent(&e) != 0){
		
		switch(e.type){
			case SDL_QUIT:
				ps->quit = true;
				break;
			case 1024:
				// Mouse move
				break;
			case 512:
				// Active window toggle
				break;
			case SDL_KEYDOWN:
				// Key down
				handle_keyswap(e, ps, true);
				break;
			case SDL_KEYUP:
				// Key up
				handle_keyswap(e, ps, false);
			default:
				SDL_LogWarn(0,"Unknown event %d\n", e.type);
				break;
		}
	}
}

void handle_keyswap(SDL_Event e, settings_t* ps, bool swap){
	switch(e.key.keysym.sym){
		case SDLK_a:
			ps->keys->A = swap;
			break;
		case SDLK_LSHIFT:
			ps->keys->SHIFT = swap;
			break;
	}
}

void update(settings_t* ps){
	read_keys(ps);
	return;
}

void read_keys(settings_t* ps){
	keys_t* profile = ps->keys;

	// TODO can this be done better?
	if(profile->A && profile->SHIFT){
		profile->A = false;
	}
}
