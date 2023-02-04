#include <gtest/gtest.h>

#include <array>
#include <vector>
#include "mac.hpp"

TEST(MACTests, SunnyCase)
{
  static const MAC test[] = {
    "FF:FF:FF:FF:FF:FF"_mac,
    "CE:59:9E:25:4B:BB"_mac,
    "FFFFFFFFFFFF"_mac,
    "DA3A.B38A.A550"_mac,
    "2D-51-0B-9F-8B-66"_mac,

  };
  static const std::vector<std::array<uint8_t, 6>> expect = {
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xCE, 0x59, 0x9E, 0x25, 0x4B, 0xBB},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xDA, 0x3A, 0xB3, 0x8A, 0xA5, 0x50},
    {0x2D, 0x51, 0x0B, 0x9F, 0x8B, 0x66},
  };
  size_t index = 0;
  for(auto it = expect.begin(); it != expect.end(); ++it)
  {
    ASSERT_EQ(test[index++].mData, *it);
  }
}

TEST(MACTests, BadFormat)
{
    EXPECT_THROW({
      try
      {
        static const MAC test = "CE:59:9E?25:4B:BB"_mac;
      }
      catch( std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ( "Invalid Character in MAC string", e.what() );
          throw;
      }
  }, std::invalid_argument);
}

TEST(MACTests, TooLong)
{
    EXPECT_THROW({
      try
      {
        static const MAC test = "CE:59:9E:25:4B:BB:EE"_mac;
      }
      catch( std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ( "MAC String Too Long: >6 Octets", e.what() );
          throw;
      }
  }, std::invalid_argument);
}
