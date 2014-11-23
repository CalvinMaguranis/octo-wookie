#ifndef __OW_ERROR_TOOLS_H
#define __OW_ERROR_TOOLS_H

namespace ow
{
	//#define OW_DEBUG

	#ifdef OW_DEBUG
		#define DEBUG_PRINT(str) std::cout << str << std::endl
	#else
		#define DEBUG_PRINT(str)
	#endif

	void log_error(std::ostream &os, const std::string &msg);
}

#endif // __OW_ERROR_TOOLS_H
