#ifndef __OW_ERROR_TOOLS_H
#define __OW_ERROR_TOOLS_H

#include <iostream>
#include <string>
#include <SDL.h>
/** <<<can't really beat this...>>>
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void log_error(std::ostream &os, const std::string &msg)
{
	os << msg << " Error: " << SDL_GetError() << std::endl;
}

#endif // __OW_ERROR_TOOLS_H