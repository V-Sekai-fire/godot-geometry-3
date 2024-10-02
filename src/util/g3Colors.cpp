/**************************************************************************/
/*  g3Colors.cpp                                                          */
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

#include <g3Colors.h>
#include <geometry3PCH.h>

#include "DMeshAABBTree3.h"
namespace g3 {

const Color4b White = Color4b(255, 255, 255, 255);
const Color4b Black = Color4b(0, 0, 0, 255);
const Color4b Blue = Color4b(0, 0, 255, 255);
const Color4b Green = Color4b(0, 255, 0, 255);
const Color4b Red = Color4b(255, 0, 0, 255);
const Color4b Yellow = Color4b(255, 255, 0, 255);
const Color4b Cyan = Color4b(0, 255, 255, 255);
const Color4b Magenta = Color4b(255, 0, 255, 255);

const Color4b VideoWhite = Color4b(235, 235, 235, 255);
const Color4b VideoBlack = Color4b(16, 16, 16, 255);
const Color4b VideoBlue = Color4b(16, 16, 235, 255);
const Color4b VideoGreen = Color4b(16, 235, 16, 255);
const Color4b VideoRed = Color4b(235, 16, 16, 255);
const Color4b VideoYellow = Color4b(235, 235, 16, 255);
const Color4b VideoCyan = Color4b(16, 235, 235, 255);
const Color4b VideoMagenta = Color4b(235, 16, 235, 255);

const Color4b Purple = Color4b(161, 16, 193, 255);
const Color4b Orange = Color4b(230, 73, 16, 255);
const Color4b Gold = Color4b(235, 115, 63, 255);
const Color4b DarkYellow = Color4b(235, 200, 95, 255);
const Color4b BlueMetal = Color4b(176, 197, 235, 255);
} // namespace g3
