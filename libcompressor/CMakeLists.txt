add_library(libcompressor STATIC
    src/libcompressor.cpp
)

target_include_directories(libcompressor
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(libcompressor
    PUBLIC
        ZLIB::ZLIB
        BZip2::BZip2
)

install(TARGETS libcompressor
    EXPORT libcompressor-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT libcompressor-targets
    FILE libcompressor-targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libcompressor
)

add_subdirectory(tests)