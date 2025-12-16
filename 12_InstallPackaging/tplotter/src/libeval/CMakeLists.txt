add_library(eval SHARED eval.c)

target_include_directories(eval PUBLIC 
    ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(eval m)

set_target_properties(eval PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/include/eval.h)

install(TARGETS eval
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
