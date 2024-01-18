#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "keys.h"
#include "canvas.h"
#include "menu.h"

#define MAX_CHAR 32

menu_t* create_menu(settings_t* ps, int x, int y, int elements, bool horizontal, char* mfile){
	menu_t* new_menu = (menu_t*)malloc(sizeof(menu_t));
	int max_width = 0, max_height = 0;
	int x_offset = 0, y_offset = 0;

	new_menu->elements = elements;

	new_menu->horizontal = horizontal;
	
	SDL_Color fg;
	fg.r = 255;
	fg.b = 0;
	fg.g = 100;
	fg.a = 255;

	SDL_Color bg;
	bg.r = 10;
	bg.b = 100;
	bg.g = 10;
	bg.a = 100;

	new_menu->fg_color = fg;
	new_menu->bg_color = bg;

	new_menu->font = TTF_OpenFont("font/static/RobotoMono-ExtraLight.ttf", 150);

	new_menu->buttons = (button_t*)malloc(sizeof(button_t)*elements);

	FILE* file = fopen(mfile, "r");

	for(int i = 0; i < elements; i++){
		button_t new_button;
		
		SDL_Rect button_rect;
		button_rect.x = x + x_offset;
		button_rect.y = y + y_offset;

		SDL_Color font_col;

		font_col.r = 0;
		font_col.g = 0;
		font_col.b = 0;
		font_col.a = 255;
		
		new_button.color = font_col;

		new_button.text = (char*)malloc(sizeof(char)*MAX_CHAR);

		memset(new_button.text, '\0', MAX_CHAR);

		fgets(new_button.text, MAX_CHAR, file);

		new_button.surface = TTF_RenderText_Solid(new_menu->font, new_button.text, new_button.color);
		new_button.texture = SDL_CreateTextureFromSurface(ps->renderer, new_button.surface);

		if(horizontal)
			x_offset += new_button.surface->w;
		else
			y_offset += new_button.surface->h;

		button_rect.h = new_button.surface->h;
		button_rect.w = new_button.surface->w;

		new_button.rect = button_rect;
		
		if(new_button.surface->h > max_height)
			max_height = new_button.surface->h;
		if(new_button.surface->w > max_width)
			max_width = new_button.surface->w;

		new_menu->buttons[i] = new_button;
	}

	if(horizontal)
		max_width = max_width * elements;
	else
		max_height = max_height * elements;
	
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	
	rect.w = max_width;
	rect.h = max_height;

	new_menu->rect = rect;

	return new_menu;
}

void render_menu(settings_t* ps, menu_t* menu){
	SDL_Color fg = menu->fg_color;
	SDL_Color bg = menu->bg_color;
	SDL_Color sel = menu->sel_color;


	SDL_SetRenderDrawColor(ps->renderer, bg.r, bg.g, bg.b, bg.a);
	SDL_RenderFillRect(ps->renderer, &menu->rect);

	SDL_SetRenderDrawColor(ps->renderer, fg.r, fg.b, fg.g, fg.a);

	for(int i = 0; i < menu->elements; i++){
		SDL_RenderCopy(ps->renderer, menu->buttons[i].texture, NULL, &menu->buttons[i].rect);
		SDL_RenderDrawRect(ps->renderer, &menu->buttons[i].rect);
	}

	SDL_RenderDrawRect(ps->renderer, &menu->rect);
}

void free_menu(menu_t* menu){
	free(menu->buttons);
	menu->buttons = NULL;

	free(menu);
	menu = NULL;
}

