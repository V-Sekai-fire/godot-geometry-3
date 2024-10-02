/**************************************************************************/
/*  parse_util.h                                                          */
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

#ifndef PARSE_UTIL_H
#define PARSE_UTIL_H

#include <string>
#include <vector>

namespace g3 {

class ParseUtil {
public:
	ParseUtil() = delete;

	enum class Options {
		RemoveEmpty = 1
	};

	static int ToInt(const std::string &s) {
		return std::stoi(s, 0);
	}
	static float ToFloat(const std::string &s) {
		return std::stof(s, 0);
	}
	static double ToDouble(const std::string &s) {
		return std::stod(s, 0);
	}

	static bool Contains(const std::string &s, char c) {
		return s.find(c, 0) != std::string::npos;
	}
	static bool Contains(const std::string &s, const std::string &sub) {
		return s.find(sub, 0) != std::string::npos;
	}

	static void Split(const std::string &s, char delimiter, std::vector<std::string> &tokens, Options options) {
		bool skip_empty = (((int)options & (int)Options::RemoveEmpty) != 0);

		tokens.clear();
		auto cur = s.begin(), end = s.end();
		auto cur_start = cur;
		cur++;
		while (cur != end) {
			if (*cur == delimiter) {
				bool is_empty = (cur_start == cur);
				if (is_empty == false || skip_empty == false) {
					tokens.push_back(std::string(cur_start, cur));
				}
				cur++; // advance to next char
				cur_start = cur;
			} else {
				cur++;
			}
		}
		if (cur_start != cur)
			tokens.push_back(std::string(cur_start, end));
	}

	static std::vector<std::string> Split(const std::string &s, char delimiter, Options options) {
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter)) {
			if (((int)options & (int)Options::RemoveEmpty) != 0 && token.size() == 0)
				continue;
			tokens.push_back(token);
		}
		return tokens;
	}
};

} // namespace g3
#endif // PARSE_UTIL_H
