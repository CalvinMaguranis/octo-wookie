// drafting for ideas...later

// If you need more than 5, I'm astounded.
#define MAX_WINDOWS 5
#define MAX_RENDERERS MAX_WINDOWS

class Engine {
public:
	Engine();
	virtual ~Engine();

	void init();
	void loop();
	void update(int dt);
private:

	std::vector<System *>        s;
	SDL_Window[MAX_WINDOWS] * w;
	SDL_Renderer[MAX_RENDERERS] * r;
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
	void remove_component(int c_type);

	Component get_component(int c_type);
	bool has_component(int c_type);

	// members
	int handle;
	std::vector<int> components;
private:
};

class Component {
public:
	// ctor/dtor
	Component(int component_type) : type(component_type) {}
	virtual ~Component();

	// functions
	virtual void init();
	virtual void remove();

	// members
private:
};