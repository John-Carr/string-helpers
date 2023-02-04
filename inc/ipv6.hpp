
#ifndef __IPV6_HPP__
#define __IPV6_HPP__

#include <array>
#include <utils.hpp>

// An IPv6 (normal) address has the format y:y:y:y:y:y:y:y, where y is called a
// segment and can be any hexadecimal value between 0 and FFFF. The segments are
// separated by colons, not periods. An IPv6 normal address must have eight
// segments; however, a short form notation can be used in the TS4500 management
// GUI for segments that are zero, or those that have leading zeros.

class IPV6
{
public:
    std::array<uint32_t, 8> mData = {0};

    IPV6() = default;
    friend constexpr IPV6 operator""_ipv6(const char* text, size_t len);
};

constexpr IPV6 operator""_ipv6(const char* text, size_t len)
{
    IPV6 result;
    size_t index = 0;
    size_t count = 0;
    // All 0s
    if(len < 3)
    {
        std::cout << "All zeros exited early " << len << std::endl;
        return result;
    }
    // First 6 segments are 0s
    if(text[0] == ':' && text[1] == ':')
    {
        index += 2;
        count += 6;
    }
    // Parse 2 segments
    for(size_t i = 0; i < 2; i++)
    {
        while(text[index] != ':' && index < len)
        {
            result.mData[count] = (result.mData[count] << 4) | hexToByte(text[index]);
            index++;
        }
        index++;
        count++;
    }
    // If we had the first 6 segments at 0 we exit here
    if(count == 8)
    {
        std::cout << " First 6 seg zeros exited early" << std::endl;
        return result;
    }
    // Check if middle 4 segments are 0s
    // This could also be last 6 segments are 0 so we need to check if
    // index < len
    if(text[index] == ':' && text[index + 1] == ':')
    {
        index += 2;
        count += 4;
    }
    // Check if it was last 6 segments
    if(index >= len)
    {
        std::cout << "Exited early last 6 seg are zeros" << std::endl;
        return result;
    }
    // Parse 2 segments
    for(size_t i = 0; i < 2; i++)
    {
        while(text[index] != ':' && index < len)
        {
            result.mData[count] = (result.mData[count] << 4) | hexToByte(text[index]);
            index++;
        }
        index++;
        count++;
    }
    // If we had the middle 4 segments at 0 we exit here
    if(count == 8)
    {
        return result;
    }
    // Parse 4 segments
    for(size_t i = 0; i < 4; i++)
    {
        while(text[index] != ':' && index < len)
        {
            result.mData[count] = (result.mData[count] << 4) | hexToByte(text[index]);
            index++;
        }
        index++;
        count++;
    }

    if(count != 8)
    {
        throw std::invalid_argument("IPV6 String Too Long");
    }
    return result;
}

#endif
