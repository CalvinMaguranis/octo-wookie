// stdlib
#include <iostream>
#include <string>

// SDL
#include <SDL.h>
#include <SDL_image.h>

// utils
#include "cleanup.h"
#include "ow_error.h"

#include "game.h"

// handles game state 
void Game::loop() 
{
	while (!quit) {

	}

	// cleanup();
	all_quit();
}

// sets up window and default renderer
bool Game::init(const char * label, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		log_error(std::cout, "SDL_Init()");
		return false;
	}

	if ((IMG_Init(__IMG_INIT_ALL) & __IMG_INIT_ALL) != __IMG_INIT_ALL) {
		log_error(std::cout, "IMG_Init()");
	}

	_w = SDL_CreateWindow(label, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (_w == nullptr) {
		log_error(std::cout, "SDL_CreateWindow()");
		all_quit();
		return false;
	}

	_r = SDL_CreateRenderer(_w, __SDL_RENDERER_USE_HW_DRIVERS,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_r == nullptr) {
		log_error(std::cout, "SDL_CreateRenderer(bg)");
		cleanup(_w);
		all_quit();
		return false;
	}

	return true;
}