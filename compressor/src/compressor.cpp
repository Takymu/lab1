#include <spdlog/spdlog.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "libcompressor/libcompressor.hpp"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    spdlog::error("Not enough arguments. Usage: compressor <algorithm> <string>");
    return EXIT_FAILURE;
  }

  std::string algorithm = argv[1];
  std::string input_string = argv[2];

  libcompressor_CompressionAlgorithm algo;
  if (algorithm == "zlib") {
    algo = libcompressor_Zlib;
  } else if (algorithm == "bzip") {
    algo = libcompressor_Bzip;
  } else {
    spdlog::error("Invalid algorithm. Use 'zlib' or 'bzip'");
    return EXIT_FAILURE;
  }

  libcompressor_Buffer input = {const_cast<char*>(input_string.c_str()), static_cast<int>(input_string.length())};

  libcompressor_Buffer result = libcompressor_compress(algo, input);

  if (result.data == nullptr || result.size == 0) {
    spdlog::error("Compression failed");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < result.size; ++i) {
    printf("%02hhx", static_cast<unsigned char>(result.data[i]));
  }
  printf("\n");

  std::free(result.data);
  return EXIT_SUCCESS;
}