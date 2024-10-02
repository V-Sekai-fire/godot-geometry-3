// Geometric Tools, LLC
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 5.0.1 (2010/10/01)

#ifndef WM5IVECTOR4_H
#define WM5IVECTOR4_H

#include "Wm5MathematicsLIB.h"
#include "Wm5IVector.h"

namespace Wm5
{

class WM5_MATHEMATICS_ITEM IVector4 : public IVector<4>
{
public:
    // Construction.
    IVector4 ();
    IVector4 (const IVector4& vec);
    IVector4 (const IVector<4>& vec);
    IVector4 (const int& x, const int& y, const int& z, const int &w);
	IVector4 (const int * pValues);

    // Assignment.
    IVector4& operator= (const IVector4& vec);
    IVector4& operator= (const IVector<4>& vec);

    // returns Dot(this,V)
    int Dot (const IVector4& vec) const;

// [geometry3]
public:
	using EVector4 = Eigen::Matrix<int, 4, 1>;
	operator EVector4() const {
		return Eigen::Map<EVector4>((int *)this);
	}
	IVector4(const EVector4 & vec) {
		const int * p = vec.data();
		mTuple[0] = p[0];
		mTuple[1] = p[1];
		mTuple[2] = p[2];
		mTuple[3] = p[3];
	}
// [geometry3]

protected:
    using IVector<4>::mTuple;
};

}

#endif
