/*
    Various things to make life better, mostly because STL is crap (I blame boost)
    Copyright (C) 2019  Martin Sandsmark <martin.sandsmark@kde.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

namespace genie {
namespace util {

inline bool floatsEquals(const float a, const float b)
{
    return (std::abs(a - b) * 100000.f <= std::min(std::abs(a), std::abs(b)));
}

inline bool floatsEquals(const double a, const double b)
{
    return (std::abs(a - b) * 1000000000000. <= std::min(std::abs(a), std::abs(b)));
}

inline std::string toLowercase(std::string input)
{
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

inline std::string stringReplace(std::string string, const std::string &oldValue, const std::string &newValue)
{
    for (size_t index = 0;; index += newValue.length()) {
        index = string.find(oldValue, index);

        if (index == std::string::npos) {
            break;
        }

        string.erase(index, oldValue.length());
        string.insert(index, newValue);
    }

    return string;
}

inline std::string trimString(std::string string)
{
    string.erase(string.begin(), std::find_if(string.begin(), string.end(), [](int c) { return !std::isspace(c); }  ));
    string.erase(std::find_if(string.rbegin(), string.rend(), [](int c) { return !std::isspace(c); }).base(), string.end());
    return string;
}

inline bool stringStartsWith(const std::string &string, const std::string &prefix)
{
    return string.compare(0, prefix.size(), prefix) == 0;
}

inline std::vector<std::string> stringSplit(const std::string &string, const char delimiter)
{
    if (string.find(delimiter) == std::string::npos) {
        return {string};
    }

    std::vector<std::string> ret;
    std::istringstream stream(string);
    std::string part;
    while (std::getline(stream, part, delimiter)) {
        if (part.empty()) {
            continue;
        }

        ret.push_back(part);
    }
    if (ret.empty()) {
        return {string};
    }
    return ret;
}

// Probably not the most efficient
std::string resolvePathCaseInsensitive(const std::string &inputPath, const std::string &basePath = "/");

std::string executablePath();
std::string executableDirectory();

} // namespace util
} // namespace genie
