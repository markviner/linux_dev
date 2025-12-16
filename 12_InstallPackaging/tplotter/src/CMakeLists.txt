add_executable(tplotter main.c)

target_include_directories(tplotter PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}
    ${Intl_INCLUDE_DIRS}
)

target_link_libraries(tplotter 
    eval
    ${Intl_LIBRARIES})

install(TARGETS tplotter
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
