/**************************************************************************/
/*  g3Debug.h                                                             */
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

#ifndef G3DEBUG_H
#define G3DEBUG_H

#include <g3Config.h>
#include <string>

namespace g3 {

g3External void g3_testAssert(bool b);

g3External void g3_devAssert(bool b);

g3External void g3_debugPrint(const char *fmt, ...);
g3External void g3_debugPrint(const wchar_t *fmt, ...);

// must pass-by-copy here because of limitation of varargs va_start macro
g3External void g3_debugPrint(std::string fmt, ...);
g3External void g3_debugPrint(std::wstring fmt, ...);

// #define gDevAssert g3_devAssert
#define gDevAssert
// #define gDebugPrint g3_debugPrint
#define gDebugPrint

#define gDevAssertReturnOnFail(x, retval) \
	if (!(x)) {                           \
		gDevAssert(false);                \
		return (retval);                  \
	}

// TODO: https://stackoverflow.com/questions/173618/is-there-a-portable-equivalent-to-debugbreak-debugbreak
// #define gBreakToDebugger gBreakToDebugger
} // namespace g3
#endif // G3DEBUG_H
