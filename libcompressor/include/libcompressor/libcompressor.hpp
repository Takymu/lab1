#ifndef LIBCOMPRESSOR_HPP
#define LIBCOMPRESSOR_HPP

/**
 * @brief Compression algorithms supported by libcompressor
 */
enum libcompressor_CompressionAlgorithm {
  libcompressor_Zlib, /**< Use zlib compression algorithm */
  libcompressor_Bzip  /**< Use bzip2 compression algorithm */
};

/**
 * @brief Buffer structure for input and output data
 */
struct libcompressor_Buffer {
  char* data; /**< Pointer to buffer data */
  int size;   /**< Size of buffer in bytes */
};

/**
 * @brief Compress input buffer using specified algorithm
 * @param algo Compression algorithm to use
 * @param input Input buffer to compress
 * @return Compressed buffer. On error, returns buffer with data == NULL && size == 0
 */
libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input);

#endif