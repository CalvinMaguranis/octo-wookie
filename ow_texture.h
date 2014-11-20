// ow_texture.h
#ifndef __OW_TEXTURE_CLASS_H
#define __OW_TEXTURE_CLASS_H

class ow_texture {
public:
	// ctor/dtor
	ow_texture();
	// can optionally initialize with a file
	ow_texture(SDL_Renderer *r, std::string path);
	~ow_texture();

	// loads a new texture and stores it in this class
	// these can be used to overwrite existing textures
	bool load_file(SDL_Renderer *ren, std::string path);
	bool load_memory(SDL_Texture *t);
	bool load_surface(SDL_Surface *s);

	// Renders texture clip at point (x,y), leave clip
	// blank to default to NULL
	void render(SDL_Renderer *ren, int x, int y, SDL_Rect *clip=NULL);

	// accessors
	int get_width() { return _width; }
	int get_height() { return _height; }

	// deallocate texture
	void free();
private:
	SDL_Texture *_texture;
	int _width;
	int _height;
};

#endif // __OW_TEXTURE_CLASS_H
