/**************************************************************************/
/*  g3Colors.h                                                            */
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

#ifndef G3COLORS_H
#define G3COLORS_H

#include <g3types.h>

namespace g3 {

class Colors {
public:
	//
	// Standard extreme-rgb colors
	//
	static const Color4b White;
	static const Color4b Black;
	static const Color4b Blue;
	static const Color4b Green;
	static const Color4b Red;
	static const Color4b Yellow;
	static const Color4b Cyan;
	static const Color4b Magenta;

	//
	// Video-codec-safe versions of standard colors.
	// These will not "shimmer" like full-saturation colors will under certain codecs.
	//
	static const Color4b VideoWhite;
	static const Color4b VideoBlack;
	static const Color4b VideoBlue;
	static const Color4b VideoGreen;
	static const Color4b VideoRed;
	static const Color4b VideoYellow;
	static const Color4b VideoCyan;
	static const Color4b VideoMagenta;

	//
	// Miscellaneous color set
	//
	static const Color4b Purple;
	static const Color4b Orange;
	static const Color4b Gold;
	static const Color4b DarkYellow;
	static const Color4b BlueMetal;
};

} // namespace g3

#endif // G3COLORS_H
