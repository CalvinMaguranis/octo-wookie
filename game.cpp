// stdlib
#include <iostream>
#include <string>

// SDL
#include <SDL.h>
#include <SDL_image.h>

// utils
//#include "cleanup.h"
#include "ow_error.hpp"

#include "game.hpp"
#include "ow_texture.hpp"

SDL_Rect foo_frames[] = {
	{ 0,   0, 64, 205 },
	{ 64,  0, 64, 205 },
	{ 128, 0, 64, 205 },
	{ 192, 0, 64, 205 },
};

// handles game state 
void Game::loop() 
{
	if (init("test SDL", win_width, win_height))
	{
		ow_texture player_sprite(_r, "foo.png");
		ow_texture background(_r, "simpsons.png");
		
		const int ms_per_frame = 1000 / max_fps;
		const int frames = sizeof(foo_frames) / sizeof(foo_frames[0]);
		const int sprite_x = player_sprite.get_width() / frames;
		const int s_x = (win_width - sprite_x) / 2;
		const int s_y = (win_height - player_sprite.get_height()) / 2;

		bool q = false;

		int dt = 0, count = 0, f=0;
		while (!q) {
			if (count > max_fps-1) {
				count = 0;
			}

			const int start_t = SDL_GetTicks();
			q = handle_input();

			// update sprite frame
			if (count % (max_fps / frames) == 0) {
				f = count / (max_fps / frames);
			}
			
			// render everything for time dt
			SDL_RenderClear(_r);
			background.render(_r, 0, 0, NULL);
			player_sprite.render(_r,
				s_x, s_y, &foo_frames[f]);
			SDL_RenderPresent(_r);
			count++;

			// spin our wheels...
			dt = SDL_GetTicks() - start_t;
			if (dt < ms_per_frame) {
				SDL_Delay(ms_per_frame - dt);
			}
		}
	}

	SDL_DestroyRenderer(_r);
	SDL_DestroyWindow(_w);
	all_quit();
}

// sets up window and default renderer
bool Game::init(const char * label, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//		log_error(std::cout, "SDL_Init()");
		return false;
	}

	if ((IMG_Init(__IMG_INIT_ALL) & __IMG_INIT_ALL) != __IMG_INIT_ALL) {
//		log_error(std::cout, "IMG_Init()");
	}

	_w = SDL_CreateWindow(label, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (_w == nullptr) {
//		log_error(std::cout, "SDL_CreateWindow()");
		all_quit();
		return false;
	}

	_r = SDL_CreateRenderer(_w, __SDL_RENDERER_USE_HW_DRIVERS,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_r == nullptr) {
//		log_error(std::cout, "SDL_CreateRenderer(bg)");
		
		all_quit();
		return false;
	}

	return true;
}

bool Game::handle_input()
{
	SDL_Event e;
	bool quit = false;
	while (SDL_PollEvent(&e)) {
		if ((e.type == SDL_QUIT) ||
			(e.type == SDL_MOUSEBUTTONDOWN) ||
			(e.type == SDL_KEYDOWN)) {
			quit = true;
		}
	}
	return quit;
}

void Game::all_quit()
{
	IMG_Quit();
	SDL_Quit();
}