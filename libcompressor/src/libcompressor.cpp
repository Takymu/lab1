#include "libcompressor/libcompressor.hpp"

#include <bzlib.h>
#include <zlib.h>

#include <cstdlib>
#include <cstring>

libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input) {
  libcompressor_Buffer result = {nullptr, 0};

  if (input.data == nullptr || input.size <= 0) {
    return result;
  }

  int output_size = input.size + 1024;
  char* output_data = static_cast<char*>(std::malloc(output_size));

  if (output_data == nullptr) {
    return result;
  }

  if (algo == libcompressor_Zlib) {
    uLongf compressed_size = output_size;
    int ret = compress(reinterpret_cast<Bytef*>(output_data), &compressed_size,
                       reinterpret_cast<const Bytef*>(input.data), input.size);

    if (ret == Z_OK) {
      result.data = output_data;
      result.size = compressed_size;
    } else {
      std::free(output_data);
    }
  } else if (algo == libcompressor_Bzip) {
    unsigned int compressed_size = output_size;
    int ret = BZ2_bzBuffToBuffCompress(output_data, &compressed_size, input.data, input.size, 1, 0, 0);

    if (ret == BZ_OK) {
      result.data = output_data;
      result.size = compressed_size;
    } else {
      std::free(output_data);
    }
  } else {
    std::free(output_data);
  }

  return result;
}