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


#ifndef INC_UUID_HPP_
#define INC_UUID_HPP_

#include <array>
#include "utils.hpp"

class UUID {
 private:
    std::array<uint8_t, 16> mData = {0};

 public:
    // Constructor
    UUID() = default;
    [[nodiscard]] uint8_t operator[](size_t) const;
    // Friends
    [[nodiscard]] friend bool operator==(const UUID& L, const std::array<uint8_t, 16>& R) noexcept;
    [[nodiscard]] friend bool operator==(const UUID& L, const UUID& R) noexcept;
    [[nodiscard]] friend bool operator!=(const UUID& L, const UUID& R) noexcept;
    [[nodiscard]] friend bool operator!=(const UUID& L, const std::array<uint8_t, 16>& R) noexcept;
    friend constexpr UUID operator""_uuid(const char* text, size_t len);

};

uint8_t UUID::operator[](const size_t index) const {
    return mData[index];
}

bool operator==(const UUID& L, const std::array<uint8_t, 16>& R) noexcept {
    return L.mData == R;
}

bool operator==(const UUID& L, const UUID& R) noexcept {
    return L.mData == R.mData;
}

bool operator!=(const UUID& L, const UUID& R) noexcept {
    return L.mData != R.mData;
}

bool operator!=(const UUID& L, const std::array<uint8_t, 16>& R) noexcept {
    return L.mData != R;
}

constexpr UUID operator""_uuid(const char* text, size_t len) {
    // Parsed string
    UUID result;
    // Index for the input sring
    size_t index = 0;
    // Index for the  parsed UUID
    size_t count = 0;
    // Loop through the input
    while(index < len) {
        // Skip over seperation chars
        if(text[index] == '-') {
            index++;
            continue;
        }
        int8_t upper = hexToByte(text[index++]);
        int8_t lower = hexToByte(text[index++]);
        // Check if it was an invalid character
        if( upper < 0 || lower < 0) {
            throw std::invalid_argument("Invalid UUID String");
        }
        else {
            result.mData[count/2] =
                (static_cast<uint8_t>(upper) << 4) | static_cast<uint8_t>(lower);
            count += 2;
        }
    }
    // UUID are represented as 32 hexadecimal (base-16) digits so error if
    // we parsed not that number
    if(count != 32) {
        throw std::invalid_argument("Invalid UUID String");
    }
    return result;
}

#endif // INC_UUID_HPP_
