#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "ow_error.hpp"
#include "ow_texture.hpp"

ow_texture::ow_texture() 
{
	_texture = nullptr;
	_width = 0;
	_height = 0;
}

ow_texture::ow_texture(SDL_Renderer *ren, std::string path) 
{
	load_file(ren, path);
}

ow_texture::~ow_texture()
{
	free();
}

bool ow_texture::load_file(SDL_Renderer *ren, std::string path)
{
	_texture = IMG_LoadTexture(ren, path.c_str());
	if (_texture == nullptr) {
		log_error(std::cout, "ow_texture::load_file");
		return false;
	} else {
		// get other parameters of the texture
		if (SDL_QueryTexture(_texture, 
		                     NULL, NULL, 
		                     &_width, &_height) != 0) {
			log_error(std::cout, "ow_texture::load_file::SDL_QueryTexture");
			return false;
		}
	}
	return true;
}

void ow_texture::render(SDL_Renderer *ren, int x, int y, SDL_Rect *clip)
{
	SDL_Rect render_quad = { x, y, _width, _height };
	if (clip != NULL) {
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}
	SDL_RenderCopy(ren, _texture, clip, &render_quad);
}

void ow_texture::free()
{
	if (_texture != nullptr) {
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
		_width = 0;
		_height = 0;
	}
}