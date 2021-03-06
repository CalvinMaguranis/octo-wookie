// stdlib
#include <iostream>
#include <string>

// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// utils
#include "ow_error.hpp"
#include "ow_types.hpp"

#include "ow_texture.hpp"

namespace ow
{
	ow_texture::ow_texture()
	{
		_texture = NULL;
		_width = 0;
		_height = 0;
	}

	ow_texture::ow_texture(SDL_Renderer *r, std::string path)
	{
		_texture = NULL;
		_width = 0;
		_height = 0;
		load_file(r, path);
	}

	ow_texture::ow_texture(SDL_Renderer *r, std::string fg, std::string bg)
	{
		_texture = NULL;
		_width = 0;
		_height = 0;
		load_file(r, fg, bg);
	}

	ow_texture::ow_texture(SDL_Renderer *r, TTF_Font *f, 
						   std::string msg, SDL_Color c)
	{
		_texture = NULL;
		_width = 0;
		_height = 0;
		load_from_text(r, f, msg, c);
	}



	ow_texture::~ow_texture()
	{
		free();
	}

	bool ow_texture::load_file(SDL_Renderer *ren, std::string fg, std::string bg)
	{
		// should have a valid fg
		if (fg == "") { return false; }
		free();

		_texture = IMG_LoadTexture(ren, fg.c_str());
		if (_texture == NULL) {
			log_error(std::cout, "ow_texture::load_file");
			return false;
		}
		else {
			if (bg != "") {
				// allow alpha blending
				blend_mode(SDL_BLENDMODE_BLEND);
				if (load_file(ren, bg.c_str()) != true) {
					log_error(std::cout, "ow_texture::load_alpha_file::load_file");
					return false;
				}
			}

			// get other parameters of the texture
			if (SDL_QueryTexture(_texture, NULL, NULL,
				&_width, &_height) != 0) {
				log_error(std::cout, "ow_texture::load_file::SDL_QueryTexture");
				return false;
			}
		}
		return true;
	}

	bool ow_texture::load_alpha_file(SDL_Renderer *ren, std::string bg)
	{
		// this load function does not call free since it is a bolt-on
		if (bg != "") {
			// allow alpha blending
			blend_mode(SDL_BLENDMODE_BLEND);
			if (load_file(ren, bg.c_str()) != true) {
				log_error(std::cout, "ow_texture::load_alpha_file::load_file");
				return false;
			}
		}
		return true;
	}

	bool ow_texture::load_from_text(SDL_Renderer *ren, TTF_Font *font,
									std::string msg, SDL_Color color)
	{
		free();
		SDL_Surface *s = TTF_RenderText_Blended(font, msg.c_str(), color);
		if (s == NULL) {
			log_error(std::cout, "ow_texture::load_from_text::TTF_RenderText_Blended");
			return false;
		} else {
			_texture = SDL_CreateTextureFromSurface(ren, s);
			SDL_FreeSurface(s);
			if (_texture == NULL) {
				log_error(std::cout, "ow_texture::load_from_text::_texture==NULL");
				return false;
			}

			// get other parameters of the texture
			if (SDL_QueryTexture(_texture, NULL, NULL,
				&_width, &_height) != 0) {
				log_error(std::cout, "ow_texture::load_file::SDL_QueryTexture");
				return false;
			}
		}
		return true;
	}

	SDL_Surface *load_surface(std::string s)
	{
		auto *loaded_surface = IMG_Load(s.c_str());
		return loaded_surface;
		//auto *optimized_surface = SDL_ConvertSurface(load_surface, ,)
	}

	void ow_texture::render(SDL_Renderer *ren, 
							const int x, 
							const int y, 
							const SDL_Rect *clip,
							const double a, 
							const SDL_Point *c, 
							const SDL_RendererFlip f)
	{
		SDL_Rect render_quad = { x, y, _width, _height };
		if (clip != NULL) {
			render_quad.w = clip->w;
			render_quad.h = clip->h;
		}
		SDL_RenderCopyEx(ren, _texture, clip, &render_quad, a, c, f);
	}

	// blend_mode
	void ow_texture::blend_mode(SDL_BlendMode b)
	{
		SDL_SetTextureBlendMode(_texture, b);
	}

	// modulates RGB
	void ow_texture::rgb_mod(ui8 r, ui8 g, ui8 b)
	{
		// blend_mode(SDL_BLENDMODE_MOD);
		SDL_SetTextureColorMod(_texture, r, g, b);
	}

	// sets alpha 
	void ow_texture::alpha(ui8 a)
	{
		// blend_mode(SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_texture, a);
	}

	void ow_texture::free()
	{
		if (_texture != NULL) {
			SDL_DestroyTexture(_texture);
			_texture = NULL;
			_width = 0;
			_height = 0;
		}
	}

} // namespace ow