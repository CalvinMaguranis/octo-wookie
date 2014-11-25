#ifndef __OW_PRIMITIVES_H
#define __OW_PRIMITIVES_H

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

namespace ow
{
	// wraps SDL primitive drawing functions
    class Primitives
    {
	public:
		Primitives() : _c({ 0, 0, 0, 0xff }) {}
		Primitives(SDL_Color c) : _c(c) {}
		//~Primitives() {}

		void color(SDL_Color c);

		void point(SDL_Renderer *r, const SDL_Point *p);
		void points(SDL_Renderer *r, const SDL_Point *p, const int count);

		// draws line from points p1 to p2
		void line(SDL_Renderer *r, const SDL_Point *p1, const SDL_Point *p2);

		// draws a series of connected lines iteration over p[0...count]
		void lines_joined(SDL_Renderer *r, const SDL_Point *p, const int count);

		// draws a series of disconnected lines from 
		// points (p1[0],p2[0])...(p1[count],p2[count])
		// 
		// note that count should be the number of (p1,p2) pairs
		void lines_disjoined(SDL_Renderer *r,
								const SDL_Point *p1, 
								const SDL_Point *p2, 
								const int count);

		void rect(SDL_Renderer *r, const SDL_Rect *rect);
		void rects(SDL_Renderer *r, const SDL_Rect *rect, const int count);

		void fill_rect(SDL_Renderer *r, const SDL_Rect *rect);
		void fill_rects(SDL_Renderer *r, const SDL_Rect *rect, const int count);

	private:
		SDL_Color _c;
    };
} // namespace ow

#endif // __OW_PRIMITIVES_H
