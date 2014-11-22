// ow_texture.h
#ifndef __OW_TEXTURE_CLASS_H
#define __OW_TEXTURE_CLASS_H

#include "ow_types.hpp"

namespace ow
{
	class ow_texture 
	{
	public:
		//-----------------------------------------------------------------//
		// ctor/dtor
		//-----------------------------------------------------------------//
		ow_texture();
		// can optionally initialize with a file
		ow_texture(SDL_Renderer *r, std::string path);
		// initialize for alpha blending
		ow_texture(SDL_Renderer *r, std::string fg, std::string bg);
		~ow_texture();

		//-----------------------------------------------------------------//
		// loaders
		//-----------------------------------------------------------------//
		// loads a new texture and stores it in this class
		// these can be used to overwrite existing textures
		bool load_file(SDL_Renderer *ren, std::string path);
		bool load_alpha_file(SDL_Renderer *ren, std::string bg = "");
		bool load_surface(SDL_Surface *s);

		// Renders texture clip at point (x,y), leave clip blank to default to NULL
		void render(SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr);

		//-----------------------------------------------------------------//
		// Texture modifiers
		//-----------------------------------------------------------------//
		// modulates RGB
		// rgb=0xFF.FF.FF->white; rgb=0x00.00.00->black
		void rgb_mod(ui8 r, ui8 g, ui8 b);

		// blend_mode
		/* may be one of the following:
		 *	====================================================================
		 *	SDL_BLENDMODE_NONE  | no blending
		 *					    | dstRGBA = srcRGBA
		 *  --------------------|-----------------------------------------------
		 *	SDL_BLENDMODE_BLEND | alpha blending
		 *	                    | dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
		 *	                    | dstA = srcA + (dstA * (1-srcA))
		 *  --------------------|-----------------------------------------------
		 *	SDL_BLENDMODE_ADD   | additive blending
		 *	                    | dstRGB = (srcRGB * srcA) + dstRGB
		 *	                    | dstA = dstA
		 *  --------------------|-----------------------------------------------
		 *	SDL_BLENDMODE_MOD   | color modulate
		 *	                    | dstRGB = srcRGB * dstRGB
		 *	                    | dstA = dstA
		 *  ====================================================================
		 */
		void blend_mode(SDL_BlendMode b);

		// sets alpha 
		// a=0->0% fully transparent (can see bg if bg!=""; 
		// a=255->100% fg is fully visible
		void alpha(ui8 a);

		//-----------------------------------------------------------------//
		// accessors
		//-----------------------------------------------------------------//
		int get_width() { return _width; }
		int get_height() { return _height; }

		// deallocate texture
		void free();

	private:
		SDL_Texture *_texture;
		int _width;
		int _height;
	};

} // namespace ow

#endif // __OW_TEXTURE_CLASS_H
