/**************************************************************************/
/*  profile_util.h                                                        */
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

#ifndef PROFILE_UTIL_H
#define PROFILE_UTIL_H

#include <chrono>
#include <string>

namespace g3 {

class BlockTimer {
	std::chrono::high_resolution_clock::time_point start_time;
	std::chrono::high_resolution_clock::time_point end_time;
	bool running;
	std::string Label;
	std::chrono::nanoseconds Accumulated;

public:
	BlockTimer(const std::string &label, bool bStart) {
		Label = label;
		running = false;
		if (bStart)
			Start();
		Accumulated = std::chrono::nanoseconds::zero();
	}
	void Start() {
		start_time = std::chrono::high_resolution_clock::now();
		end_time = start_time;
		running = true;
	}
	void Stop() {
		end_time = std::chrono::high_resolution_clock::now();
		running = false;
	}
	bool Running() {
		return running;
	}

	void Accumulate(bool bReset = false) {
		Stop();
		Accumulated += end_time - start_time;
		if (bReset)
			start_time = std::chrono::high_resolution_clock::now();
	}
	void Reset() {
		Stop();
		Start();
	}

	std::string AccumulatedString() {
		return ToTimeString(Accumulated);
	}
	std::string ToString() {
		return ToTimeString(end_time - start_time);
	}

	static std::string ToTimeString(std::chrono::nanoseconds span) {
		char buf[256];
		long milliseconds = (long)std::chrono::duration_cast<std::chrono::milliseconds>(span).count();
		int seconds = (int)(milliseconds / 1000);
		int minutes = (int)(milliseconds / 60000);
		if (minutes > 0) {
			seconds -= minutes * 60;
			milliseconds -= minutes * 60000;
			milliseconds -= seconds * 1000;
			sprintf(buf, "%02d:%02d.%5ld", minutes, seconds, milliseconds);
		} else {
			milliseconds -= seconds * 1000;
			sprintf(buf, "%02d.%ld", seconds, milliseconds);
		}
		return std::string(buf);
	}
};

//
//
//
// class LocalProfiler : IDisposable
//{
//	Dictionary<std::string, BlockTimer> Timers = new Dictionary<std::string, BlockTimer>();
//	List<std::string> Order = new List<std::string>();
//
//	BlockTimer Start(std::string label)
//	{
//		if (Timers.ContainsKey(label)) {
//			Timers[label].Reset();
//		}
//		else {
//			Timers[label] = new BlockTimer(label, true);
//			Order.Add(label);
//		}
//		return Timers[label];
//	}
//
//
//	BlockTimer StopAllAndStartNew(std::string label)
//	{
//		StopAll();
//		return Start(label);
//	}
//
//	BlockTimer Get(std::string label)
//	{
//		return Timers[label];
//	}
//
//
//	void Stop(std::string label)
//	{
//		Timers[label].Stop();
//	}
//
//	void StopAll()
//	{
//		foreach(BlockTimer t in Timers.Values)
//			if (t.Running)
//				t.Stop();
//	}
//
//
//	void StopAndAccumulate(std::string label, bool bReset = false)
//	{
//		Timers[label].Accumulate(bReset);
//	}
//
//	void Reset(std::string label)
//	{
//		Timers[label].Reset();
//	}
//
//	void ResetAccumulated(std::string label)
//	{
//		Timers[label].Accumulated = TimeSpan.Zero;
//	}
//
//	void ResetAllAccumulated(std::string label)
//	{
//		foreach(BlockTimer t in Timers.Values)
//			t.Accumulated = TimeSpan.Zero;
//	}
//
//	void DivideAllAccumulated(int div)
//	{
//		foreach(BlockTimer t in Timers.Values) {
//			t.Accumulated = new TimeSpan(t.Accumulated.Ticks / div);
//		}
//	}
//
//
//	std::string Elapsed(std::string label)
//	{
//		return Timers[label].Tostd::string();
//	}
//	std::string Accumulated(std::string label)
//	{
//		TimeSpan accum = Timers[label].Accumulated;
//		return std::string.Format(BlockTimer.TimeFormatstd::string(accum), accum);
//	}
//
//	std::string AllTicks(std::string prefix = "Times:")
//	{
//		std::stringBuilder b = new std::stringBuilder();
//		b.Append(prefix + " ");
//		foreach(std::string label in Order) {
//			b.Append(label + ": " + Timers[label].Tostd::string() + " ");
//		}
//		return b.Tostd::string();
//	}
//
//	std::string AllAccumulatedTicks(std::string prefix = "Times:")
//	{
//		std::stringBuilder b = new std::stringBuilder();
//		b.Append(prefix + " ");
//		foreach(std::string label in Order) {
//			b.Append(label + ": " + Accumulated(label) + " ");
//		}
//		return b.Tostd::string();
//	}
//
//
//
//	std::string AllTimes(std::string prefix = "Times:", std::string separator = " ")
//	{
//		std::stringBuilder b = new std::stringBuilder();
//		b.Append(prefix + " ");
//		foreach(std::string label in Order) {
//			TimeSpan span = Timers[label].Watch.Elapsed;
//			b.Append(label + ": " + std::string.Format(BlockTimer.TimeFormatstd::string(span), span) + separator);
//		}
//		return b.Tostd::string();
//	}
//
//	std::string AllAccumulatedTimes(std::string prefix = "Times:", std::string separator = " ")
//	{
//		std::stringBuilder b = new std::stringBuilder();
//		b.Append(prefix + " ");
//		foreach(std::string label in Order) {
//			TimeSpan span = Timers[label].Accumulated;
//			b.Append(label + ": " + std::string.Format(BlockTimer.TimeFormatstd::string(span), span) + separator);
//		}
//		return b.Tostd::string();
//	}
//
//
//
//	void Dispose()
//	{
//		foreach(var timer in Timers.Values)
//			timer.Stop();
//		Timers.Clear();
//	}
//};

} // namespace g3
#endif // PROFILE_UTIL_H
