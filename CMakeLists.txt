cmake_minimum_required(VERSION 3.15)
project(CompressorProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

find_package(PkgConfig REQUIRED)

if(EXISTS ${CMAKE_BINARY_DIR}/conandeps.cmake)
    include(${CMAKE_BINARY_DIR}/conandeps.cmake)
endif()

find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

include(GNUInstallDirs)
include(CTest)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_EXTRACT_ALL YES)
    doxygen_add_docs(docs
        ${CMAKE_SOURCE_DIR}/libcompressor/include
        ${CMAKE_SOURCE_DIR}/libcompressor/src
        COMMENT "Generate API documentation"
    )
endif()

add_subdirectory(libcompressor)
add_subdirectory(compressor)