#include <gtest/gtest.h>

#include <array>
#include <vector>
#include "ipv6.hpp"

TEST(IPV6Tests, ValidAddresses)
{
  static const IPV6 test[] = {
    // Normal formatting
    "2001:db8:3333:4444:5555:6666:7777:8888"_ipv6,  // 0
    "2001:db8:3333:4444:CCCC:DDDD:EEEE:FFFF"_ipv6,  // 1
    // Implies all 8 segments are zero
    "::"_ipv6,                                      // 2
    // Implies that the last six segments are zero
    "2001:db8::"_ipv6,                              // 3
    // Implies that the first six segments are zero
    "::1234:5678"_ipv6,                             // 4
    // Implies that the middle four segments are zero
    "2001:db8::1234:5678"_ipv6,                     // 5
    // This is testing leading zeros
    "2001:0db8:0001:0000:0000:0ab9:C0A8:0102"_ipv6, // 6
    // This is testing odd sizes
    "2001:0db8:1:000:00:ab9:C0A8:102"_ipv6          // 7
  };

  static const std::vector<std::array<uint32_t, 8>> expect = {
    {0x2001, 0xdb8, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888},
    {0x2001, 0xdb8, 0x3333, 0x4444, 0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF},
    {0x0000, 0x000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x2001, 0xdb8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1234, 0x5678},
    {0x2001, 0xdb8, 0x0000, 0x0000, 0x0000, 0x0000, 0x1234, 0x5678},
    {0x2001, 0x0db8, 0x0001, 0x0000, 0x0000, 0x0ab9, 0xC0A8, 0x0102},
    {0x2001, 0x0db8, 0x0001, 0x0000, 0x0000, 0x0ab9, 0xC0A8, 0x0102}
  };

  size_t index = 0;
  for(auto it = expect.begin(); it != expect.end(); it++)
  {
    ASSERT_EQ(test[index].mData, expect[index]) << "Failed at index: " << index;
  }
}

TEST(IPV6Tests, InvalidFormat)
{
    EXPECT_THROW({
        try
        {
        static const IPV6 test = "::db8:3333:4444:5555:6666:7777:8888"_ipv6;
        }
        catch( std::invalid_argument& e )
        {
            // and this tests that it has the correct message
            EXPECT_STREQ( "IPV6 String Too Long", e.what() );
            throw;
        }
    }, std::invalid_argument);
}
