/**************************************************************************/
/*  parallel_util.h                                                       */
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

#ifndef PARALLEL_UTIL_H
#define PARALLEL_UTIL_H

#include <g3platform.h>
#include <atomic>

#ifdef G3_ENABLE_TBB
#include <tbb/parallel_for.h>
#endif

namespace g3 {

// Non-TBB versions of these functions must use portable (eg C++11)
//   multi-threading, or do serial computations
#ifndef G3_ENABLE_TBB

// evaluate f[k] = f(k)
template <typename vector_type, typename ValueFunc>
void parallel_fill(vector_type &v, const ValueFunc &f) {
	size_t nCount = v.size();
	for (unsigned int k = 0; k < nCount; ++k)
		v[k] = f(k);
}

// evaluate f[k] = f(k), if valid(k)
template <typename vector_type, typename ValueFunc, typename ValidFunc>
void parallel_fill(vector_type &v, const ValueFunc &f, const ValidFunc &valid) {
	size_t nCount = v.size();
	for (unsigned int k = 0; k < nCount; ++k) {
		if (valid(k) == true)
			v[k] = f(k);
	}
}

#else
// TBB versions of these functions

// evaluate f[k] = f(k)
template <typename vector_type, typename ValueFunc>
void parallel_fill(vector_type &v, const ValueFunc &f) {
	unsigned int nCount = (unsigned int)v.size();
	tbb::parallel_for(tbb::blocked_range<unsigned int>(0, nCount),
			[&](const tbb::blocked_range<unsigned int> &r) {
				for (unsigned int k = r.begin(); k != r.end(); ++k)
					v[k] = f(k);
			});
}

// evaluate f[k] = f(k), if valid(k)
template <typename vector_type, typename ValueFunc, typename ValidFunc>
void parallel_fill(vector_type &v, const ValueFunc &f, const ValidFunc &valid) {
	unsigned int nCount = (unsigned int)v.size();
	tbb::parallel_for(tbb::blocked_range<unsigned int>(0, nCount),
			[&](const tbb::blocked_range<unsigned int> &r) {
				for (unsigned int k = r.begin(); k != r.end(); ++k) {
					if (valid(k) == true)
						v[k] = f(k);
				}
			});
}

#endif

} // end namespace g3
#endif // PARALLEL_UTIL_H
