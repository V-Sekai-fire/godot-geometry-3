/**************************************************************************/
/*  SpatialQueryTypes.h                                                   */
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

#ifndef SPATIALQUERYTYPES_H
#define SPATIALQUERYTYPES_H

#include <g3types.h>

namespace g3 {

class IPixelHitRadius {
public:
	virtual ~IPixelHitRadius() {}
	virtual float GetWorldHitRadius(const g3::Vector3f &vHit) const = 0;
};

class HitTestRay {
public:
	g3::Vector3f vOrigin;
	g3::Vector3f vDirection;
	IPixelHitRadius *pHitThresh;

	HitTestRay() {
		vOrigin = vDirection = g3::Vector3f::Zero();
		pHitThresh = nullptr;
	}
	HitTestRay(const g3::Vector3f &o, const g3::Vector3f &d) {
		vOrigin = o;
		vDirection = d;
		pHitThresh = nullptr;
	}
	HitTestRay(const g3::Vector3f &o, const g3::Vector3f &d, IPixelHitRadius *pPixelRadius) {
		vOrigin = o;
		vDirection = d;
		pHitThresh = pPixelRadius;
	}
};

} // namespace g3

#endif // SPATIALQUERYTYPES_H
