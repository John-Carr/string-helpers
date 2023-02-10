/*
 Copyright (c) 2023 John Carr

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef INC_IPV6_HPP_
#define INC_IPV6_HPP_

#include <array>
#include <utils.hpp>

// An IPv6 (normal) address has the format y:y:y:y:y:y:y:y, where y is called a
// segment and can be any hexadecimal value between 0 and FFFF. The segments are
// separated by colons, not periods. An IPv6 normal address must have eight
// segments; however, a short form notation can be used in the TS4500 management
// GUI for segments that are zero, or those that have leading zeros.

class IPV6 {
 public:
    std::array<uint32_t, 8> mData = {0};

    IPV6() = default;
    friend constexpr IPV6 operator""_ipv6(const char* text, size_t len);
};

constexpr IPV6 operator""_ipv6(const char* text, size_t len) {
    // TODO: This would probably be better served as a regular expression
    IPV6 result;
    size_t index = 0;
    size_t count = 0;
    // All 0s (Ex. `::`)
    if (len < 3) {
        return result;
    }
    // If the length is >= 3 but the string starts with :: then the first 6
    // segments are 0s
    if (text[0] == ':' && text[1] == ':') {
        // Skip the :'s
        index += 2;
        // Skip the first 6 segments
        count += 6;
    }
    // Parse 2 segments
    for (size_t i = 0; i < 2; i++) {
        while (text[index] != ':' && index < len) {
            result.mData[count] =
                (result.mData[count] << 4) | hexToByte(text[index]);
            index++;
        }
        index++;
        count++;
    }
    // If the count is at 8 the first 6 segments were 0
    // But we also need to check the index since a badly formatted string
    if (count == 8 && index >= len) {
        return result;
    }
    else if (count == 8 && index < len) {
        throw std::invalid_argument("IPV6 String Too Long");
    }
    // Check if middle 4 segments are 0s
    // This could also be last 6 segments are 0 so we need to check if
    // index < len
    if (text[index] == ':' && text[index + 1] == ':') {
        index += 2;
        count += 4;
    }
    // Check if it was last 6 segments
    if (index >= len) {
        std::cout << "Exited early last 6 seg are zeros" << std::endl;
        return result;
    }
    // Parse 2 segments
    for (size_t i = 0; i < 2; i++) {
        while(text[index] != ':' && index < len) {
            result.mData[count] =
                (result.mData[count] << 4) | hexToByte(text[index]);
            index++;
        }
        index++;
        count++;
    }
    // If we had the middle 4 segments at 0 we exit here
    if (count == 8) {
        return result;
    }
    // Parse 4 segments
    for (size_t i = 0; i < 4; i++) {
        while(text[index] != ':' && index < len) {
            result.mData[count] =
                (result.mData[count] << 4) | hexToByte(text[index]);
            index++;
        }
        index++;
        count++;
    }

    if (count != 8) {
        throw std::invalid_argument("IPV6 String Too Long");
    }
    return result;
}

#endif // INC_IPV6_HPP_
