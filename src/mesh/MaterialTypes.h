/**************************************************************************/
/*  MaterialTypes.h                                                       */
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

#ifndef MATERIALTYPES_H
#define MATERIALTYPES_H

#include <g3types.h>

namespace g3 {

class GenericMaterial {
public:
	static constexpr float Invalidf = std::numeric_limits<float>::max();
	static Vector3f InvalidColor() { return Vector3f(-1, -1, -1); }

	std::string name;
	int id;

	Vector3f diffuse_color;
	float alpha;

	virtual Vector3f DiffuseColor() = 0;
	virtual float Alpha() = 0;

	enum class KnownMaterialTypes {
		OBJ_MTL_Format
	};
	KnownMaterialTypes Type;

	GenericMaterial() {
		diffuse_color = InvalidColor();
		alpha = Invalidf;
	}

	virtual ~GenericMaterial() {}
};
typedef std::shared_ptr<GenericMaterial> GenericMaterialPtr;

// details: http://www.fileformat.info/format/material/
// Note: if value is initialized to Invalid vector, -1, or NaN, it was not defined in material file
class OBJMaterial : public GenericMaterial {
public:
	Vector3f Ka; // rgb ambient reflectivity
	Vector3f Kd; // rgb diffuse reflectivity
	Vector3f Ks; // rgb specular reflectivity
	Vector3f Ke; // rgb emissive
	Vector3f Tf; // rgb transmission filter
	int illum; // illumination model 0-10
	float d; // dissolve (alpha)
	float Ns; // specular exponent (shininess)
	float sharpness; // reflection sharpness
	float Ni; // index of refraction / optical density

	std::string map_Ka;
	std::string map_Kd;
	std::string map_Ks;
	std::string map_Ke;
	std::string map_d;
	std::string map_Ns;

	std::string bump;
	std::string disp;
	std::string decal;
	std::string refl;

	// [TODO] texture materials

	OBJMaterial() {
		Type = KnownMaterialTypes::OBJ_MTL_Format;
		id = -1;
		name = "///INVALID_NAME";
		Ka = Kd = Ks = Ke = Tf = InvalidColor();
		illum = -1;
		d = Ns = sharpness = Ni = Invalidf;
	}

	virtual ~OBJMaterial() {}

	virtual Vector3f DiffuseColor() {
		return (Kd == InvalidColor()) ? Vector3f(1, 1, 1) : Kd;
		;
	}
	virtual float Alpha() {
		return (d == Invalidf) ? 1.0f : d;
	}
};

} // namespace g3
#endif // MATERIALTYPES_H
