typedef struct button{
	char* text;
	SDL_Rect rect;

} button_t;

typedef struct menu{
	int elements;
	int max_str;

	SDL_Rect rect;

	SDL_Color fg_color;
	SDL_Color bg_color;
	SDL_Color sel_color;

	button_t* buttons;

} menu_t;

menu_t* create_menu(int, int, int, char*);
void render_menu(settings_t*, menu_t*);

