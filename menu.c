#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "canvas.h"
#include "menu.h"

#define MAX_CHAR 32

menu_t* create_menu(int x, int y, int elements, char* mfile){
	menu_t* new_menu = (menu_t*)malloc(sizeof(menu_t));
	int max_str = 0;

	new_menu->elements = elements;

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;

	rect.w = 100;
	rect.h = 200;

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

	new_menu->rect = rect;

	new_menu->buttons = (button_t*)malloc(sizeof(button_t)*elements);

	FILE* file = fopen(mfile, "r");

	for(int i = 0; i < elements; i++){
		button_t new_button;
		new_button.text = (char*)malloc(sizeof(char)*MAX_CHAR);

		memset(new_button.text, '\0', MAX_CHAR);

		fgets(new_button.text, MAX_CHAR, file);

		int t = strlen(new_button.text);

		if(t > max_str)
			max_str = t;

		printf("Max str is %d\n", max_str);

		new_menu->buttons[i] = new_button;
	}

	return new_menu;
}

void render_menu(settings_t* ps, menu_t* menu){
	SDL_Color fg = menu->fg_color;
	SDL_Color bg = menu->bg_color;
	SDL_Color sel = menu->sel_color;


	SDL_SetRenderDrawColor(ps->renderer, bg.r, bg.g, bg.b, bg.a);
	SDL_RenderFillRect(ps->renderer, &menu->rect);
	
	SDL_SetRenderDrawColor(ps->renderer, fg.r, fg.b, fg.g, fg.a);
	SDL_RenderDrawRect(ps->renderer, &menu->rect);
}

void free_menu(menu_t* menu){
	free(menu->buttons);
	menu->buttons = NULL;

	free(menu);
	menu = NULL;
}

