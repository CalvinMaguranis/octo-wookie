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

#ifdef DICKING_AROUND

class Engine {
public:
	Engine();
	virtual ~Engine();

	void init();
	void loop();
	void update(int dt);
private:
	std::vector<System *>       s;
	std::vector<SDL_Window *>   w;
	std::vector<SDL_Renderer *> r;
};

class System {
public:
	System();
	virtual ~System();
private:
	// std::vector<Component *> c;
};

class Entity {
public:
	// ctor/dtor
	Entity();
	virtual ~Entity();

	// functions
	void add_component(Component c);
	void remove_component(int c_id);

	Component get_component(int c_id);
	bool has_component(int c_id);

	// members
	std::vector<int> components;
private:
};

class Component {
public:
	// ctor/dtor
	Component (int component_type) : type(component_type) {}
	virtual ~Component();

	// functions
	virtual void init();
	virtual void remove();

	// members
	int guid;
private:
};


#endif // will never be true...