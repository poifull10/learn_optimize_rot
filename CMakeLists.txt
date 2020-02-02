cmake_minimum_required(VERSION 3.10)
project(rot)

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(tests)
