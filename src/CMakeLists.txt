
add_library(rot_lib dataloader.cpp optimizer.cpp utility.cpp)
set_property(TARGET rot_lib PROPERTY CXX_STANDARD 17)

target_link_libraries(rot_lib Eigen3 stdc++fs)
target_include_directories(rot_lib PUBLIC ${rot_SOURCE_DIR}/include)
