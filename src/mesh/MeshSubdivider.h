/**************************************************************************/
/*  MeshSubdivider.h                                                      */
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

#ifndef MESHSUBDIVIDER_H
#define MESHSUBDIVIDER_H

#include <DMesh3.h>

namespace g3 {

// [TODO]
//    - version of 1-4 that takes ROI
//    - optional loop subd vtx placement for 1-4 split
//    - 1-3 split, also with 1-3+flip  (eg sqrt(3) subd)
//    - feedback for new tris/verts
//    - reprojection (here?)

class MeshSubdivider {
public:
	MeshSubdivider() {}
	virtual ~MeshSubdivider() = default;

	virtual void Split1to4(DMesh3 &mesh) {
		EdgeID nMaxEdge = mesh.MaxEdgeID();
		std::vector<VertexID> vNewV(nMaxEdge, InvalidID);

		for (auto eid : mesh.EdgeIndices())
			vNewV[eid] = MarkerID1;

		// [TODO] can we do this without saving triangles? Could we process each triangle
		//   sequentially somehow? The problem is that our original triangles go away
		//   each time we split...

		// save triangle edges & verts (do we need both?)
		static const Vector3i InvalidTri(-1, -1, -1);
		TriangleID nMaxInitialTri = mesh.MaxTriangleID();
		std::vector<Vector3i> vTris(nMaxInitialTri);
		std::vector<Vector3i> vTriEdges(nMaxInitialTri);
		for (int k = 0; k < nMaxInitialTri; ++k) {
			if (mesh.IsTriangle(k)) {
				vTris[k] = mesh.GetTriangle(k);
				vTriEdges[k] = mesh.GetTriEdges(k);
			} else {
				vTris[k] = InvalidTri;
				vTriEdges[k] = InvalidTri;
			}
		}

		// split all edges
		for (auto eid : mesh.EdgeIndices()) {
			if (vNewV[eid] == MarkerID1) {
				DMesh3::EdgeSplitInfo info;
				auto eResult = mesh.SplitEdge(eid, info);
				vNewV[eid] = (eResult == MeshResult::Ok) ? info.vNew : InvalidID;
			}
		}

		// for each triangle, if split edge doesn't exist, then it is flipped
		//   and we need to rotate it one more time. Should happen once per triangle.
		for (int k = 0; k < nMaxInitialTri; ++k) {
			if (vTriEdges[k] == InvalidTri)
				continue;
			for (int j = 0; j < 3; ++j) {
				EdgeID e0 = vTriEdges[k][j];
				EdgeID e1 = vTriEdges[k][(j + 1) % 3];
				VertexID a = vNewV[e0];
				VertexID b = vNewV[e1];
				if (mesh.FindEdge(a, b) == InvalidID) {
					VertexID o = vTris[k][(j + 1) % 3];
					VertexID c = vNewV[vTriEdges[k][(j + 2) % 3]];
					if (c != InvalidID && mesh.FindEdge(o, c)) {
						DMesh3::EdgeFlipInfo info;
						auto eResult = mesh.FlipEdge(o, c, info);
					}
				}
			}
		}
	}
};

} // namespace g3

#endif // MESHSUBDIVIDER_H
