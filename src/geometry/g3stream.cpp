/**************************************************************************/
/*  g3stream.cpp                                                          */
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

#include <geometry3PCH.h>

#include <g3types.h>

std::ostream &operator<<(std::ostream &os, const g3::Vector2f &v) {
	os << v[0] << "," << v[1];
	return os;
}
std::ostream &operator<<(std::ostream &os, const g3::Vector2d &v) {
	os << v[0] << "," << v[1];
	return os;
}

std::ostream &operator<<(std::ostream &os, const g3::Vector3f &v) {
	os << v[0] << "," << v[1] << "," << v[2];
	return os;
}
std::ostream &operator<<(std::ostream &os, const g3::Vector3d &v) {
	os << v[0] << "," << v[1] << "," << v[2];
	return os;
}

std::ostream &operator<<(std::ostream &os, const g3::Vector4f &v) {
	os << v[0] << "," << v[1] << "," << v[2] << "," << v[3];
	return os;
}
std::ostream &operator<<(std::ostream &os, const g3::Vector4d &v) {
	os << v[0] << "," << v[1] << "," << v[2] << "," << v[3];
	return os;
}

std::ostream &operator<<(std::ostream &os, const g3::Vector2i &v) {
	os << v[0] << "," << v[1];
	return os;
}
std::ostream &operator<<(std::ostream &os, const g3::Vector3i &v) {
	os << v[0] << "," << v[1] << "," << v[2];
	return os;
}
std::ostream &operator<<(std::ostream &os, const g3::Vector4i &v) {
	os << v[0] << "," << v[1] << "," << v[2] << "," << v[3];
	return os;
}

std::ostream &operator<<(std::ostream &os, const g3::AxisAlignedBox2f &b) {
	os << b.Min[0] << "-" << b.Max[0] << "," << b.Min[1] << "-" << b.Max[1];
	return os;
}
std::ostream &operator<<(std::ostream &os, const g3::AxisAlignedBox2d &b) {
	os << b.Min[0] << "-" << b.Max[0] << "," << b.Min[1] << "-" << b.Max[1];
	return os;
}

std::ostream &operator<<(std::ostream &os, const g3::AxisAlignedBox3f &b) {
	os << b.Min[0] << "-" << b.Max[0] << "," << b.Min[1] << "-" << b.Max[1] << ","
	   << b.Min[2] << "-" << b.Max[2];
	return os;
}
std::ostream &operator<<(std::ostream &os, const g3::AxisAlignedBox3d &b) {
	os << b.Min[0] << "-" << b.Max[0] << "," << b.Min[1] << "-" << b.Max[1] << ","
	   << b.Min[2] << "-" << b.Max[2];
	return os;
}
