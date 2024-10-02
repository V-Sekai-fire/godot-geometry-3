/**************************************************************************/
/*  ProgressCancel.h                                                      */
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

#ifndef PROGRESSCANCEL_H
#define PROGRESSCANCEL_H

#include <g3types.h>

namespace g3 {

/// <summary>
/// interface that provides a cancel function
/// </summary>
class ICancelSource {
public:
	virtual bool Cancelled() = 0;
};

/// <summary>
/// Just wraps a func<bool> as an ICancelSource
/// </summary>
class CancelFunction : public ICancelSource {
public:
	const std::function<bool()> &CancelF;
	CancelFunction(const std::function<bool()> &cancelF) :
			CancelF(cancelF) {
	}
	bool Cancelled() { return CancelF(); }
};

/// <summary>
/// This class is intended to be passed to long-running computes to
///  1) provide progress info back to caller (not implemented yet)
///  2) allow caller to cancel the computation
/// </summary>
class ProgressCancel {
public:
	std::shared_ptr<ICancelSource> Source;

	bool WasCancelled = false; // will be set to true if CancelF() ever returns true

	ProgressCancel(std::shared_ptr<ICancelSource> source) {
		Source = source;
	}
	ProgressCancel(const std::function<bool()> &cancelF) {
		Source = std::make_shared<CancelFunction>(cancelF);
	}

	/// <summary>
	/// Check if client would like to cancel
	/// </summary>
	bool Cancelled() {
		if (WasCancelled)
			return true;
		WasCancelled = Source->Cancelled();
		return WasCancelled;
	}
};

} // namespace g3
#endif // PROGRESSCANCEL_H
