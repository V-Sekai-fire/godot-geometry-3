/**************************************************************************/
/*  dvector_util.h                                                        */
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

#ifndef DVECTOR_UTIL_H
#define DVECTOR_UTIL_H

#include <dvector.h>
#include <g3platform.h>
#include <atomic>

#ifndef G3_DISABLE_TBB
#include <tbb/parallel_for.h>
#endif

namespace g3 {

// Non-TBB versions of these functions must use portable (eg C++11)
//   multi-threading, or do serial computations
#ifdef G3_DISABLE_TBB

// apply f() to each element of v, parallelized by segment blocks
template <typename Type, typename Func>
void parallel_apply(dvector<Type> &v, const Func &f) {
	v.apply(f);
}

#else
// TBB versions of these functions

// apply f() to each element of v, parallelized by segment blocks
template <typename Type, typename Func>
void parallel_apply(dvector<Type> &v, const Func &f) {
	unsigned int nSegments = (unsigned int)v.m_vSegments.size();
	tbb::parallel_for(tbb::blocked_range<unsigned int>(0, nSegments),
			[&](const tbb::blocked_range<unsigned int> &r) {
				for (unsigned int si = r.begin(); si != r.end(); ++si) {
					dvector_segment<Type> &seg = v.m_vSegments[si];
					for (unsigned int i = 0; i < seg.nCur; ++i) {
						f(seg.pData[i]);
					}
				}
			});
}

#endif

} // end namespace g3
#endif // DVECTOR_UTIL_H
