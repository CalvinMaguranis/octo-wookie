#include <iostream>

#include <SDL.h>

#include "ow_error.hpp"
#include "primitives.hpp"

namespace ow
{
	void Primitives::point(SDL_Renderer *r, const SDL_Point *p)
	{
		if (SDL_RenderDrawPoint(r, p->x, p->y) != 0) {
			log_error(std::cout, "Primitives::point");
		}
	}

	void Primitives::points(SDL_Renderer *r, const SDL_Point *p, const int count)
	{
		if (SDL_RenderDrawPoints(r, p, count) != 0) {
			log_error(std::cout, "Primitives::points");
		}
	}

	// draws line from points p1 to p2
	void Primitives::line(SDL_Renderer *r, const SDL_Point *p1, const SDL_Point *p2)
	{
		if (SDL_RenderDrawLine(r, p1->x, p1->y, p2->x, p2->y) != 0) {
			log_error(std::cout, "Primitives::line");
		}
	}

	// draws a series of connected lines iteration over p[0...count]
	void Primitives::lines_joined(SDL_Renderer *r, const SDL_Point *p, const int count)
	{
		if (SDL_RenderDrawLines(r, p, count) != 0) {
			log_error(std::cout, "Primitives::lines_joined");
		}
	}

	// draws a series of disconnected lines from 
	// points (p1[0],p2[0])...(p1[count],p2[count])
	// 
	// note that count should be the number of (p1,p2) pairs
	void Primitives::lines_disjoined(SDL_Renderer *r,
		const SDL_Point *p1,
		const SDL_Point *p2,
		const int count)
	{
		for (int c = 0; c < count; c++) {
			if (SDL_RenderDrawLine(r, p1[c].x, p1[c].y, p2[c].x, p2[c].y) != 0) {
				log_error(std::cout, "Primitives::lines_disjoined");
			}
		}
	}

	void Primitives::rect(SDL_Renderer *r, const SDL_Rect *rect)
	{
		if (SDL_RenderDrawRect(r, rect) != 0) {
			log_error(std::cout, "Primitives::rect");
		}
	}

	void Primitives::rects(SDL_Renderer *r, const SDL_Rect *rect, const int count)
	{
		if (SDL_RenderDrawRects(r, rect, count) != 0) {
			log_error(std::cout, "Primitives::rects");
		}
	}

	void Primitives::fill_rect(SDL_Renderer *r, const SDL_Rect *rect)
	{
		if (SDL_RenderFillRect(r, rect) != 0) {
			log_error(std::cout, "Primitives::fill_rect");
		}
	}

	void Primitives::fill_rects(SDL_Renderer *r, const SDL_Rect *rect, const int count)
	{
		if (SDL_RenderFillRects(r, rect, count) != 0) {
			log_error(std::cout, "Primitives::fill_rects");
		}
	}

} // namespace ow
