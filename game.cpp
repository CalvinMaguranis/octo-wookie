// stdlib
#include <iostream>
#include <string>

// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// utils
#include "ow_error.hpp"
#include "ow_types.hpp"

#include "game.hpp"
#include "ow_texture.hpp"

namespace ow
{
	SDL_Rect foo_frames[] = {
		{ 0, 0, 64, 205 },
		{ 64, 0, 64, 205 },
		{ 128, 0, 64, 205 },
		{ 192, 0, 64, 205 },
	};

	Game::~Game()
	{
		all_quit();
	}

	// handles game state 
	void Game::loop()
	{
		if (init("test SDL", win_width, win_height))
		{
			if (load_font("UbuntuMono-R.ttf") == false) {
				std::cout << "Font loading failed!" << std::endl;
				all_quit();
				return;
			}

			ow_texture player_sprite(_r, "foo.png");			
			ow_texture background(_r, "simpsons.png");
			ow_texture doh(_r, "doh.png");
			doh.blend_mode(SDL_BLENDMODE_BLEND);
			ow_texture msg(_r, _f, "fuck font rendering!");

			const int ms_per_frame = 1000 / max_fps;

			const int frames = sizeof(foo_frames) / sizeof(foo_frames[0]);
			const int sprite_x = player_sprite.width() / frames;
			const int s_x = (win_width - sprite_x) / 2;
			const int s_y = (win_height - player_sprite.height()) / 2;

			bool q = false;

			int dt = 0, count = 0, f = 0;
			ui8 alpha = 0;
			si8 add = 4;
			
			while (!q) {
				const int start_t = SDL_GetTicks();
				if (count >= max_fps - 1) {
					count = 0;
				}
				if (alpha <= 0) {
					alpha = 255;
					add = 4;
				} else if (alpha >= 254) {
					alpha = 0;
					add = -4;
				}
				alpha += add;
				doh.alpha(alpha);

				q = handle_input();

				// update sprite frame
				if (count % (max_fps / frames) == 0) {
					f = count / (max_fps / frames);
				}
				//DEBUG_PRINT("Frame: " << f << ", alpha: " << (int)alpha);

				// render everything for time dt
				SDL_RenderClear(_r);

				background.render(_r, 0, 0, NULL);
				doh.render(_r, (win_width - doh.width()),
					(win_height - doh.height()), NULL);
				player_sprite.render(_r,
					s_x, s_y, &foo_frames[f]);
				msg.render(_r, (win_width - msg.width()) / 2, (win_height - msg.width()) / 2);
				
				SDL_RenderPresent(_r);
				count++;

				// spin our wheels...
				dt = SDL_GetTicks() - start_t;
				if (dt < ms_per_frame) {
					SDL_Delay(ms_per_frame - dt);
				}
			}
		}
		else {
			DEBUG_PRINT("Game::init() failed");
		}
		all_quit();
	}

	bool Game::load_font(std::string font, const int pt)
	{
		_f = TTF_OpenFont(font.c_str(), pt);
		if (_f == NULL) {
			return false;
		}
		return true;
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
			return false;
		}

		if (TTF_Init() != 0) {
			log_error(std::cout, "TTF_Init()");
			return false;
		}

		const int m_flags = MIX_INIT_OGG | MIX_INIT_MP3;
		if ((Mix_Init(m_flags) & m_flags) != m_flags) {
			log_error(std::cout, "Mix_Init()");
			return false;
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
			SDL_DestroyWindow(_w);
			all_quit();
			return false;
		}

		return true;
	}

	void Game::all_quit()
	{
		if (_f != NULL) {
			TTF_CloseFont(_f);
			_f = NULL;
		}
		if (_r != NULL) {
			SDL_DestroyRenderer(_r);
			_r = NULL;
		}
		if (_w != NULL) {
			SDL_DestroyWindow(_w);
			_w = NULL;
		}

		Mix_Quit();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	bool Game::handle_input()
	{
		SDL_Event e;
		bool quit = false;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		return quit;
	}



} // namespace ow