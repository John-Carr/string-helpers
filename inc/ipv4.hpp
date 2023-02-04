
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
    while(index < len)
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
                throw std::invalid_argument("Invalid IPV4 String");
            }

            result.mData[count] = tmp;
            index++;
        }
        index++;
        count++;
    }
    if(count != 4)
    {
        throw std::invalid_argument("IPV4 String Too Long");
    }
    return result;
}

#endif
