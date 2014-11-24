#ifndef __OW_TEXT_STREAM_H
#define __OW_TEXT_STREAM_H

#pragma once

#include <SDL.h>

namespace ow
{
	typedef enum {
	     TDM_IMMEDIATE = 0,
	     TDM_SCROLLING = 1
	} txt_disp_mode ;

	/*
	-load ttf font
	-generate ASCII characters 0x20-0x7E into a 10x10 unit surface
		-a unit is the width & height of a single character
	-convert surface into texture
	-use (ASCII value - 0x20) to determine the unit image to be rendered
	*/
	class ow_text_stream
	{
	public:
		ow_text_stream(TTF_Font *font, int pt);
		~ow_text_stream();

		// Render text `t` at position (`x`,`y`) using text render mode `m` and
		// start a new line when text `t` is more than `p` pixels long.
		void render(SDL_Renderer *r, int x, int y, std::string t, uint32_t p = NULL,
			txt_disp_mode m = TDM_IMMEDIATE, const uint8_t scroll_speed = 0);
	private:
		ow_texture _t;
		int _w;
		int _h;
		int _pt;


		int scale_index(ui8 ascii_char);
		SDL_Surface *gen_ascii(TTF_Font *f);

	};

	class char_stream 
	{
	public:
		char_stream(std::string font, int pt);
		~char_stream();

		void wrap_width(int pixels);
		int get_wrap_width();

		void scroll_height(int pixels);
		int get_scroll_height();

		// -1 for error, 0 for sucess, 1 if still iterating over string
		int render(SDL_Renderer *r, int x, int y, std::string msg);

	private:
		TTF_Font *f;
		SDL_Texture *texture;
		int w, h, pt; // characters
		int box_w, box_h; // pixels

		void process_lines();
		void init_texture_map();
	};

	/*
	[char stream]
	every dt;
		SDL_Surface *s;
		if scroll_speed = 0;
			// determine box size (x,y,w,h)
			// ...
			s=TTF_RenderText_*(font, str)
		else:
			char_idx++;
			// determine if char_idx starts a new line
			if (char_idx==newline);
				line++;
			s=TTF_RenderText_*(font, str[line].char)


		SDL_FreeSurface(s)
	
	....

	[texture map]
	create blank texture
	load TTF_Font
	generate all ascii characters (or whatever)
	
	*/

} // namespace ow

#endif // __OW_TEXT_STREAM_H