/**************************************************************************/
/*  atomic_util.h                                                         */
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

#ifndef ATOMIC_UTIL_H
#define ATOMIC_UTIL_H

#include <atomic>

//
// Use spinlock to allow mutex-free threadsafe accumulation of value(s)
// To use with non-POD type, you just have to implement += operator
//
namespace g3 {

template <class Type>
class atomic_accumulator {
private:
	std::atomic<bool> lock;
	Type value;

public:
	atomic_accumulator() = delete;
	atomic_accumulator(const Type &init) :
			lock(false) {
		value = init;
	}

	inline void accumulate(Type v) {
		while (std::atomic_exchange_explicit(&lock, true, std::memory_order_acquire))
			; // spin until acquired
		value += v;
		std::atomic_store_explicit(&lock, false, std::memory_order_release);
	}

	inline void set(Type v) {
		while (std::atomic_exchange_explicit(&lock, true, std::memory_order_acquire))
			; // spin until acquired
		value = v;
		std::atomic_store_explicit(&lock, false, std::memory_order_release);
	}

	// assuming that we do not need calls to this function to be atomic...
	inline Type operator()(bool bAtomic = false) {
		Type tmp;
		if (bAtomic) {
			while (std::atomic_exchange_explicit(&lock, true, std::memory_order_acquire))
				; // spin until acquired
			tmp = value;
			std::atomic_store_explicit(&lock, false, std::memory_order_release);
			return tmp;
		} else
			return value;
	}
};

//
// This class allows you to test-and-update a single value and
//   an associated data structure, using a mutex-free spinlock
//
// For example in a raycast loop you might want to find the nearest
//   hit point, so the ValueType would be the ray-T and the OtherDataType
//   would be the point data structure
//
// update_if_less() / update_if_greater() safely update the value
// operator() returns the current <value,data> as a pair-struct
//
template <class CheckValueType, class OtherDataType>
class atomic_compare {
private:
	std::atomic<bool> lock;
	CheckValueType value;
	OtherDataType data;

public:
	atomic_compare() = delete;
	atomic_compare(CheckValueType init_v, OtherDataType init_d) :
			lock(false) {
		value = init_v;
		data = init_d;
	}

	inline void update_if_less(CheckValueType v, OtherDataType d) {
		while (std::atomic_exchange_explicit(&lock, true, std::memory_order_acquire))
			; // spin until acquired
		if (v < value) {
			value = v;
			data = d;
		}
		std::atomic_store_explicit(&lock, false, std::memory_order_release);
	}

	inline void update_if_greater(CheckValueType v, OtherDataType d) {
		while (std::atomic_exchange_explicit(&lock, true, std::memory_order_acquire))
			; // spin until acquired
		if (v > value) {
			value = v;
			data = d;
		}
		std::atomic_store_explicit(&lock, false, std::memory_order_release);
	}

	inline void set(CheckValueType v, OtherDataType d) {
		while (std::atomic_exchange_explicit(&lock, true, std::memory_order_acquire))
			; // spin until acquired
		value = v;
		data = d;
		std::atomic_store_explicit(&lock, false, std::memory_order_release);
	}

	// assuming that we do not need calls to this function to be atomic...
	struct result {
		CheckValueType value;
		OtherDataType data;
	};
	inline result operator()(bool bAtomic = false) {
		if (bAtomic) {
			while (std::atomic_exchange_explicit(&lock, true, std::memory_order_acquire))
				; // spin until acquired
			result r = { value, data };
			std::atomic_store_explicit(&lock, false, std::memory_order_release);
			return r;
		} else
			return { value, data };
	}
};

} // end namespace g3
#endif // ATOMIC_UTIL_H
