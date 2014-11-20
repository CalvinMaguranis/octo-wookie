#ifndef __GAME_CLASS_H
#define __GAME_CLASS_H


class Game {
public:
	Game();
	~Game();

	void loop();
	SDL_Renderer *get_ren() { return _r; }
private:
	bool quit;
	SDL_Window   *_w;
	SDL_Renderer *_r;

	const int __IMG_INIT_ALL = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	const int __SDL_RENDERER_USE_HW_DRIVERS = -1;

	// sets up window and default renderer
	bool init(const char * label, int width, int height);
	bool handle_input();

	void all_quit();
};

#endif // __GAME_CLASS_H

