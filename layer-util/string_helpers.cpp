/* Copyright (c) 2017-2024 Hans-Kristian Arntzen
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "string_helpers.hpp"

namespace Util
{
static std::vector<std::string> split(const std::string &str, const char *delim, bool allow_empty)
{
	if (str.empty())
		return {};
	std::vector<std::string> ret;

	size_t start_index = 0;
	size_t index = 0;
	while ((index = str.find_first_of(delim, start_index)) != std::string::npos)
	{
		if (allow_empty || index > start_index)
			ret.push_back(str.substr(start_index, index - start_index));
		start_index = index + 1;

		if (allow_empty && (index == str.size() - 1))
			ret.emplace_back();
	}

	if (start_index < str.size())
		ret.push_back(str.substr(start_index));
	return ret;
}

std::vector<std::string> split(const std::string &str, const char *delim)
{
	return split(str, delim, true);
}

std::vector<std::string> split_no_empty(const std::string &str, const char *delim)
{
	return split(str, delim, false);
}

std::string strip_whitespace(const std::string &str)
{
	std::string ret;
	auto index = str.find_first_not_of(" \t");
	if (index == std::string::npos)
		return "";
	ret = str.substr(index, std::string::npos);
	index = ret.find_last_not_of(" \t");
	if (index != std::string::npos)
		return ret.substr(0, index + 1);
	else
		return ret;
}
}