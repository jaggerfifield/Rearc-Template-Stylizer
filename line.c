#include <stdlib.h>
#include <SDL2/SDL.h>

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

line_t* make_line(int x, int y, int size){
	line_t* new_line = (line_t*)malloc(sizeof(line_t));

	new_line->x = x;
	new_line->y = y;

	new_line->a = 0.0;
	new_line->b = 50;
	new_line->scale = 1.0;

	new_line->size = size;

	SDL_Color col;
	col.r = 0;
	col.g = 0;
	col.b = 255;
	col.a = 255;

	new_line->color = col;
	new_line->points = (SDL_Point*)malloc(8*size);

	return new_line;
}

void set_a(line_t* line, float a){
	line->a = a;
}

void set_scale(line_t* line, float scale){
	line->scale = scale;
}

void draw_line(line_t* line, SDL_Point* points){

	for(int i = 0; i < line->size; i++){
		SDL_Point point;
		point.x = i;
		point.y = line->scale * (line->a * (i*i) ) + line->b;

		points[i] = point;
	}
	return;
}

void render_line(line_t* line){
	for(int i = 0; i < line->size; i++){
		SDL_Point point;
		point.x = i;
		point.y = line->scale * (line->a * (i*i) ) + line->b;
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
