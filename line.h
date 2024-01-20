typedef struct line{
	// IntX and IntY are the location of the line
	int x;
	int y;

	// a is the coefficient
	float a;
	int b;
	int c;

	float prev_a;
	int prev_b;
	int prev_c;

	// scale is a general scaleing factor
	float scale;

	int size;

	SDL_Color color;
	SDL_Point* points;
} line_t;

line_t* make_line(int, int, int);
void render_line(line_t*);

void set_a(line_t*, float);
void set_scale(line_t*, float);

void free_line(line_t*);
