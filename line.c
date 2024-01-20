#include <stdlib.h>
#include <SDL2/SDL.h>

#include "line.h"
/*
typedef struct line{
	// IntX and IntY are the location of the line
	int x;
	int y;

	// a is the coefficient
	float a;
	int b;

	// scale is a general scaleing factor
	float scale;

	int size;

	SDL_Color color;
	SDL_Point* points;
} line_t;
*/

line_t* make_line(int x, int y, int size){
	line_t* new_line = (line_t*)malloc(sizeof(line_t));

	// Line x and y is calculated when rendered
	new_line->x = 0;
	new_line->y = 0;

	new_line->a = 0.0;
	new_line->prev_a = 0.0;
	new_line->b = x;
	new_line->c = y;
	new_line->scale = 0.001;

	new_line->prev_b = x;
	new_line->prev_c = y;

	new_line->size = size;

	SDL_Color col;
	col.r = 0;
	col.g = 0;
	col.b = 0;
	col.a = 255;

	new_line->color = col;
	new_line->points = (SDL_Point*)malloc(8*size);

	SDL_LogInfo(0, "Line control is at: (%d, %d)\n", new_line->b, new_line->c);

	return new_line;
}

void set_a(line_t* line, float a){
	line->a = a;
}

void set_b(line_t* line, int b){
	line->b = b;
}

void set_scale(line_t* line, float scale){
	line->scale = scale;
}

void set_pos(line_t* line, int x, int y){
	line->b = x;
	line->c = y;
}

void draw_line(line_t* line, SDL_Point* points){

	for(int i = 0; i < line->size; i++){
		SDL_Point point;
		point.x = i;

		points[i] = point;
	}
	return;
}

void render_line(line_t* line){
	for(int i = 0; i < line->size; i++){
		SDL_Point point;
		point.x = i;
		point.y = line->scale * (line->a * ((i-line->b)*(i-line->b)) ) + line->c;
		line->points[i] = point;
	}
}

void free_line(line_t* line){
	free(line->points);
	line->points=NULL;
	free(line);
	line = NULL;
	return;
}
