add_executable(libcompressortest
    libcompressortest.cpp
)

target_link_libraries(libcompressortest
    PRIVATE
        libcompressor
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME LibcompressorTest COMMAND libcompressortest --gtest_output=xml:${CMAKE_BINARY_DIR}/test_results.xml)