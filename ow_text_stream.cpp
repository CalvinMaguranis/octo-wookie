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
#include "ow_text_stream.hpp"

namespace ow
{
	ow_text_stream::ow_text_stream(TTF_Font *font, int pt)
	{
		_h = TTF_FontLineSkip(font);
		_pt = pt;
	}

	int ow_text_stream::scale_index(const ui8 ascii_char)
	{
		const ui8 ascii_start = 0x20;
		const ui8 ascii_end = 0x7E;
		int retval = -1;

		if ((ascii_char > ascii_start) && 
			(ascii_char < ascii_end + 1)) {
			retval = ascii_char - ascii_start;
		}
		return retval;
	}

	SDL_Surface *ow_text_stream::gen_ascii(TTF_Font *f) 
	{
		const ui8 ascii_start = 0x20;
		const ui8 ascii_end =   0x7E;
		const ui8 char_len = ascii_end - ascii_start + 1;
		ui8 idx = 0;
		const SDL_Color black = { 0x00, 0x00, 0x00, 0xFF };

		char *ascii_charset = new char[char_len];

		// create all printable, non-extended ASCII characters
		for (ui8 c = ascii_start; c < ascii_end + 1; c++, idx++) {
			ascii_charset[idx] = c;
		}

		// get font characteristics


//		auto loaded_surface = TTF_RenderText_Blended_Wrapped(f, ascii_charset, black, );

		delete(ascii_charset);
		return NULL;
	}

} // namespace ow