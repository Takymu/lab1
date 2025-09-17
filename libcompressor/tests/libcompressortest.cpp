#include <gtest/gtest.h>

#include <cstring>

#include "libcompressor/libcompressor.hpp"

class LibcompressorTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(LibcompressorTest, ZlibNonEmptyInputProducesNonEmptyOutput) {
  const char* test_data = "test data";
  libcompressor_Buffer input = {const_cast<char*>(test_data), static_cast<int>(strlen(test_data))};

  libcompressor_Buffer result = libcompressor_compress(libcompressor_Zlib, input);

  EXPECT_NE(result.data, nullptr);
  EXPECT_GT(result.size, 0);

  if (result.data) {
    std::free(result.data);
  }
}

TEST_F(LibcompressorTest, BzipNonEmptyInputProducesNonEmptyOutput) {
  const char* test_data = "test data";
  libcompressor_Buffer input = {const_cast<char*>(test_data), static_cast<int>(strlen(test_data))};

  libcompressor_Buffer result = libcompressor_compress(libcompressor_Bzip, input);

  EXPECT_NE(result.data, nullptr);
  EXPECT_GT(result.size, 0);

  if (result.data) {
    std::free(result.data);
  }
}

TEST_F(LibcompressorTest, ZlibEmptyInputProducesEmptyOutput) {
  libcompressor_Buffer input = {nullptr, 0};

  libcompressor_Buffer result = libcompressor_compress(libcompressor_Zlib, input);

  EXPECT_EQ(result.data, nullptr);
  EXPECT_EQ(result.size, 0);
}

TEST_F(LibcompressorTest, BzipEmptyInputProducesEmptyOutput) {
  libcompressor_Buffer input = {nullptr, 0};

  libcompressor_Buffer result = libcompressor_compress(libcompressor_Bzip, input);

  EXPECT_EQ(result.data, nullptr);
  EXPECT_EQ(result.size, 0);
}

TEST_F(LibcompressorTest, ZlibTestStringCompression) {
  const char* test_string = "test_string";
  libcompressor_Buffer input = {const_cast<char*>(test_string), static_cast<int>(strlen(test_string))};

  libcompressor_Buffer result = libcompressor_compress(libcompressor_Zlib, input);

  unsigned char expected[] = {0x78, 0x9c, 0x2b, 0x49, 0x2d, 0x2e, 0x89, 0x2f, 0x2e, 0x29,
                              0xca, 0xcc, 0x4b, 0x07, 0x00, 0x1c, 0x79, 0x04, 0xb7};

  EXPECT_EQ(result.size, sizeof(expected));
  EXPECT_EQ(memcmp(result.data, expected, sizeof(expected)), 0);

  if (result.data) {
    std::free(result.data);
  }
}

TEST_F(LibcompressorTest, BzipTestStringCompression) {
  const char* test_string = "test_string";
  libcompressor_Buffer input = {const_cast<char*>(test_string), static_cast<int>(strlen(test_string))};

  libcompressor_Buffer result = libcompressor_compress(libcompressor_Bzip, input);

  unsigned char expected[] = {0x42, 0x5a, 0x68, 0x31, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0x4a, 0x7c,
                              0x69, 0x05, 0x00, 0x00, 0x04, 0x83, 0x80, 0x00, 0x00, 0x82, 0xa1, 0x1c,
                              0x00, 0x20, 0x00, 0x22, 0x03, 0x68, 0x84, 0x30, 0x22, 0x50, 0xdf, 0x04,
                              0x99, 0xe2, 0xee, 0x48, 0xa7, 0x0a, 0x12, 0x09, 0x4f, 0x8d, 0x20, 0xa0};

  EXPECT_EQ(result.size, sizeof(expected));
  EXPECT_EQ(memcmp(result.data, expected, sizeof(expected)), 0);

  if (result.data) {
    std::free(result.data);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}