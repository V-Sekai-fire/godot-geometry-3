#pragma once

#include "core/object/ref_counted.h"
#include "scene/resources/mesh.h"

#include "MeshboundaryLoop.h"
#include "profile_util.h"
#include "src/geometry/g3types.h"
#include "src/mesh/DMesh3Builder.h"
#include "src/mesh/Remesher.h"
#include "src/spatial/BasicProjectionTargets.h"
#include <DMesh3.h>
#include <DMeshAABBTree3.h>
#include <MeshQueries.h>
#include <MeshSubdivider.h>
#include <VectorUtil.h>
#include <refcount_vector.h>
#include <small_list_set.h>
#include <algorithm>
#include <limits>
#include <list>

#include "scene/resources/surface_tool.h"
#include "src/geometry/MeshboundaryLoop.h"
#include "src/mesh/DMesh3.h"
#include "src/mesh/MeshConstraints.h"
#include "src/spatial/DCurveProject.h"

class RemeshOperator : public RefCounted {
    GDCLASS(RemeshOperator, RefCounted);

protected:
	static void _bind_methods();
public:
	Ref<ArrayMesh> process(Ref <ArrayMesh> p_mesh);
	RemeshOperator() {}
};
