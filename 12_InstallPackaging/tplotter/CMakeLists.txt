cmake_minimum_required(VERSION 3.10)
project(tplotter VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_DOC "Build documentation" ON)

find_package(Gettext REQUIRED)
find_package(Intl REQUIRED)

include(GNUInstallDirs)

configure_file(
    ${CMAKE_SOURCE_DIR}/src/config.h.in
    ${CMAKE_BINARY_DIR}/config.h
    @ONLY
)

add_subdirectory(src/libeval)
add_subdirectory(src)
add_subdirectory(po)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

install(FILES doc/tplotter.1 
        DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

# for docs
if(BUILD_DOC)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        configure_file(${CMAKE_SOURCE_DIR}/doc/Doxyfile.in 
                       ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(doc
            ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
    endif()
endif()

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
