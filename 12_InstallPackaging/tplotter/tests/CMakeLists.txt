add_executable(test_eval test_eval.c)

target_include_directories(test_eval PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(test_eval 
    eval
    ${MATH_LIBRARY}
)

add_test(NAME test_eval COMMAND test_eval)
