#ifdef Windows_NT
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include <stdbool.h>

#include "keys.h"
#include "canvas.h"

bool init(void);
int cleanup(int, SDL_Window*, SDL_Renderer*);

int main( void ){

	SDL_LogInfo(0,"Let's do this~");
	SDL_LogInfo(0,"Staritng init stage.");

	if(!init())
		return -1;

	SDL_DisplayMode mode;
	if(SDL_GetDesktopDisplayMode(0, &mode) != 0){
		SDL_LogError(0,"SDL, could not generate display! %s", SDL_GetError());
		return -1;
	}

	SDL_LogInfo(0,"Found window size (%d x %d)", mode.w, mode.h);

	SDL_Window* window = NULL;
	SDL_Renderer* render = NULL;

	if(SDL_CreateWindowAndRenderer(mode.w, mode.h, SDL_WINDOW_SHOWN, &window, &render) < 0){
		SDL_LogError(0,"SDL could not create window/renderer! %s", SDL_GetError());
		return -1;
	}

	if(window == NULL || render == NULL){
		SDL_LogError(0,"Window or renderer is NULL! %s", SDL_GetError());
		return -1;
	}

	SDL_LogInfo(0, "Done with init! ;p");

	// goto the program loop here!
	int return_val = call_program(window);

	SDL_LogInfo(0,"Enter cleanup.");
	
	return cleanup(return_val, window, render);
}

bool init(){
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		success = false;
		SDL_LogError(0,"SDL could not init! %s", SDL_GetError());
	}

	return success;
}

int cleanup(int err, SDL_Window* window, SDL_Renderer* render){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	
	window = NULL;
	render = NULL;

	SDL_LogInfo(0,"All done, goodbye~");
	
	SDL_Quit();

	return err;
}
