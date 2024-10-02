/**************************************************************************/
/*  object_pool.h                                                         */
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

#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <dvector.h>

namespace g3 {

// object_pool

template <class Type>
class object_allocator {
public:
	virtual ~object_allocator() = default;

	virtual Type *allocate() = 0;
	virtual void release(Type *pObject) = 0;
};

template <class Type>
class object_pool : public object_allocator<Type> {
public:
	object_pool();
	virtual ~object_pool();

	// cannot do standard copy constructors because we have no way to tell clients
	// that they need new pointers! (need to return pointer map!)
	object_pool(const object_pool<Type> &copy) = delete;
	const object_pool<Type> &operator=(const object_pool<Type> &copy) = delete;

	// can do move semantics because as pointers will not be invalidated
	object_pool(const object_pool<Type> &&moved);
	const object_pool<Type> &operator=(const object_pool<Type> &&moved);

	//
	// object_allocator interface
	//

	// allocate a new instance of the object (either new memory or from free list)
	virtual Type *allocate();

	// return pObject to the pool
	virtual void release(Type *pObject);

	//
	// object_pool
	//

	// reset usage but do not clear memory
	void reset_pool();

	// clear memory
	void free_pool();

protected:
	// dvector grows in blocks, so it is safe to store pointers into it
	dvector<Type> m_store;

	// pointers here are into m_store, but we do not actually know what index
	// because we only gave clients the pointer
	std::vector<Type *> m_free;
};

template <class Type>
object_pool<Type>::object_pool() {
}

template <class Type>
object_pool<Type>::~object_pool() {
}

template <class Type>
object_pool<Type>::object_pool(const object_pool<Type> &&moved) {
	*this = std::move(moved);
}

template <class Type>
const object_pool<Type> &object_pool<Type>::operator=(const object_pool<Type> &&moved) {
	m_store = std::move(moved.m_store);
	m_free = std::move(moved.m_free);
	return *this;
}

template <class Type>
Type *object_pool<Type>::allocate() {
	if (m_free.empty()) {
		m_store.push_back(Type());
		return &m_store.back();
	} else {
		Type *pObject = m_free.back();
		*pObject = Type();
		m_free.pop_back();
		return pObject;
	}
}

template <class Type>
void object_pool<Type>::release(Type *pObject) {
	m_free.push_back(pObject);
}

template <class Type>
void object_pool<Type>::reset_pool() {
	m_free.clear();
	m_store.clear(false);
}

template <class Type>
void object_pool<Type>::free_pool() {
	m_free.clear();
	m_store.clear();
}

} // end namespace g3

#endif // OBJECT_POOL_H
