
#ifndef __UUID_HPP__
#define __UUID_HPP__

#include <array>
#include "utils.hpp"

class UUID
{

public:
    std::array<uint8_t, 16> mData = {0};

    UUID() = default;
    friend constexpr UUID operator""_uuid(const char* text, size_t len);

};

constexpr UUID operator""_uuid(const char* text, size_t len)
{
    // Parsed string
    UUID result;
    // Index for the input sring
    size_t index = 0;
    // Index for the  parsed UUID
    size_t count = 0;
    // Loop through the input
    while(index < len)
    {
        // Skip over seperation chars
        if(text[index] == '-')
        {
            index++;
            continue;
        }
        int8_t upper = hexToByte(text[index++]);
        // index++;
        int8_t lower = hexToByte(text[index++]);
        // index++;
        // Check if it was an invalid character
        if( upper < 0 || lower < 0)
        {
            throw std::invalid_argument("Invalid UUID String");
        }
        else
        {
            result.mData[count/2] =
                (static_cast<uint8_t>(upper) << 4) | static_cast<uint8_t>(lower);
            count += 2;
        }
    }
    // UUID are represented as 32 hexadecimal (base-16) digits so error if
    // we parsed not that number
    if(count != 32)
    {
        throw std::invalid_argument("Invalid UUID String");
    }
    return result;
}

#endif
