#ifndef __GAME_CLASS_H
#define __GAME_CLASS_H

struct SDL_Window;
struct SDL_Renderer;
//struct TTF_Font;

namespace ow
{
	class Game {
	public:
		Game() : max_fps(60), win_width(640), win_height(480),
			__IMG_INIT_ALL(0xF), /* IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP */
			__SDL_RENDERER_USE_HW_DRIVERS(-1)
		{}
		~Game();

		void loop();
		SDL_Renderer *get_ren() { return _r; }
	private:
		const int max_fps;
		const int win_width;
		const int win_height;

		bool quit;
		SDL_Window   *_w;
		SDL_Renderer *_r;

		const int __IMG_INIT_ALL;
		const int __SDL_RENDERER_USE_HW_DRIVERS;

		// sets up window and default renderer
		bool init(const char * label, int width, int height);
		bool handle_input();
		bool load_font(std::string font, const int pt=20);

		void all_quit();
	};

} // namespace ow

#endif // __GAME_CLASS_H