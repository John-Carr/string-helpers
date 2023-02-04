#include <gtest/gtest.h>

#include <array>
#include "ipv4.hpp"

TEST(IPV4Tests, SunnyCase)
{
  static const IPV4 test = "192.168.1.1"_ipv4;
  std::array<uint8_t, 4> expect = {192, 168, 1, 1};
  ASSERT_EQ(test.mData, expect);
}

TEST(IPV4Tests, InvalidChar)
{
  EXPECT_THROW({
      try
      {
        static const IPV4 test = "a.168.1.1"_ipv4;
      }
      catch( std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ( "Invalid character in IPV4 String", e.what() );
          throw;
      }
  }, std::invalid_argument);
}

TEST(IPV4Tests, OctetTooLarge)
{
  EXPECT_THROW({
      try
      {
        static const IPV4 test = "300.168.1.1"_ipv4;
      }
      catch( std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ( "Invalid IPV4 String", e.what() );
          throw;
      }
  }, std::invalid_argument);
}

TEST(IPV4Tests, OctetStringTooLong)
{
  EXPECT_THROW({
      try
      {
        static const IPV4 test = "192.168.1.1.1"_ipv4;
      }
      catch( std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ( "IPV4 String Too Long", e.what() );
          throw;
      }
  }, std::invalid_argument);
}
