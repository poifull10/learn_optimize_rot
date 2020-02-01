add_library(rot_lib optimizer.cpp)
target_link_libraries(rot_lib Eigen3)
target_include_directories(rot_lib PUBLIC ${rot_SOURCE_DIR}/include)
