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


#ifndef INC_UTILS_HPP_
#define INC_UTILS_HPP_

#include <cstdint>

inline int8_t hexToByte(char c) {
    if ( (c >= '0') && (c <= '9') ) {
        // Digits in string
        return (c - '0');
    } else if ( (c >= 'a') && (c <= 'f') ) {
        // Lowercase in string
        return (c - 'a' + 10);
    } else if ( (c >= 'A') && (c <= 'F') ) {
        // Uppercase in string
        return (c - 'A' + 10);
    } else {
        // Non hex character
        return -1;
    }
}

#endif  // INC_UTILS_HPP_
