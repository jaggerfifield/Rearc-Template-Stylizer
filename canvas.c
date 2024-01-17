#ifdef Windows_NT
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "line.h"

#define MAX_POINTS 1920

void draw(SDL_Window*, bool*);
void event(SDL_Window*, bool*);
void update();

int call_program(SDL_Window* window){
	bool* p_draw = (bool*) malloc(sizeof(bool));
	bool* p_quit = (bool*) malloc(sizeof(bool));
	*p_quit = false;
	*p_draw = true;

	while(!*p_quit){
		if(*p_draw)
			draw(window, p_draw);
		event(window, p_quit);
		update();
	}

	free(p_draw);
	free(p_quit);
	p_quit = NULL;
	p_draw = NULL;

	return 0;
}

void draw(SDL_Window* window, bool* draw){
	SDL_Renderer* render = SDL_GetRenderer(window);
	
	int top, left, bottom, right;

	if(SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right) != 0)
		SDL_LogError(0, "Border size problem! %s", SDL_GetError());

	SDL_LogInfo(0, "Border is of size (%d, %d, %d, %d)", top, left, bottom, right);

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

	if(SDL_SetRenderDrawColor(render, c.r, c.g, c.b, c.a) != 0){
		SDL_LogError(0, "Could not set draw color. %s", SDL_GetError());
	}

	SDL_RenderClear(render);

	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

	SDL_RenderDrawPoints(render, points, MAX_POINTS);
	SDL_RenderDrawPoints(render, center_line, 1080);
	SDL_RenderDrawPoints(render, prab, 1920);

	SDL_SetRenderDrawColor(render, 0,0,255,255);
	SDL_RenderDrawPoints(render, my_line->points, my_line->size);

	// Push to screen
	SDL_RenderPresent(render);
	
	*draw = false;
}

void event(SDL_Window* window, bool* quit){
	SDL_Event e;

	while(SDL_PollEvent(&e) != 0){
		
		switch(e.type){
			case SDL_QUIT:
				*quit = true;
				break;
			case 1024:
				// Mouse move
				break;
			case 512:
				// Active window toggle
				break;
			default:
				printf("%d\n", e.type);
				break;
		}
	}
}

void update(){
	return;
}
