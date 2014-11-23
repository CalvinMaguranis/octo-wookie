#ifndef __OW_TEXT_STREAM_H
#define __OW_TEXT_STREAM_H

#include "ow_types.h"
#include "ow_texture.h"

struct SDL_Renderer;

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
		ow_text_stream();
		~ow_text_stream();
		// Render text `t` at position (`x`,`y`) using text render mode `m` and
		// start a new line when text `t` is more than `p` pixels long.
		// 

		void render(SDL_Renderer *r, int x, int y, std::string t, si32 pi = NULL,
			txt_disp_mode m = TDM_IMMEDIATE, ui8 scroll_speed = 127);
	private:
		ow::ow_texture t;
	};

} // namespace ow

#endif // __OW_TEXT_STREAM_H