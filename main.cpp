#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "game.hpp"

#if 0
// globals
const int __IMG_INIT_ALL = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
const int __SDL_RENDERER_USE_HW_DRIVERS = -1;
SDL_Window *win;
SDL_Renderer *ren;
SDL_Texture *bg;
SDL_Texture *fg;


// forward declarations
void all_quit();
bool handle_input();
std::string get_res_path(const std::string &path="");
bool init(const char * label, int width, int height);
SDL_Texture * load_texture(const std::string &file_path, SDL_Renderer *ren);
void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

/** <<<can't really beat this...>>>
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void log_error(std::ostream &os, const std::string &msg) 
{
	os << msg << " Error: " << SDL_GetError() << std::endl;
	SDL_Delay(5000);
}
#endif

int main(int argc, char** argv)
{
#if 0
    if (init("test SDL", 640, 480)==false) {
        return -1;
    } else {
		auto *player_sprite = load_texture("foo.png", ren);
		SDL_Rect sprite_info = { (640-64)/2, (480-205)/2, 64, 205 };
		SDL_Rect sprite_loc = { 0, 0, 64, 205 };


		const int max_fps = 60;
		const int ms_per_frame = 1000 / max_fps;
		bool q = false;

		/*
		SDL_RenderClear(ren);
		render_texture(bg, ren, 0, 0);
		render_texture(fg, ren, 0, 0);
		SDL_RenderCopy(ren, player_sprite, &sprite_info, &sprite_loc);
		SDL_RenderPresent(ren);
		*/

		int dt = 0, frame = 0, count = 0;
		while (!q) {
			if (count > max_fps) {
				count = 0;
			}

			const int start_t = SDL_GetTicks();
			q = handle_input();

			if (count % (max_fps / 4) == 0) {
				SDL_RenderClear(ren);
				render_texture(bg, ren, 0, 0);
				render_texture(fg, ren, 0, 0);
				SDL_RenderCopy(ren, player_sprite, &sprite_loc, &sprite_info);
				SDL_RenderPresent(ren);

				sprite_loc.x = frame*sprite_info.w;
				frame = (frame + 1) % 4;
				//std::cout << "sprite x: " << sprite_loc.x << std::endl;
			}
			count++;

			dt = SDL_GetTicks() - start_t;
			if (dt < ms_per_frame) {
				SDL_Delay(ms_per_frame - dt);
			}
		}

		cleanup(fg, bg, ren, win);
		all_quit();
    }
#endif

	Game game;
	game.loop();

    return 0;
}

#if 0
void all_quit() 
{
	IMG_Quit();
	SDL_Quit();
}



std::string get_res_path(const std::string &path)
{
    std::string base_path;
    const char *base = SDL_GetBasePath();
    if (base == nullptr) {
        // something went wrong
		log_error(std::cout, "SDL_GetBasePath()");
        return "";
    } else {
        base_path = base;
    }
    return base_path + path;
}

//log_error(std::ostream &os, const std::string &msg)
SDL_Texture * load_texture(const std::string &file_path, SDL_Renderer *ren) 
{
	auto *tex = IMG_LoadTexture(ren, file_path.c_str());
	if (tex == nullptr) {
		log_error(std::cout, "IMG_LoadTexture");
	}
	return tex;
}

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) 
{
	SDL_Rect dest;
	int w, h;
	if (SDL_QueryTexture(tex, NULL, NULL, &w, &h) != 0) {
		log_error(std::cout, "SDL_QueryTexture");
	}
	render_texture(tex, ren, x, y, w, h);
}

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	if (SDL_RenderCopy(ren, tex, NULL, &dest) != 0) {
		log_error(std::cout, "SDL_RenderCopy");
	}
}



void animate_player(SDL_Texture *sprite, SDL_Rect sprite_info, int fps, int dt) {
		
}
#endif