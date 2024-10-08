/**************************************************************************/
/*  iterator_util.h                                                       */
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

#ifndef ITERATOR_UTIL_H
#define ITERATOR_UTIL_H

#include <functional>

namespace g3 {

/*
 * Wrapper around an object of type IteratorT that provides STL
 * iterator-like semantics, that converts from the iteration type
 * (FromType) to a new type (ToType).
 *
 * Conversion is done via a provided mapping function
 */
template <typename FromType, typename ToType, typename IteratorT>
class mapped_iterator {
	using MapFunctionT = std::function<ToType(FromType)>;

public:
	inline mapped_iterator() {}

	inline bool operator==(const mapped_iterator &r2) const {
		return icur == r2.icur;
	}
	inline bool operator!=(const mapped_iterator &r2) const {
		return icur != r2.icur;
	}

	inline ToType operator*() const {
		return mapF(*icur);
	}

	inline const mapped_iterator &operator++() { // prefix
		icur++;
		return *this;
	}

	inline mapped_iterator(IteratorT cur_itr, const MapFunctionT &map_func) {
		icur = cur_itr;
		mapF = map_func;
	}

	IteratorT icur;
	MapFunctionT mapF;
};

/*
 * Wrapper around an existing iterator that skips over
 * values for which the filter_func returns false.
 */
template <typename ValueType, typename IteratorT>
class filtered_iterator {
	using FilterFunctionT = std::function<bool(ValueType)>;

public:
	inline filtered_iterator() {}

	inline bool operator==(const filtered_iterator &r2) const {
		return icur == r2.icur;
	}
	inline bool operator!=(const filtered_iterator &r2) const {
		return icur != r2.icur;
	}

	inline ValueType operator*() const {
		return *icur;
	}

	inline const filtered_iterator &operator++() { // prefix
		goto_next();
		return *this;
	}

	inline void goto_next() {
		do {
			icur++;
		} while (icur != iend && filter_func(*icur) == false);
	}

	inline filtered_iterator(IteratorT cur_itr, IteratorT end_itr, const FilterFunctionT &filter_func) {
		icur = cur_itr;
		iend = end_itr;
		this->filter_func = filter_func;
		if (filter_func(*icur) == false)
			goto_next();
	}

	IteratorT icur;
	IteratorT iend;
	FilterFunctionT filter_func;
};

/*
 * Wrapper around existing iterator that returns multiple values, of potentially
 * different type, for each value that input iterator returns.
 *
 * This is done via an "expansion" function that takes an int reference which
 * indicates "where" we are in the expansion (eg like a state machine).
 * How you use this value is up to you.
 *
 * When the input is -1, you should interpret this as the "beginning" of
 * handling the input value (ie we have not returned any values yet for
 * this input value)
 *
 * When you are "done" with an input value, set the outgoing int reference to -1
 * and the base iterator will be incremented.
 *
 * If you have more values to return for this input value, set it to some positive
 * number of your choosing.
 *
 * See DMesh3::VtxTrianglesItr for an example
 */
template <typename OutputType, typename InputType, typename InputIteratorT>
class expand_iterator {
	using ExpandFunctionT = std::function<OutputType(InputType, int &)>;

public:
	inline expand_iterator() {}

	inline bool operator==(const expand_iterator &r2) const {
		return icur == r2.icur;
	}
	inline bool operator!=(const expand_iterator &r2) const {
		return icur != r2.icur;
	}

	inline OutputType operator*() const {
		return cur_value;
	}

	inline const expand_iterator &operator++() { // prefix
		goto_next();
		return *this;
	}

	inline void goto_next() {
		while (icur != iend) {
			cur_value = expand_func(*icur, cur_k);
			if (cur_k == -1)
				++icur; // done with this base value
			else
				break; // want caller to see current output value
		}
	}

	inline expand_iterator(InputIteratorT cur_itr, InputIteratorT end_itr, const ExpandFunctionT &expand_func) {
		icur = cur_itr;
		iend = end_itr;
		this->expand_func = expand_func;
		cur_k = -1;
		goto_next();
	}

	InputIteratorT icur;
	InputIteratorT iend;
	OutputType cur_value;
	int cur_k;
	ExpandFunctionT expand_func;
};

/*
 * Generic "enumerable" object that provides begin/end semantics for
 * an expand_iterator. Allows usage like for ( type x : your_expand_enumerable ) { ... }
 * You can either provide begin/end iterators, or another
 * "enumerable" object that has begin()/end() functions.
 */
template <typename OutputType, typename InputType, typename InputIteratorT>
class expand_enumerable {
	using ExpandFunctionT = std::function<OutputType(InputType, int &)>;

public:
	ExpandFunctionT expand_func;
	InputIteratorT begin_itr, end_itr;

	expand_enumerable(InputIteratorT begin, InputIteratorT end, ExpandFunctionT expand_func) {
		this->begin_itr = begin;
		this->end_itr = end;
		this->expand_func = expand_func;
	}

	template <typename IteratorSource>
	expand_enumerable(IteratorSource source, ExpandFunctionT expand_func) {
		this->begin_itr = source.begin();
		this->end_itr = source.end();
		this->expand_func = expand_func;
	}

	expand_iterator<OutputType, InputType, InputIteratorT> begin() {
		return expand_iterator<OutputType, InputType, InputIteratorT>(begin_itr, end_itr, expand_func);
	}

	expand_iterator<OutputType, InputType, InputIteratorT> end() {
		return expand_iterator<OutputType, InputType, InputIteratorT>(end_itr, end_itr, expand_func);
	}
};

} // namespace g3
#endif // ITERATOR_UTIL_H
