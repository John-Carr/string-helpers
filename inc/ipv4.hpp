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


#ifndef INC_IPV4_HPP_
#define INC_IPV4_HPP_

#include <array>

class IPV4 {
 public:
    std::array<uint8_t, 4> mData = {0};

    IPV4() = default;
    friend constexpr IPV4 operator""_ipv4(const char* text, size_t len);
};

constexpr IPV4 operator""_ipv4(const char* text, size_t len) {
    IPV4 result;
    size_t index = 0;
    size_t count = 0;
    while (index < len && count < 4) {
        while (text[index] != '.' && index < len) {
            if (text[index] < '0' || text[index] > '9') {
                throw std::invalid_argument("Invalid character in IPV4 String");
            }

            size_t tmp = (text[index] - '0') + (result.mData[count] * 10);

            if (tmp > 255) {
                throw std::invalid_argument("Invalid IPV4 String: Octet > 255");
            }

            result.mData[count] = tmp;
            index++;
        }
        index++;
        count++;
    }
    // Its len + 1 here because of the extra increment
    // We are checking if we parsed the whole string because if we didn't then
    // we would want to error out
    if (index != (len + 1)) {
        throw std::invalid_argument("IPV4 String Too Long: >4 Octets");
    }
    return result;
}

#endif  // INC_IPV4_HPP_
