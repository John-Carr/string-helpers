#include <gtest/gtest.h>

#include <array>
#include "uuid.hpp"

/******************************************************************************
 * String Literal Operator Tests
 *****************************************************************************/
TEST(UUIDTests, SunnyCase)
{
  static const UUID test = "89ede841-12aa-49e0-8727-79f2ce8552df"_uuid;
  static const std::array<uint8_t, 16> expect = {0x89, 0xED, 0xE8, 0x41, 0x12, 0xAA, 0x49, 0xE0,
                                    0x87, 0x27, 0x79, 0xF2, 0xCE, 0x85, 0x52, 0xDF};
  ASSERT_EQ(test, expect);
}

TEST(UUIDTests, BadChar)
{
  // this tests _that_ the expected exception is thrown
  EXPECT_THROW({
      try
      {
        static const UUID test = "89ede841?12aa-49e0-8727-79f2ce8552df"_uuid;
      }
      catch( std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ( "Invalid UUID String", e.what() );
          throw;
      }
  }, std::invalid_argument);
}

TEST(UUIDTests, OddSeperation)
{
  // this tests _that_ the expected exception is thrown
  EXPECT_THROW({
      try
      {
        static const UUID test = "89ede84-112aa-49e0-8727-79f2ce8552df"_uuid;
      }
      catch( std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ( "Invalid UUID String", e.what() );
          throw;
      }
  }, std::invalid_argument);
}

TEST(UUIDTests, UUIDTooLong)
{
  EXPECT_THROW({
      try
      {
        static const UUID test = "89ede84-112aa-49e0-8727-79f2ce8552dfBEEF"_uuid;
      }
      catch( std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ( "Invalid UUID String", e.what() );
          throw;
      }
  }, std::invalid_argument);
}

TEST(UUIDTests, UUIDTooShort)
{
  EXPECT_THROW({
      try
      {
        static const UUID test = "89ede84-112aa-49e0-8727-79f2ce8552"_uuid;
      }
      catch( std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ( "Invalid UUID String", e.what() );
          throw;
      }
  }, std::invalid_argument);
}

/******************************************************************************
 * Other Operator Tests
 *****************************************************************************/

TEST(UUIDTests, EqOpGood)
{
  static const UUID test = "89ede841-12aa-49e0-8727-79f2ce8552df"_uuid;
  static const UUID test2 = "89ede841-12aa-49e0-8727-79f2ce8552df"_uuid;
  static const std::array<uint8_t, 16> expect = {
                                0x89, 0xED, 0xE8, 0x41, 0x12, 0xAA, 0x49, 0xE0,
                                0x87, 0x27, 0x79, 0xF2, 0xCE, 0x85, 0x52, 0xDF};
  bool test_result_arr = (test == expect);
  bool test_result_uuid = (test == test2);
  ASSERT_TRUE(test_result_arr);
  ASSERT_TRUE(test_result_uuid);
}

TEST(UUIDTests, EqOpBad)
{
  static const UUID test = "89ede841-12aa-49e0-8727-79f2ce8552df"_uuid;
  static const UUID test2 = "89ede841-12aa-49e0-8727-79f2ce8552BB"_uuid;
  static const std::array<uint8_t, 16> expect = {
                                0x89, 0xED, 0xE8, 0x41, 0x12, 0xAA, 0x49, 0xE0,
                                0x87, 0x27, 0x79, 0xF2, 0xBB, 0x85, 0x52, 0xDF};
  bool test_result_arr = (test == expect);
  bool test_result_uuid = (test == test2);
  ASSERT_FALSE(test_result_arr);
  ASSERT_FALSE(test_result_uuid);
}

TEST(UUIDTests, InEqOpGood)
{
  static const UUID test = "89ede841-12aa-49e0-8727-79f2ce8552df"_uuid;
  static const UUID test2 = "89ede841-12aa-49e0-8727-79f2ce8552AA"_uuid;
  static const std::array<uint8_t, 16> expect = {
                                0x89, 0xED, 0xE8, 0x41, 0x12, 0xAA, 0x49, 0xE0,
                                0x87, 0x27, 0x79, 0xF2, 0xBB, 0x85, 0x52, 0xDF};
  bool test_result_arr = (test != expect);
  bool test_result_uuid = (test != test2);
  ASSERT_TRUE(test_result_uuid);
  ASSERT_TRUE(test_result_arr);
}

TEST(UUIDTests, AccessOp)
{
  static const UUID test = "89ede841-12aa-49e0-8727-79f2ce8552df"_uuid;
  static const std::array<uint8_t, 16> expect = {
                                0x89, 0xED, 0xE8, 0x41, 0x12, 0xAA, 0x49, 0xE0,
                                0x87, 0x27, 0x79, 0xF2, 0xCE, 0x85, 0x52, 0xDF};
  ASSERT_EQ(expect[0], test[0]);
}
