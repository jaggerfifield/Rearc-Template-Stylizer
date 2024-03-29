#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "line.h"
#include "keys.h"
#include "canvas.h"
#include "menu.h"

#define MAX_POINTS 1920

void draw(settings_t*);
void draw_test(settings_t*);
void event(settings_t*);
void update(settings_t*);
void update_mouse(settings_t*, SDL_Event);
void read_keys(settings_t*);
void handle_keyswap(SDL_Event, settings_t*, bool);
void create_line(settings_t*);

settings_t* init_settings(SDL_Window* window){
	settings_t* new_settings = (settings_t*)malloc(sizeof(settings_t));
	
	new_settings->window = window;
	new_settings->renderer = SDL_GetRenderer(window);
	
	new_settings->surface = SDL_GetWindowSurface(window);

	new_settings->width = new_settings->surface->w;
	new_settings->height = new_settings->surface->h;

	keys_t* key_profile = init_keys();
	new_settings->keys = key_profile;

	new_settings->quit = false;
	new_settings->draw = true;

	new_settings->curve_line = false;
	new_settings->move_line = false;

	line_t* base = make_line(new_settings->width/2,new_settings->height/2,new_settings->width);
	node_t* lines = malloc(sizeof(node_t));
	
	lines->line = base;
	lines->next = NULL;
	
	new_settings->selected = base;
	new_settings->layer = lines;

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
void draw_test(settings_t* ps){
	//menu_t* add_menu = create_menu(ps,0,0,2, false,"menus/eng/add.m");
	
	SDL_Point points[MAX_POINTS];
	SDL_Point center_line[1080];

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
		if(i > 1080-32-1)
			point.y = 1080 -32 -1;
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
	
	SDL_SetRenderDrawColor(ps->renderer, 255, 0, 0, 255);
	SDL_RenderDrawPoints(ps->renderer, points, MAX_POINTS);
	SDL_RenderDrawPoints(ps->renderer, center_line, 1080);
	SDL_RenderDrawPoints(ps->renderer, prab, 1920);
	
	SDL_RenderPresent(ps->renderer);

	ps->draw = false;
}

void draw(settings_t* ps){
	int top, left, bottom, right;

	if(SDL_GetWindowBordersSize(ps->window, &top, &left, &bottom, &right) != 0)
		SDL_LogError(0, "Border size problem! %s", SDL_GetError());

	SDL_LogInfo(0, "Border is of size (%d, %d, %d, %d)", top, left, bottom, right);
	SDL_SetRenderDrawColor(ps->renderer, 255, 255, 255, 255);

	SDL_RenderClear(ps->renderer);

	node_t* c = ps->layer;

	while(c != NULL){
		SDL_LogInfo(0,"Drawing a line!");
		if(SDL_SetRenderDrawColor(ps->renderer, c->line->color.r, c->line->color.g, c->line->color.b, c->line->color.a) != 0){
			SDL_LogError(0, "Could not set draw color. %s", SDL_GetError());
		}
		
		render_line(c->line);
		SDL_RenderDrawPoints(ps->renderer, c->line->points, c->line->size);
		c = c->next;
	}

	SDL_LogInfo(0, "Lines done");


	//SDL_SetRenderDrawColor(ps->renderer, 0, 255, 255, 255);
	//render_menu(ps, add_menu);
	
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
			case SDL_MOUSEMOTION:
				// Mouse move
				update_mouse(ps, e);
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

void update_mouse(settings_t* ps, SDL_Event e){
	ps->mouse_x = e.motion.x;
	ps->mouse_y = e.motion.y;
}

void handle_keyswap(SDL_Event e, settings_t* ps, bool swap){
	switch(e.key.keysym.sym){
		case SDLK_a:
			ps->keys->A = swap;
			break;
		case SDLK_c:
			  ps->keys->C = swap;
			  break;
		case SDLK_g:
			  ps->keys->G = swap;
			  break;
		case SDLK_l:
			ps->keys->L = swap;
			break;
		case SDLK_LSHIFT:
			ps->keys->SHIFT = swap;
			break;
	}
}

void update(settings_t* ps){
	read_keys(ps);
	
	if(ps->curve_line){
		float new_a = ps->selected->prev_a + (float) (ps->mouse_y - ps->cap_mouse_y)/ps->height;
		set_a(ps->selected, new_a);
		ps->draw = true;
	}

	if(ps->move_line){
		ps->selected->b = (ps->mouse_x - ps->cap_mouse_x) + ps->selected->prev_b;
		ps->selected->c = (ps->mouse_y - ps->cap_mouse_y) + ps->selected->prev_c;
		ps->draw = true;
	}

	return;
}

void read_keys(settings_t* ps){
	keys_t* profile = ps->keys;

	if(profile->menu){
		if(profile->L){
			SDL_LogInfo(0,"Create new line!");
			profile->L = false;
			profile->menu = false;
			create_line(ps);
		}
	}

	// TODO can this be done better?
	if(profile->A && profile->SHIFT){
		profile->menu = true;
		profile->A = false;
	}

	if(profile->C){
		ps->curve_line = !ps->curve_line;
		SDL_GetMouseState(&ps->cap_mouse_x, &ps->cap_mouse_y);
		ps->selected->prev_a = ps->selected->a;
		profile->C = false;
	}

	if(profile->G){
		ps->move_line = !ps->move_line;
		SDL_GetMouseState(&ps->cap_mouse_x, &ps->cap_mouse_y);
		ps->selected->prev_b = ps->selected->b;
		ps->selected->prev_c = ps->selected->c;
		profile->G = false;
	}
}

void create_line(settings_t* ps){
	line_t* new_line = make_line(0,ps->height/2,ps->width);

	node_t* next = malloc(sizeof(node_t));
	next->line = new_line;
	next->next = NULL;

	ps->selected = new_line;
	
	node_t* current = ps->layer;

	while(current->next != NULL)
		current = current->next;

	current->next = next;
	ps->draw = true;
}

