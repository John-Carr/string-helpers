#include <cstdint>

int8_t hexToByte(char c)
{
    // Digits in string
    if( (c >= '0') && (c <= '9') )
    {
        return (c - '0');
    }
    // Lowercase in string
    else if( (c >= 'a') && (c <= 'f') )
    {
        return (c - 'a' + 10);
    }
    // Uppercase in string
    else if( (c >= 'A') && (c <= 'F') )
    {
        return (c - 'A' + 10);
    }
    // Non hex character
    else
    {
        return -1;
    }
}
