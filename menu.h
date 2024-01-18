typedef struct button{
	char* text;
	SDL_Rect rect;
	SDL_Color color;
	SDL_Surface* surface;
	SDL_Texture* texture;
} button_t;

typedef struct menu{
	int elements;
	int max_str;

	bool horizontal;

	SDL_Rect rect;

	SDL_Color fg_color;
	SDL_Color bg_color;
	SDL_Color sel_color;

	TTF_Font* font;

	button_t* buttons;

} menu_t;

menu_t* create_menu(settings_t*, int, int, int, bool, char*);
void render_menu(settings_t*, menu_t*);

