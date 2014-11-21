#ifndef __CROSS_PLATFORM_TOOLS_H
#define __CROSS_PLATFORM_TOOLS_H

/*----------------------------------------------------------------------------*/
// UTF-8 SUPPORT
/*----------------------------------------------------------------------------*/

// [RULE 1]
// All data serialization files (currently in JSON) MUST be UTF-8 encoded.

// Ensure unicode (UTF-8) support is enabled.
//	However, http://utf8everywhere.org/ suggests avoiding using this define for 
// operation. I will follow it for now...
#ifndef UNICODE
#define UNICODE
#endif // UNICODE

// We only need these conversions for Windows
#if defined(_WIN32) || defined(_WIN64)

//#include "Windows.h"
#include <codecvt>

// conversion functions adapted from: http://www.nubaria.com/en/blog/?p=289
// NOTE: these are intended to be std::strings! (std::string-> UTF-8; std::string16->UTF-16)
std::string to_utf8(std::u16string utf16str) {
	return std::wstring_convert<std::codecvt_utf8_utf16 <char16_t>, char16_t>().to_bytes(utf16str);
}

std::u16string to_utf16(std::string utf8str) {
	return std::wstring_convert<std::codecvt_utf8_utf16 <char16_t>, char16_t>().from_bytes(utf8str);
}

#define UTF16_TO_UTF8(utf16str) \
	std::wstring_convert<std::codecvt_utf8_utf16 <char16_t>, char16_t>().to_bytes(utf16str)

#define UTF8_TO_UTF16(utf8str) \
	std::wstring_convert<std::codecvt_utf8_utf16 <char16_t>, char16_t>().from_bytes(utf8str)

#ifdef __UTF8_TEST
/* TODO: implement me */
#error Error: there are currently no unit tests defined for UTF-8 support! Implement me!
// Tests should stream in sample strings from a (set of) test file(s) mirrored 
// in both UTF-8 and UTF-16. UTF-8 <-> UTF-16 conversion are compared to the 
// original sample string in the test file(s) byte by byte to determine success.

#include <string>

// load JSON file
...

// UTF-8 -> UTF-16
...

// UTF-16 -> UTF-8
...
	
#endif // __UTF8_TEST

#endif // defined(_WIN32) || defined(_WIN64)

/*----------------------------------------------------------------------------*/

#endif // __CROSS_PLATFORM_TOOLS_H
