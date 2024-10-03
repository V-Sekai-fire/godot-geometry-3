/**************************************************************************/
/*  g3Debug.cpp                                                           */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "g3Debug.h"
#include <geometry3PCH.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

// for OutputDebugString
#ifdef WIN32
#include <windows.h>
#endif

namespace g3 {

void g3_testAssert(bool b) {
	if (!b)
#ifdef __APPLE__
		__asm__("int $3\n"
				:
				:);
#elif __linux__
#else
		__debugbreak();
#endif
	;
}

void g3_devAssert(bool b) {
	if (!b)
#ifdef __APPLE__
		__asm__("int $3\n"
				:
				:);
#elif __linux__
#else
		__debugbreak();
#endif
	;
}

void g3_debugPrint(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char buf[2048];
	vsprintf(buf, fmt, args);
	va_end(args);

#ifdef WIN32
	OutputDebugString(buf);
#else
	fprintf(stderr, "%s", buf);
#endif
}

void g3_debugPrint(const wchar_t *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	wchar_t buf[2048];
	vswprintf(buf, 2048, fmt, args);
	va_end(args);

#ifdef WIN32
	OutputDebugStringW(buf);
#else
	fwprintf(stderr, L"%s", buf);
#endif
}
} // namespace g3
