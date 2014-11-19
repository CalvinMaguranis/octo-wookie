#ifndef __GAME_CLASS_H
#define __GAME_CLASS_H


class Game {
public:
	Game();
	~Game();

	void loop();
	SDL_Renderer *get_ren() { return _renderer; }
private:
	bool quit;
	SDL_Window   *_game;
	SDL_Renderer *_renderer;

	// sets up window and default renderer
	bool init(const char * label, int width, int height);
	bool handle_input();
};

#endif // __GAME_CLASS_H