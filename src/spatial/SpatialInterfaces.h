/**************************************************************************/
/*  SpatialInterfaces.h                                                   */
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

#ifndef SPATIALINTERFACES_H
#define SPATIALINTERFACES_H

#include <g3types.h>

namespace g3 {

class ISpatial {
public:
	virtual ~ISpatial() {}

	virtual bool SupportsPointContainment() = 0;

	/// <summary> return true if query point is inside object </summary>
	virtual bool IsInside(const Vector3d &p) = 0;
};

class IMeshSpatial : public ISpatial {
public:
	virtual ~IMeshSpatial() {}

	virtual bool SupportsNearestTriangle() = 0;

	/// <summary>
	/// Find id of triangle nearest to p within distance fMaxDist, or return DMesh3.InvalidID if not found
	/// </summary>
	virtual int FindNearestTriangle(const Vector3d &p, double &fNearestDistSqr, double fMaxDist = std::numeric_limits<double>::max()) = 0;

	virtual bool SupportsTriangleRayIntersection() = 0;

	/// <summary>
	/// Find id of triangle intersected by ray, where intersection point is within distance fMaxDist, or return DMesh3.InvalidID if not found
	/// </summary>
	virtual int FindNearestHitTriangle(const Ray3d &ray, double fMaxDist = std::numeric_limits<double>::max()) = 0;
};

class IProjectionTarget {
public:
	virtual ~IProjectionTarget() {}

	virtual Vector3d Project(const Vector3d &vPoint, int identifier = -1) = 0;
};

class IOrientedProjectionTarget : public IProjectionTarget {
public:
	virtual ~IOrientedProjectionTarget() {}

	virtual Vector3d Project(const Vector3d &vPoint, int identifier = -1) override = 0;
	virtual Vector3d Project(const Vector3d &vPoint, Vector3d &vProjectNormal, int identifier = -1) = 0;
};

class IIntersectionTarget {
public:
	virtual ~IIntersectionTarget() {}

	virtual bool HasNormal() = 0;
	virtual bool RayIntersect(const Ray3d &ray, Vector3d &vHit, Vector3d &vHitNormal) = 0;
};

} // namespace g3
#endif // SPATIALINTERFACES_H
