add_library(Eigen3 INTERFACE)
target_include_directories(Eigen3 SYSTEM INTERFACE ${rot_SOURCE_DIR}/third_party/eigen3)
