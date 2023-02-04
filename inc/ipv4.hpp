
#ifndef __IPV4_HPP__
#define __IPV4_HPP__

#include <array>

class IPV4
{
public:
    std::array<uint8_t, 4> mData = {0};

    IPV4() = default;
    friend constexpr IPV4 operator""_ipv4(const char* text, size_t len);
};

constexpr IPV4 operator""_ipv4(const char* text, size_t len)
{
    IPV4 result;
    size_t index = 0;
    size_t count = 0;
    while(index < len && count < 4)
    {
        while(text[index] != '.' && index < len)
        {
            if(text[index] < '0' || text[index] > '9')
            {
                throw std::invalid_argument("Invalid character in IPV4 String");
            }

            size_t tmp = (text[index] - '0') + (result.mData[count] * 10);

            if(tmp > 255)
            {
                std::cout << "index " << index << " count " << count << std::endl;
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
    if(index != (len + 1))
    {
        throw std::invalid_argument("IPV4 String Too Long: >4 Octets");
    }
    return result;
}

#endif
