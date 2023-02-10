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


#ifndef INC_MAC_HPP_
#define INC_MAC_HPP_

#include <array>
#include <utils.hpp>

class MAC {
 public:
    std::array<uint8_t, 6> mData = {0};

    MAC() = default;
    friend constexpr MAC operator""_mac(const char* text, size_t len);
    static constexpr uint8_t numOctets = 6;
    // TODO(John Carr): NIC
    // TODO(John Carr): OUI
    // TODO(John Carr): isUniCast
    // TODO(John Carr): isMultiCast
    // TODO(John Carr): isLocallyAdmin
    // TODO(John Carr): isGloballyUnique
};

constexpr MAC operator""_mac(const char* text, size_t len) {
    MAC result;
    size_t index = 0;
    size_t count = 0;
    while (index < len && count < 6) {
        // Skip over seperation characters
        if (text[index] == ':' || text[index] == '-' || text[index] == '.') {
            index++;
        }
        // Parse in increments of 2 chars
        int8_t upper = hexToByte(text[index++]);
        int8_t lower = hexToByte(text[index]);
        if (upper < 0 || lower < 0) {
            throw std::invalid_argument("Invalid Character in MAC string");
        }
        result.mData[count] =
            (static_cast<uint8_t>(upper) << 4) | static_cast<uint8_t>(lower);
        index++;
        count++;
    }
    // Its len + 1 here because of the extra increment
    // We are checking if we parsed the whole string because if we didn't then
    // we would want to error out
    if (index != len) {
        throw std::invalid_argument("MAC String Too Long: >6 Octets");
    }
    return result;
}

#endif  // INC_MAC_HPP_
