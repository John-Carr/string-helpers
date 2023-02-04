
#ifndef __MAC_HPP__
#define __MAC_HPP__

#include <array>
#include "utils.hpp"

class MAC
{
public:
    std::array<uint8_t, 6> mData = {0};

    MAC() = default;
    friend constexpr MAC operator""_mac(const char* text, size_t len);
    static constexpr uint8_t numOctets = 6;
    // TODO NIC
    // TODO OUI
    // TODO isUniCast
    // TODO isMultiCast
    // TODO isLocallyAdmin
    // TODO isGloballyUnique
};

constexpr MAC operator""_mac(const char* text, size_t len)
{
    MAC result;
    size_t index = 0;
    size_t count = 0;
    while(index < len)
    {
        // Skip over seperation characters
        if(text[index] == ':' || text[index] == '-' || text[index] == '.')
        {
            index++;
        }
        // Parse in increments of 2 chars
        int8_t upper = hexToByte(text[index++]);
        int8_t lower = hexToByte(text[index]);
        if(upper < 0 || lower < 0)
        {
            throw std::invalid_argument("Invalid Character in MAC string");
        }
        result.mData[count] = (static_cast<uint8_t>(upper) << 4) | static_cast<uint8_t>(lower);
        index++;
        count++;
    }
    // Its len + 1 here because of the extra increment
    // We are checking if we parsed the whole string because if we didn't then
    // we would want to error out
    if(count > 6)
    {
        throw std::invalid_argument("MAC String Too Long: >6 Octets");
    }
    return result;
}

#endif
