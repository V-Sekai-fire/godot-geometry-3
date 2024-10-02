/**************************************************************************/
/*  DCurveProject.h                                                       */
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

#ifndef DCURVEPROJECT_H
#define DCURVEPROJECT_H

#include "src/geometry/DCurve3.h"
#include "src/spatial/SpatialInterfaces.h"

#include "g3types.h"

#include <limits>
#include <string>

namespace g3 {
class DCurveProjectionTarget : public IProjectionTarget {
public:
	DCurve3Ptr Curve;

	DCurveProjectionTarget(DCurve3Ptr curve) {
		Curve = curve;
	}

	virtual Vector3d Project(const Vector3d &vPoint, int identifier = -1) override {
		Vector3d vNearest;
		double fNearestSqr = std::numeric_limits<double>::max();

		int N = Curve->VertexCount();
		int NStop = (Curve->Closed()) ? N : N - 1;
		for (int i = 0; i < NStop; ++i) {
			Segment3d seg = Segment3d(Curve->GetVertex(i), Curve->GetVertex((i + 1) % N));
			Vector3d pt = seg.NearestPoint(vPoint);
			double dsqr = (vPoint - pt).squaredNorm();
			if (dsqr < fNearestSqr) {
				fNearestSqr = dsqr;
				vNearest = pt;
			}
		}

		return (fNearestSqr < std::numeric_limits<double>::max()) ? vNearest : vPoint;
	}
};
} // namespace g3

#endif // DCURVEPROJECT_H
